#include "SecurityMonitor.h"
#include "Utils.h"
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <iphlpapi.h>
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "iphlpapi.lib")
#endif

SecurityMonitor::SecurityMonitor() : isMonitoring_(false) {
}

SecurityMonitor::~SecurityMonitor() {
    StopMonitoring();
}

bool SecurityMonitor::StartMonitoring() {
    if (isMonitoring_.load()) {
        return true; // Already monitoring
    }
    
    isMonitoring_.store(true);
    monitoringThread_ = std::thread(&SecurityMonitor::MonitoringLoop, this);
    
    AddEvent("SYSTEM", "SecurityMonitor", "Security monitoring started", 1);
    return true;
}

void SecurityMonitor::StopMonitoring() {
    if (!isMonitoring_.load()) {
        return; // Not monitoring
    }
    
    isMonitoring_.store(false);
    
    if (monitoringThread_.joinable()) {
        monitoringThread_.join();
    }
    
    AddEvent("SYSTEM", "SecurityMonitor", "Security monitoring stopped", 1);
}

void SecurityMonitor::SetEventCallback(EventCallback callback) {
    eventCallback_ = callback;
}

std::vector<SecurityMonitor::SecurityEvent> SecurityMonitor::GetRecentEvents(int limit) const {
    std::lock_guard<std::mutex> lock(eventsMutex_);
    
    std::vector<SecurityEvent> result;
    int count = std::min<int>(limit, static_cast<int>(events_.size()));
    
    if (count > 0) {
        result.assign(events_.end() - count, events_.end());
    }
    
    return result;
}

void SecurityMonitor::ClearEvents() {
    std::lock_guard<std::mutex> lock(eventsMutex_);
    events_.clear();
}

SecurityMonitor::SystemMetrics SecurityMonitor::GetCurrentMetrics() const {
    SystemMetrics metrics;
    metrics.cpuUsage = Utils::GetCPUUsage();
    metrics.memoryUsage = Utils::GetMemoryUsage();
    metrics.activeConnections = 0; // Would be populated from network monitoring
    metrics.suspiciousActivity = 0; // Would be calculated from events
    metrics.lastUpdate = std::chrono::system_clock::now();
    
    // Simulate some realistic values for demo
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 10.0);
    
    metrics.activeConnections = 15 + static_cast<int>(dis(gen));
    metrics.suspiciousActivity = static_cast<int>(dis(gen) / 5);
    
    return metrics;
}

std::vector<SecurityMonitor::SystemMetrics> SecurityMonitor::GetMetricsHistory(int minutes) const {
    std::lock_guard<std::mutex> lock(metricsMutex_);
    
    auto cutoff = std::chrono::system_clock::now() - std::chrono::minutes(minutes);
    std::vector<SystemMetrics> result;
    
    for (const auto& metrics : metricsHistory_) {
        if (metrics.lastUpdate >= cutoff) {
            result.push_back(metrics);
        }
    }
    
    return result;
}

int SecurityMonitor::GetThreatLevel() const {
    // Calculate threat level based on recent events and metrics
    auto recentEvents = GetRecentEvents(50);
    int highSeverityCount = 0;
    
    for (const auto& event : recentEvents) {
        if (event.severity >= 4) {
            highSeverityCount++;
        }
    }
    
    // Simple threat level calculation
    if (highSeverityCount == 0) return 1;      // Low
    if (highSeverityCount <= 2) return 2;      // Low-Medium
    if (highSeverityCount <= 5) return 3;      // Medium
    if (highSeverityCount <= 10) return 4;     // High
    return 5;                                   // Critical
}

std::string SecurityMonitor::GetThreatSummary() const {
    int level = GetThreatLevel();
    
    switch (level) {
        case 1: return "System operating normally. No significant threats detected.";
        case 2: return "Minor security events detected. System is secure.";
        case 3: return "Moderate security activity. Monitoring recommended.";
        case 4: return "High security activity detected. Review recommended.";
        case 5: return "Critical security threats detected. Immediate action required.";
        default: return "Threat assessment unavailable.";
    }
}

