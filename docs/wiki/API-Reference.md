# API Reference

Complete reference for Security Sentinel's APIs, including the Gemini AI integration and internal component interfaces.

## 🤖 Gemini AI Integration

### Overview

Security Sentinel integrates with Google's Gemini API to provide AI-powered security analysis and recommendations. The integration is implemented in both the C++ application and web interface.

### Authentication

All API requests require a valid Gemini API key:

```cpp
// C++ Configuration
[gemini]
api_key=YOUR_API_KEY_HERE
model=gemini-2.5-flash
```

```env
// Web Interface
GEMINI_API_KEY=YOUR_API_KEY_HERE
```

### GeminiClient API (C++)

#### Class: `GeminiClient`

##### Constructor
```cpp
GeminiClient(const std::string& apiKey, const std::string& model = "gemini-2.5-flash");
```

##### Methods

**SendMessage**
```cpp
std::string SendMessage(const std::string& message);
```
- **Purpose**: Send a message to Gemini and get a complete response
- **Parameters**: 
  - `message`: User query or security-related question
- **Returns**: Complete AI response as string
- **Throws**: `std::runtime_error` on API errors

**StreamResponse**
```cpp
bool StreamResponse(const std::string& message, 
                   std::function<void(const std::string&)> callback);
```
- **Purpose**: Stream AI response in real-time chunks
- **Parameters**:
  - `message`: User query
  - `callback`: Function called for each response chunk
- **Returns**: `true` if successful, `false` on error

**SetSystemPrompt**
```cpp
void SetSystemPrompt(const std::string& prompt);
```
- **Purpose**: Configure the AI's behavior and expertise focus
- **Parameters**: 
  - `prompt`: System-level instructions for the AI

##### Example Usage

```cpp
#include "GeminiClient.h"

// Initialize client
GeminiClient client("your-api-key-here");

// Set security-focused system prompt
client.SetSystemPrompt(
    "You are a cybersecurity expert specializing in Windows 11 security. "
    "Provide technical, actionable advice about security monitoring, "
    "threat detection, and system hardening."
);

// Send a message
try {
    std::string response = client.SendMessage("How can I detect port scans?");
    std::cout << "AI Response: " << response << std::endl;
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

// Stream a response
client.StreamResponse("Analyze this network activity", 
    [](const std::string& chunk) {
        std::cout << chunk << std::flush;
    });
```

### Gemini Service API (TypeScript)

#### Class: `GeminiService`

```typescript
class GeminiService {
  constructor(apiKey: string, model?: string);
  
  async sendMessage(message: string): Promise<string>;
  async streamResponse(
    message: string, 
    onChunk: (chunk: string) => void
  ): Promise<void>;
  
  setSystemPrompt(prompt: string): void;
}
```

##### Methods

**sendMessage**
```typescript
async sendMessage(message: string): Promise<string>
```
- **Purpose**: Send message and receive complete response
- **Parameters**: User message string
- **Returns**: Promise resolving to AI response
- **Throws**: Error on API failure

**streamResponse**
```typescript
async streamResponse(
  message: string, 
  onChunk: (chunk: string) => void
): Promise<void>
```
- **Purpose**: Stream response in real-time
- **Parameters**:
  - `message`: User query
  - `onChunk`: Callback for each response chunk
- **Returns**: Promise that resolves when streaming completes

##### Example Usage

```typescript
import { GeminiService } from './services/geminiService';

// Initialize service
const gemini = new GeminiService(process.env.GEMINI_API_KEY!);

// Send message
try {
  const response = await gemini.sendMessage("What are signs of malware?");
  console.log(response);
} catch (error) {
  console.error('AI Error:', error);
}

// Stream response
await gemini.streamResponse(
  "Explain Windows Defender features",
  (chunk) => {
    // Update UI with each chunk
    updateChatDisplay(chunk);
  }
);
```

## 🔧 Internal Component APIs

### SecurityMonitor API

#### Class: `SecurityMonitor`

