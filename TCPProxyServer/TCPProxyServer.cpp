#include "TCPProxyServer.h"
#include <cstring>   // For memset
#include <cerrno>    // For error handling
#include <stdexcept> // For exceptions

TCPProxyServer::TCPProxyServer(int port, int threadCount)
    : port(port), threadCount(threadCount), activeThreads(0), threads(threadCount), logger("server_log.txt") {
    createServerSocket();
    bindAndListen();
}

TCPProxyServer::~TCPProxyServer() {
    close(serverSocket); // Close server socket
}

void TCPProxyServer::createServerSocket() {
    // Create a TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
}

void TCPProxyServer::bindAndListen() {
    // Set server address information
    serverAddr.sin_family = AF_INET; // Set address family
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface
    serverAddr.sin_port = htons(port); // Set the port number

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Failed to bind socket: " + std::string(strerror(errno)));
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        throw std::runtime_error("Failed to listen on socket: " + std::string(strerror(errno)));
    }

    std::cout << "Server is listening on port " << port << "..." << std::endl; // Notify server is ready
    logger.log("Server is listening on port " + std::to_string(port));
}

void TCPProxyServer::start() {
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);

        // Accept an incoming client connection
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket < 0) {
            logger.log("Failed to accept client connection: " + std::string(strerror(errno)));
            continue;
        }

        {
            std::unique_lock<std::mutex> lock(mtx);
            if (activeThreads < threadCount) {
                activeThreads++;
                std::cout << "Active threads: " << activeThreads << ", Thread ID: " << std::this_thread::get_id() << std::endl;
                lock.unlock(); // Unlock before enqueueing to allow other threads to proceed

                logger.log("Client connected from " + std::string(inet_ntoa(clientAddr.sin_addr)) +
                           ":" + std::to_string(ntohs(clientAddr.sin_port)));

                // Use the thread pool to handle the client connection
                threads.enqueue([this, clientSocket] { 
                    handleClient(clientSocket); 
                });
            } else {
                lock.unlock(); // Unlock if no action is taken
                logger.log("Maximum active threads reached, rejecting new connection.");
                close(clientSocket); // Close the client socket since the limit is reached
            }
        }
    }
}

void TCPProxyServer::handleClient(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;

    // Read data from the client
    bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        logger.log("Error reading from client: " + std::string(strerror(errno)));
        close(clientSocket);
        return;
    }

    buffer[bytesRead] = '\0'; // Null-terminate the received data
    logger.log("Received from client: " + std::string(buffer));

    // Create a basic HTTP response
    std::string httpResponse = "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/plain\r\n"
                                "Content-Length: 13\r\n"
                                "Connection: close\r\n"
                                "\r\n"
                                "Hello, client!";
    
    // Log the response that will be sent to the client
    logger.log("Sending response: " + httpResponse);
    std::cout << "Sending response: " << httpResponse << std::endl;

    // Send the response to the client
    if (write(clientSocket, httpResponse.c_str(), httpResponse.size()) < 0) {
        logger.log("Failed to send data to client: " + std::string(strerror(errno)));
    }

    close(clientSocket); // Close client socket

    // Lock for thread-safe access to active thread count
    {
        std::lock_guard<std::mutex> lock(mtx);
        activeThreads--; // Decrement the active thread count
        logger.log("Client disconnected, active threads: " + std::to_string(activeThreads));
        std::cout << "Client disconnected, active threads: " << activeThreads << std::endl; // Log to console
    }
}
