#include "SecurityApp.h"
#include "Utils.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        // Set console title and properties
        Utils::SetConsoleTitle("Security Sentinel");
        Utils::ClearConsole();
        
        // Check if running as administrator
        if (!Utils::IsRunningAsAdmin()) {
            std::cout << "WARNING: This application should be run as Administrator for full functionality.\n";
            std::cout << "Some security monitoring features may be limited.\n\n";
        }

        // Create and initialize application
        SecurityApp app;
        
        if (!app.Initialize()) {
            std::cerr << "Failed to initialize Security Sentinel application!" << std::endl;
            return 1;
        }

        std::cout << "Security Sentinel initialized successfully!" << std::endl;
        std::cout << "Starting application..." << std::endl;

        // Run main application loop
        int result = app.Run();
        
        // Cleanup
        app.Shutdown();
        
        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        Utils::WaitForKeyPress();
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred!" << std::endl;
        Utils::WaitForKeyPress();
        return 1;
    }
}