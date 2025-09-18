#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

class SecurityApp;

/**
 * AI Assistant component for security analysis and recommendations
 * Provides intelligent assistance for security-related tasks
 */
class AIAssistant {
public:
    AIAssistant();
    ~AIAssistant();

    // Core functionality
    bool Initialize();
    void Shutdown();

    // AI interaction
    std::string ProcessQuery(const std::string& query);
    std::vector<std::string> GetSuggestions() const;
    
    // Security analysis
    std::string AnalyzeThreat(const std::string& threatData);
    std::string GetRecommendations() const;

private:
    bool initialized_;
    std::vector<std::string> suggestions_;
};