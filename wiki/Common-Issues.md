# Common Issues and Troubleshooting

This guide helps you solve the most frequently encountered issues when installing, configuring, and running Security Sentinel for Windows 11.

## 🚨 Installation Issues

### Build and Compilation Problems

#### CMake Not Found
**Error**: `'cmake' is not recognized as an internal or external command`

**Solution**:
```bash
# Install CMake via chocolatey
choco install cmake

# Or download from https://cmake.org/download/
# Add CMake to your PATH environment variable
```

**Verification**:
```bash
cmake --version
# Should display CMake version 3.16 or higher
```

#### Visual Studio Not Detected
**Error**: `No suitable compiler found` or `Visual Studio not found`

**Solution**:
1. Install Visual Studio 2019/2022 with C++ development tools
2. Ensure "MSVC compiler" and "Windows SDK" are selected
3. Restart command prompt after installation

**Alternative**:
```bash
# Use MinGW instead
cmake .. -G "MinGW Makefiles"
```

#### Missing Windows SDK
**Error**: `Windows.h not found` or `WinINet.h not found`

**Solution**:
1. Open Visual Studio Installer
2. Modify your installation
3. Add "Windows 10/11 SDK" under Individual Components
4. Install the latest version

### Node.js and Web Interface Issues

#### npm Command Not Found
**Error**: `'npm' is not recognized as an internal or external command`

**Solution**:
```bash
# Download and install Node.js from https://nodejs.org/
# Choose LTS version (18.0.0 or later)

# Verify installation
node --version
npm --version
```

#### Package Installation Failures
**Error**: `npm ERR! peer dep missing` or similar dependency errors

**Solution**:
```bash
# Clear npm cache
npm cache clean --force

# Delete node_modules and package-lock.json
rm -rf node_modules package-lock.json

# Reinstall dependencies
npm install

# Alternative: Use yarn
npm install -g yarn
yarn install
```

#### Build Process Fails
**Error**: `Failed to resolve import` or module resolution errors

**Solution**:
```bash
# Check if all dependencies are installed
npm list

# Update all packages
npm update

# Try building again
npm run build
```

## 🔑 API Key and Configuration Issues

### API Key Problems

#### Invalid API Key Format
**Error**: `Invalid API key` or `Authentication failed`

**Common Causes**:
- Extra spaces before/after the key
- Incorrect quotes in configuration file
- Wrong environment variable name

**Solution**:
```ini
# config.ini - Correct format (no quotes, no spaces)
[gemini]
api_key=AIza...your_key_here

# ❌ Wrong - has quotes
api_key="AIza...your_key_here"

# ❌ Wrong - has spaces
api_key= AIza...your_key_here 
```

#### API Key Not Loading
**Error**: `GEMINI_API_KEY not found` or similar

**Solution**:
```bash
# Check environment variable (Windows CMD)
echo %GEMINI_API_KEY%

# Check environment variable (PowerShell)
$env:GEMINI_API_KEY

# Set environment variable permanently
setx GEMINI_API_KEY "your_key_here"
```

#### API Key Permissions
**Error**: `API key does not have required permissions`

