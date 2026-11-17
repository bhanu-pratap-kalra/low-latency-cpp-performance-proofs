#include <iostream>
#include <vector>
#include <chrono>

struct ArrayOfStructure
{
    int m_x{1};
    int m_y{1};
    int m_z{1};
    char m_info[128]{};
};

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Incorrect Usage\n"
            << "Use: ArrayOfStructure <num_iterations>\n";
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

    std::vector<ArrayOfStructure> array_of_structure(iterations);

    int total_x_sum = 0;
    int total_z_sum = 0;

    using Clock = std::chrono::steady_clock;

    auto start = Clock::now();

    for (std::uint32_t i = 0; i < iterations; ++i)
    {
        total_x_sum += array_of_structure[i].m_x;
        total_z_sum += array_of_structure[i].m_z;
    }

    auto end = Clock::now();

    auto time_taken = std::chrono::duration<double, std::nano>(end-start).count();

    std::cout << "total_x_sum = " << total_x_sum << " total_z_sum = " << "\n"
        << "Total time to process ArrayOfStructure = " << time_taken << "\n";
    return 0;
}