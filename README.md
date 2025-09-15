# Windows 11 Security Sentinel

A comprehensive security monitoring application for Windows 11 with AI-powered threat analysis using Google's Gemini API.

## 🚀 NEW: C++ Implementation Available!

This repository now contains a **complete C++ implementation** of the Security Sentinel application with enhanced Windows integration and native performance. 

### Choose Your Version:

#### 🔥 **C++ Edition (Recommended)**
- **Native Windows performance** with direct API integration
- **Real-time security monitoring** using Windows APIs
- **Advanced threat detection** with behavioral analysis
- **Professional console interface** with color-coded output
- **Enhanced Gemini AI integration** with streaming support

📖 **[See C++ Documentation](README_CPP.md)**

#### 🌐 **Web Edition (Original)**
- Browser-based interface using React/TypeScript
- Gemini AI chat assistant for security guidance
- Interactive dashboard with security metrics
- Cross-platform compatibility

---

## Quick Start (C++ Edition)

1. **Build the application:**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build . --config Release
   ```

2. **Configure API key:**
   ```ini
   # config.ini
   [gemini]
   api_key=your_gemini_api_key_here
   ```

3. **Run as Administrator:**
   ```bash
   SecuritySentinel.exe
   ```

## Features

- **🛡️ Real-time Security Monitoring**: Monitor system processes, network activity, and security events
- **🤖 AI-Powered Analysis**: Integrated Gemini AI assistant for threat analysis and security recommendations
- **🌐 Network Traffic Monitoring**: Track network connections, detect suspicious activity, and block threats
- **⚡ Threat Protection**: Real-time threat detection with automated blocking capabilities
- **📊 Interactive Dashboard**: Console-based interface with real-time metrics and alerts

## Architecture

The C++ implementation provides a robust, multi-threaded architecture:

- **SecurityApp**: Main application controller
- **GeminiClient**: HTTP client for AI integration with streaming support
- **SecurityMonitor**: System security monitoring with Windows API integration
- **NetworkMonitor**: Network traffic analysis and threat detection
- **ViewManager**: Console UI with interactive menus
- **Utils**: Comprehensive utility functions and configuration management

## Security Features

- **Process Monitoring**: Track running processes and detect suspicious activity
- **Network Analysis**: Monitor TCP/UDP connections and detect port scans/DDoS
- **Resource Monitoring**: Track CPU/memory usage for anomaly detection
- **Event Logging**: Comprehensive security event logging and correlation
- **Threat Intelligence**: Built-in threat detection with AI-powered analysis

---

## Original Web Version

### Run Locally (Web Edition)

**Prerequisites:** Node.js

1. Install dependencies:
   ```bash
   npm install
   ```

2. Set the `GEMINI_API_KEY` in [.env.local](.env.local):
   ```
   GEMINI_API_KEY=your_api_key_here
   ```

3. Run the app:
   ```bash
   npm run dev
   ```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please read our contributing guidelines and submit pull requests for any improvements.

---

**⚠️ Security Note**: This application is designed for legitimate security monitoring purposes. Users are responsible for complying with all applicable laws and regulations when using this software.