**Solution**:
1. Visit [Google AI Studio](https://makersuite.google.com/app/apikey)
2. Regenerate your API key
3. Ensure your Google account has access to Gemini API
4. Check API usage quotas

### Configuration File Issues

#### Config File Not Found
**Error**: `Unable to load configuration file`

**Solution**:
```bash
# Ensure config.ini is in the same directory as SecuritySentinel.exe
C:\SecuritySentinel\
├── SecuritySentinel.exe
└── config.ini

# Check file permissions - ensure it's readable
# Right-click config.ini → Properties → Security → Ensure you have Read access
```

#### Invalid Configuration Format
**Error**: `Configuration parsing error` or similar

**Solution**:
```ini
# ✅ Correct INI format
[gemini]
api_key=your_key_here
model=gemini-2.5-flash

[monitoring]
enabled=true
update_interval=5

# ❌ Wrong - missing section headers
api_key=your_key_here
enabled=true

# ❌ Wrong - invalid boolean values
enabled=yes  # Should be: enabled=true
```

## 🚫 Runtime and Permission Issues

### Administrator Privileges

#### Access Denied Errors
**Error**: `Access is denied` when monitoring processes or network

**Solution**:
```bash
# Always run as Administrator
# Right-click SecuritySentinel.exe → "Run as administrator"

# Or use command prompt as admin
# Press Win+X → "Command Prompt (Admin)" or "PowerShell (Admin)"
cd "C:\SecuritySentinel"
SecuritySentinel.exe
```

#### Limited Functionality
**Symptom**: Some features don't work or show limited data

**Explanation**: Without administrator privileges, Security Sentinel cannot:
- Access detailed process information
- Monitor network connections
- Block suspicious IPs
- Access certain Windows APIs

**Solution**: Always run with administrator privileges for full functionality

### Windows Defender and Antivirus Issues

#### Application Blocked
**Error**: `Windows Defender has blocked this application`

**Solution**:
1. **Add to Exclusions**:
   - Open Windows Security (Win+I → Update & Security → Windows Security)
   - Go to Virus & threat protection
   - Click "Manage settings" under Virus & threat protection settings
   - Add SecuritySentinel folder to exclusions

2. **Temporarily Disable Real-time Protection**:
   - Only for testing purposes
   - Re-enable after confirming the application works

#### False Positive Detection
**Symptom**: Antivirus flags SecuritySentinel as malicious

**Explanation**: Security monitoring tools can trigger false positives because they:
- Monitor processes and network activity
- Use advanced Windows APIs
- Analyze system behavior

**Solution**:
1. Add SecuritySentinel to your antivirus whitelist
2. Report false positive to your antivirus vendor
3. Download from official GitHub releases only

### Firewall Issues

#### Network Monitoring Not Working
**Symptom**: No network connections displayed or AI not responding

**Solution**:
1. **Check Windows Firewall**:
   ```bash
   # Open Windows Firewall settings
   wf.msc
   ```

2. **Add Firewall Exception**:
   - Click "Inbound Rules" → "New Rule"
   - Select "Program"
   - Browse to SecuritySentinel.exe
   - Allow the connection

3. **Test Network Connectivity**:
   ```bash
   # Test internet connectivity
   ping google.com
   
   # Test HTTPS connectivity
   curl -I https://generativelanguage.googleapis.com/
   ```

## 🌐 Network and Connectivity Issues

### AI Assistant Not Responding

#### No Internet Connection
**Error**: `Failed to connect to AI service` or timeouts

**Solution**:
```bash
# Test basic connectivity
ping 8.8.8.8

# Test DNS resolution
nslookup generativelanguage.googleapis.com

# Test HTTPS connectivity
curl https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent
```

#### Proxy or Corporate Network
**Error**: Connection timeouts in corporate environments

**Solution**:
```ini
# Add proxy settings to config.ini
[network]
proxy_server=proxy.company.com:8080
proxy_username=your_username
proxy_password=your_password

# Or set system proxy
# Control Panel → Internet Options → Connections → LAN Settings
```

#### SSL/TLS Certificate Issues
**Error**: `SSL certificate verification failed`

**Solution**:
1. Update Windows to latest version
2. Update certificate store:
   ```bash
   certlm.msc
   # Refresh certificate store
   ```
3. Check system date/time is correct

### Rate Limiting and API Quotas

#### API Rate Limit Exceeded
**Error**: `Rate limit exceeded` or `Quota exceeded`

**Solution**:
1. **Check API Usage**:
   - Visit [Google AI Studio](https://makersuite.google.com/)
   - Review your API usage and quotas

2. **Reduce Request Frequency**:
   ```ini
   # config.ini - Increase intervals
   [ai]
   request_delay=2000  # Wait 2 seconds between requests
   max_requests_per_minute=30
   ```

3. **Implement Request Queuing**:
   - The application automatically queues requests
   - Avoid sending multiple simultaneous requests

## 🖥️ Performance Issues

### High CPU Usage

#### Excessive Monitoring Overhead
**Symptom**: SecuritySentinel uses high CPU continuously

**Solution**:
```ini
# config.ini - Reduce monitoring frequency
[monitoring]
update_interval=10     # Increase from 5 to 10 seconds
max_events=1000       # Reduce from 10000

[network]
monitor_enabled=false  # Disable if not needed
```

#### Memory Leaks
**Symptom**: Memory usage continuously increases

**Solution**:
1. **Restart the Application**: Temporary fix
2. **Update to Latest Version**: Often fixes memory issues
3. **Check Log Files**: Look for error patterns
4. **Reduce Event History**:
   ```ini
   [monitoring]
   max_events=1000  # Reduce stored events
   log_rotation=true
   ```

### Slow Performance

#### Large Log Files
**Symptom**: Application becomes slower over time

**Solution**:
```bash
# Check log file size
dir logs\security_sentinel.log

# Rotate log files manually
ren logs\security_sentinel.log logs\security_sentinel_old.log

# Configure automatic rotation
```

```ini
# config.ini
[logging]
max_log_size=10MB
auto_rotate=true
keep_logs=5
```

#### Too Many Connections
**Symptom**: Network monitoring is slow with many connections

**Solution**:
```ini
# config.ini - Filter connections
[network]
filter_local_only=true    # Only show external connections
max_connections=100       # Limit displayed connections
update_interval=10        # Reduce update frequency
```

## 🔧 Application-Specific Issues

### Console Display Problems

#### Colors Not Working
**Symptom**: No colors in console output or garbled text

**Solution**:
```ini
# config.ini
[ui]
color_scheme=default  # Try different schemes
force_colors=false    # Disable colors if problematic
```

**Alternative**:
```bash
# Run with color support
chcp 65001  # Enable UTF-8
SecuritySentinel.exe
```

#### Text Encoding Issues
**Symptom**: Special characters display incorrectly

**Solution**:
```bash
# Set console to UTF-8
chcp 65001

# Or run from PowerShell instead of CMD
powershell
cd "C:\SecuritySentinel"
.\SecuritySentinel.exe
```

### Data Not Updating

#### Monitoring Stopped
**Symptom**: Metrics are not updating, connections not changing

**Solution**:
1. **Check Service Status**:
   - Verify monitoring threads are running
   - Look for error messages in console

2. **Restart Monitoring**:
   - Press '0' to exit
   - Restart SecuritySentinel.exe as Administrator

3. **Check Configuration**:
   ```ini
   [monitoring]
   enabled=true  # Ensure monitoring is enabled
   ```

#### Stale Network Data
**Symptom**: Network connections show old or incorrect data

**Solution**:
```bash
# Refresh network stack
ipconfig /flushdns
netsh winsock reset
# Restart computer if necessary
```

## 📋 Diagnostic Steps

### Collecting Debug Information

#### Enable Debug Mode
```bash
# Run with verbose logging
SecuritySentinel.exe --debug --log-level=DEBUG
```

```ini
# config.ini
[logging]
log_level=DEBUG
enable_file_logging=true
```

#### System Information Collection
```bash
# Collect system info for support
systeminfo > system_info.txt
ipconfig /all > network_info.txt
tasklist > process_info.txt
```

#### Check Windows Event Logs
```bash
# Open Event Viewer
eventvwr.msc

# Check Application and System logs for errors
# Filter by "SecuritySentinel" or look for errors around the time of issues
```

### Log File Analysis

#### Key Log Messages to Look For
```
ERROR: API key validation failed
WARNING: Insufficient privileges detected  
INFO: Monitoring thread started successfully
DEBUG: Network scan completed, found X connections
ERROR: Failed to enumerate processes: Access denied
```

#### Log File Locations
```
# C++ Application
logs\security_sentinel.log
logs\security_sentinel_debug.log

# Web Interface
Browser Console (F12 → Console tab)
Network tab for API call failures
```

## 🆘 Getting Additional Help

### Before Reporting Issues

1. **Check this troubleshooting guide** first
2. **Search existing GitHub issues**: Many problems have known solutions
3. **Try the latest version**: Issues may already be fixed
4. **Test with minimal configuration**: Use default settings to isolate the problem

### Information to Include in Bug Reports

```markdown
**System Information**:
- Windows version: (Windows 11 build XXXXX)
- Security Sentinel version: (v1.0.0)
- Installation method: (Built from source / Downloaded release)

**Configuration**:
- API key configured: (Yes/No - don't include the actual key)
- Running as Administrator: (Yes/No)
- Antivirus software: (Windows Defender / Norton / etc.)

**Error Details**:
- Exact error message: (copy/paste full error)
- Steps to reproduce: (detailed steps)
- Expected behavior: (what should happen)
- Actual behavior: (what actually happens)

**Log Files**:
```
(Include relevant log entries - remove any sensitive information)
```

### Support Channels

1. **GitHub Issues**: [Create a new issue](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues)
2. **Discussions**: [GitHub Discussions](https://github.com/GizzZmo/security-sentinel-for-windows-11/discussions)
3. **Documentation**: Check other WIKI pages for detailed guides

### Emergency Situations

#### Security Concerns
If you discover a security vulnerability:
1. **DO NOT** report it in public issues
2. **DO** email security concerns privately
3. **DO** follow responsible disclosure practices

#### System Instability
If SecuritySentinel causes system problems:
1. **Immediately stop** the application
2. **Restart** your computer
3. **Remove** from startup if configured
4. **Report** the issue with detailed system information

---

Most issues can be resolved by following this guide. If you're still experiencing problems, don't hesitate to reach out to the community for help!

**Related**: [Installation Guide](Installation-Guide.md) | [Configuration](Configuration.md) | [Performance Optimization](Performance-Optimization.md)