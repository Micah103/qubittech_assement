#ifndef FRAGMENTER_H
#define FRAGMENTER_H

#include <string>
#include <vector>

class Fragmenter {
public:
    // Constructor
    Fragmenter(size_t chunkSize) : chunkSize(chunkSize) {}

    // Splits a long message into chunks of fixed size.
    std::vector<std::string> fragmentMessage(const std::string& message);

private:
    size_t chunkSize; // Size of each chunk
};

#endif // FRAGMENTER_H
