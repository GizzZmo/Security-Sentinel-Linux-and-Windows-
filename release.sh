#!/bin/bash

# Release Script for Security Sentinel v1.1.0
# This script prepares everything needed for the release

set -e

echo "🚀 Security Sentinel Release Script"
echo "=================================="
echo ""

# Check if we're in the right directory
if [ ! -f "CMakeLists.txt" ] || [ ! -f "package.json" ]; then
    echo "❌ Error: Run this script from the project root directory"
    exit 1
fi

echo "📋 Current Status:"
echo "- CMake version: $(grep "VERSION" CMakeLists.txt | head -n1)"
echo "- Package version: $(grep "version" package.json | head -n1)"
echo ""

# Test builds
echo "🔨 Testing builds..."
echo ""

# Test C++ build
echo "Testing C++ build..."
if [ -d "build" ]; then
    rm -rf build
fi
mkdir build
cd build
cmake .. > /dev/null 2>&1
make -j$(nproc) > /dev/null 2>&1
if [ -f "bin/SecuritySentinel" ]; then
    echo "✅ C++ build successful ($(du -h bin/SecuritySentinel | cut -f1))"
else
    echo "❌ C++ build failed"
    exit 1
fi
cd ..

# Test web build
echo "Testing web build..."
npm run build > /dev/null 2>&1
if [ -d "dist" ] && [ -f "dist/index.html" ]; then
    echo "✅ Web build successful ($(du -sh dist | cut -f1))"
else
    echo "❌ Web build failed"
    exit 1
fi

echo ""
echo "🎯 Release Ready!"
echo "================"
echo ""
echo "To create the release:"
echo "1. Create and push tag: git tag v1.1.0 && git push origin v1.1.0"
echo "2. Or manually trigger via GitHub Actions:"
echo "   https://github.com/GizzZmo/Security-Sentinel-Linux-and-Windows-/actions"
echo ""
echo "Expected artifacts:"
echo "- security-sentinel-windows-v1.1.0.zip"
echo "- security-sentinel-web-v1.1.0.tar.gz"
echo ""
echo "✨ All systems ready for release v1.1.0!"