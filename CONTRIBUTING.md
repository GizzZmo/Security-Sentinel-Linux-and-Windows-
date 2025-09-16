# Contributing Guidelines

Thank you for your interest in contributing to Security Sentinel for Windows 11! This document outlines how you can help improve the project.

## 🤝 Ways to Contribute

### 🐛 Bug Reports
- Found an issue? [Create a bug report](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues/new?template=bug_report.md)
- Include detailed steps to reproduce
- Provide system information and logs
- Test on a clean environment if possible

### 💡 Feature Requests
- Have an idea? [Submit a feature request](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues/new?template=feature_request.md)
- Explain the use case and benefits
- Consider implementation complexity
- Be open to alternative solutions

### 📝 Documentation
- Improve existing documentation
- Add missing guides or tutorials
- Fix typos and grammatical errors
- Translate documentation to other languages

### 🔧 Code Contributions
- Fix bugs and implement features
- Improve performance and security
- Add tests and improve code coverage
- Enhance user interface and experience

## 🚀 Getting Started

### Development Environment Setup

#### Prerequisites
- **Windows 11** (for full testing)
- **Visual Studio 2019/2022** with C++ development tools
- **Node.js 18+** for web interface
- **CMake 3.16+**
- **Git** for version control

#### C++ Development Setup
```bash
# Clone the repository
git clone https://github.com/GizzZmo/security-sentinel-for-windows-11.git
cd security-sentinel-for-windows-11

# Create build directory
mkdir build && cd build

# Generate build files (Visual Studio)
cmake .. -G "Visual Studio 17 2022" -A x64

# Build debug version
cmake --build . --config Debug

# Build release version  
cmake --build . --config Release
```

#### Web Interface Development Setup
```bash
# Install dependencies
npm install

# Start development server
npm run dev

# Build for production
npm run build
```

#### API Key Setup
```ini
# Create config.ini for C++ application
[gemini]
api_key=your_development_api_key_here
model=gemini-2.5-flash

# Create .env.local for web interface
GEMINI_API_KEY=your_development_api_key_here
```

## 📋 Development Guidelines

### Code Style

#### C++ Code Style
```cpp
// Use modern C++17 features
// Use RAII patterns and smart pointers
// Follow Google C++ Style Guide basics

class ExampleClass {
private:
    std::unique_ptr<Component> component_;
    std::string member_variable_;
    
public:
    ExampleClass() = default;
    ~ExampleClass() = default;
    
    // Use descriptive function names
    bool InitializeComponent();
    void ProcessSecurityEvent(const SecurityEvent& event);
    
    // Const correctness
    std::string GetComponentName() const;
};

// Use namespaces appropriately
namespace security_sentinel {
namespace utils {
    bool ValidateIPAddress(const std::string& ip);
}
}
```

#### TypeScript/React Code Style
```typescript
// Use TypeScript for type safety
interface SecurityMetrics {
  cpuUsage: number;
  memoryUsage: number;
  threatLevel: ThreatLevel;
  timestamp: Date;
}

// Use functional components with hooks
const Dashboard: React.FC = () => {
  const [metrics, setMetrics] = useState<SecurityMetrics | null>(null);
  
  useEffect(() => {
    const fetchMetrics = async () => {
      // Implementation
    };
    
    fetchMetrics();
  }, []);
  
  return (
    <div className="dashboard">
      {/* Component JSX */}
    </div>
  );
};
```

### Documentation Standards

#### Code Comments
```cpp
/**
 * @brief Monitors network connections for suspicious activity
 * 
 * This class provides real-time monitoring of TCP/UDP connections,
 * analyzes traffic patterns for threats, and automatically blocks
 * suspicious IP addresses.
 * 
 * @note Requires administrator privileges for full functionality
 */
class NetworkMonitor {
private:
    // Connection tracking data
    std::vector<ConnectionInfo> active_connections_;
    
public:
    /**
     * @brief Starts network monitoring in a separate thread
     * @return true if monitoring started successfully, false otherwise
     * @throws SecurityException if insufficient privileges
     */
    bool StartMonitoring();
};
```