```cpp
class SecurityMonitor {
public:
    void StartMonitoring();
    void StopMonitoring();
    
    // System metrics
    SystemMetrics GetCurrentMetrics() const;
    std::vector<ProcessInfo> GetProcessList() const;
    std::vector<SecurityEvent> GetRecentEvents() const;
    
    // Threat analysis
    ThreatLevel GetCurrentThreatLevel() const;
    std::vector<ThreatIndicator> GetActiveThreats() const;
    
    // Configuration
    void SetUpdateInterval(int seconds);
    void EnableProcessMonitoring(bool enabled);
    void SetThreatThreshold(float threshold);
};
```

#### Data Structures

**SystemMetrics**
```cpp
struct SystemMetrics {
    float cpuUsage;           // CPU usage percentage (0-100)
    float memoryUsage;        // Memory usage percentage (0-100)
    uint64_t totalMemory;     // Total system memory in bytes
    uint64_t availableMemory; // Available memory in bytes
    uint32_t processCount;    // Number of running processes
    uint32_t threadCount;     // Total number of threads
    std::chrono::system_clock::time_point timestamp;
};
```

**ProcessInfo**
```cpp
struct ProcessInfo {
    uint32_t processId;       // Process ID
    std::string processName;  // Executable name
    std::string fullPath;     // Full executable path
    float cpuUsage;           // Process CPU usage
    uint64_t memoryUsage;     // Process memory usage
    uint32_t threadCount;     // Number of threads
    bool isSuspicious;        // Threat indicator
    ThreatLevel threatLevel;  // Assessed threat level
};
```

**SecurityEvent**
```cpp
struct SecurityEvent {
    uint64_t eventId;         // Unique event identifier
    EventType type;           // Type of security event
    ThreatLevel severity;     // Event severity level
    std::string description;  // Human-readable description
    std::string source;       // Event source (process, network, etc.)
    std::chrono::system_clock::time_point timestamp;
    std::unordered_map<std::string, std::string> metadata;
};
```

#### Enumerations

**ThreatLevel**
```cpp
enum class ThreatLevel {
    None = 0,      // No threat detected
    Low = 1,       // Minor suspicious activity
    Medium = 2,    // Moderate threat indicators
    High = 3,      // Significant threat detected
    Critical = 4,  // Immediate attention required
    Severe = 5     // System compromise likely
};
```

**EventType**
```cpp
enum class EventType {
    ProcessStart,        // New process started
    ProcessEnd,          // Process terminated
    HighCpuUsage,       // CPU usage spike
    HighMemoryUsage,    // Memory usage spike
    SuspiciousProcess,  // Potentially malicious process
    NetworkActivity,    // Network connection event
    ThreatDetected,     // Security threat identified
    SystemAnomaly       // Unusual system behavior
};
```

### NetworkMonitor API

#### Class: `NetworkMonitor`

```cpp
class NetworkMonitor {
public:
    void StartNetworkMonitoring();
    void StopNetworkMonitoring();
    
    // Connection management
    std::vector<ConnectionInfo> GetActiveConnections() const;
    std::vector<ConnectionInfo> GetConnectionHistory() const;
    
    // Security features
    void BlockIP(const std::string& ipAddress);
    void UnblockIP(const std::string& ipAddress);
    std::vector<std::string> GetBlockedIPs() const;
    
    // Threat detection
    std::vector<NetworkThreat> GetDetectedThreats() const;
    void SetPortScanThreshold(int threshold);
    void SetDDoSThreshold(int threshold);
    
    // Statistics
    NetworkStatistics GetNetworkStats() const;
    void ResetStatistics();
};
```

#### Data Structures

**ConnectionInfo**
```cpp
struct ConnectionInfo {
    std::string protocol;        // TCP, UDP, ICMP
    std::string localAddress;    // Local IP:Port
    std::string remoteAddress;   // Remote IP:Port
    std::string state;           // Connection state
    std::string processName;     // Associated process
    uint32_t processId;          // Process ID
    bool isIncoming;             // Direction of connection
    bool isSuspicious;           // Threat indicator
    std::chrono::system_clock::time_point establishedTime;
};
```

