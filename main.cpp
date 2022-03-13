// From https://www.youtube.com/watch?v=FfbZfBk-3rI
//
#include <iostream>
#include <future>
#include <functional>
#include "ThreadPool.h"


int factorial(int N)
{
    int result = 1;
    for (int ii = N; ii > 1; ii--)
    {
        result *= ii;
    }
    return result;
}


int main()
{
    ThreadPool threadPool;

    std::packaged_task<int()> t(std::bind(factorial, 6));
    std::future<int> fu = t.get_future();

    threadPool.enqueue(std::move(t));

    threadPool.startWorkers(4);

    std::cout << "Value is: " << fu.get() << std::endl;

    threadPool.shutdown();

    return 0;
}
