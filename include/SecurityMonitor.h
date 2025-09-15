#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>

/**
 * Core security monitoring system
 * Integrates with Windows APIs to monitor system security
 */
class SecurityMonitor {
public:
    struct SecurityEvent {
        std::chrono::system_clock::time_point timestamp;
        std::string type;
        std::string source;
        std::string description;
        int severity; // 1-5 (1=info, 5=critical)
    };

    struct SystemMetrics {
        double cpuUsage;
        double memoryUsage;
        int activeConnections;
        int suspiciousActivity;
        std::chrono::system_clock::time_point lastUpdate;
    };

    using EventCallback = std::function<void(const SecurityEvent&)>;

    SecurityMonitor();
    ~SecurityMonitor();

    // Monitoring control
    bool StartMonitoring();
    void StopMonitoring();
    bool IsMonitoring() const { return isMonitoring_.load(); }

    // Event management
    void SetEventCallback(EventCallback callback);
    std::vector<SecurityEvent> GetRecentEvents(int limit = 100) const;
    void ClearEvents();

    // System metrics
    SystemMetrics GetCurrentMetrics() const;
    std::vector<SystemMetrics> GetMetricsHistory(int minutes = 60) const;

    // Threat analysis
    int GetThreatLevel() const; // 1-5 scale
    std::string GetThreatSummary() const;

private:
    std::atomic<bool> isMonitoring_;
    std::thread monitoringThread_;
    EventCallback eventCallback_;
    
    mutable std::mutex eventsMutex_;
    std::vector<SecurityEvent> events_;
    
    mutable std::mutex metricsMutex_;
    std::vector<SystemMetrics> metricsHistory_;

    // Monitoring methods
    void MonitoringLoop();
    void CheckProcesses();
    void CheckNetworkActivity();
    void CheckSystemResources();
    void CheckFileSystem();
    
    // Windows API integrations
    void CollectProcessInfo();
    void CollectNetworkInfo();
    void CollectSystemInfo();
    
    // Event generation
    void AddEvent(const std::string& type, const std::string& source, 
                  const std::string& description, int severity);
};