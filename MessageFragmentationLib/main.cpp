#include <iostream>
#include <thread>
#include "Fragmenter.h"
#include "MessageAssembler.h"

// Callback function to handle missing chunks
void onMissingChunk(size_t index) {
    std::cout << "Missing chunk at index: " << index << std::endl;
}

void testFragmentation(const std::string& message) {
    // Fragment the message
    Fragmenter fragmenter(16); // Chunk size of 16 characters
    std::vector<std::string> chunks = fragmenter.fragmentMessage(message);

    // Display fragmented chunks
    std::cout << "Fragmented Chunks:" << std::endl;
    for (size_t i = 0; i < chunks.size(); ++i) {
        std::cout << "Chunk " << i << ": " << chunks[i] << std::endl;
    }

    // Initialize MessageAssembler with a timeout of 5000 milliseconds and the callback
    MessageAssembler assembler(chunks.size(), 5000, onMissingChunk);

    // Simulate receiving all chunks
    for (size_t i = 0; i < chunks.size(); ++i) {
        assembler.addChunk(i, chunks[i]);
    }

    // Attempt reassembly
    std::vector<size_t> missingIndices; // For storing missing indices
    auto reassembledMessage = assembler.reassemble(missingIndices);

    // Output result
    if (!reassembledMessage.empty()) {
        std::cout << "Reassembled Message: " << reassembledMessage << std::endl;
    }
    else {
        std::cout << "Message is incomplete or has missing chunks." << std::endl;
    }
}

void testUserFragmentation(const std::string& message, int  chunck_size) {
    // Fragment the message
    Fragmenter fragmenter(chunck_size); // Chunk size of 16 characters
    std::vector<std::string> chunks = fragmenter.fragmentMessage(message);

    // Display fragmented chunks
    std::cout << "Fragmented Chunks:" << std::endl;
    for (size_t i = 0; i < chunks.size(); ++i) {
        std::cout << "Chunk " << i << ": " << chunks[i] << std::endl;
    }

    // Initialize MessageAssembler with a timeout of 5000 milliseconds and the callback
    MessageAssembler assembler(chunks.size(), 5000, onMissingChunk);

    // Simulate receiving all chunks
    for (size_t i = 0; i < chunks.size(); ++i) {
        assembler.addChunk(i, chunks[i]);
    }

    // Attempt reassembly
    std::vector<size_t> missingIndices; // For storing missing indices
    auto reassembledMessage = assembler.reassemble(missingIndices);

    // Output result
    if (!reassembledMessage.empty()) {
        std::cout << "Reassembled Message: " << reassembledMessage << std::endl;
    }
    else {
        std::cout << "Message is incomplete or has missing chunks." << std::endl;
    }
}

void testUserInput() {
    std::string userInput;
    int size;
    std::cout << "\nEnter a message to fragment and reassemble: ";
    std::getline(std::cin, userInput);
    std::cout << "\nEnter a size of each chunk: ";
    std::cin >> size;

    testUserFragmentation(userInput,  size);
}

void testWithMissingChunks() {
    std::string message = "This is a test message to simulate missing chunks.";
    Fragmenter fragmenter(16);
    std::vector<std::string> chunks = fragmenter.fragmentMessage(message);

    // Display fragmented chunks
    std::cout << "\nSimulating Missing Chunks:\nFragmented Chunks:" << std::endl;
    for (size_t i = 0; i < chunks.size(); ++i) {
        std::cout << "Chunk " << i << ": " << chunks[i] << std::endl;
    }

    MessageAssembler assembler(chunks.size(), 5000, onMissingChunk);

    // Simulate receiving some chunks, deliberately skipping chunk 2
    for (size_t i = 0; i < chunks.size(); ++i) {
        if (i != 2) { // Simulating missing chunk at index 2
            assembler.addChunk(i, chunks[i]);
        }
    }

    // Attempt reassembly
    std::vector<size_t> missingIndices; // For storing missing indices
    auto reassembledMessage = assembler.reassemble(missingIndices);

    // Output result
    if (!reassembledMessage.empty()) {
        std::cout << "Partial Reassembled Message: " << reassembledMessage << std::endl;
    }
    else {
        std::cout << "Message is incomplete or has missing chunks." << std::endl;
    }
}

void testTimeout() {
    std::string message = "This is a test message to validate timeout functionality.";
    Fragmenter fragmenter(16);
    std::vector<std::string> chunks = fragmenter.fragmentMessage(message);

    // Display fragmented chunks
    std::cout << "\nTesting Timeout:\nFragmented Chunks:" << std::endl;
    for (size_t i = 0; i < chunks.size(); ++i) {
        std::cout << "Chunk " << i << ": " << chunks[i] << std::endl;
    }

    MessageAssembler assembler(chunks.size(), 5000, onMissingChunk);

    // Simulate adding only the first chunk and wait longer than the timeout
    assembler.addChunk(0, chunks[0]);

    // Wait for 6 seconds to exceed the timeout
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));

    // Attempt reassembly
    std::vector<size_t> missingIndices; // For storing missing indices
    auto reassembledMessage = assembler.reassemble(missingIndices);

    // Output result
    if (!reassembledMessage.empty()) {
        std::cout << "Partial Reassembled Message: " << reassembledMessage << std::endl;
    }
    else {
        std::cout << "Message is incomplete or has missing chunks." << std::endl;
        std::cout << "Missing chunks at indices: ";
        for (const auto& index : missingIndices) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Step 1: Test with a predefined message
    std::string predefinedMessage = "This is a long message that needs to be fragmented and then reassembled correctly.";
    testFragmentation(predefinedMessage);

    // Step 2: Prompt user for a message
    testUserInput();

    // Step 3: Simulate missing chunks
    testWithMissingChunks();

    // Step 4: Test timeout functionality
    testTimeout();

    return 0;
}
