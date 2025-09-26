# System Requirements

Complete system requirements and compatibility information for Security Sentinel for Windows 11.

## 📋 Minimum System Requirements

### Operating System
| Requirement | C++ Application | Web Interface |
|-------------|-----------------|---------------|
| **OS** | Windows 11 (21H2 or later) | Windows 11 (any version) |
| **Architecture** | x64 (64-bit) | x64 (64-bit) |
| **Build Version** | 22000 or higher | 22000 or higher |
| **Updates** | Latest security updates recommended | Latest security updates recommended |

### Hardware Requirements

#### Minimum Specifications
| Component | C++ Application | Web Interface |
|-----------|-----------------|---------------|
| **Processor** | Dual-core 1.8 GHz | Dual-core 2.0 GHz |
| **Memory (RAM)** | 4 GB | 4 GB |
| **Storage** | 100 MB free space | 500 MB free space |
| **Network** | Internet connection for AI features | Internet connection required |
| **Graphics** | Console support (integrated graphics) | Modern browser with hardware acceleration |

#### Recommended Specifications
| Component | C++ Application | Web Interface |
|-----------|-----------------|---------------|
| **Processor** | Quad-core 2.5 GHz or higher | Quad-core 3.0 GHz or higher |
| **Memory (RAM)** | 8 GB or more | 8 GB or more |
| **Storage** | 1 GB free space (for logs) | 2 GB free space |
| **Network** | Broadband internet connection | Broadband internet connection |
| **Graphics** | Not applicable | Dedicated graphics card recommended |

### Permissions and Access
| Requirement | C++ Application | Web Interface |
|-------------|-----------------|---------------|
| **User Account** | Administrator privileges required | Standard user account |
| **UAC Settings** | Must be enabled | Standard settings |
| **Execution Policy** | Allow application execution | Standard browser security |

## 🔧 Software Dependencies

### C++ Application

#### Required Dependencies
- **Windows SDK**: Version 10.0.22000.0 or later
- **Visual C++ Redistributable**: 2019 or 2022 (x64)
- **Windows API Support**: WinINet, PSAPI, IPHLPAPI

#### Build Dependencies (Development Only)
- **Visual Studio**: 2019/2022 with C++ development tools
- **CMake**: Version 3.16 or later
- **Windows 10/11 SDK**: Latest version
- **MSVC Compiler**: v143 toolset or compatible

#### Optional Dependencies
- **Windows Terminal**: For enhanced console experience
- **PowerShell**: 5.1 or later for advanced scripting

### Web Interface

#### Required Dependencies
- **Node.js**: Version 18.0.0 or later
- **npm**: Version 8.0.0 or later (included with Node.js)
- **Modern Browser**: Chrome 100+, Firefox 100+, Edge 100+

#### Development Dependencies
- **Git**: For source code management
- **Code Editor**: VS Code, Visual Studio, or similar

## 🌐 Browser Compatibility

### Supported Browsers (Web Interface)
| Browser | Minimum Version | Recommended Version | Notes |
|---------|----------------|---------------------|--------|
| **Google Chrome** | 100 | Latest | Full feature support |
| **Microsoft Edge** | 100 | Latest | Optimized for Windows 11 |
| **Mozilla Firefox** | 100 | Latest | Good compatibility |
| **Safari** | Not supported | N/A | WebKit limitations |
| **Internet Explorer** | Not supported | N/A | Deprecated |

### Browser Features Required
- **ES2020 Support**: Modern JavaScript features
- **WebSocket**: For real-time updates
- **Fetch API**: For HTTP requests
- **Local Storage**: For settings persistence
- **Hardware Acceleration**: For smooth UI

## 🔒 Security Requirements

### Windows Security Features
| Feature | Required | Recommended | Notes |
|---------|----------|-------------|--------|
| **Windows Defender** | Compatible | Enabled with exclusions | May require exclusions |
| **Windows Firewall** | Compatible | Enabled | Allow application through firewall |
| **UAC** | Required | Enabled | Needed for administrator privileges |
| **Secure Boot** | Compatible | Enabled | No conflicts |
| **TPM 2.0** | Compatible | Available | Enhanced security |

### Third-party Antivirus
| Software | Compatibility | Notes |
|----------|---------------|--------|
| **Norton** | Compatible | May require exclusions |
| **McAfee** | Compatible | May require exclusions |
| **Kaspersky** | Compatible | May require exclusions |
| **Bitdefender** | Compatible | May require exclusions |
| **Avast/AVG** | Compatible | May require exclusions |

## 🌍 Network Requirements

### Internet Connectivity
| Feature | Requirement | Bandwidth | Notes |
|---------|-------------|-----------|--------|
| **AI Assistant** | Required | 1 Mbps | For Gemini API access |
| **Updates** | Recommended | 1 Mbps | For software updates |
| **Documentation** | Optional | 0.5 Mbps | For online help |

### Network Protocols
- **HTTPS**: Port 443 (outbound) - Required for AI features
- **HTTP**: Port 80 (outbound) - Optional for some services
- **DNS**: Port 53 (outbound) - Required for domain resolution

### Corporate Networks
| Requirement | Details |
|-------------|---------|
| **Proxy Support** | Configurable via system proxy settings |
| **Firewall** | Allow outbound HTTPS to `*.googleapis.com` |
| **SSL Inspection** | May require certificate configuration |
| **VPN** | Fully compatible with VPN connections |

## 🔧 Installation Prerequisites

