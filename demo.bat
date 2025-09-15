@echo off
echo Windows 11 Security Sentinel - C++ Demo
echo =========================================
echo.
echo This script demonstrates the C++ Security Sentinel application
echo with Gemini AI integration.
echo.
echo Prerequisites:
echo - Windows 11 (recommended)
echo - Gemini API key set in config.ini or GEMINI_API_KEY environment variable
echo - Administrator privileges (for full functionality)
echo.
echo Building the application...
cd build
cmake --build . --config Release
echo.
echo Build complete! 
echo.
echo Starting Security Sentinel...
echo (This will show the main menu - select options to explore features)
echo.
pause
bin\SecuritySentinel.exe