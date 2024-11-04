#ifndef TCPPROXYSERVER_H
#define TCPPROXYSERVER_H

#include <sys/socket.h>  // Linux socket programming
#include <netinet/in.h>  // For sockaddr_in
#include <arpa/inet.h>   // For inet_addr
#include <unistd.h>      // For close
#include <string>        // For std::string
#include <thread>        // For multithreading
#include <mutex>         // For mutex
#include <vector>        // For dynamic arrays
#include <iostream>      // For input/output
#include "Logger.h"      // Logger class
#include "ThreadPool.h"  // ThreadPool class

// TCPProxyServer class definition
class TCPProxyServer {
public:
    // Constructor: Initializes the server with a specified port and number of threads
    TCPProxyServer(int port, int threadCount);

    // Destructor: Cleans up resources used by the server
    ~TCPProxyServer();

    // Starts the server and begins accepting client connections
    void start();

private:
    // Handles communication with a connected client
    void handleClient(int clientSocket);

    // Creates a TCP socket for the server
    void createServerSocket();

    // Binds the socket to the specified address and port, then listens for incoming connections
    void bindAndListen();

    int serverSocket;           // Socket for the server
    sockaddr_in serverAddr;      // Structure to hold server address information
    int port;                    // Port number for the server
    int threadCount;             // Number of threads in the thread pool
    ThreadPool threads;          // ThreadPool instance for managing client handling threads
    Logger logger;               // Logger instance for logging server activities
    std::mutex mtx;             // Mutex for thread-safe access to active thread count
    int activeThreads;           // Count of currently active threads
    const int maxActiveThreads = 5; // Define a constant for maximum active threads
};

#endif // TCPPROXYSERVER_H
