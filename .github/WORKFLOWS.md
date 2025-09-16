
# GitHub Actions Workflows

This repository includes a comprehensive GitHub Actions workflow system that ensures code quality, security, and reliable builds.

## 🔄 Available Workflows

### CI/CD Pipeline (`ci.yml`)
**Trigger**: Push to main/develop, Pull Requests
- ✅ Web interface build and type checking
- ✅ Windows C++ application build
- ✅ Linux compatibility check
- ✅ Code quality checks
- ✅ Documentation validation
- ✅ Integration testing

### Release (`release.yml`)
**Trigger**: Git tags (v*.*.*), Manual dispatch
- 📦 Builds release artifacts for Windows and Web
- 🚀 Creates GitHub releases with downloadable assets
- 📋 Auto-generates release notes

### Code Quality & Security (`code-quality.yml`)
**Trigger**: Push, Pull Requests, Weekly schedule
- 🔍 CodeQL security analysis
- 🛡️ Dependency vulnerability scanning
- 📜 License compliance checking
- 🎨 Code style validation
- 📊 Bundle size analysis

### Documentation (`docs.yml`)
**Trigger**: Changes to .md files, wiki/, docs/
- 📝 Markdown linting and link checking
- 📊 Documentation metrics and coverage
- 🔤 Spell checking with custom dictionary
- 📚 Auto-generated documentation index

### Pull Request Automation (`pr-automation.yml`)
**Trigger**: PR events, Issue comments
- 🏷️ Auto-labeling based on changed files
- 📏 PR size checking and warnings
- 🤖 Comment commands (`/ready`, `/help`)
- ✅ PR requirement validation

### Workflow Testing (`workflow-test.yml`)
**Trigger**: Changes to workflow files
- ✅ YAML syntax validation
- 🧪 Cross-platform compatibility testing
- 🔧 Workflow dependency verification
- 🚀 Execution simulation

## 🎯 Workflow Features

### Automated Labeling
PRs are automatically labeled based on changed files:
- `documentation` - Markdown file changes
- `web-interface` - TypeScript/React changes
- `cpp-application` - C++ source changes
- `dependencies` - Package file changes
- `ci/cd` - Workflow changes
- `size/small|medium|large` - Based on PR size

### Security & Quality
- **CodeQL Analysis**: Automated security vulnerability detection
- **Dependency Scanning**: Weekly checks for package vulnerabilities
- **License Compliance**: Ensures only approved licenses are used
- **Code Style**: TypeScript and markdown formatting checks

### Cross-Platform Support
- **Windows**: Full C++ application build with MSVC
- **Linux**: Compatibility checking and web interface builds
- **macOS**: Node.js workflow testing

### Release Automation
- **Tagged Releases**: Automatic builds for version tags
- **Asset Generation**: Windows executables and web bundles
- **Release Notes**: Auto-generated from commits and PRs

## 🔧 Configuration

### Required Secrets
The workflows use these repository secrets:
- `GITHUB_TOKEN` - Automatically provided by GitHub

### Optional Configuration
- **Dependabot**: Automated dependency updates (configured in `.github/dependabot.yml`)
- **Branch Protection**: Recommended to require CI checks before merging

### Environment Variables
- Workflows are designed to work without additional environment variables
- API keys and sensitive data should be stored in repository secrets

## 📋 Workflow Status

All workflows are designed to:
- ✅ **Run without failure** on the main branch
- ⚠️ **Provide warnings** instead of errors where appropriate
- 🔄 **Handle cross-platform differences** gracefully
- 📊 **Generate useful reports** and metrics
- 🛡️ **Maintain security** best practices

## 🚀 Usage

### Triggering Workflows

**Automatic Triggers:**
- Push to `main` or `develop` → Runs CI/CD pipeline
- Create PR → Runs CI/CD + PR automation
- Push git tag `v*.*.*` → Creates release
- Edit documentation → Runs docs workflow
- Weekly schedule → Runs security scans

**Manual Triggers:**
```bash
# Go to repository → Actions → Select workflow → Run workflow
```

### PR Commands
Comment on PRs to trigger automation:
```
/ready     # Mark PR as ready for review
/help      # Show available commands
```

### Creating Releases
```bash
git tag v1.0.0
git push origin v1.0.0
# Release workflow automatically creates GitHub release
```

## 📞 Troubleshooting

### Common Issues

**Build Failures:**
- Check the CI workflow logs for specific error messages
- Windows builds require MSVC toolchain
- Web builds require Node.js 18+

**Permission Errors:**
- Ensure `GITHUB_TOKEN` has required permissions
- Some workflows need `contents: write` for releases

**Workflow Not Triggering:**
- Check trigger conditions in workflow files
- Verify file paths match the `paths` filters
- Ensure branch names match the configuration

### Getting Help

1. Check workflow logs in the Actions tab
2. Review this documentation
3. Create an issue with the `ci/cd` label
4. Use `/help` command in PR comments

