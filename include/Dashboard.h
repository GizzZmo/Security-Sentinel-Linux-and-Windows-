#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>

class SecurityApp;

/**
 * Dashboard component for displaying security status and metrics
 * Provides real-time overview of system security state
 */
class Dashboard {
public:
    struct SecurityMetric {
        std::string name;
        std::string value;
        std::string status; // "good", "warning", "critical"
        std::chrono::system_clock::time_point lastUpdate;
    };

    Dashboard();
    ~Dashboard();

    // Core functionality
    bool Initialize();
    void Update();
    void Render();

    // Metrics management
    std::vector<SecurityMetric> GetMetrics() const;
    void AddMetric(const SecurityMetric& metric);
    void UpdateMetric(const std::string& name, const std::string& value, const std::string& status);

    // Status
    std::string GetOverallStatus() const;
    int GetThreatLevel() const; // 1-5 scale

private:
    std::vector<SecurityMetric> metrics_;
    std::string overallStatus_;
    int threatLevel_;
    std::chrono::system_clock::time_point lastUpdate_;
    
    void CalculateOverallStatus();
};