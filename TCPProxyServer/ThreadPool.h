
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional> // For std::function
#include <queue>      // For std::queue
#include <thread>     // For std::thread
#include <vector>     // For std::vector
#include <condition_variable> // For std::condition_variable

// Class definition for ThreadPool
class ThreadPool {
public:
    // Constructor: Initializes the thread pool with a specified number of threads
    ThreadPool(size_t numThreads);
    // Destructor: Cleans up resources by joining all worker threads
    ~ThreadPool();

    // Method to add a new task to the queue
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers; // Vector to hold the worker threads
    std::queue<std::function<void()>> tasks; // Queue to hold tasks waiting to be executed
    std::mutex mtx; // Mutex for synchronizing access to shared resources
    std::condition_variable cv; // Condition variable to synchronize thread execution
    bool stop; // Flag indicating whether the thread pool is stopping
};

#endif // THREADPOOL_H
