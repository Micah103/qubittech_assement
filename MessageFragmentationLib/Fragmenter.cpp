#include "Fragmenter.h"
#include <algorithm>

// Splits a long message into chunks of fixed size.
std::vector<std::string> Fragmenter::fragmentMessage(const std::string& message) {
    std::vector<std::string> chunks;
    size_t numChunks = (message.size() + chunkSize - 1) / chunkSize;

    for (size_t i = 0; i < numChunks; ++i) {
        size_t start = i * chunkSize;
        size_t length = std::min(chunkSize, message.size() - start);
        chunks.push_back(message.substr(start, length));
    }
    return chunks;
}
