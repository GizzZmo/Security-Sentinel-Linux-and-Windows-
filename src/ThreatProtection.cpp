#include "ThreatProtection.h"
#include <algorithm>
#include <random>
#include <sstream>

ThreatProtection::ThreatProtection() 
    : protectionActive_(false), protectionLevel_(ProtectionLevel::Medium) {
}

ThreatProtection::~ThreatProtection() {
    Shutdown();
}

bool ThreatProtection::Initialize() {
    // Initialize threat protection system
    activeThreats_.clear();
    threatHistory_.clear();
    blockedIPs_.clear();
    
    return true;
}

void ThreatProtection::Shutdown() {
    StopProtection();
    activeThreats_.clear();
    threatHistory_.clear();
    blockedIPs_.clear();
}

bool ThreatProtection::StartProtection() {
    if (protectionActive_) {
        return true;
    }
    
    protectionActive_ = true;
    // Start monitoring threads/services
    return true;
}

void ThreatProtection::StopProtection() {
    protectionActive_ = false;
    // Stop monitoring threads/services
}

std::vector<ThreatProtection::ThreatInfo> ThreatProtection::GetActiveThreats() const {
    return activeThreats_;
}

std::vector<ThreatProtection::ThreatInfo> ThreatProtection::GetThreatHistory(int limit) const {
    std::vector<ThreatInfo> result;
    int count = std::min(limit, static_cast<int>(threatHistory_.size()));
    
    for (int i = 0; i < count; ++i) {
        result.push_back(threatHistory_[i]);
    }
    
    return result;
}

bool ThreatProtection::MitigateThreat(const std::string& threatId) {
    auto it = std::find_if(activeThreats_.begin(), activeThreats_.end(),
        [&threatId](const ThreatInfo& threat) { return threat.id == threatId; });
    
    if (it != activeThreats_.end()) {
        it->mitigated = true;
        threatHistory_.push_back(*it);
        activeThreats_.erase(it);
        return true;
    }
    
    return false;
}

void ThreatProtection::SetProtectionLevel(ProtectionLevel level) {
    protectionLevel_ = level;
}

ThreatProtection::ProtectionLevel ThreatProtection::GetProtectionLevel() const {
    return protectionLevel_;
}

void ThreatProtection::BlockIP(const std::string& ip) {
    blockedIPs_.insert(ip);
}

void ThreatProtection::UnblockIP(const std::string& ip) {
    blockedIPs_.erase(ip);
}

std::vector<std::string> ThreatProtection::GetBlockedIPs() const {
    return std::vector<std::string>(blockedIPs_.begin(), blockedIPs_.end());
}

bool ThreatProtection::IsProtectionActive() const {
    return protectionActive_;
}

int ThreatProtection::GetThreatCount() const {
    return static_cast<int>(activeThreats_.size());
}

void ThreatProtection::ScanForThreats() {
    // Placeholder threat scanning implementation
}

void ThreatProtection::ProcessThreat(const ThreatInfo& threat) {
    // Process detected threat
    activeThreats_.push_back(threat);
}

std::string ThreatProtection::GenerateThreatId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(100000, 999999);
    
    std::stringstream ss;
    ss << "THREAT_" << dis(gen);
    return ss.str();
}