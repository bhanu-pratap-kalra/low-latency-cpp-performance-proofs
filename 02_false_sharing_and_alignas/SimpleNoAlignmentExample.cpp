#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <functional>
#include <new>
#include <vector>

struct PerThreadCounterNoAlignment
{
    std::atomic<int> counter;
};

void IncrementCounters(int interations, PerThreadCounterNoAlignment& thread_counter, double& elapsed)
{
    using Clock = std::chrono::steady_clock;

    auto start = Clock::now();

    for (int i = 0; i < interations; ++i)
    {
        thread_counter.counter++;
    }

    auto end = Clock::now();

    elapsed = std::chrono::duration<double, std::nano>(end - start).count();
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Incorrect number of arguments\n"
            << "Usage: SimpleAlignas64Example <num_iterations>\n";
        return -1;
    }

    std::cout << "std::hardware_destructive_interference_size = "
              << std::hardware_destructive_interference_size
              << std::endl;

    std::vector<PerThreadCounterNoAlignment> thread_counters(2);

    double elapsed_thread_1{0.0};
    double elapsed_thread_2{0.0};

    try 
    {
        std::jthread thread1(IncrementCounters, static_cast<int>(std::stoi(argv[1])), std::ref(thread_counters[0]), std::ref(elapsed_thread_1));
        std::jthread thread2(IncrementCounters, static_cast<int>(std::stoi(argv[1])), std::ref(thread_counters[1]), std::ref(elapsed_thread_2));
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    std::cout << "Time taken by thread 1 = " << elapsed_thread_1 << " ns\n"
        << "Time taken by thread 2 = " << elapsed_thread_2 << " ns\n";

    return 0;
}