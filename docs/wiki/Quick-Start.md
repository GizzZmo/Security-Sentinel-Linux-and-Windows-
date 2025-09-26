# Quick Start Guide

Get up and running with Security Sentinel for Windows 11 in just a few minutes! This guide will help you start monitoring your system's security immediately.

## 🚀 5-Minute Setup

### Step 1: Choose Your Version

**C++ Native Application** (Recommended for full features)
- ✅ Full Windows API integration
- ✅ Real-time monitoring
- ✅ Administrator-level access
- ✅ High performance

**Web Interface** (Great for visualization)
- ✅ Modern dashboard
- ✅ Cross-platform compatibility
- ✅ Easy to use
- ✅ No installation required

### Step 2: Get Your API Key

1. Visit [Google AI Studio](https://makersuite.google.com/app/apikey)
2. Sign in with your Google account
3. Click "Create API Key"
4. Copy the generated key (you'll need this in Step 4)

### Step 3: Download and Install

#### For C++ Application:
```bash
# Download from GitHub releases
https://github.com/GizzZmo/security-sentinel-for-windows-11/releases

# Extract to any folder, e.g.:
C:\SecuritySentinel\
```

#### For Web Interface:
```bash
# Clone the repository
git clone https://github.com/GizzZmo/security-sentinel-for-windows-11.git
cd security-sentinel-for-windows-11

# Install dependencies
npm install
```

### Step 4: Configure API Key

#### For C++ Application:
Create `config.ini` in the application folder:
```ini
[gemini]
api_key=YOUR_API_KEY_HERE
model=gemini-2.5-flash
```

#### For Web Interface:
Create `.env.local` in the project root:
```env
GEMINI_API_KEY=YOUR_API_KEY_HERE
```

### Step 5: Launch the Application

#### For C++ Application:
```bash
# Right-click SecuritySentinel.exe
# Select "Run as administrator"
```

#### For Web Interface:
```bash
# Start the development server
npm run dev

# Open browser to http://localhost:5173
```

## 🎯 First Steps Tutorial

### 1. Dashboard Overview

When you first launch Security Sentinel, you'll see the main dashboard:

**C++ Console Interface:**
```
==================================================
        SECURITY SENTINEL FOR WINDOWS 11
==================================================

SYSTEM OVERVIEW:
- CPU Usage: 15.2%
- Memory Usage: 42.7%
- Active Connections: 23
- Threat Level: LOW (1/5)

MENU OPTIONS:
1. Dashboard
2. Network Monitor
3. Threat Protection  
4. AI Assistant
0. Exit

Select option:
```

**Web Interface:**
- Modern dashboard with security metrics
- Real-time charts and graphs
- Navigation sidebar with all features
- AI chat interface

### 2. Explore the Dashboard

#### C++ Application - Press '1' for Dashboard
You'll see real-time information about:
- System resource usage (CPU, Memory)
- Network activity summary
- Security event counts
- Current threat level

#### Web Interface - Dashboard Tab
Interactive charts showing:
- System performance metrics
- Network traffic visualization
- Security status indicators
- Recent activity timeline

### 3. Check Network Activity

#### C++ Application - Press '2' for Network Monitor
```
NETWORK MONITOR:
================

ACTIVE CONNECTIONS:
Protocol | Local Address      | Remote Address     | State      | Process
TCP      | 192.168.1.100:443  | 172.217.164.110:80| ESTABLISHED| chrome.exe
TCP      | 192.168.1.100:993  | 209.85.167.109:993| ESTABLISHED| outlook.exe
UDP      | 192.168.1.100:53   | 8.8.8.8:53        | LISTENING  | dns.exe

STATISTICS:
- Total Connections: 23
- Suspicious Activity: 0
- Blocked IPs: 2

Press 'b' to view blocked IPs, 'r' to refresh, or any key to return...
```

#### Web Interface - Network Monitor Tab
- Visual network connection map
- Real-time traffic graphs
- Connection details table
- Suspicious activity alerts

### 4. Test Threat Protection

#### C++ Application - Press '3' for Threat Protection
```
THREAT PROTECTION STATUS:
========================

PROTECTION STATUS: ACTIVE
- Real-time monitoring: ENABLED
- Automatic blocking: ENABLED
- Threat detection: ACTIVE

THREAT SUMMARY:
- Threats Detected: 0
- IPs Blocked: 2
- Suspicious Processes: 0
- Port Scans Blocked: 1

BLOCKED IPs:
- 192.168.1.200 (Port Scan Detected)
- 10.0.0.50 (Suspicious Activity)

Press 'u' to unblock an IP, 'r' to refresh, or any key to return...
```

#### Web Interface - Threat Protection Tab
- Protection status indicators
- Threat timeline and history
- Blocked IP management
- Alert configuration

### 5. Try the AI Assistant

#### C++ Application - Press '4' for AI Assistant
```
AI SECURITY ASSISTANT:
======================

Welcome! I'm your AI security expert powered by Google Gemini. 
Ask me anything about your system's security, threat analysis, 
or cybersecurity best practices.

You: What should I check first on a new Windows 11 system?

AI Assistant: Great question! For a new Windows 11 system, I recommend 
checking these security essentials first:

1. **Windows Updates**: Ensure all security patches are installed
2. **Windows Defender**: Verify real-time protection is enabled
3. **Firewall Settings**: Check that Windows Firewall is active
4. **User Account Control**: Ensure UAC is set to appropriate level
5. **Network Security**: Review active connections and services

Would you like me to help you check any of these specific areas?

You: _
```

#### Web Interface - AI Assistant Tab
- Chat interface with conversation history
- Contextual security recommendations
- Real-time streaming responses
- Security-focused knowledge base

## 🔍 Essential First Checks

### 1. Verify System Status

Check that monitoring is working:

**Signs of Proper Operation:**
- ✅ CPU and memory readings update regularly
- ✅ Network connections are detected
- ✅ Threat level indicator is active
- ✅ AI assistant responds to queries

### 2. Test Security Features

Try these quick tests:

1. **Network Detection Test:**
   - Open a web browser
   - Navigate to a website
   - Verify new connections appear in Network Monitor

2. **AI Response Test:**
   - Ask: "What security tools are built into Windows 11?"
   - Verify you get a detailed, relevant response

3. **System Monitoring Test:**
   - Run a resource-intensive application
   - Watch CPU/memory usage change in real-time

### 3. Configure Basic Settings

Customize for your environment:

#### C++ Application (`config.ini`):
```ini
[monitoring]
enabled=true
update_interval=5          # Update every 5 seconds
log_level=INFO            # Adjust verbosity

[network]
monitor_enabled=true
block_suspicious=true
whitelist_ips=192.168.1.0/24  # Trust your local network

[ai]
max_tokens=1000           # Limit response length
temperature=0.7           # Balance accuracy vs creativity
```

#### Web Interface:
- Settings available in the dashboard
- Customize refresh rates
- Configure alert thresholds
- Set up notification preferences

## 📚 Learn More

### Next Steps

Now that you're up and running, explore these guides:

1. **[Dashboard Overview](Dashboard-Overview.md)** - Understand all interface elements
2. **[Network Monitoring](Network-Monitoring.md)** - Deep dive into network analysis
3. **[Threat Protection](Threat-Protection.md)** - Configure advanced protection
4. **[AI Assistant](AI-Assistant.md)** - Maximize AI capabilities
5. **[Configuration](Configuration.md)** - Advanced settings and customization

### Common First-Time Questions

**Q: Why do I need administrator privileges?**
A: Administrator rights allow Security Sentinel to access Windows APIs for process monitoring, network analysis, and system-level security features.

**Q: How much network data does the AI use?**
A: Only security-related queries are sent to the AI. Your monitoring data stays local unless you specifically ask the AI to analyze something.

**Q: Can I run both versions simultaneously?**
A: Yes! The C++ application and web interface can run together, providing different views of the same system.

**Q: What if I don't have a Gemini API key?**
A: The core monitoring features work without an API key. You'll only miss the AI assistant functionality.

## 🛠️ Quick Troubleshooting

### Application Won't Start

1. **Check administrator privileges:**
   ```bash
   # Right-click SecuritySentinel.exe
   # Select "Run as administrator"
   ```

2. **Verify API key format:**
   ```ini
   # config.ini - no quotes, no extra spaces
   [gemini]
   api_key=AIza...your_key_here
   ```

3. **Check Windows Defender:**
   - Add SecuritySentinel to exclusions
   - Temporarily disable real-time protection to test

### No Network Data

1. **Verify administrator mode:** Network monitoring requires elevated privileges
2. **Check Windows Firewall:** Ensure it's not blocking the application
3. **Test with browser:** Open a website to generate network activity

### AI Not Responding

1. **Verify API key:** Ensure it's correctly set in configuration
2. **Check internet connection:** AI requires online access
3. **Test API key:** Visit Google AI Studio to verify the key works

### Performance Issues

1. **Adjust update interval:** Increase from 5 seconds to 10 or 15
2. **Close other security tools:** Avoid conflicts with other monitoring software
3. **Check system resources:** Ensure adequate RAM and CPU available

## 🎉 You're Ready!

Congratulations! You now have Security Sentinel monitoring your Windows 11 system. The application will:

- 🔍 **Monitor** your system continuously
- 🛡️ **Protect** against known threats
- 🤖 **Assist** with AI-powered security guidance
- 📊 **Report** security status in real-time

Take some time to explore the different features and customize the settings to your preferences. Security Sentinel is now your intelligent security companion for Windows 11!

---

**Having Issues?** Check our [Common Issues](Common-Issues.md) page or create an issue on [GitHub](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues).

**Ready for More?** Explore [Advanced Configuration](Configuration.md) or dive into [Security Best Practices](Security-Best-Practices.md).