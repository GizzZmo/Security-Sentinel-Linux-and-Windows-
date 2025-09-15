#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <chrono>

// Forward declarations
class ViewManager;
class GeminiClient;
class SecurityMonitor;

/**
 * Main application class for Windows 11 Security Sentinel
 * Coordinates all components and manages application lifecycle
 */
class SecurityApp {
public:
    SecurityApp();
    ~SecurityApp();

    // Application lifecycle
    bool Initialize();
    int Run();
    void Shutdown();

    // View management
    void ShowView(const std::string& viewName);
    void SetStatusMessage(const std::string& message);

    // Getters for components
    GeminiClient* GetGeminiClient() const { return geminiClient_.get(); }
    SecurityMonitor* GetSecurityMonitor() const { return securityMonitor_.get(); }

private:
    std::unique_ptr<ViewManager> viewManager_;
    std::unique_ptr<GeminiClient> geminiClient_;
    std::unique_ptr<SecurityMonitor> securityMonitor_;
    
    bool isRunning_;
    std::string statusMessage_;

    void InitializeComponents();
    void SetupEventHandlers();
};