#### README and Wiki Updates
- Use clear, descriptive headings
- Include code examples for complex features
- Add screenshots for UI changes
- Keep language simple and accessible
- Update related documentation when making changes

### Commit Message Guidelines

Follow conventional commit format:

```bash
# Format: type(scope): description

# Examples:
feat(network): add DDoS detection algorithm
fix(ai): resolve API timeout issues  
docs(wiki): update installation guide
refactor(security): improve threat scoring logic
test(network): add unit tests for port scanning
style(ui): fix console color formatting
perf(monitor): optimize process enumeration
```

#### Commit Types
- `feat`: New features
- `fix`: Bug fixes
- `docs`: Documentation changes
- `style`: Code style/formatting
- `refactor`: Code restructuring
- `test`: Adding/updating tests
- `perf`: Performance improvements
- `build`: Build system changes
- `ci`: CI/CD changes

## 🧪 Testing Guidelines

### Testing Strategy
- **Unit Tests**: Test individual components in isolation
- **Integration Tests**: Test component interactions
- **System Tests**: Test full application functionality
- **Security Tests**: Verify security features work correctly

### C++ Testing
```cpp
// Use Google Test framework (when available)
#include <gtest/gtest.h>

TEST(NetworkMonitorTest, DetectsPortScan) {
    NetworkMonitor monitor;
    
    // Simulate port scan activity
    monitor.SimulateConnections({
        {"192.168.1.100", "80"},
        {"192.168.1.100", "443"},
        {"192.168.1.100", "22"},
        {"192.168.1.100", "8080"},
        {"192.168.1.100", "3389"}
    });
    
    // Verify port scan detection
    auto threats = monitor.GetDetectedThreats();
    ASSERT_FALSE(threats.empty());
    EXPECT_EQ(threats[0].threatType, "Port Scan");
}
```

### Web Interface Testing
```typescript
// Use Jest and React Testing Library
import { render, screen, fireEvent } from '@testing-library/react';
import { Dashboard } from './Dashboard';

describe('Dashboard Component', () => {
  test('displays system metrics correctly', () => {
    const mockMetrics = {
      cpuUsage: 25.5,
      memoryUsage: 60.2,
      threatLevel: ThreatLevel.Low,
      timestamp: new Date()
    };
    
    render(<Dashboard metrics={mockMetrics} />);
    
    expect(screen.getByText('25.5%')).toBeInTheDocument();
    expect(screen.getByText('60.2%')).toBeInTheDocument();
  });
});
```

### Manual Testing Checklist

Before submitting a pull request:

- [ ] **C++ Application**
  - [ ] Builds successfully in Debug and Release
  - [ ] Runs without crashes as Administrator
  - [ ] All menu options work correctly
  - [ ] Network monitoring displays connections
  - [ ] AI assistant responds to queries
  - [ ] Configuration loads properly

- [ ] **Web Interface**
  - [ ] Builds without errors or warnings
  - [ ] All components render correctly
  - [ ] Navigation works properly
  - [ ] AI chat functionality works
  - [ ] Responsive design on different screen sizes

- [ ] **Cross-Platform**
  - [ ] Documentation is accurate
  - [ ] Installation instructions work
  - [ ] API integration functions correctly

## 🔄 Pull Request Process

### Before Submitting

1. **Test Thoroughly**: Ensure your changes work as expected
2. **Update Documentation**: Update relevant docs and comments
3. **Check Code Style**: Follow the established coding standards
4. **Run Builds**: Verify both Debug and Release builds work
5. **Test on Clean System**: Test on a fresh Windows 11 installation if possible

### Pull Request Template

