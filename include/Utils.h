#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <set>
#include <map>

/**
 * Utility functions for the Security Sentinel application
 */
namespace Utils {
    // String utilities
    std::string Trim(const std::string& str);
    std::vector<std::string> Split(const std::string& str, char delimiter);
    std::string ToLower(const std::string& str);
    std::string ToUpper(const std::string& str);
    bool StartsWith(const std::string& str, const std::string& prefix);
    bool EndsWith(const std::string& str, const std::string& suffix);

    // Time utilities
    std::string FormatTime(const std::chrono::system_clock::time_point& time);
    std::string FormatDuration(const std::chrono::seconds& duration);
    std::chrono::system_clock::time_point ParseTime(const std::string& timeStr);

    // Network utilities
    bool IsValidIPv4(const std::string& ip);
    bool IsValidIPv6(const std::string& ip);
    bool IsPrivateIP(const std::string& ip);
    bool IsLocalIP(const std::string& ip);
    std::string GetHostname(const std::string& ip);
    std::string GetLocalIP();

    // File utilities
    bool FileExists(const std::string& filename);
    std::string ReadFile(const std::string& filename);
    bool WriteFile(const std::string& filename, const std::string& content);
    std::string GetExecutableDirectory();
    std::string GetConfigDirectory();

    // JSON utilities
    std::string EscapeJson(const std::string& str);
    std::string CreateJsonString(const std::map<std::string, std::string>& data);
    std::map<std::string, std::string> ParseJsonString(const std::string& json);

    // Console utilities
    void ClearConsole();
    void SetConsoleTitle(const std::string& title);
    void SetConsoleTitleW(const std::string& title);
    void SetConsoleColor(int foreground, int background = -1);
    void ResetConsoleColor();
    std::string GetConsoleInput(const std::string& prompt = "");
    void WaitForKeyPress();

    // System utilities
    std::string GetSystemInfo();
    double GetCPUUsage();
    double GetMemoryUsage();
    std::vector<std::string> GetRunningProcesses();
    bool IsProcessRunning(const std::string& processName);
    bool IsRunningAsAdmin();

    // Crypto/Security utilities
    std::string HashString(const std::string& input);
    std::string GenerateRandomString(int length);
    bool ValidateApiKey(const std::string& apiKey);

    // Configuration utilities
    class Config {
    public:
        static Config& Instance();
        
        bool Load(const std::string& filename = "config.ini");
        bool Save(const std::string& filename = "config.ini");
        
        std::string GetString(const std::string& section, const std::string& key, 
                             const std::string& defaultValue = "");
        int GetInt(const std::string& section, const std::string& key, int defaultValue = 0);
        bool GetBool(const std::string& section, const std::string& key, bool defaultValue = false);
        
        void SetString(const std::string& section, const std::string& key, const std::string& value);
        void SetInt(const std::string& section, const std::string& key, int value);
        void SetBool(const std::string& section, const std::string& key, bool value);
        
    private:
        std::map<std::string, std::map<std::string, std::string>> config_;
        Config() = default;
    };
}