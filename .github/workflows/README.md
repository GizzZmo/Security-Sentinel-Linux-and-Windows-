# GitHub Workflows for Security Sentinel

This directory contains GitHub Actions workflows for automated CI/CD of the Security Sentinel project.

## Workflows Overview

### 1. **Main CI Workflow** (`ci.yml`)
**Comprehensive multi-platform build and integration testing**

- **Triggers**: Push and PR to `main`/`develop` branches
- **Components**:
  - **Web Interface**: Build and test React/TypeScript app on Ubuntu with Node.js 18.x & 20.x
  - **Native Application**: Build C++ app on Windows with MSVC in Debug & Release modes
  - **Integration Check**: Verify both components work together
  - **Build Summary**: Overall status reporting

### 2. **Web Interface CI** (`web-interface.yml`)
**Focused on React/TypeScript web application**

- **Triggers**: Changes to web-related files
- **Actions**: TypeScript compilation, linting, building, artifact upload
- **Platforms**: Ubuntu with Node.js 18.x & 20.x

### 3. **C++ Native CI** (`cpp-native.yml`)
**Focused on Windows native application**

- **Triggers**: Changes to C++ source files
- **Actions**: CMake configuration, MSVC build, executable verification
- **Platforms**: Windows with Visual Studio 2022

### 4. **Pull Request Checks** (`pr-checks.yml`)
**Fast validation for pull requests**

- **Triggers**: PR opened/updated
- **Actions**: Quick TypeScript check and build verification
- **Purpose**: Fast feedback for contributors

## Build Matrix

| Component | Platform | Versions | Build Types |
|-----------|----------|----------|-------------|
| Web Interface | Ubuntu | Node.js 18.x, 20.x | Production |
| Native App | Windows | MSVC 2022 | Debug, Release |

## Artifacts

The workflows generate build artifacts that are stored for 30 days:

- **web-interface-dist**: Built React application (dist/)
- **native-application-windows-latest**: Built C++ executable and dependencies

## Status Badges

Add these to your README.md:

```markdown
[![CI](https://github.com/GizzZmo/security-sentinel-for-windows-11/workflows/Security%20Sentinel%20CI/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions)
[![Web Interface](https://github.com/GizzZmo/security-sentinel-for-windows-11/workflows/Web%20Interface%20CI/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions)
[![C++ Native](https://github.com/GizzZmo/security-sentinel-for-windows-11/workflows/C%2B%2B%20Native%20Application%20CI/badge.svg)](https://github.com/GizzZmo/security-sentinel-for-windows-11/actions)
```

## Local Development

To run the same checks locally:

```bash
# Web Interface
npm ci
npm run lint     # TypeScript compilation check
npm run build    # Production build

# C++ Native (Windows only)
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## Troubleshooting

### Common Issues

1. **TypeScript Errors**: Ensure `@types/react` and `@types/react-dom` are installed
2. **Build Failures**: Check that all dependencies are properly listed in package.json
3. **C++ Build Issues**: Verify Windows SDK and MSVC are available in the runner

### Workflow Failures

- Check the Actions tab in GitHub for detailed logs
- Artifact downloads are available for 30 days after build
- Failed builds will show specific error messages in the workflow logs

## Customization

### Adding New Checks

To add new validation steps:

1. Edit the appropriate workflow file
2. Add new steps to existing jobs or create new jobs
3. Update this README with changes

### Changing Triggers

Modify the `on:` section in workflow files to change when they run:

```yaml
on:
  push:
    branches: [ main, develop, feature/* ]
    paths: [ 'src/**', 'package.json' ]
```

## Maintenance

- Review workflow runs regularly
- Update Node.js versions as needed
- Keep actions versions current (monthly check recommended)
- Monitor artifact storage usage