### Pre-installation Checklist

#### For C++ Application
- [ ] Windows 11 (21H2 or later) installed
- [ ] Administrator account access
- [ ] At least 4 GB RAM available
- [ ] 100 MB free disk space
- [ ] Internet connection for AI features
- [ ] Windows Defender exclusions configured (optional)

#### For Web Interface
- [ ] Node.js 18+ installed
- [ ] Modern browser available
- [ ] Administrator privileges (for npm global packages)
- [ ] Git installed (for cloning repository)
- [ ] At least 4 GB RAM available
- [ ] 500 MB free disk space

### System Preparation Steps

1. **Update Windows**:
   ```powershell
   # Check for updates
   Get-WindowsUpdate
   # Install updates
   Install-WindowsUpdate -AcceptAll -AutoReboot
   ```

2. **Verify System Information**:
   ```cmd
   # Check Windows version
   winver
   
   # Check system specifications
   systeminfo | findstr /B /C:"OS Name" /C:"OS Version" /C:"Total Physical Memory"
   ```

3. **Configure Windows Defender** (if needed):
   ```powershell
   # Add exclusion for installation directory
   Add-MpPreference -ExclusionPath "C:\SecuritySentinel"
   ```

## ⚡ Performance Expectations

### Runtime Performance

#### C++ Application
| Metric | Typical Value | Maximum Value | Notes |
|--------|---------------|---------------|--------|
| **Memory Usage** | 15-30 MB | 50 MB | Depends on monitored processes |
| **CPU Usage** | <1% idle | 5% active | During active monitoring |
| **Startup Time** | 2-3 seconds | 5 seconds | From launch to ready |
| **Response Time** | <1 second | 2 seconds | UI updates and commands |

#### Web Interface
| Metric | Typical Value | Maximum Value | Notes |
|--------|---------------|---------------|--------|
| **Memory Usage** | 50-100 MB | 200 MB | Browser process |
| **CPU Usage** | <1% idle | 10% active | Including browser overhead |
| **Load Time** | 2-5 seconds | 10 seconds | Initial page load |
| **Response Time** | <1 second | 3 seconds | UI interactions |

### Scalability Limits

#### Monitoring Capacity
| Resource | Typical Limit | Maximum Limit | Performance Impact |
|----------|---------------|---------------|-------------------|
| **Processes** | 200 | 500+ | Minimal impact |
| **Network Connections** | 100 | 1000+ | Slight increase in CPU |
| **Security Events** | 1,000 | 10,000+ | Increased memory usage |
| **AI Queries** | 60/minute | API limits | Rate limiting applies |

## 🔍 Compatibility Testing

### Tested Configurations

#### Hardware Platforms
- **Intel Core i5/i7** (8th gen and later) ✅
- **AMD Ryzen 5/7** (3000 series and later) ✅
- **Surface devices** (Pro 8, Laptop 4) ✅
- **Virtual machines** (VMware, Hyper-V) ⚠️ Limited functionality

#### Software Combinations
- **Windows 11 Pro** + **Visual Studio 2022** ✅
- **Windows 11 Home** + **MinGW** ✅
- **Windows 11 Enterprise** + **Corporate antivirus** ✅
- **Windows 11 Education** + **Windows Defender** ✅

### Known Compatibility Issues

#### Hardware
- **ARM processors**: Not currently supported
- **Very low memory systems** (<4GB): May experience performance issues
- **Older CPUs** (pre-2015): May have compatibility issues

#### Software
- **Windows 10**: Not supported (Windows APIs require Windows 11)
- **32-bit systems**: Not supported
- **Windows S Mode**: Requires switching to standard Windows 11

## 🆘 Troubleshooting Requirements

### Minimum Requirements Not Met

#### Insufficient Memory
**Symptoms**: Slow performance, application crashes
**Solutions**:
- Close unnecessary applications
- Increase virtual memory
- Add more physical RAM
- Reduce monitoring frequency

#### Outdated Windows Version
**Symptoms**: API errors, feature limitations
**Solutions**:
- Update to Windows 11 21H2 or later
- Install latest Windows updates
- Check system compatibility

#### Missing Dependencies
**Symptoms**: Application won't start, build failures
**Solutions**:
- Install Visual C++ Redistributable
- Update Windows SDK
- Install required development tools

### Performance Issues

#### High CPU Usage
**Causes**: Too frequent monitoring, many processes
**Solutions**:
- Increase monitoring intervals
- Reduce maximum events stored
- Close unnecessary applications

#### Memory Leaks
**Causes**: Extended runtime, high event volume
**Solutions**:
- Restart application periodically
- Reduce event history size
- Update to latest version

## 📞 Getting Help

### System Information Collection

Before seeking support, collect this information:

```cmd
# System information
systeminfo > system_info.txt

# Installed software
wmic product get name,version > installed_software.txt

# Memory information
wmic memorychip list full > memory_info.txt

# Network configuration
ipconfig /all > network_config.txt
```

### Performance Monitoring

Use these tools to diagnose performance issues:

```cmd
# CPU and memory usage
tasklist /fo csv > running_processes.csv

# Performance counters
typeperf "\Processor(_Total)\% Processor Time" -sc 10

# Network activity
netstat -an > network_connections.txt
```

---

**Having issues with system requirements?** Check our [Common Issues](Common-Issues.md) guide or [create an issue](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues) with your system information.

**Ready to install?** Continue to the [Installation Guide](Installation-Guide.md).