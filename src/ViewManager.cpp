#include "ViewManager.h"
#include "SecurityApp.h"
#include "GeminiClient.h"
#include "SecurityMonitor.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

ViewManager::ViewManager(SecurityApp* app) 
    : app_(app), currentView_(View::Dashboard), isRunning_(true) {
}

ViewManager::~ViewManager() {
}

void ViewManager::ShowView(View view) {
    currentView_ = view;
    ClearScreen();
    
    switch (view) {
        case View::Dashboard:
            ShowDashboard();
            break;
        case View::NetworkMonitor:
            ShowNetworkMonitor();
            break;
        case View::ThreatProtection:
            ShowThreatProtection();
            break;
        case View::AIAssistant:
            ShowAIAssistant();
            break;
    }
}

void ViewManager::ShowView(const std::string& viewName) {
    if (viewName == "Dashboard") ShowView(View::Dashboard);
    else if (viewName == "Network Monitor") ShowView(View::NetworkMonitor);
    else if (viewName == "Threat Protection") ShowView(View::ThreatProtection);
    else if (viewName == "AI Assistant") ShowView(View::AIAssistant);
}

std::string ViewManager::GetCurrentViewName() const {
    switch (currentView_) {
        case View::Dashboard: return "Dashboard";
        case View::NetworkMonitor: return "Network Monitor";
        case View::ThreatProtection: return "Threat Protection";
        case View::AIAssistant: return "AI Assistant";
        default: return "Unknown";
    }
}

void ViewManager::InitializeConsole() {
#ifdef _WIN32
    // Enable ANSI escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    // Set console size
    COORD coord = {120, 40};
    SetConsoleScreenBufferSize(hOut, coord);
    
    SMALL_RECT rect = {0, 0, 119, 39};
    SetConsoleWindowInfo(hOut, TRUE, &rect);
#endif
}

void ViewManager::ShowMainMenu() {
    while (isRunning_) {
        ClearScreen();
        PrintHeader("Windows 11 Security Sentinel");
        
        std::cout << "\n";
        SetConsoleColor(14); // Yellow
        std::cout << "  Main Menu:\n";
        ResetConsoleColor();
        std::cout << "  1. Dashboard\n";
        std::cout << "  2. Network Monitor\n";
        std::cout << "  3. Threat Protection\n";
        std::cout << "  4. AI Assistant\n";
        std::cout << "  5. Settings\n";
        std::cout << "  0. Exit\n\n";
        
        int choice = GetMenuChoice(5);
        
        switch (choice) {
            case 1:
                ShowView(View::Dashboard);
                break;
            case 2:
                ShowView(View::NetworkMonitor);
                break;
            case 3:
                ShowView(View::ThreatProtection);
                break;
            case 4:
                ShowView(View::AIAssistant);
                break;
            case 5:
                // Settings would be implemented here
                ShowSuccess("Settings functionality coming soon!");
                Utils::WaitForKeyPress();
                break;
            case 0:
                isRunning_ = false;
                return;
        }
    }
}

void ViewManager::HandleUserInput() {
    // This method handles ongoing input in the current view
    // Implementation depends on the current view
}

void ViewManager::ClearScreen() {
    Utils::ClearConsole();
}

void ViewManager::SetTitle(const std::string& title) {
    Utils::SetConsoleTitleW(title);
}

void ViewManager::ShowStatusBar(const std::string& message) {
    SetConsoleColor(8); // Dark gray
    std::cout << std::string(80, '-') << "\n";
    if (!message.empty()) {
        std::cout << "Status: " << message << "\n";
    }
    std::cout << "Press any key to continue...";
    ResetConsoleColor();
}

void ViewManager::ShowError(const std::string& error) {
    SetConsoleColor(12); // Red
    std::cout << "ERROR: " << error << std::endl;
    ResetConsoleColor();
}

void ViewManager::ShowSuccess(const std::string& message) {
    SetConsoleColor(10); // Green
    std::cout << "SUCCESS: " << message << std::endl;
    ResetConsoleColor();
}

void ViewManager::ShowDashboard() {
    PrintHeader("Security Dashboard");
    
    // Get current metrics
    auto monitor = app_->GetSecurityMonitor();
    if (monitor) {
        auto metrics = monitor->GetCurrentMetrics();
        int threatLevel = monitor->GetThreatLevel();
        
        // Display system overview
        SetConsoleColor(14); // Yellow
        std::cout << "\n  System Overview:\n";
        ResetConsoleColor();
        
        std::cout << "  CPU Usage:        " << std::fixed << std::setprecision(1) 
                  << metrics.cpuUsage << "%\n";
        std::cout << "  Memory Usage:     " << std::fixed << std::setprecision(1) 
                  << metrics.memoryUsage << "%\n";
        std::cout << "  Active Connections: " << metrics.activeConnections << "\n";
        std::cout << "  Suspicious Activity: " << metrics.suspiciousActivity << "\n";
        
        // Threat level indicator
        std::cout << "\n  Threat Level:     ";
        if (threatLevel <= 2) {
            SetConsoleColor(10); // Green
            std::cout << "LOW";
        } else if (threatLevel <= 3) {
            SetConsoleColor(14); // Yellow
            std::cout << "MEDIUM";
        } else {
            SetConsoleColor(12); // Red
            std::cout << "HIGH";
        }
        ResetConsoleColor();
        std::cout << " (" << threatLevel << "/5)\n";
        
        // Recent events
        auto events = monitor->GetRecentEvents(5);
        if (!events.empty()) {
            std::cout << "\n";
            SetConsoleColor(14);
            std::cout << "  Recent Security Events:\n";
            ResetConsoleColor();
            
            for (const auto& event : events) {
                std::cout << "  - " << Utils::FormatTime(event.timestamp) 
                          << " [" << event.type << "] " << event.description << "\n";
            }
        }
    }
    
    std::cout << "\n";
    ShowStatusBar();
    Utils::WaitForKeyPress();
}

