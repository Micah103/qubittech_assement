cmake_minimum_required(VERSION 3.10)
project(TCPProxyServer)

set(CMAKE_CXX_STANDARD 17)

# Add source files for each component
add_executable(TCPProxyServer
    main.cpp
    Logger.cpp
    TCPProxyServer.cpp
    ThreadPool.cpp
)

# Link against Winsock library if on Windows
if (WIN32)
    target_link_libraries(TCPProxyServer ws2_32)
endif()
