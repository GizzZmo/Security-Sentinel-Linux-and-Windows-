#include "Utils.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <random>
#include <iostream>
#include <vector>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <pdh.h>
#include <conio.h>
#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "psapi.lib")
#endif

namespace Utils {

std::string Trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string ToLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string ToUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool StartsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && 
           str.compare(0, prefix.size(), prefix) == 0;
}

bool EndsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && 
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string FormatTime(const std::chrono::system_clock::time_point& time) {
    auto time_t = std::chrono::system_clock::to_time_t(time);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string FormatDuration(const std::chrono::seconds& duration) {
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration % std::chrono::hours(1));
    auto seconds = duration % std::chrono::minutes(1);
    
    std::stringstream ss;
    if (hours.count() > 0) {
        ss << hours.count() << "h ";
    }
    if (minutes.count() > 0) {
        ss << minutes.count() << "m ";
    }
    ss << seconds.count() << "s";
    
    return ss.str();
}

std::chrono::system_clock::time_point ParseTime(const std::string& timeStr) {
    // Simple parsing - would need more robust implementation
    return std::chrono::system_clock::now();
}

bool IsValidIPv4(const std::string& ip) {
    std::regex ipRegex(R"(^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$)");
    std::smatch matches;
    
    if (!std::regex_match(ip, matches, ipRegex)) {
        return false;
    }
    
    for (int i = 1; i <= 4; ++i) {
        try {
            int octet = std::stoi(matches[i].str());
            if (octet < 0 || octet > 255) {
                return false;
            }
        } catch (const std::exception&) {
            return false; // Invalid number format
        }
    }
    
    return true;
}

bool IsValidIPv6(const std::string& ip) {
    // Basic IPv6 validation with proper format checking
    if (ip.empty() || ip.length() > 39) {
        return false;
    }
    
    // Must contain at least one colon
    if (ip.find(':') == std::string::npos) {
        return false;
    }
    
    // Split by colons and validate each segment
    auto segments = Split(ip, ':');
    
    // IPv6 has 8 segments (or fewer with :: compression)
    if (segments.size() > 8) {
        return false;
    }
    
    // Check for double colon (compression)
    size_t doubleColonPos = ip.find("::");
    bool hasCompression = (doubleColonPos != std::string::npos);
    
    // If no compression, must have exactly 8 segments
    if (!hasCompression && segments.size() != 8) {
        return false;
    }
    
    // Validate each non-empty segment
    for (const auto& segment : segments) {
        if (!segment.empty()) {
            // Each segment must be 1-4 hex digits
            if (segment.length() > 4) {
                return false;
            }
            
            // Check if all characters are valid hex digits
            for (char c : segment) {
                if (!std::isxdigit(c)) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

bool IsPrivateIP(const std::string& ip) {
    if (!IsValidIPv4(ip)) return false;
    
    auto parts = Split(ip, '.');
    if (parts.size() != 4) return false;
    
    try {
        int first = std::stoi(parts[0]);
        int second = std::stoi(parts[1]);
        
        // 10.0.0.0/8
        if (first == 10) return true;
        
        // 172.16.0.0/12
        if (first == 172 && second >= 16 && second <= 31) return true;
        
        // 192.168.0.0/16
        if (first == 192 && second == 168) return true;
        
        return false;
    } catch (const std::exception&) {
        return false; // Invalid number format
    }
}

bool IsLocalIP(const std::string& ip) {
    return ip == "127.0.0.1" || ip == "::1" || ip == "localhost";
}

std::string GetHostname(const std::string& ip) {
    // Would implement reverse DNS lookup
    return ip; // Placeholder
}

std::string GetLocalIP() {
    // Would implement local IP detection
    return "192.168.1.100"; // Placeholder
}

bool FileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string ReadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    
    // Check if file is actually readable
    if (!file.good()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    // Check for read errors
    if (file.bad()) {
        return "";
    }
    
    return buffer.str();
}

bool WriteFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    
    // Check both good() and the stream state
    bool success = file.good();
    file.close();
    
    // Additional check after close
    return success && !file.bad();
}

std::string GetExecutableDirectory() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string path(buffer);
    return path.substr(0, path.find_last_of("\\/"));
#else
    return "./";
#endif
}

std::string GetConfigDirectory() {
    return GetExecutableDirectory();
}

std::string EscapeJson(const std::string& str) {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\b': result += "\\b"; break;
            case '\f': result += "\\f"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default: result += c; break;
        }
    }
    return result;
}

