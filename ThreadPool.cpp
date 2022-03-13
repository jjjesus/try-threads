//
// Created by jjesus on 10/28/19.
//

#include "ThreadPool.h"
#include <thread>

void ThreadPool::enqueue(std::packaged_task<int()> t)
{
    {
        std::unique_lock<std::mutex> locker(mu);
        task_q.push_back(std::move(t));
    }
    cv.notify_one();

}

void ThreadPool::startWorkers(int numWorkers)
{
    for (int ii = 0; ii < numWorkers; ii++) {
        std::thread th(&ThreadPool::workerThread, this);
        workerList.push_back(std::move(th));
    }
}

void ThreadPool::workerThread()
{
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> locker(mu);
        cv.wait(locker, [this]() { return this->stop || !task_q.empty(); });
        if (this->stop && this->task_q.empty())
        {
            return;
        }
        t = std::move(task_q.front());
        task_q.pop_front();
    }
    t();
}

void ThreadPool::shutdown() {
    {
        std::unique_lock<std::mutex> locker(mu);
        stop = true;
    }
    cv.notify_all();
    for (auto& th: workerList)
    {
        th.join();
    }
}
