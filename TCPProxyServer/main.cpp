
#include "TCPProxyServer.h" // Include the TCPProxyServer header to access its functionality

int main() {
    int port = 8080; // Define the port number for the server; change as needed
    int threadCount = 5; // Define the size of the thread pool for handling client connections

    // Create an instance of TCPProxyServer with the specified port and thread count
    TCPProxyServer server(port, threadCount);

    // Start the server to begin accepting client connections
    server.start();

    return 0; // Return 0 to indicate successful execution
}