std::string CreateJsonString(const std::map<std::string, std::string>& data) {
    std::stringstream json;
    json << "{";
    bool first = true;
    for (const auto& pair : data) {
        if (!first) json << ",";
        json << "\"" << EscapeJson(pair.first) << "\":\"" << EscapeJson(pair.second) << "\"";
        first = false;
    }
    json << "}";
    return json.str();
}

std::map<std::string, std::string> ParseJsonString(const std::string& json) {
    // Simplified JSON parsing - would need proper JSON parser
    std::map<std::string, std::string> result;
    return result;
}

void ClearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void SetConsoleTitleW(const std::string& title) {
#ifdef _WIN32
    // Convert UTF-8 to wide string safely
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, nullptr, 0);
    if (wideSize > 0) {
        std::vector<wchar_t> wideTitle(wideSize);
        if (MultiByteToWideChar(CP_UTF8, 0, title.c_str(), -1, wideTitle.data(), wideSize) > 0) {
            ::SetConsoleTitleW(wideTitle.data());
        }
    }
#endif
}

void SetConsoleTitle(const std::string& title) {
#ifdef _WIN32
    SetConsoleTitleA(title.c_str());
#endif
}

void SetConsoleColor(int foreground, int background) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = foreground;
    if (background >= 0) {
        color |= (background << 4);
    }
    SetConsoleTextAttribute(hConsole, color);
#endif
}

void ResetConsoleColor() {
#ifdef _WIN32
    SetConsoleColor(7, -1); // Default white, no background change
#endif
}

std::string GetConsoleInput(const std::string& prompt) {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void WaitForKeyPress() {
#ifdef _WIN32
    _getch();
#else
    std::cin.get();
#endif
}

std::string GetSystemInfo() {
#ifdef _WIN32
    // Use GetVersion() instead of deprecated GetVersionExA()
    DWORD version = GetVersion();
    DWORD majorVersion = (DWORD)(LOBYTE(LOWORD(version)));
    DWORD minorVersion = (DWORD)(HIBYTE(LOWORD(version)));
    
    return "Windows " + std::to_string(majorVersion) + "." + std::to_string(minorVersion);
#else
    return "Unknown OS";
#endif
}

double GetCPUUsage() {
#ifdef _WIN32
    static PDH_HQUERY cpuQuery = nullptr;
    static PDH_HCOUNTER cpuTotal = nullptr;
    static bool initialized = false;
    
    if (!initialized) {
        PDH_STATUS status = PdhOpenQuery(nullptr, NULL, &cpuQuery);
        if (status != ERROR_SUCCESS) {
            return 0.0; // Return 0 on error
        }
        
        status = PdhAddCounterA(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
        if (status != ERROR_SUCCESS) {
            PdhCloseQuery(cpuQuery);
            cpuQuery = nullptr;
            return 0.0; // Return 0 on error
        }
        
        PdhCollectQueryData(cpuQuery);
        initialized = true;
        return 0.0; // First call returns 0
    }
    
    PDH_FMT_COUNTERVALUE counterVal;
    PDH_STATUS status = PdhCollectQueryData(cpuQuery);
    if (status != ERROR_SUCCESS) {
        return 0.0; // Return 0 on error
    }
    
    status = PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, nullptr, &counterVal);
    if (status != ERROR_SUCCESS) {
        return 0.0; // Return 0 on error
    }
    
    return counterVal.doubleValue;
#else
    // Simulate CPU usage
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(15.0, 45.0);
    return dis(gen);
#endif
}

double GetMemoryUsage() {
#ifdef _WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return static_cast<double>(memInfo.dwMemoryLoad);
#else
    // Simulate memory usage
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(40.0, 70.0);
    return dis(gen);
#endif
}

std::vector<std::string> GetRunningProcesses() {
    std::vector<std::string> processes;
    
#ifdef _WIN32
    DWORD processIds[1024];
    DWORD bytesReturned;
    
    if (EnumProcesses(processIds, sizeof(processIds), &bytesReturned)) {
        DWORD numProcesses = bytesReturned / sizeof(DWORD);
        
        for (DWORD i = 0; i < numProcesses; ++i) {
            if (processIds[i] != 0) {
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                            FALSE, processIds[i]);
                if (hProcess) {
                    char processName[MAX_PATH] = "";
                    if (GetModuleBaseNameA(hProcess, nullptr, processName, sizeof(processName))) {
                        processes.push_back(processName);
                    }
                    CloseHandle(hProcess);
                }
            }
        }
    }
#endif
    
    return processes;
}

