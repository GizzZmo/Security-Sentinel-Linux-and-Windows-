cmake_minimum_required(VERSION 3.16)
project(SecuritySentinel VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Include directories
include_directories(src)
include_directories(include)

# Add executable
add_executable(SecuritySentinel
    src/main.cpp
    src/SecurityApp.cpp
    src/GeminiClient.cpp
    src/ViewManager.cpp
    src/SecurityMonitor.cpp
    src/NetworkMonitor.cpp
    src/Utils.cpp
)

# Link libraries
target_link_libraries(SecuritySentinel 
    Threads::Threads
)

# Windows-specific libraries
if(WIN32)
    target_link_libraries(SecuritySentinel 
        ws2_32 
        wininet
        iphlpapi
        psapi
    )
endif()

# Set output directory
set_target_properties(SecuritySentinel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Enable modern C++ features
target_compile_features(SecuritySentinel PRIVATE cxx_std_17)

# Add compile definitions
target_compile_definitions(SecuritySentinel PRIVATE
    _WIN32_WINNT=0x0A00  # Windows 10+
    UNICODE
    _UNICODE
)