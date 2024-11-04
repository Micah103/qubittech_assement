#ifndef MESSAGEASSEMBLER_H
#define MESSAGEASSEMBLER_H

#include <unordered_map>
#include <chrono>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

class MessageAssembler {
public:
    using MissingChunkCallback = std::function<void(size_t)>;

    // Constructor
    MessageAssembler(int totalChunks, int timeoutMilliseconds, MissingChunkCallback callback);

    // Add chunk to the assembler
    void addChunk(size_t index, const std::string& chunk);

    // Reassemble the message from chunks
    std::string reassemble(std::vector<size_t>& missingIndices); // Ensure this matches

private:
    void checkForTimeout();

    std::unordered_map<size_t, std::string> chunks; // Use unordered_map for flexibility
    std::chrono::steady_clock::time_point startTime;
    int timeoutMilliseconds;
    int totalChunks; // Store the total expected number of chunks
    MissingChunkCallback missingChunkCallback; // Declare the callback member
};

#endif // MESSAGEASSEMBLER_H
