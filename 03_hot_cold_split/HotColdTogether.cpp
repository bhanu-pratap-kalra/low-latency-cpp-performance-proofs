#include <cstdint>
#include <iostream>
#include <chrono>
#include <vector>

struct HotColdTogether
{
    std::uint32_t m_id{0};
    std::uint32_t m_counter{0};
    char m_info[128]{};
};

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Incorrect usage\n"
            << "Use: HotColdTogether <num_iterations>\n";
        return -1;
    }

    std::uint32_t iterations = 0;

    try
    {
        iterations = static_cast<std::uint32_t>(std::stoi(argv[1]));
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    std::vector<HotColdTogether> hot_cold_together(iterations);
    using Clock = std::chrono::steady_clock;

    auto start = Clock::now();

    for (std::uint32_t i = 0; i < iterations; ++i)
    {
        hot_cold_together[i].m_counter = i;
    }

    auto end = Clock::now();

    std::uint32_t counter_total = 0;
    
    for (std::uint32_t i = 0; i < iterations; ++i)
    {
        counter_total += hot_cold_together[i].m_counter;
    }

    auto time_taken = std::chrono::duration<double, std::nano>(end - start).count();

    std::cout << "HotColdTogether counter_total = " << counter_total << "\n"
        << "Time taken to process HotColdTogether counter = " << time_taken << " ns\n";
    return 0;
}
