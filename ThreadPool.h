#pragma once
#include <functional>
#include <deque>
#include <future>
#include <vector>
#include <thread>

class ThreadPool {
public:
    void enqueue(std::packaged_task<int()> t);
    void startWorkers(int numWorkers);
    void shutdown();

private:
    std::deque<std::packaged_task<int()> > task_q;
    std::mutex mu;
    std::condition_variable cv;
    std::vector<std::thread> workerList;
    bool stop;

    void workerThread();

};