---

*For more information about GitHub Actions, see the [official documentation](https://docs.github.com/en/actions).*
=======
# 🚀 GitHub Workflow System Documentation

This repository includes a comprehensive GitHub Actions workflow system that provides automated CI/CD, security scanning, code quality checks, and deployment capabilities.

## 📋 Workflow Overview

| Workflow | Trigger | Purpose | Status |
|----------|---------|---------|--------|
| 🌐 [Web Interface CI](.github/workflows/ci-web.yml) | Push/PR to main/develop | Build and test React web interface | [![🌐 Web Interface CI](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/ci-web.yml/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/ci-web.yml) |
| 🔨 [C++ Build CI](.github/workflows/ci-cpp.yml) | Push/PR to main/develop | Build and test C++ native application | [![🔨 C++ Build CI](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/ci-cpp.yml/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/ci-cpp.yml) |
| 🔐 [Security Scanning](.github/workflows/security.yml) | Push/PR + Weekly | Comprehensive security analysis | [![🔐 Security Scanning](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/security.yml/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/security.yml) |
| 🧹 [Code Quality](.github/workflows/code-quality.yml) | Push/PR + Weekly | Code quality and linting checks | [![🧹 Code Quality](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/code-quality.yml/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/code-quality.yml) |
| 🔍 [PR Validation](.github/workflows/pr-validation.yml) | Pull Requests | Validate PR title, changes, and requirements | Manual trigger |
| 🚀 [Release](.github/workflows/release.yml) | Git Tags | Automated release builds and publishing | Manual trigger |
| 🌐 [Deploy to GitHub Pages](.github/workflows/deploy-pages.yml) | Push to main | Deploy web interface to GitHub Pages | [![🌐 Deploy to GitHub Pages](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/deploy-pages.yml/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions/workflows/deploy-pages.yml) |

## 🌐 Web Interface CI (`ci-web.yml`)

### **Purpose**
Builds and tests the React TypeScript web interface across multiple Node.js versions.

### **Triggers**
- Push to `main`/`develop` branches (web-related files)
- Pull requests to `main`/`develop` branches (web-related files)

### **Jobs**
1. **Build & Test** - Multi-version Node.js builds (18.x, 20.x)
2. **Lint** - ESLint and Prettier code quality checks
3. **Security Scan** - npm audit for dependency vulnerabilities

### **Artifacts**
- Web build artifacts (7-day retention)
- ESLint reports (30-day retention)

## 🔨 C++ Build CI (`ci-cpp.yml`)

### **Purpose**
Builds the native C++ application using MSVC on Windows with static analysis.

### **Triggers**
- Push to `main`/`develop` branches (C++ files)
- Pull requests to `main`/`develop` branches (C++ files)

### **Jobs**
1. **Windows Build** - Debug and Release builds with MSVC
2. **Static Analysis** - MSVC static code analysis
3. **Security Check** - Semgrep security scanning for C++

### **Features**
- CMake-based build system
- Multi-configuration builds (Debug/Release)
- Executable validation
- SARIF security reports

### **Artifacts**
- C++ build artifacts (7-day retention)
- SARIF security reports

## 🔐 Security Scanning (`security.yml`)

### **Purpose**
Comprehensive security analysis including dependency scanning, code analysis, and secret detection.

### **Triggers**
- Push to `main`/`develop` branches
- Pull requests to `main`/`develop` branches
- Weekly schedule (Sundays at 2 AM UTC)

### **Jobs**
1. **Dependency Scan** - npm audit with detailed reporting
2. **CodeQL Analysis** - GitHub's semantic code analysis (JavaScript & C++)
3. **Secret Scan** - GitLeaks and TruffleHog for secrets detection
4. **License Scan** - License compliance checking
5. **Security Summary** - Consolidated security report

### **Features**
- SARIF integration for GitHub Security tab
- Detailed vulnerability reporting
- License compliance tracking
- Secret detection with verification

### **Artifacts**
- Security audit reports (30-day retention)
- License reports (30-day retention)

## 🧹 Code Quality (`code-quality.yml`)

### **Purpose**
Automated code quality checks and style enforcement across all languages.

### **Triggers**
- Push to `main`/`develop` branches
- Pull requests to `main`/`develop` branches
- Weekly schedule (Mondays at 9 AM UTC)

### **Jobs**
1. **ESLint** - JavaScript/TypeScript linting with auto-configuration
2. **Prettier** - Code formatting validation with auto-configuration
3. **C++ Lint** - clang-format and cppcheck analysis
4. **Documentation Check** - Documentation quality and completeness
5. **Dependency Analysis** - Dependency health and bundle size analysis

### **Features**
- Auto-generates linter configs if missing
- Bundle size monitoring
- Documentation completeness checking
- Outdated dependency detection

### **Artifacts**
- ESLint reports (30-day retention)

## 🔍 PR Validation (`pr-validation.yml`)

### **Purpose**
Validates pull request quality, titles, and change safety.

### **Triggers**
- Pull request events (opened, synchronized, reopened, ready_for_review)

### **Jobs**
1. **PR Information** - Analyzes changed files and statistics
2. **Title Validation** - Ensures descriptive PR titles
3. **Branch Protection** - Validates main branch targeting
4. **Change Validation** - Checks for sensitive files and development comments
5. **Dependency Changes** - Reviews package.json modifications
6. **PR Summary** - Consolidated validation report

### **Features**
- Conventional commit format validation
- Sensitive file detection
- TODO/FIXME comment tracking
- Dependency change analysis

## 🚀 Release (`release.yml`)

### **Purpose**
Automated release builds and publishing for both C++ and web applications.

### **Triggers**
- Git tags matching `v*.*.*`
- Manual workflow dispatch

### **Jobs**
1. **Create Release** - Generates release notes and creates GitHub release
2. **C++ Build** - Windows x64 release build with packaging
3. **Web Build** - Production web build with deployment instructions
4. **Publish Summary** - Release deployment report

### **Features**
- Automatic changelog generation
- Multi-platform build artifacts
- Sample configuration files
- Pre-release detection (alpha/beta/rc)

### **Artifacts**
- `SecuritySentinel-Windows-x64.zip` - Native Windows application
- `SecuritySentinel-Web.tar.gz` - Web interface deployment package

## 🌐 Deploy to GitHub Pages (`deploy-pages.yml`)

### **Purpose**
Deploys the web interface to GitHub Pages for live demonstration.

### **Triggers**
- Push to `main` branch (web-related files)
- Manual workflow dispatch

### **Jobs**
1. **Build** - Production build with GitHub Pages configuration
2. **Deploy** - Deploys to GitHub Pages environment

### **Features**
- GitHub Pages base path configuration
- Deployment metadata injection
- Live demo accessibility
- Privacy-focused deployment

### **Environment**
- **URL**: `https://gizzmo.github.io/security-sentinel-for-windows-11/`
- **Environment**: `github-pages`

## 🔧 Configuration and Customization

### **Environment Variables**
Set these in your repository settings under "Settings > Secrets and variables > Actions":

| Variable | Purpose | Required |
|----------|---------|----------|
| `SEMGREP_APP_TOKEN` | Semgrep security scanning | Optional |
| `GEMINI_API_KEY` | For web interface testing | Optional |

### **Branch Protection**
Recommended branch protection rules for `main`:
- Require status checks to pass before merging
- Require up-to-date branches before merging
- Required status checks:
  - `🔨 Build & Test Web Interface`
  - `🔨 Build Windows (MSVC)`
  - `🔐 Security Scanning`

### **Workflow Permissions**
The workflows require these permissions:
- `contents: read` - Repository access
- `security-events: write` - SARIF upload
- `pages: write` - GitHub Pages deployment
- `id-token: write` - GitHub Pages deployment

## 📊 Monitoring and Maintenance

### **Status Dashboard**
Monitor all workflows from the main README.md badges or the [Actions tab](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions).

### **Scheduled Maintenance**
- **Security scans**: Weekly (Sundays 2 AM UTC)
- **Code quality**: Weekly (Mondays 9 AM UTC)
- **Dependency updates**: Manual via Dependabot (recommended)

### **Troubleshooting**
Common issues and solutions:

1. **Build Failures**
   - Check Node.js version compatibility
   - Verify CMake and MSVC installation
   - Review dependency versions

2. **Security Alerts**
   - Review Security tab for detailed findings
   - Check SARIF uploads in workflow logs
   - Update dependencies for vulnerability fixes

3. **Deployment Issues**
   - Verify GitHub Pages is enabled
   - Check repository permissions
   - Review build artifacts

## 🤝 Contributing to Workflows

### **Adding New Workflows**
1. Create workflow files in `.github/workflows/`
2. Follow naming convention: `action-name.yml`
3. Add appropriate badges to README.md
4. Update this documentation

### **Workflow Standards**
- Use emojis in workflow and job names for visual clarity
- Include comprehensive step summaries
- Add appropriate error handling and continue-on-error where needed
- Upload relevant artifacts with appropriate retention periods

### **Testing Workflows**
- Test changes in feature branches
- Use `workflow_dispatch` for manual testing
- Monitor workflow runs in the Actions tab
- Review step summaries and artifacts

## 📚 Additional Resources

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Workflow Syntax](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions)
- [SARIF Upload](https://docs.github.com/en/code-security/code-scanning/integrating-with-code-scanning/uploading-a-sarif-file-to-github)
- [GitHub Pages](https://docs.github.com/en/pages)

---

*This workflow system provides enterprise-grade CI/CD capabilities for the Security Sentinel project, ensuring code quality, security, and reliable deployments across all platforms.*