bool IsProcessRunning(const std::string& processName) {
    auto processes = GetRunningProcesses();
    return std::find(processes.begin(), processes.end(), processName) != processes.end();
}

bool IsRunningAsAdmin() {
#ifdef _WIN32
    BOOL isAdmin = FALSE;
    PSID adminGroup = nullptr;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    
    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(nullptr, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    
    return isAdmin == TRUE;
#else
    return false; // Assume not admin on non-Windows
#endif
}

std::string HashString(const std::string& input) {
    // Simple hash function - would use proper crypto in production
    std::hash<std::string> hasher;
    return std::to_string(hasher(input));
}

std::string GenerateRandomString(int length) {
    static const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, sizeof(charset) - 2);
    
    std::string result;
    result.reserve(length);
    
    for (int i = 0; i < length; ++i) {
        result += charset[dis(gen)];
    }
    
    return result;
}

bool ValidateApiKey(const std::string& apiKey) {
    // Basic validation for Gemini API key format
    return !apiKey.empty() && apiKey.length() > 20;
}

// Config implementation
Config& Config::Instance() {
    static Config instance;
    return instance;
}

bool Config::Load(const std::string& filename) {
    std::string content = ReadFile(filename);
    if (content.empty()) {
        return false;
    }
    
    // Simple INI parser with bounds checking
    std::istringstream stream(content);
    std::string line;
    std::string currentSection;
    
    while (std::getline(stream, line)) {
        line = Trim(line);
        if (line.empty() || line[0] == '#' || line[0] == ';') {
            continue;
        }
        
        if (line[0] == '[' && line.back() == ']' && line.length() > 2) {
            currentSection = line.substr(1, line.length() - 2);
        } else {
            size_t pos = line.find('=');
            if (pos != std::string::npos && pos > 0 && pos < line.length() - 1) {
                std::string key = Trim(line.substr(0, pos));
                std::string value = Trim(line.substr(pos + 1));
                if (!key.empty()) {
                    config_[currentSection][key] = value;
                }
            }
        }
    }
    
    return true;
}

bool Config::Save(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& section : config_) {
        if (!section.first.empty()) {
            file << "[" << section.first << "]\n";
            if (file.bad()) {
                return false;
            }
        }
        for (const auto& keyValue : section.second) {
            file << keyValue.first << "=" << keyValue.second << "\n";
            if (file.bad()) {
                return false;
            }
        }
        file << "\n";
        if (file.bad()) {
            return false;
        }
    }
    
    file.close();
    return !file.bad();
}

std::string Config::GetString(const std::string& section, const std::string& key, 
                             const std::string& defaultValue) const {
    auto sectionIt = config_.find(section);
    if (sectionIt != config_.end()) {
        auto keyIt = sectionIt->second.find(key);
        if (keyIt != sectionIt->second.end()) {
            return keyIt->second;
        }
    }
    return defaultValue;
}

int Config::GetInt(const std::string& section, const std::string& key, int defaultValue) const {
    std::string value = GetString(section, key);
    if (value.empty()) {
        return defaultValue;
    }
    try {
        return std::stoi(value);
    } catch (...) {
        return defaultValue;
    }
}

bool Config::GetBool(const std::string& section, const std::string& key, bool defaultValue) const {
    std::string value = ToLower(GetString(section, key));
    if (value.empty()) {
        return defaultValue;
    }
    return value == "true" || value == "1" || value == "yes" || value == "on";
}

void Config::SetString(const std::string& section, const std::string& key, const std::string& value) {
    config_[section][key] = value;
}

void Config::SetInt(const std::string& section, const std::string& key, int value) {
    SetString(section, key, std::to_string(value));
}

void Config::SetBool(const std::string& section, const std::string& key, bool value) {
    SetString(section, key, value ? "true" : "false");
}

} // namespace Utils