**NetworkThreat**
```cpp
struct NetworkThreat {
    std::string threatType;      // Port scan, DDoS, etc.
    std::string sourceIP;        // Threat source IP
    ThreatLevel severity;        // Threat severity
    std::string description;     // Threat description
    bool isBlocked;              // Whether IP is blocked
    uint32_t eventCount;         // Number of threat events
    std::chrono::system_clock::time_point firstSeen;
    std::chrono::system_clock::time_point lastSeen;
};
```

**NetworkStatistics**
```cpp
struct NetworkStatistics {
    uint64_t totalConnections;     // Total connections seen
    uint64_t activeConnections;    // Currently active connections
    uint64_t blockedConnections;   // Blocked connection attempts
    uint64_t threatsDetected;      // Total threats detected
    uint64_t bytesReceived;        // Total bytes received
    uint64_t bytesSent;            // Total bytes sent
    float connectionsPerSecond;    // Connection rate
    std::chrono::system_clock::time_point startTime;
};
```

### ViewManager API

#### Class: `ViewManager`

```cpp
class ViewManager {
public:
    void Initialize();
    void RunMainLoop();
    void Shutdown();
    
    // Display management
    void ShowDashboard();
    void ShowNetworkMonitor();
    void ShowThreatProtection();
    void ShowAIAssistant();
    void ShowSettings();
    
    // User interaction
    int GetUserChoice();
    std::string GetUserInput(const std::string& prompt);
    void ShowMessage(const std::string& message, MessageType type);
    
    // UI configuration
    void SetColorScheme(ColorScheme scheme);
    void SetRefreshRate(int milliseconds);
    void EnableAdvancedMode(bool enabled);
};
```

#### Enumerations

**MessageType**
```cpp
enum class MessageType {
    Info,        // Informational message
    Warning,     // Warning message
    Error,       // Error message
    Success,     // Success message
    Debug        // Debug information
};
```

**ColorScheme**
```cpp
enum class ColorScheme {
    Default,     // Default console colors
    Dark,        // Dark theme
    Light,       // Light theme
    HighContrast // High contrast for accessibility
};
```

## 🌐 Web Interface APIs

### React Component APIs

#### SecurityContext

```typescript
interface SecurityContextType {
  state: SecurityState;
  dispatch: React.Dispatch<SecurityAction>;
}

interface SecurityState {
  currentView: View;
  systemMetrics: SystemMetrics | null;
  networkConnections: NetworkConnection[];
  threats: Threat[];
  aiMessages: ChatMessage[];
  configuration: Configuration;
  isLoading: boolean;
  error: string | null;
}
```

#### Custom Hooks

**useSecurityData**
```typescript
function useSecurityData(): SecurityContextType {
  const context = useContext(SecurityContext);
  if (!context) {
    throw new Error('useSecurityData must be used within SecurityProvider');
  }
  return context;
}
```

**useRealTimeUpdates**
```typescript
function useRealTimeUpdates(updateInterval: number = 5000): void {
  // Automatically update security data at specified intervals
}
```

**useAIChat**
```typescript
function useAIChat(): {
  messages: ChatMessage[];
  sendMessage: (message: string) => Promise<void>;
  isStreaming: boolean;
  clearHistory: () => void;
} {
  // Manage AI chat functionality
}
```

### Type Definitions

#### Core Types

```typescript
interface SystemMetrics {
  cpuUsage: number;
  memoryUsage: number;
  totalMemory: number;
  availableMemory: number;
  processCount: number;
  timestamp: Date;
}

interface NetworkConnection {
  id: string;
  protocol: 'TCP' | 'UDP';
  localAddress: string;
  remoteAddress: string;
  state: string;
  processName: string;
  processId: number;
  isIncoming: boolean;
  isSuspicious: boolean;
  establishedTime: Date;
}

interface Threat {
  id: string;
  type: string;
  severity: ThreatLevel;
  description: string;
  source: string;
  isBlocked: boolean;
  eventCount: number;
  firstSeen: Date;
  lastSeen: Date;
}

interface ChatMessage {
  id: string;
  role: 'user' | 'assistant';
  content: string;
  timestamp: Date;
  isStreaming?: boolean;
}

enum View {
  Dashboard = 'Dashboard',
  NetworkMonitor = 'Network Monitor',
  ThreatProtection = 'Threat Protection',
  AIAssistant = 'AI Assistant'
}

enum ThreatLevel {
  None = 0,
  Low = 1,
  Medium = 2,
  High = 3,
  Critical = 4,
  Severe = 5
}
```

