# Architecture Overview

This document provides a comprehensive overview of Security Sentinel's architecture, covering both the native C++ application and the web interface components.

## 🏗️ System Architecture

Security Sentinel employs a modular, multi-tier architecture designed for scalability, performance, and maintainability. The system is composed of two main implementations that can work independently or in tandem.

```
┌─────────────────────────────────────────────────────────────┐
│                    Security Sentinel                        │
├─────────────────────────────────────────────────────────────┤
│  C++ Native Application        │   Web Interface            │
│  ┌─────────────────────────┐   │   ┌─────────────────────┐  │
│  │     SecurityApp         │   │   │   React Frontend     │  │
│  │   (Main Controller)     │   │   │  (Dashboard & UI)    │  │
│  └─────────────────────────┘   │   └─────────────────────┘  │
├─────────────────────────────────────────────────────────────┤
│                Core Components                              │
│  ┌─────────────┐ ┌─────────────┐ ┌─────────────────────┐   │
│  │SecurityMonit│ │NetworkMonit │ │    GeminiClient     │   │
│  │or (System)  │ │or (Network) │ │  (AI Integration)   │   │
│  └─────────────┘ └─────────────┘ └─────────────────────┘   │
├─────────────────────────────────────────────────────────────┤
│                Windows Integration Layer                    │
│  ┌─────────────┐ ┌─────────────┐ ┌─────────────────────┐   │
│  │Windows APIs │ │Network APIs │ │   Security APIs     │   │
│  │(Process/Mem)│ │(TCP/UDP)    │ │  (Tokens/Events)    │   │
│  └─────────────┘ └─────────────┘ └─────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

## 🔧 C++ Native Application Architecture

### Core Components

#### 1. SecurityApp (Main Controller)
**Purpose**: Central orchestrator managing all application components and lifecycle.

**Responsibilities**:
- Application initialization and cleanup
- Component coordination and communication
- Configuration management
- Main event loop processing
- Error handling and recovery

**Key Features**:
```cpp
class SecurityApp {
private:
    std::unique_ptr<ViewManager> viewManager;
    std::unique_ptr<SecurityMonitor> securityMonitor;
    std::unique_ptr<NetworkMonitor> networkMonitor;
    std::unique_ptr<GeminiClient> geminiClient;
    
public:
    bool Initialize();
    void Run();
    void Shutdown();
};
```

#### 2. GeminiClient (AI Integration)
**Purpose**: Handles all communication with Google's Gemini AI API.

**Architecture Features**:
- **HTTP Client**: Custom WinINet-based implementation
- **Streaming Support**: Real-time AI response processing
- **Error Handling**: Robust retry mechanisms and fallback strategies
- **JSON Processing**: Request/response serialization
- **Rate Limiting**: Automatic throttling and queue management

**Implementation Details**:
```cpp
class GeminiClient {
private:
    HINTERNET hSession;
    HINTERNET hConnect;
    std::string apiKey;
    std::queue<std::string> requestQueue;
    std::mutex queueMutex;
    
public:
    std::string SendMessage(const std::string& message);
    bool StreamResponse(const std::string& message, 
                       std::function<void(const std::string&)> callback);
};
```

#### 3. SecurityMonitor (System Monitoring)
**Purpose**: Real-time monitoring of system-level security events and metrics.

**Monitoring Capabilities**:
- **Process Monitoring**: Track running processes, detect suspicious activity
- **Resource Monitoring**: CPU, memory, disk usage analysis
- **Event Correlation**: Identify patterns across multiple security vectors
- **Threat Assessment**: Assign threat levels (1-5 scale) to events

**Windows API Integration**:
```cpp
class SecurityMonitor {
private:
    std::vector<ProcessInfo> processes;
    SystemMetrics currentMetrics;
    std::thread monitoringThread;
    std::atomic<bool> isRunning;
    
    // Windows API functions
    void EnumerateProcesses();
    void GetSystemMetrics();
    void AnalyzeThreatLevel();
    
public:
    void StartMonitoring();
    void StopMonitoring();
    ThreatLevel GetCurrentThreatLevel();
};
```

#### 4. NetworkMonitor (Network Security)
**Purpose**: Monitor network traffic, detect threats, and manage network security.

**Network Analysis Features**:
- **Connection Tracking**: Monitor TCP/UDP connections in real-time
- **Traffic Pattern Analysis**: Detect anomalous network behavior
- **Threat Detection**: Identify port scans, DDoS attacks, suspicious IPs
- **Automatic Blocking**: Real-time threat response and IP blocking
- **Statistics Collection**: Network usage metrics and reporting

**Implementation Architecture**:
```cpp
class NetworkMonitor {
private:
    std::vector<ConnectionInfo> activeConnections;
    std::unordered_set<std::string> blockedIPs;
    std::thread networkThread;
    