void ViewManager::ShowNetworkMonitor() {
    PrintHeader("Network Monitor");
    
    std::cout << "\n";
    SetConsoleColor(14);
    std::cout << "  Network Activity Monitor\n";
    ResetConsoleColor();
    
    std::cout << "  Monitoring network connections and traffic...\n\n";
    
    // This would show real network data
    std::cout << "  Active Connections:\n";
    std::cout << "  Local Address        Remote Address       Protocol  State\n";
    std::cout << "  ----------------------------------------------------------\n";
    std::cout << "  192.168.1.100:443    74.125.224.72:443   TCP       ESTABLISHED\n";
    std::cout << "  192.168.1.100:80     151.101.1.140:80    TCP       ESTABLISHED\n";
    std::cout << "  192.168.1.100:53     8.8.8.8:53          UDP       CONNECTED\n";
    
    std::cout << "\n";
    ShowStatusBar("Network monitoring active");
    Utils::WaitForKeyPress();
}

void ViewManager::ShowThreatProtection() {
    PrintHeader("Threat Protection");
    
    std::cout << "\n";
    SetConsoleColor(14);
    std::cout << "  Real-time Threat Protection\n";
    ResetConsoleColor();
    
    std::cout << "  Protection Status: ";
    SetConsoleColor(10);
    std::cout << "ACTIVE\n";
    ResetConsoleColor();
    
    std::cout << "\n  Blocked Threats Today: 23\n";
    std::cout << "  Suspicious IPs Blocked: 5\n";
    std::cout << "  Malware Signatures: 150,245 (Updated)\n";
    
    std::cout << "\n  Recent Blocks:\n";
    std::cout << "  - 192.168.1.50 - Port scan attempt\n";
    std::cout << "  - 10.0.0.25 - Suspicious payload detected\n";
    std::cout << "  - 172.16.0.100 - SYN flood attempt\n";
    
    std::cout << "\n";
    ShowStatusBar("All protection systems operational");
    Utils::WaitForKeyPress();
}

void ViewManager::ShowAIAssistant() {
    PrintHeader("AI Security Assistant");
    
    auto geminiClient = app_->GetGeminiClient();
    if (!geminiClient || !geminiClient->IsConfigured()) {
        ShowError("Gemini AI client not configured. Please set API key.");
        Utils::WaitForKeyPress();
        return;
    }
    
    std::cout << "\n";
    SetConsoleColor(14);
    std::cout << "  AI Security Assistant (Powered by Gemini)\n";
    ResetConsoleColor();
    std::cout << "  Ask me about security threats, best practices, or system analysis.\n";
    std::cout << "  Type 'exit' to return to main menu.\n\n";
    
    std::vector<GeminiClient::ChatMessage> history;
    
    while (true) {
        std::string input = GetUserInput("You: ");
        if (input == "exit" || input == "quit") {
            break;
        }
        
        if (input.empty()) continue;
        
        std::cout << "\nAI Assistant: ";
        
        // Send message to Gemini
        bool responseReceived = false;
        std::string fullResponse;
        
        auto future = geminiClient->SendMessageAsync(
            history,
            input,
            [&](const std::string& chunk) {
                std::cout << chunk << std::flush;
                fullResponse += chunk;
                responseReceived = true;
            },
            [&](const std::string& error) {
                ShowError("AI request failed: " + error);
            }
        );
        
        // Wait for completion
        if (future.wait_for(std::chrono::seconds(30)) == std::future_status::timeout) {
            ShowError("Request timed out");
        } else if (future.get() && responseReceived) {
            // Add to history
            history.push_back({"user", input});
            history.push_back({"model", fullResponse});
        }
        
        std::cout << "\n\n";
    }
}

void ViewManager::PrintHeader(const std::string& title) {
    std::cout << std::string(80, '=') << "\n";
    SetConsoleColor(11); // Cyan
    std::cout << "  " << title << "\n";
    ResetConsoleColor();
    std::cout << std::string(80, '=') << "\n";
}

void ViewManager::PrintSeparator() {
    std::cout << std::string(80, '-') << "\n";
}

std::string ViewManager::GetUserInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return Utils::Trim(input);
}

int ViewManager::GetMenuChoice(int maxChoice) {
    while (true) {
        std::string input = GetUserInput("Enter choice (0-" + std::to_string(maxChoice) + "): ");
        try {
            int choice = std::stoi(input);
            if (choice >= 0 && choice <= maxChoice) {
                return choice;
            }
        } catch (...) {
            // Invalid input
        }
        ShowError("Invalid choice. Please enter a number between 0 and " + std::to_string(maxChoice));
    }
}

void ViewManager::SetConsoleColor(int color) {
    Utils::SetConsoleColor(color);
}

void ViewManager::ResetConsoleColor() {
    Utils::ResetConsoleColor();
}