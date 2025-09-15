#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <future>
#include <map>

/**
 * HTTP client for interacting with Google Gemini API
 * Handles authentication, request formatting, and streaming responses
 */
class GeminiClient {
public:
    struct ChatMessage {
        std::string role;      // "user" or "model"
        std::string content;
    };

    using StreamCallback = std::function<void(const std::string&)>;
    using ErrorCallback = std::function<void(const std::string&)>;

    GeminiClient();
    ~GeminiClient();

    // Configuration
    bool SetApiKey(const std::string& apiKey);
    void SetModel(const std::string& model = "gemini-2.5-flash");
    void SetSystemInstruction(const std::string& instruction);

    // Chat operations
    std::future<bool> SendMessageAsync(
        const std::vector<ChatMessage>& history,
        const std::string& message,
        StreamCallback onChunk,
        ErrorCallback onError
    );

    // Utility methods
    bool IsConfigured() const;
    std::string GetLastError() const;

private:
    std::string apiKey_;
    std::string model_;
    std::string systemInstruction_;
    std::string lastError_;
    std::string baseUrl_;

    // HTTP client implementation
    std::string PerformHttpRequest(
        const std::string& url,
        const std::string& postData,
        const std::map<std::string, std::string>& headers
    );
    
    bool ParseStreamResponse(
        const std::string& response,
        StreamCallback onChunk,
        ErrorCallback onError
    );
    
    std::string FormatChatRequest(
        const std::vector<ChatMessage>& history,
        const std::string& newMessage
    );
};