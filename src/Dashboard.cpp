#include "Dashboard.h"
#include <algorithm>

Dashboard::Dashboard() : overallStatus_("Unknown"), threatLevel_(1) {
    lastUpdate_ = std::chrono::system_clock::now();
}

Dashboard::~Dashboard() {
}

bool Dashboard::Initialize() {
    // Initialize dashboard with default metrics
    metrics_.clear();
    
    // Add default metrics
    SecurityMetric cpuMetric = {"CPU Usage", "0%", "good", std::chrono::system_clock::now()};
    SecurityMetric memoryMetric = {"Memory Usage", "0%", "good", std::chrono::system_clock::now()};
    SecurityMetric networkMetric = {"Network Status", "Monitoring", "good", std::chrono::system_clock::now()};
    
    metrics_.push_back(cpuMetric);
    metrics_.push_back(memoryMetric);
    metrics_.push_back(networkMetric);
    
    CalculateOverallStatus();
    return true;
}

void Dashboard::Update() {
    lastUpdate_ = std::chrono::system_clock::now();
    CalculateOverallStatus();
}

void Dashboard::Render() {
    // Placeholder rendering - actual implementation would draw UI
}

std::vector<Dashboard::SecurityMetric> Dashboard::GetMetrics() const {
    return metrics_;
}

void Dashboard::AddMetric(const SecurityMetric& metric) {
    metrics_.push_back(metric);
    CalculateOverallStatus();
}

void Dashboard::UpdateMetric(const std::string& name, const std::string& value, const std::string& status) {
    auto it = std::find_if(metrics_.begin(), metrics_.end(),
        [&name](const SecurityMetric& metric) { return metric.name == name; });
    
    if (it != metrics_.end()) {
        it->value = value;
        it->status = status;
        it->lastUpdate = std::chrono::system_clock::now();
        CalculateOverallStatus();
    }
}

std::string Dashboard::GetOverallStatus() const {
    return overallStatus_;
}

int Dashboard::GetThreatLevel() const {
    return threatLevel_;
}

void Dashboard::CalculateOverallStatus() {
    int criticalCount = 0;
    int warningCount = 0;
    
    for (const auto& metric : metrics_) {
        if (metric.status == "critical") criticalCount++;
        else if (metric.status == "warning") warningCount++;
    }
    
    if (criticalCount > 0) {
        overallStatus_ = "Critical";
        threatLevel_ = 5;
    } else if (warningCount > 0) {
        overallStatus_ = "Warning";
        threatLevel_ = 3;
    } else {
        overallStatus_ = "Good";
        threatLevel_ = 1;
    }
}