## 🔌 HTTP API Endpoints

### Internal API (Future Enhancement)

The following REST API is planned for future releases to enable external integrations:

#### Security Metrics
```
GET /api/v1/metrics/system
GET /api/v1/metrics/network
GET /api/v1/metrics/threats
```

#### Network Monitoring
```
GET /api/v1/network/connections
GET /api/v1/network/blocked-ips
POST /api/v1/network/block-ip
DELETE /api/v1/network/unblock-ip/:ip
```

#### Threat Management
```
GET /api/v1/threats
GET /api/v1/threats/:id
POST /api/v1/threats/:id/resolve
```

#### AI Assistant
```
POST /api/v1/ai/chat
POST /api/v1/ai/analyze
```

## 🛠️ Configuration APIs

### ConfigManager

```cpp
class ConfigManager {
public:
    bool LoadConfiguration(const std::string& filename);
    bool SaveConfiguration();
    
    // Generic getters/setters
    template<typename T>
    T GetValue(const std::string& section, const std::string& key, 
               const T& defaultValue = T{});
    
    template<typename T>
    void SetValue(const std::string& section, const std::string& key, 
                  const T& value);
    
    // Specialized configuration methods
    std::string GetGeminiApiKey() const;
    void SetGeminiApiKey(const std::string& key);
    
    int GetUpdateInterval() const;
    void SetUpdateInterval(int seconds);
    
    bool IsMonitoringEnabled() const;
    void EnableMonitoring(bool enabled);
};
```

### Configuration Schema

```ini
[gemini]
api_key=string              # Gemini API key
model=string               # AI model name (default: gemini-2.5-flash)
max_tokens=int             # Maximum response tokens (default: 1000)
temperature=float          # AI creativity level (0.0-1.0, default: 0.7)

[monitoring]
enabled=bool               # Enable system monitoring (default: true)
update_interval=int        # Update interval in seconds (default: 5)
log_level=string          # Log level: DEBUG, INFO, WARNING, ERROR
max_events=int            # Maximum events to store (default: 10000)

[network]
monitor_enabled=bool       # Enable network monitoring (default: true)
block_suspicious=bool      # Auto-block suspicious IPs (default: true)
whitelist_ips=string      # Comma-separated whitelisted IP ranges
scan_detection_threshold=int    # Port scan detection threshold (default: 5)
ddos_detection_threshold=int    # DDoS detection threshold (default: 100)

[ui]
color_scheme=string       # Color scheme: default, dark, light, high_contrast
refresh_rate=int          # UI refresh rate in milliseconds (default: 1000)
show_advanced=bool        # Show advanced options (default: false)
```

## 📝 Error Handling

### Error Codes

```cpp
enum class ErrorCode {
    Success = 0,
    ConfigurationError = 1000,
    APIKeyMissing = 1001,
    NetworkError = 2000,
    APITimeout = 2001,
    InvalidResponse = 2002,
    MonitoringError = 3000,
    InsufficientPrivileges = 3001,
    SystemError = 4000,
    UnknownError = 9999
};

class SecuritySentinelException : public std::exception {
private:
    ErrorCode code;
    std::string message;
    
public:
    SecuritySentinelException(ErrorCode code, const std::string& message);
    ErrorCode GetErrorCode() const noexcept { return code; }
    const char* what() const noexcept override { return message.c_str(); }
};
```

### Error Response Format

```json
{
  "error": {
    "code": 2001,
    "message": "API request timed out",
    "details": "Failed to receive response from Gemini API within 30 seconds",
    "timestamp": "2024-12-15T10:30:00Z"
  }
}
```

---

This API reference provides comprehensive documentation for developers working with Security Sentinel's components and integrations.

**Next**: [Development Setup](Development-Setup.md) | [Code Style](Code-Style.md) | [Testing](Testing.md)