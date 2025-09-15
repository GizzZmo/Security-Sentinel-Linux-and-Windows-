#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

class SecurityApp;

/**
 * Manages different views/screens in the application
 * Handles navigation and view state
 */
class ViewManager {
public:
    enum class View {
        Dashboard,
        NetworkMonitor,
        ThreatProtection,
        AIAssistant
    };

    explicit ViewManager(SecurityApp* app);
    ~ViewManager();

    // View management
    void ShowView(View view);
    void ShowView(const std::string& viewName);
    View GetCurrentView() const { return currentView_; }
    std::string GetCurrentViewName() const;

    // Console-based UI management
    void InitializeConsole();
    void ShowMainMenu();
    void HandleUserInput();
    void ClearScreen();
    void SetTitle(const std::string& title);

    // Status and messaging
    void ShowStatusBar(const std::string& message = "");
    void ShowError(const std::string& error);
    void ShowSuccess(const std::string& message);

private:
    SecurityApp* app_;
    View currentView_;
    bool isRunning_;

    // View implementations
    void ShowDashboard();
    void ShowNetworkMonitor();
    void ShowThreatProtection();
    void ShowAIAssistant();

    // UI helpers
    void PrintHeader(const std::string& title);
    void PrintSeparator();
    std::string GetUserInput(const std::string& prompt);
    int GetMenuChoice(int maxChoice);
    
    // Console color support
    void SetConsoleColor(int color);
    void ResetConsoleColor();
};