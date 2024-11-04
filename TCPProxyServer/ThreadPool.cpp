
#include "ThreadPool.h"

// Constructor: Initializes the thread pool with a specified number of threads
ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    // Create the specified number of worker threads
    for (size_t i = 0; i < numThreads; ++i) {
        // Lambda function to handle tasks
        workers.emplace_back([this] {
            while (true) {
                std::function<void()> task; // Placeholder for the task to execute
                {
                    // Lock the mutex to safely access the task queue
                    std::unique_lock<std::mutex> lock(this->mtx);
                    // Wait until a task is available or the thread pool is stopped
                    this->cv.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    // Check if we should stop and no tasks are left
                    if (this->stop && this->tasks.empty()) return;
                    // Move the front task from the queue and remove it from the queue
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task(); // Execute the task
            }
            });
    }
}

// Destructor: Cleans up resources by joining all worker threads
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx); // Lock the mutex to modify shared state
        stop = true; // Indicate that the thread pool is stopping
    }
    cv.notify_all(); // Wake up all threads to exit
    // Join all worker threads
    for (std::thread& worker : workers) {
        worker.join();
    }
}

// Method to add a new task to the queue
void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(mtx); // Lock the mutex for safe access
        tasks.emplace(std::move(task)); // Move the task into the queue
    }
    cv.notify_one(); // Notify one waiting thread that a new task is available
}
