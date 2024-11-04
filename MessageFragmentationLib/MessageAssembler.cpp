#include "MessageAssembler.h"

// Constructor
MessageAssembler::MessageAssembler(int totalChunks, int timeoutMilliseconds, MissingChunkCallback callback)
    : totalChunks(totalChunks), timeoutMilliseconds(timeoutMilliseconds), missingChunkCallback(callback) {
    startTime = std::chrono::steady_clock::now();
}

// Add chunk to the assembler
void MessageAssembler::addChunk(size_t index, const std::string& chunk) {
    chunks[index] = chunk; // Add chunk at given index
    checkForTimeout(); // Check for timeouts every time a chunk is added
}

// Reassemble the message from chunks
std::string MessageAssembler::reassemble(std::vector<size_t>& missingIndices) {
    std::string message;

    // Check for missing chunks and report their indices
    for (size_t i = 0; i < totalChunks; ++i) {
        if (chunks.find(i) == chunks.end()) {
            missingIndices.push_back(i); // Record the index of the missing chunk
            missingChunkCallback(i);      // Invoke the callback for missing chunks
        }
        else {
            message += chunks[i]; // Append each chunk to the message
        }
    }

    return message; // Return the assembled message (might be incomplete)
}

// Check for timeouts and invoke the callback for missing chunks if needed
void MessageAssembler::checkForTimeout() {
    auto now = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

    if (elapsedTime > timeoutMilliseconds) {
        for (size_t i = 0; i < totalChunks; ++i) {
            if (chunks.find(i) == chunks.end()) {
                missingChunkCallback(i); // Invoke the callback for missing chunks
            }
        }
    }
}