```markdown
## Description
Brief description of changes made.

## Type of Change
- [ ] Bug fix (non-breaking change that fixes an issue)
- [ ] New feature (non-breaking change that adds functionality)
- [ ] Breaking change (fix or feature that changes existing functionality)
- [ ] Documentation update
- [ ] Performance improvement
- [ ] Code refactoring

## Testing
- [ ] Unit tests pass
- [ ] Integration tests pass
- [ ] Manual testing completed
- [ ] Tested on Windows 11

## Checklist
- [ ] Code follows project style guidelines
- [ ] Self-review of code completed
- [ ] Documentation updated where necessary
- [ ] No new warnings introduced
- [ ] Related issues linked

## Screenshots (if applicable)
Add screenshots to help explain your changes.

## Additional Notes
Any additional information about the changes.
```

### Review Process

1. **Automated Checks**: GitHub Actions will run automated tests
2. **Code Review**: Project maintainers will review your code
3. **Feedback**: Address any feedback or requested changes
4. **Approval**: Once approved, your PR will be merged

## 🔒 Security Considerations

### Security-First Development

- **Input Validation**: Always validate user inputs
- **Error Handling**: Don't expose sensitive information in errors
- **Privilege Separation**: Use minimum required privileges
- **Secure Defaults**: Default to secure configurations

### Reporting Security Issues

**⚠️ DO NOT** report security vulnerabilities in public issues.

Instead:
1. Email security concerns privately to project maintainers
2. Provide detailed information about the vulnerability
3. Allow time for the issue to be patched before disclosure
4. Follow responsible disclosure practices

### Security Review Process

Security-sensitive changes require additional review:
- Authentication and authorization code
- Network communication protocols
- Data encryption and storage
- Windows API security interactions
- Input validation and sanitization

## 📊 Performance Considerations

### Performance Guidelines

- **Memory Management**: Use RAII and smart pointers in C++
- **Thread Safety**: Ensure thread-safe operations
- **Resource Usage**: Minimize CPU and memory impact
- **Responsiveness**: Keep UI responsive during operations

### Performance Testing

- Monitor CPU and memory usage during development
- Test with high load (many processes/connections)
- Measure startup and response times
- Profile critical code paths

## 🌍 Community Guidelines

### Code of Conduct

- **Be Respectful**: Treat all contributors with respect
- **Be Constructive**: Provide helpful feedback and suggestions
- **Be Patient**: Understand that review and implementation take time
- **Be Collaborative**: Work together toward common goals

### Communication

- **Issues**: Use GitHub issues for bug reports and feature requests
- **Discussions**: Use GitHub discussions for questions and ideas
- **Pull Requests**: Use PR comments for code-specific discussions
- **Email**: Use email only for security issues

## 🎯 Contribution Ideas

### Good First Issues

Perfect for new contributors:
- Documentation improvements
- UI/UX enhancements
- Unit test additions
- Bug fixes in non-critical areas
- Code style improvements

### Advanced Contributions

For experienced developers:
- Performance optimizations
- New security monitoring features
- AI integration improvements
- Cross-platform compatibility
- Advanced threat detection algorithms

### Ongoing Needs

Always looking for help with:
- Documentation translation
- Testing on different configurations
- UI/UX design improvements
- Performance optimization
- Security auditing

## 📝 Recognition

### Contributors

All contributors are recognized in:
- Project README contributors section
- Release notes for significant contributions
- Special recognition for major features

### Maintainer Path

Consistent, high-quality contributors may be invited to become maintainers with:
- Write access to the repository
- Ability to review and merge pull requests
- Input on project direction and roadmap

---

Thank you for contributing to Security Sentinel! Your efforts help make Windows 11 security monitoring accessible to everyone.

**Questions?** Feel free to ask in [GitHub Discussions](https://github.com/GizzZmo/security-sentinel-for-windows-11/discussions) or create an issue.

**Ready to contribute?** Check out our [good first issues](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22) or [help wanted](https://github.com/GizzZmo/security-sentinel-for-windows-11/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22) labels!