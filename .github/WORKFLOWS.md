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