    void UpdateConnections();
    void AnalyzeTraffic();
    void DetectThreats();
    
public:
    void StartNetworkMonitoring();
    std::vector<ConnectionInfo> GetActiveConnections();
    void BlockIP(const std::string& ip);
};
```

#### 5. ViewManager (Console Interface)
**Purpose**: Manage the console-based user interface and user interactions.

**UI Features**:
- **Interactive Menus**: Navigation between different application views
- **Real-time Updates**: Dynamic display of monitoring data
- **Color-coded Output**: Visual status indicators and alerts
- **Input Handling**: User command processing and validation

**Console Management**:
```cpp
class ViewManager {
private:
    HANDLE hConsole;
    int currentView;
    bool shouldExit;
    
    void DisplayDashboard();
    void DisplayNetworkMonitor();
    void DisplayThreatProtection();
    void DisplayAIAssistant();
    
public:
    void Initialize();
    void RunMainLoop();
    void SetConsoleColor(int color);
};
```

#### 6. Utils (Support Functions)
**Purpose**: Provide common utility functions used across all components.

**Utility Categories**:
- **Configuration Management**: INI file parsing and settings management
- **Network Utilities**: IP validation, hostname resolution, network calculations
- **Console Utilities**: Text formatting, color management, input processing
- **System Information**: OS version detection, privilege checking
- **String Processing**: Text manipulation, encoding/decoding

### Data Flow Architecture

```
User Input → ViewManager → SecurityApp → Core Components
                                ↓
Windows APIs ← Component Logic ← Data Processing
                                ↓
AI Analysis ← GeminiClient ← Threat Assessment
                                ↓
Display Output ← ViewManager ← Results Aggregation
```

## 🌐 Web Interface Architecture

### Frontend Components (React/TypeScript)

#### 1. Application Structure
```typescript
App.tsx                 // Main application container
├── components/
│   ├── Dashboard.tsx   // System overview and metrics
│   ├── NetworkMonitor.tsx // Network activity visualization
│   ├── ThreatProtection.tsx // Security status and controls
│   ├── AIAssistant.tsx // Chat interface with AI
│   ├── Sidebar.tsx     // Navigation menu
│   ├── Header.tsx      // Application header
│   └── icon.tsx        // Icon components
├── services/
│   └── geminiService.ts // API integration service
└── types.ts            // TypeScript type definitions
```

#### 2. Component Architecture

**Dashboard Component**:
- Real-time metrics visualization
- Chart rendering with Recharts
- System status indicators
- Performance monitoring widgets

**NetworkMonitor Component**:
- Live connection table
- Traffic visualization
- Filtering and search capabilities
- Connection details modal

**ThreatProtection Component**:
- Security status dashboard
- Alert management interface
- Threat timeline visualization
- Configuration controls

**AIAssistant Component**:
- Chat interface with conversation history
- Real-time message streaming
- Context-aware suggestions
- Security-focused prompting

#### 3. State Management
```typescript
// Application state structure
interface AppState {
  currentView: View;
  systemMetrics: SystemMetrics;
  networkConnections: NetworkConnection[];
  threats: ThreatEvent[];
  aiMessages: ChatMessage[];
  configuration: AppConfig;
}
```

### Service Layer

#### Gemini Service Integration
```typescript
class GeminiService {
  private apiKey: string;
  private baseUrl: string;
  
  async sendMessage(message: string): Promise<string>;
  async streamResponse(message: string, 
                      onChunk: (chunk: string) => void): Promise<void>;
  private buildSecurityPrompt(userMessage: string): string;
}
```

## 🔄 Inter-Component Communication

### Event-Driven Architecture

Both implementations use event-driven patterns for component communication:

#### C++ Implementation
```cpp
// Event system for component communication
class EventManager {
    std::unordered_map<EventType, std::vector<EventCallback>> callbacks;
    
public:
    void Subscribe(EventType type, EventCallback callback);
    void Publish(EventType type, const EventData& data);
};

// Example events
enum class EventType {
    ThreatDetected,
    NetworkActivity,
    SystemAlert,
    ConfigurationChanged
};
```

#### React Implementation
```typescript
// Context-based state management
const SecurityContext = createContext<SecurityContextType>({
  state: initialState,
  dispatch: () => {},
});

