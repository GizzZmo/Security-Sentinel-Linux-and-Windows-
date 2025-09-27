#!/bin/bash

# Build script for Security Sentinel C++ application
# This script builds the SecuritySentinel executable using CMake

set -e

echo "🔨 Building Security Sentinel C++ Application"
echo "=============================================="
echo ""

# Check if we're in the right directory
if [ ! -f "CMakeLists.txt" ]; then
    echo "❌ Error: Run this script from the project root directory"
    exit 1
fi

# Create build directory
echo "📁 Creating build directory..."
mkdir -p build
cd build

# Configure with CMake
echo "⚙️  Configuring build with CMake..."
cmake ..

# Build the application
echo "🔨 Building application..."
make -j$(nproc)

# Check if build was successful
if [ -f "bin/SecuritySentinel" ]; then
    echo ""
    echo "✅ Build successful!"
    echo "📍 Executable location: build/bin/SecuritySentinel"
    echo "📊 Executable size: $(du -h bin/SecuritySentinel | cut -f1)"
    echo ""
    echo "To run the application:"
    echo "  cd build && ./bin/SecuritySentinel"
    echo ""
    echo "Or copy to project root:"
    echo "  cp build/bin/SecuritySentinel ./"
else
    echo "❌ Build failed!"
    exit 1
fi