#include "NetworkMonitor.h"
#include "Utils.h"
#include <thread>
#include <mutex>
#include <random>
#include <algorithm>

NetworkMonitor::NetworkMonitor() : isMonitoring_(false), nextLogId_(1) {
}

NetworkMonitor::~NetworkMonitor() {
    StopMonitoring();
}

bool NetworkMonitor::StartMonitoring() {
    if (isMonitoring_) {
        return true;
    }
    
    isMonitoring_ = true;
    monitoringThread_ = std::thread(&NetworkMonitor::MonitoringLoop, this);
    return true;
}

void NetworkMonitor::StopMonitoring() {
    if (!isMonitoring_) {
        return;
    }
    
    isMonitoring_ = false;
    if (monitoringThread_.joinable()) {
        monitoringThread_.join();
    }
}

bool NetworkMonitor::IsMonitoring() const {
    return isMonitoring_;
}

std::vector<NetworkMonitor::NetworkConnection> NetworkMonitor::GetActiveConnections() const {
    std::lock_guard<std::mutex> lock(connectionsMutex_);
    return connections_;
}

std::vector<NetworkMonitor::NetworkLog> NetworkMonitor::GetNetworkLogs(int limit) const {
    std::lock_guard<std::mutex> lock(logsMutex_);
    
    std::vector<NetworkLog> result;
    int count = std::min(limit, static_cast<int>(logs_.size()));
    
    if (count > 0) {
        result.assign(logs_.end() - count, logs_.end());
    }
    
    return result;
}

NetworkMonitor::TrafficStats NetworkMonitor::GetCurrentStats() const {
    TrafficStats stats;
    stats.bytesReceived = 1024000;
    stats.bytesSent = 512000;
    stats.packetsReceived = 1500;
    stats.packetsSent = 800;
    stats.connectionsActive = 25;
    stats.connectionsTotal = 150;
    stats.timestamp = std::chrono::system_clock::now();
    return stats;
}

std::vector<NetworkMonitor::TrafficStats> NetworkMonitor::GetStatsHistory(int minutes) const {
    std::lock_guard<std::mutex> lock(statsMutex_);
    
    auto cutoff = std::chrono::system_clock::now() - std::chrono::minutes(minutes);
    std::vector<TrafficStats> result;
    
    for (const auto& stats : statsHistory_) {
        if (stats.timestamp >= cutoff) {
            result.push_back(stats);
        }
    }
    
    return result;
}

std::vector<std::string> NetworkMonitor::GetSuspiciousIPs() const {
    return std::vector<std::string>(suspiciousIPs_.begin(), suspiciousIPs_.end());
}

int NetworkMonitor::GetThreatCount() const {
    return static_cast<int>(suspiciousIPs_.size());
}

void NetworkMonitor::BlockIP(const std::string& ip) {
    blockedIPs_.insert(ip);
    AddNetworkLog("SYSTEM", ip, "BLOCK", "IP Blocked", "BLOCKED");
}

void NetworkMonitor::UnblockIP(const std::string& ip) {
    blockedIPs_.erase(ip);
    AddNetworkLog("SYSTEM", ip, "UNBLOCK", "IP Unblocked", "ALLOWED");
}

std::vector<std::string> NetworkMonitor::GetBlockedIPs() const {
    return std::vector<std::string>(blockedIPs_.begin(), blockedIPs_.end());
}

bool NetworkMonitor::IsIPSuspicious(const std::string& ip) const {
    return suspiciousIPs_.find(ip) != suspiciousIPs_.end();
}

std::string NetworkMonitor::AnalyzeTrafficPattern(const std::string& ip) const {
    auto it = ipActivity_.find(ip);
    if (it == ipActivity_.end()) {
        return "No activity recorded";
    }
    
    int count = it->second;
    if (count > 100) {
        return "High activity - possible DDoS";
    } else if (count > 50) {
        return "Moderate activity - monitoring recommended";
    } else {
        return "Normal activity";
    }
}

void NetworkMonitor::UpdateThreatDatabase() {
    // Placeholder for threat database updates
}

void NetworkMonitor::MonitoringLoop() {
    while (isMonitoring_) {
        ScanActiveConnections();
        AnalyzeTraffic();
        DetectThreats();
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void NetworkMonitor::ScanActiveConnections() {
    GetTcpTable();
    GetUdpTable();
}

void NetworkMonitor::AnalyzeTraffic() {
    // Store current stats
    auto stats = GetCurrentStats();
    {
        std::lock_guard<std::mutex> lock(statsMutex_);
        statsHistory_.push_back(stats);
        
        // Keep only last hour of data
        auto cutoff = std::chrono::system_clock::now() - std::chrono::hours(1);
        statsHistory_.erase(
            std::remove_if(statsHistory_.begin(), statsHistory_.end(),
                          [cutoff](const TrafficStats& s) { return s.timestamp < cutoff; }),
            statsHistory_.end()
        );
    }
}

void NetworkMonitor::DetectThreats() {
    // Simulate threat detection
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 1000);
    
    if (dis(gen) > 990) { // 1% chance
        std::string suspiciousIP = "192.168.1." + std::to_string(dis(gen) % 255);
        suspiciousIPs_.insert(suspiciousIP);
        AddNetworkLog(suspiciousIP, "192.168.1.100", "TCP", "Port Scan Detected", "BLOCKED");
    }
}

void NetworkMonitor::AnalyzeConnectionPattern(const NetworkConnection& conn) {
    ipActivity_[conn.remoteAddress]++;
    
    if (IsPortScanDetected(conn.remoteAddress)) {
        suspiciousIPs_.insert(conn.remoteAddress);
        AddNetworkLog(conn.remoteAddress, conn.localAddress, conn.protocol, "Port Scan", "BLOCKED");
    }
}

bool NetworkMonitor::IsPortScanDetected(const std::string& ip) const {
    auto it = ipActivity_.find(ip);
    return it != ipActivity_.end() && it->second > 20; // Threshold for port scan
}

bool NetworkMonitor::IsDDoSDetected(const std::string& ip) const {
    auto it = ipActivity_.find(ip);
    return it != ipActivity_.end() && it->second > 100; // Threshold for DDoS
}

void NetworkMonitor::GetTcpTable() {
    // Windows API implementation would go here
}

void NetworkMonitor::GetUdpTable() {
    // Windows API implementation would go here
}

void NetworkMonitor::GetNetworkStatistics() {
    // Windows API implementation would go here
}

void NetworkMonitor::AddNetworkLog(const std::string& sourceIp, const std::string& destIp,
                                  const std::string& protocol, const std::string& threat,
                                  const std::string& status) {
    NetworkLog log;
    log.id = nextLogId_++;
    log.timestamp = std::chrono::system_clock::now();
    log.sourceIp = sourceIp;
    log.destinationIp = destIp;
    log.protocol = protocol;
    log.threat = threat;
    log.status = status;
    
    {
        std::lock_guard<std::mutex> lock(logsMutex_);
        logs_.push_back(log);
        
        // Keep only last 1000 logs
        if (logs_.size() > 1000) {
            logs_.erase(logs_.begin(), logs_.begin() + 100);
        }
    }
}