// Custom hooks for component communication
export const useSecurityData = () => {
  const context = useContext(SecurityContext);
  return context;
};
```

## 🔒 Security Architecture

### Security Principles

1. **Defense in Depth**: Multiple security layers and validation points
2. **Principle of Least Privilege**: Minimal required permissions
3. **Data Minimization**: Only necessary data is processed or transmitted
4. **Secure by Default**: Safe default configurations

### Security Boundaries

```
┌─────────────────────────────────────────────────────────────┐
│                    Security Boundaries                      │
├─────────────────────────────────────────────────────────────┤
│  Local System Boundary                                     │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  Security Sentinel Application                      │   │
│  │  ├─ Process Monitoring (Admin Required)             │   │
│  │  ├─ Network Monitoring (Admin Required)             │   │
│  │  ├─ System APIs (Controlled Access)                 │   │
│  │  └─ Configuration Files (Local Storage)             │   │
│  └─────────────────────────────────────────────────────┘   │
├─────────────────────────────────────────────────────────────┤
│  Network Boundary                                          │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  External API Communication                         │   │
│  │  ├─ HTTPS to Gemini API (Encrypted)                 │   │
│  │  ├─ API Key Authentication (Secure)                 │   │
│  │  ├─ Request Validation (Input Sanitization)         │   │
│  │  └─ Response Filtering (Output Validation)          │   │
│  └─────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

## 📊 Performance Architecture

### Optimization Strategies

#### 1. Multi-threading Design
```cpp
// Asynchronous monitoring for performance
class SecurityApp {
private:
    std::thread securityThread;    // System monitoring
    std::thread networkThread;     // Network analysis
    std::thread uiThread;          // User interface
    std::thread aiThread;          // AI communication
    
    // Thread synchronization
    std::mutex dataMutex;
    std::condition_variable dataReady;
};
```

#### 2. Memory Management
- **RAII Patterns**: Automatic resource management
- **Smart Pointers**: Prevent memory leaks
- **Object Pooling**: Reduce allocation overhead
- **Lazy Loading**: Load data only when needed

#### 3. Caching Strategy
```cpp
class DataCache {
private:
    std::unordered_map<std::string, CacheEntry> cache;
    std::chrono::seconds ttl;
    
public:
    template<typename T>
    std::optional<T> Get(const std::string& key);
    
    template<typename T>
    void Set(const std::string& key, const T& value);
};
```

## 🔧 Configuration Architecture

### Hierarchical Configuration System

```ini
# config.ini - Hierarchical configuration
[gemini]
api_key=API_KEY_HERE
model=gemini-2.5-flash
max_tokens=1000
temperature=0.7

[monitoring]
enabled=true
update_interval=5
log_level=INFO
max_events=10000

[network]
monitor_enabled=true
block_suspicious=true
whitelist_ips=192.168.1.0/24,10.0.0.0/8
scan_detection_threshold=5
ddos_detection_threshold=100

[ui]
color_scheme=dark
refresh_rate=1000
show_advanced=false
```

### Configuration Management
```cpp
class ConfigManager {
private:
    std::unordered_map<std::string, std::string> settings;
    std::string configFile;
    
public:
    bool LoadConfiguration(const std::string& filename);
    template<typename T>
    T GetValue(const std::string& section, const std::string& key);
    void SetValue(const std::string& section, const std::string& key, 
                  const std::string& value);
    bool SaveConfiguration();
};
```

## 🚀 Deployment Architecture

### Distribution Models

#### 1. Standalone Executable
- Single executable with embedded resources
- Minimal dependencies (Windows APIs only)
- Self-contained configuration
- Portable installation

#### 2. Web Application
- Node.js development environment
- Vite build system for production
- Static file deployment capability
- Progressive Web App features

### Installation Patterns

```
Security Sentinel Installation
├── SecuritySentinel.exe      # Main C++ application
├── config.ini               # Configuration file
├── logs/                    # Log directory
│   └── security_sentinel.log
├── docs/                    # Documentation
│   ├── README.md
│   └── wiki/
├── web/                     # Web interface (optional)
│   ├── dist/               # Built web files
│   └── node_modules/       # Dependencies
└── uninstall.exe           # Uninstaller
```

## 📈 Scalability Considerations

### Horizontal Scaling
- **Multi-instance Support**: Run multiple monitoring instances
- **Distributed Monitoring**: Network-based monitoring across systems
- **Central Management**: Aggregated reporting and control

### Vertical Scaling
- **Resource Optimization**: Efficient memory and CPU usage
- **Adaptive Monitoring**: Adjust monitoring frequency based on load
- **Intelligent Caching**: Reduce redundant operations

### Future Architecture Extensions
- **Plugin System**: Modular extension capabilities
- **Database Integration**: Persistent data storage
- **API Gateway**: RESTful API for external integration
- **Microservices**: Service-oriented architecture components

---

This architecture provides a solid foundation for secure, efficient, and scalable security monitoring while maintaining simplicity and ease of use for end users.

**Next**: [Development Setup](Development-Setup.md) | [API Reference](API-Reference.md) | [Performance Optimization](Performance-Optimization.md)