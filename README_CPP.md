# Windows 11 Security Sentinel - C++ Edition

A comprehensive security monitoring application for Windows 11 with AI-powered threat analysis using Google's Gemini API.

## Features

- **Real-time Security Monitoring**: Monitor system processes, network activity, and security events
- **AI-Powered Analysis**: Integrated Gemini AI assistant for threat analysis and security recommendations
- **Network Traffic Monitoring**: Track network connections, detect suspicious activity, and block threats
- **Threat Protection**: Real-time threat detection with automated blocking capabilities
- **Interactive Dashboard**: Console-based interface with real-time metrics and alerts

## Prerequisites

- **Windows 11** (required for full functionality)
- **Visual Studio 2019/2022** or **MinGW-w64** with C++17 support
- **CMake 3.16+**
- **Google Gemini API Key** (for AI features)

## Building the Application

### Using CMake (Recommended)

1. Clone the repository:
   ```bash
   git clone https://github.com/GizzZmo/security-sentinel-for-windows-11.git
   cd security-sentinel-for-windows-11
   ```

2. Create build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Generate build files:
   ```bash
   cmake ..
   ```

4. Build the application:
   ```bash
   cmake --build . --config Release
   ```

### Using Visual Studio

1. Open the project folder in Visual Studio
2. CMake integration will automatically configure the project
3. Build using `Ctrl+Shift+B`

## Configuration

1. Create a `config.ini` file in the executable directory:
   ```ini
   [gemini]
   api_key=YOUR_GEMINI_API_KEY_HERE
   model=gemini-2.5-flash
   
   [monitoring]
   enabled=true
   update_interval=5
   
   [network]
   monitor_enabled=true
   block_suspicious=true
   ```

2. Alternatively, set the environment variable:
   ```bash
   set GEMINI_API_KEY=your_api_key_here
   ```

## Running the Application

1. **Run as Administrator** (recommended for full security monitoring):
   ```bash
   SecuritySentinel.exe
   ```

2. Navigate through the menu:
   - **1. Dashboard**: View system overview and security metrics
   - **2. Network Monitor**: Monitor network connections and traffic
   - **3. Threat Protection**: View threat status and blocked IPs
   - **4. AI Assistant**: Chat with the AI security expert
   - **0. Exit**: Quit the application

## AI Assistant Features

The integrated AI assistant powered by Google Gemini provides:

- **Threat Analysis**: Analyze security events and provide recommendations
- **Best Practices**: Security guidance and configuration advice
- **Incident Response**: Help with security incident investigation
- **Risk Assessment**: Evaluate system security posture

Example queries:
- "What does this network activity indicate?"
- "How can I improve my system's security?"
- "Explain this security alert"
- "What are the latest threats I should be aware of?"

## Architecture

### Core Components

- **SecurityApp**: Main application controller
- **ViewManager**: Console UI management and navigation
- **GeminiClient**: HTTP client for Gemini API integration
- **SecurityMonitor**: System security monitoring and event detection
- **NetworkMonitor**: Network traffic analysis and threat detection
- **Utils**: Utility functions and configuration management

### Security Features

- **Process Monitoring**: Track running processes and detect suspicious activity
- **Network Analysis**: Monitor TCP/UDP connections and detect port scans
- **Resource Monitoring**: Track CPU/memory usage for anomaly detection
- **Event Logging**: Comprehensive security event logging and analysis
- **Threat Intelligence**: Built-in threat detection algorithms

## API Integration

The application integrates with the Google Gemini API for AI-powered security analysis:

- **Streaming Responses**: Real-time AI responses with streaming support
- **Context Awareness**: Security-focused system prompt for relevant responses
- **Error Handling**: Robust error handling and fallback mechanisms
- **Rate Limiting**: Automatic request throttling and retry logic

## Windows API Integration

The application leverages Windows APIs for comprehensive system monitoring:

- **Process Management**: `EnumProcesses`, `OpenProcess`, `GetModuleBaseName`
- **Network Monitoring**: `GetTcpTable`, `GetUdpTable`, `GetNetworkParams`
- **System Metrics**: `GlobalMemoryStatusEx`, `GetSystemTimes`, PDH counters
- **Security Context**: `CheckTokenMembership` for administrator detection

## Security Considerations

- **Administrator Privileges**: Full functionality requires administrator rights
- **API Key Security**: Store API keys securely, never commit to source control
- **Network Access**: Application requires internet access for AI features
- **Privacy**: Local security data is not transmitted except for AI analysis

## Troubleshooting

### Common Issues

1. **API Key Not Working**:
   - Verify the API key is correctly set in config.ini or environment
   - Check that the Gemini API key has proper permissions

2. **Limited Functionality**:
   - Run as Administrator for full security monitoring capabilities
   - Ensure Windows Defender doesn't block the application

3. **Build Errors**:
   - Verify C++17 compiler support
   - Ensure all Windows SDK components are installed

### Debug Build

For debugging, build with debug configuration:
```bash
cmake --build . --config Debug
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly on Windows 11
5. Submit a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Disclaimer

This security monitoring tool is for educational and legitimate security purposes only. Users are responsible for complying with all applicable laws and regulations when using this software.