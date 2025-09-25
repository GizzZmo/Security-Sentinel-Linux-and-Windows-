#include "SecurityApp.h"
#include "ViewManager.h"
#include "GeminiClient.h"
#include "SecurityMonitor.h"
#include "Utils.h"
#include <iostream>
#include <memory>

SecurityApp::SecurityApp() 
    : isRunning_(false) {
}

SecurityApp::~SecurityApp() {
    Shutdown();
}

bool SecurityApp::Initialize() {
    try {
        // Load configuration
        auto& config = Utils::Config::Instance();
        if (!config.Load()) {
            std::cout << "No configuration file found, using defaults.\n";
        }

        // Initialize components
        InitializeComponents();
        
        // Setup event handlers
        SetupEventHandlers();
        
        isRunning_ = true;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        return false;
    }
}

int SecurityApp::Run() {
    if (!isRunning_) {
        std::cerr << "Application not initialized!" << std::endl;
        return 1;
    }

    try {
        // Start security monitoring
        if (securityMonitor_) {
            securityMonitor_->StartMonitoring();
        }

        // Show main interface
        if (viewManager_) {
            viewManager_->InitializeConsole();
            viewManager_->ShowMainMenu();
            
            // Main application loop
            while (isRunning_) {
                viewManager_->HandleUserInput();
            }
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    }
}

void SecurityApp::Shutdown() {
    if (!isRunning_) return;
    
    isRunning_ = false;
    
    // Stop monitoring
    if (securityMonitor_) {
        securityMonitor_->StopMonitoring();
    }

    // Save configuration
    auto& config = Utils::Config::Instance();
    config.Save();
    
    std::cout << "Security Sentinel shutdown complete." << std::endl;
}

void SecurityApp::ShowView(const std::string& viewName) {
    if (viewManager_) {
        viewManager_->ShowView(viewName);
    }
}

void SecurityApp::SetStatusMessage(const std::string& message) {
    statusMessage_ = message;
    if (viewManager_) {
        viewManager_->ShowStatusBar(message);
    }
}

void SecurityApp::InitializeComponents() {
    // Initialize Gemini client
    geminiClient_ = std::make_unique<GeminiClient>();
    
    // Load API key from config
    auto& config = Utils::Config::Instance();
    std::string apiKey = config.GetString("gemini", "api_key", "");
    
    if (apiKey.empty()) {
        std::cout << "No Gemini API key found in configuration.\n";
        std::cout << "Please set GEMINI_API_KEY in environment or config file.\n";
        
        // Try environment variable
        const char* envKey = getenv("GEMINI_API_KEY");
        if (envKey) {
            apiKey = envKey;
        }
    }
    
    if (!apiKey.empty()) {
        geminiClient_->SetApiKey(apiKey);
        geminiClient_->SetSystemInstruction(
            "You are a world-class cybersecurity expert integrated into \"Security Sentinel,\" "
            "a security application. Your role is to assist users in understanding and mitigating network threats. "
            "Provide clear, concise, and actionable security advice based on the context provided."
        );
    }

    // Initialize security monitor
    securityMonitor_ = std::make_unique<SecurityMonitor>();
    
    // Initialize view manager
    viewManager_ = std::make_unique<ViewManager>(this);
}

void SecurityApp::SetupEventHandlers() {
    // Setup security event handler
    if (securityMonitor_) {
        securityMonitor_->SetEventCallback([this](const SecurityMonitor::SecurityEvent& event) {
            // Handle security events
            if (event.severity >= 4) { // High/Critical severity
                SetStatusMessage("ALERT: " + event.description);
            }
        });
    }
}