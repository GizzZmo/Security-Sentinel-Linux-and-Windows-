#include "GeminiClient.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <future>
#include <thread>
#include <regex>

#ifdef _WIN32
#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
#endif

GeminiClient::GeminiClient() 
    : model_("gemini-2.5-flash")
    , baseUrl_("https://generativelanguage.googleapis.com/v1beta/models/") {
}

GeminiClient::~GeminiClient() {
}

bool GeminiClient::SetApiKey(const std::string& apiKey) {
    if (apiKey.empty() || !Utils::ValidateApiKey(apiKey)) {
        lastError_ = "Invalid API key format";
        return false;
    }
    
    apiKey_ = apiKey;
    return true;
}

void GeminiClient::SetModel(const std::string& model) {
    model_ = model;
}

void GeminiClient::SetSystemInstruction(const std::string& instruction) {
    systemInstruction_ = instruction;
}

std::future<bool> GeminiClient::SendMessageAsync(
    const std::vector<ChatMessage>& history,
    const std::string& message,
    StreamCallback onChunk,
    ErrorCallback onError) {
    
    return std::async(std::launch::async, [this, history, message, onChunk, onError]() -> bool {
        try {
            if (!IsConfigured()) {
                if (onError) onError("Gemini client not properly configured");
                return false;
            }

            // Format request
            std::string requestData = FormatChatRequest(history, message);
            
            // Prepare headers
            std::map<std::string, std::string> headers;
            headers["Content-Type"] = "application/json";
            headers["x-goog-api-key"] = apiKey_;
            
            // Build URL
            std::string url = baseUrl_ + model_ + ":streamGenerateContent";
            
            // Perform request
            std::string response = PerformHttpRequest(url, requestData, headers);
            
            if (response.empty()) {
                if (onError) onError("No response from Gemini API");
                return false;
            }

            // Parse streaming response
            return ParseStreamResponse(response, onChunk, onError);
        }
        catch (const std::exception& e) {
            lastError_ = std::string("Request failed: ") + e.what();
            if (onError) onError(lastError_);
            return false;
        }
    });
}

bool GeminiClient::IsConfigured() const {
    return !apiKey_.empty() && !model_.empty();
}

std::string GeminiClient::GetLastError() const {
    return lastError_;
}

std::string GeminiClient::PerformHttpRequest(
    const std::string& url,
    const std::string& postData,
    const std::map<std::string, std::string>& headers) {
    
#ifdef _WIN32
    std::string response;
    HINTERNET hInternet = nullptr;
    HINTERNET hConnect = nullptr;
    HINTERNET hRequest = nullptr;
    
    try {
        // Initialize WinINet
        hInternet = InternetOpenA("SecuritySentinel/1.0", 
                                  INTERNET_OPEN_TYPE_PRECONFIG, 
                                  nullptr, nullptr, 0);
        if (!hInternet) {
            throw std::runtime_error("Failed to initialize internet connection");
        }

        // Parse URL
        std::regex urlRegex(R"(https?://([^/]+)(/.*)?)");
        std::smatch matches;
        if (!std::regex_match(url, matches, urlRegex)) {
            throw std::runtime_error("Invalid URL format");
        }
        
        std::string host = matches[1].str();
        std::string path = matches.size() > 2 ? matches[2].str() : "/";
        
        // Connect to server
        hConnect = InternetConnectA(hInternet, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT,
                                   nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0);
        if (!hConnect) {
            throw std::runtime_error("Failed to connect to server");
        }

        // Create request
        hRequest = HttpOpenRequestA(hConnect, "POST", path.c_str(), nullptr, nullptr,
                                   nullptr, INTERNET_FLAG_SECURE, 0);
        if (!hRequest) {
            throw std::runtime_error("Failed to create HTTP request");
        }

        // Add headers
        std::string allHeaders;
        for (const auto& header : headers) {
            allHeaders += header.first + ": " + header.second + "\r\n";
        }
        
        if (!allHeaders.empty()) {
            HttpAddRequestHeadersA(hRequest, allHeaders.c_str(), 
                                  static_cast<DWORD>(allHeaders.length()), 
                                  HTTP_ADDREQ_FLAG_ADD);
        }

        // Send request
        BOOL result = HttpSendRequestA(hRequest, nullptr, 0, 
                                      const_cast<char*>(postData.c_str()), 
                                      static_cast<DWORD>(postData.length()));
        if (!result) {
            throw std::runtime_error("Failed to send HTTP request");
        }

        // Read response
        char buffer[4096];
        DWORD bytesRead;
        while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            response += buffer;
        }
    }
    catch (...) {
        // Cleanup
        if (hRequest) InternetCloseHandle(hRequest);
        if (hConnect) InternetCloseHandle(hConnect);
        if (hInternet) InternetCloseHandle(hInternet);
        throw;
    }
    
    // Cleanup
    if (hRequest) InternetCloseHandle(hRequest);
    if (hConnect) InternetCloseHandle(hConnect);
    if (hInternet) InternetCloseHandle(hInternet);
    
    return response;
#else
    // For non-Windows platforms, implement using curl or similar
    lastError_ = "HTTP client not implemented for this platform";
    return "";
#endif
}

bool GeminiClient::ParseStreamResponse(
    const std::string& response,
    StreamCallback onChunk,
    ErrorCallback onError) {
    
    try {
        // Simple parsing for Gemini streaming response
        // In a real implementation, this would parse Server-Sent Events format
        std::istringstream stream(response);
        std::string line;
        std::string content;
        
        while (std::getline(stream, line)) {
            // Look for content in JSON response
            if (line.find("\"text\":") != std::string::npos) {
                // Extract text content (simplified parsing)
                size_t start = line.find("\"text\":") + 8;
                size_t end = line.find("\"", start + 1);
                if (start != std::string::npos && end != std::string::npos) {
                    std::string chunk = line.substr(start, end - start);
                    // Unescape JSON
                    chunk = std::regex_replace(chunk, std::regex("\\\\n"), "\n");
                    chunk = std::regex_replace(chunk, std::regex("\\\\\""), "\"");
                    
                    if (onChunk && !chunk.empty()) {
                        onChunk(chunk);
                    }
                }
            }
        }
        
        return true;
    }
    catch (const std::exception& e) {
        lastError_ = std::string("Failed to parse response: ") + e.what();
        if (onError) onError(lastError_);
        return false;
    }
}

std::string GeminiClient::FormatChatRequest(
    const std::vector<ChatMessage>& history,
    const std::string& newMessage) {
    
    std::ostringstream json;
    json << "{";
    
    // Add system instruction if available
    if (!systemInstruction_.empty()) {
        json << "\"systemInstruction\":{\"parts\":[{\"text\":\"" 
             << Utils::EscapeJson(systemInstruction_) << "\"}]},";
    }
    
    // Add contents (conversation history)
    json << "\"contents\":[";
    
    // Add history
    for (size_t i = 0; i < history.size(); ++i) {
        if (i > 0) json << ",";
        json << "{\"role\":\"" << history[i].role << "\","
             << "\"parts\":[{\"text\":\"" << Utils::EscapeJson(history[i].content) << "\"}]}";
    }
    
    // Add new message
    if (!history.empty()) json << ",";
    json << "{\"role\":\"user\","
         << "\"parts\":[{\"text\":\"" << Utils::EscapeJson(newMessage) << "\"}]}";
    
    json << "],";
    json << "\"generationConfig\":{\"temperature\":0.7,\"maxOutputTokens\":2048}";
    json << "}";
    
    return json.str();
}