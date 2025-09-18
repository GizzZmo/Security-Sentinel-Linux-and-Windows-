#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <set>

class SecurityApp;

/**
 * Threat Protection component for active security measures
 * Provides real-time threat detection and mitigation
 */
class ThreatProtection {
public:
    struct ThreatInfo {
        std::string id;
        std::string type;
        std::string source;
        std::string description;
        int severity; // 1-5 scale
        std::chrono::system_clock::time_point detected;
        bool mitigated;
    };

    enum class ProtectionLevel {
        Low = 1,
        Medium = 2,
        High = 3,
        Maximum = 4
    };

    ThreatProtection();
    ~ThreatProtection();

    // Core functionality
    bool Initialize();
    void Shutdown();
    bool StartProtection();
    void StopProtection();

    // Threat management
    std::vector<ThreatInfo> GetActiveThreats() const;
    std::vector<ThreatInfo> GetThreatHistory(int limit = 100) const;
    bool MitigateThreat(const std::string& threatId);
    
    // Protection settings
    void SetProtectionLevel(ProtectionLevel level);
    ProtectionLevel GetProtectionLevel() const;
    
    // Blocking and filtering
    void BlockIP(const std::string& ip);
    void UnblockIP(const std::string& ip);
    std::vector<std::string> GetBlockedIPs() const;
    
    // Status
    bool IsProtectionActive() const;
    int GetThreatCount() const;

private:
    bool protectionActive_;
    ProtectionLevel protectionLevel_;
    std::vector<ThreatInfo> activeThreats_;
    std::vector<ThreatInfo> threatHistory_;
    std::set<std::string> blockedIPs_;
    
    void ScanForThreats();
    void ProcessThreat(const ThreatInfo& threat);
    std::string GenerateThreatId();
};