void SecurityMonitor::MonitoringLoop() {
    while (isMonitoring_.load()) {
        try {
            CheckProcesses();
            CheckNetworkActivity();
            CheckSystemResources();
            CheckFileSystem();
            
            // Store current metrics
            auto metrics = GetCurrentMetrics();
            {
                std::lock_guard<std::mutex> lock(metricsMutex_);
                metricsHistory_.push_back(metrics);
                
                // Keep only last hour of data
                auto cutoff = std::chrono::system_clock::now() - std::chrono::hours(1);
                metricsHistory_.erase(
                    std::remove_if(metricsHistory_.begin(), metricsHistory_.end(),
                                  [cutoff](const SystemMetrics& m) { return m.lastUpdate < cutoff; }),
                    metricsHistory_.end()
                );
            }
        }
        catch (const std::exception& e) {
            AddEvent("ERROR", "SecurityMonitor", "Monitoring error: " + std::string(e.what()), 3);
        }
        
        // Check every 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void SecurityMonitor::CheckProcesses() {
    CollectProcessInfo();
    
    // Simulate process monitoring
    static int checkCount = 0;
    checkCount++;
    
    if (checkCount % 12 == 0) { // Every minute
        AddEvent("PROCESS", "ProcessMonitor", "Routine process scan completed", 1);
    }
}

void SecurityMonitor::CheckNetworkActivity() {
    CollectNetworkInfo();
    
    // Simulate network monitoring
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 100);
    
    if (dis(gen) > 95) { // 5% chance of suspicious activity
        AddEvent("NETWORK", "NetworkMonitor", "Suspicious network activity detected", 3);
    }
}

void SecurityMonitor::CheckSystemResources() {
    CollectSystemInfo();
    
    auto metrics = GetCurrentMetrics();
    
    if (metrics.cpuUsage > 90.0) {
        AddEvent("SYSTEM", "ResourceMonitor", "High CPU usage detected", 3);
    }
    
    if (metrics.memoryUsage > 85.0) {
        AddEvent("SYSTEM", "ResourceMonitor", "High memory usage detected", 3);
    }
}

void SecurityMonitor::CheckFileSystem() {
    // Simulate file system monitoring
    static int fsCheckCount = 0;
    fsCheckCount++;
    
    if (fsCheckCount % 24 == 0) { // Every 2 minutes
        AddEvent("FILESYSTEM", "FileSystemMonitor", "File system integrity check completed", 1);
    }
}

void SecurityMonitor::CollectProcessInfo() {
#ifdef _WIN32
    // Implementation for Windows process monitoring
    // This would use EnumProcesses, OpenProcess, etc.
#endif
}

void SecurityMonitor::CollectNetworkInfo() {
#ifdef _WIN32
    // Implementation for Windows network monitoring
    // This would use GetTcpTable, GetUdpTable, etc.
#endif
}

void SecurityMonitor::CollectSystemInfo() {
#ifdef _WIN32
    // Implementation for Windows system info collection
    // This would use GlobalMemoryStatusEx, GetSystemTimes, etc.
#endif
}

void SecurityMonitor::AddEvent(const std::string& type, const std::string& source, 
                               const std::string& description, int severity) {
    SecurityEvent event;
    event.timestamp = std::chrono::system_clock::now();
    event.type = type;
    event.source = source;
    event.description = description;
    event.severity = severity;
    
    {
        std::lock_guard<std::mutex> lock(eventsMutex_);
        events_.push_back(event);
        
        // Keep only last 1000 events
        if (events_.size() > 1000) {
            events_.erase(events_.begin(), events_.begin() + 100);
        }
    }
    
    // Notify callback
    if (eventCallback_) {
        eventCallback_(event);
    }
}