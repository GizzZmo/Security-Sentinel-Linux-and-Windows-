# Installation Guide

This guide provides comprehensive instructions for installing Security Sentinel for Windows 11. Choose between the native C++ application or the web interface based on your needs.

## 📋 System Requirements

### Minimum Requirements
- **Operating System**: Windows 11 (version 21H2 or later)
- **RAM**: 4 GB minimum, 8 GB recommended
- **Storage**: 100 MB for application, additional space for logs
- **Network**: Internet connection for AI features
- **Privileges**: Administrator rights recommended for full functionality

### Recommended Requirements
- **Operating System**: Windows 11 (latest version)
- **RAM**: 16 GB or more
- **Storage**: 1 GB free space
- **Network**: Broadband internet connection
- **Processor**: Multi-core processor for optimal performance

## 🔧 C++ Application Installation

### Method 1: Pre-built Releases (Recommended)

1. **Download the Latest Release**
   ```bash
   # Visit GitHub releases page
   https://github.com/GizzZmo/security-sentinel-for-windows-11/releases
   ```

2. **Extract the Archive**
   - Download `SecuritySentinel-v1.0-Windows.zip`
   - Extract to your preferred location (e.g., `C:\Program Files\SecuritySentinel\`)

3. **Configure API Key**
   - Create `config.ini` in the application directory:
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

4. **Run the Application**
   - Right-click on `SecuritySentinel.exe`
   - Select "Run as administrator"
   - The application will start in console mode

### Method 2: Build from Source

#### Prerequisites
- **Visual Studio 2019/2022** with C++ development tools
- **CMake 3.16+**
- **Git** for cloning the repository

#### Build Steps

1. **Clone the Repository**
   ```bash
   git clone https://github.com/GizzZmo/security-sentinel-for-windows-11.git
   cd security-sentinel-for-windows-11
   ```

2. **Create Build Directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Generate Build Files**
   ```bash
   # For Visual Studio 2022
   cmake .. -G "Visual Studio 17 2022" -A x64
   
   # For Visual Studio 2019
   cmake .. -G "Visual Studio 16 2019" -A x64
   
   # For MinGW
   cmake .. -G "MinGW Makefiles"
   ```

4. **Build the Application**
   ```bash
   # Release build (recommended)
   cmake --build . --config Release
   
   # Debug build (for development)
   cmake --build . --config Debug
   ```

5. **Find the Executable**
   - Release build: `build\Release\SecuritySentinel.exe`
   - Debug build: `build\Debug\SecuritySentinel.exe`

## 🌐 Web Interface Installation

### Prerequisites
- **Node.js** 18.0.0 or later
- **npm** or **yarn** package manager

### Installation Steps

1. **Clone the Repository** (if not already done)
   ```bash
   git clone https://github.com/GizzZmo/security-sentinel-for-windows-11.git
   cd security-sentinel-for-windows-11
   ```

2. **Install Dependencies**
   ```bash
   npm install
   # or
   yarn install
   ```

3. **Configure Environment**
   - Create or modify `.env.local`:
   ```env
   GEMINI_API_KEY=your_gemini_api_key_here
   ```

4. **Build the Application**
   ```bash
   npm run build
   # or
   yarn build
   ```

5. **Run in Development Mode**
   ```bash
   npm run dev
   # or
   yarn dev
   ```

6. **Access the Interface**
   - Open your browser to `http://localhost:5173`
   - The dashboard will be available for interaction

## 🔑 API Key Setup

### Getting a Gemini API Key

1. **Visit Google AI Studio**
   - Go to [https://makersuite.google.com/app/apikey](https://makersuite.google.com/app/apikey)
   - Sign in with your Google account

2. **Create a New API Key**
   - Click "Create API Key"
   - Select your project or create a new one
   - Copy the generated API key

3. **Configure the Application**
   
   **For C++ Application:**
   ```ini
   # config.ini
   [gemini]
   api_key=YOUR_API_KEY_HERE
   ```
   
   **For Web Interface:**
   ```env
   # .env.local
   GEMINI_API_KEY=YOUR_API_KEY_HERE
   ```

### Alternative: Environment Variable

Set a system environment variable:
```bash
# Windows Command Prompt
set GEMINI_API_KEY=your_api_key_here

# Windows PowerShell
$env:GEMINI_API_KEY="your_api_key_here"
```

## 🔒 Security Configuration

### Windows Defender Exclusions

Add Security Sentinel to Windows Defender exclusions to prevent interference:

1. **Open Windows Security**
   - Press `Win + I` → Update & Security → Windows Security

2. **Add Exclusions**
   - Go to Virus & threat protection
   - Click "Manage settings" under Virus & threat protection settings
   - Click "Add or remove exclusions"
   - Add the SecuritySentinel installation directory

### Firewall Configuration

Allow Security Sentinel through Windows Firewall:

1. **Open Windows Defender Firewall**
   - Press `Win + R` → `wf.msc` → Enter

2. **Create Inbound Rule**
   - Click "Inbound Rules" → "New Rule"
   - Select "Program" → Browse to `SecuritySentinel.exe`
   - Allow the connection for all profiles

## 🚀 Post-Installation Setup

### 1. Initial Configuration

Run the application for the first time:

```bash
# Navigate to installation directory
cd "C:\Program Files\SecuritySentinel"

# Run as administrator
SecuritySentinel.exe
```

### 2. Verify Installation

Check that all components are working:

1. **Dashboard Display**: Verify the main dashboard loads
2. **Network Monitor**: Confirm network connections are detected
3. **AI Assistant**: Test AI responses with a simple query
4. **Threat Protection**: Verify threat detection is active

### 3. Customize Settings

Modify `config.ini` for your environment:

```ini
[monitoring]
enabled=true
update_interval=5          # Update frequency in seconds
log_level=INFO            # DEBUG, INFO, WARNING, ERROR

[network]
monitor_enabled=true
block_suspicious=true
whitelist_ips=192.168.1.0/24,10.0.0.0/8

[ai]
max_tokens=1000          # Maximum AI response length
temperature=0.7          # AI response creativity (0.0-1.0)
```

## 🛠️ Troubleshooting Installation

### Common Issues

#### Build Errors

**Error**: `CMake not found`
```bash
# Install CMake from https://cmake.org/download/
# Or use chocolatey
choco install cmake
```

**Error**: `Visual Studio not found`
```bash
# Install Visual Studio Community with C++ tools
# Or specify the generator manually
cmake .. -G "Visual Studio 17 2022"
```

#### Runtime Errors

**Error**: `API key not found`
- Verify `config.ini` exists in the same directory as the executable
- Check that the API key is correctly formatted
- Ensure no extra spaces or characters in the key

**Error**: `Access denied`
- Run the application as Administrator
- Check Windows Defender exclusions
- Verify firewall settings

#### Web Interface Issues

**Error**: `npm command not found`
```bash
# Install Node.js from https://nodejs.org/
# Verify installation
node --version
npm --version
```

**Error**: `Module not found`
```bash
# Clear npm cache and reinstall
npm cache clean --force
rm -rf node_modules package-lock.json
npm install
```

### Debug Mode

Run in debug mode for detailed logging:

```bash
# C++ Application
SecuritySentinel.exe --debug --log-level=DEBUG

# Web Interface
npm run dev
```

### Log Files

Check log files for detailed error information:

- **C++ Application**: `logs\security_sentinel.log`
- **Web Interface**: Browser developer console (F12)

## 📞 Getting Help

If you encounter issues during installation:

1. **Check the [Common Issues](Common-Issues.md)** page
2. **Search [GitHub Issues](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues)**
3. **Create a new issue** with detailed system information:
   - Windows version
   - Installation method used
   - Complete error messages
   - Log file contents

## ✅ Installation Verification

After successful installation, you should be able to:

- ✅ Launch the application without errors
- ✅ See system metrics in the dashboard
- ✅ View network connections in real-time
- ✅ Receive responses from the AI assistant
- ✅ See threat detection status
- ✅ Access all menu options

Congratulations! Security Sentinel is now installed and ready to protect your Windows 11 system.

---

**Next Steps**: [Quick Start Guide](Quick-Start.md) | [Configuration](Configuration.md) | [Dashboard Overview](Dashboard-Overview.md)