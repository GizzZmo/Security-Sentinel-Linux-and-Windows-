#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <set>
#include <algorithm>

/**
 * Network monitoring and analysis component
 * Tracks network traffic, connections, and suspicious activity
 */
class NetworkMonitor {
public:
    struct NetworkConnection {
        std::string localAddress;
        std::string remoteAddress;
        int localPort;
        int remotePort;
        std::string protocol;
        std::string state;
        std::string processName;
        int processId;
        std::chrono::system_clock::time_point timestamp;
    };

    struct NetworkLog {
        int id;
        std::chrono::system_clock::time_point timestamp;
        std::string sourceIp;
        std::string destinationIp;
        std::string protocol;
        std::string threat;
        std::string status;
    };

    struct TrafficStats {
        uint64_t bytesReceived;
        uint64_t bytesSent;
        uint32_t packetsReceived;
        uint32_t packetsSent;
        uint32_t connectionsActive;
        uint32_t connectionsTotal;
        std::chrono::system_clock::time_point timestamp;
    };

    NetworkMonitor();
    ~NetworkMonitor();

    // Monitoring control
    bool StartMonitoring();
    void StopMonitoring();
    bool IsMonitoring() const;

    // Connection tracking
    std::vector<NetworkConnection> GetActiveConnections() const;
    std::vector<NetworkLog> GetNetworkLogs(int limit = 100) const;
    
    // Traffic analysis
    TrafficStats GetCurrentStats() const;
    std::vector<TrafficStats> GetStatsHistory(int minutes = 60) const;
    
    // Threat detection
    std::vector<std::string> GetSuspiciousIPs() const;
    int GetThreatCount() const;
    void BlockIP(const std::string& ip);
    void UnblockIP(const std::string& ip);
    std::vector<std::string> GetBlockedIPs() const;

    // Analysis methods
    bool IsIPSuspicious(const std::string& ip) const;
    std::string AnalyzeTrafficPattern(const std::string& ip) const;
    void UpdateThreatDatabase();

private:
    bool isMonitoring_;
    std::thread monitoringThread_;
    int nextLogId_;
    
    mutable std::mutex connectionsMutex_;
    std::vector<NetworkConnection> connections_;
    
    mutable std::mutex logsMutex_;
    std::vector<NetworkLog> logs_;
    
    mutable std::mutex statsMutex_;
    std::vector<TrafficStats> statsHistory_;
    
    std::set<std::string> blockedIPs_;
    std::set<std::string> suspiciousIPs_;
    std::map<std::string, int> ipActivity_;

    // Monitoring implementation
    void MonitoringLoop();
    void ScanActiveConnections();
    void AnalyzeTraffic();
    void DetectThreats();
    
    // Windows API integration
    void GetTcpTable();
    void GetUdpTable();
    void GetNetworkStatistics();
    
    // Threat analysis
    void AnalyzeConnectionPattern(const NetworkConnection& conn);
    bool IsPortScanDetected(const std::string& ip) const;
    bool IsDDoSDetected(const std::string& ip) const;
    
    // Logging
    void AddNetworkLog(const std::string& sourceIp, const std::string& destIp,
                      const std::string& protocol, const std::string& threat,
                      const std::string& status);
};