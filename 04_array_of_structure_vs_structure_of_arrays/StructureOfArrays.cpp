#include <iostream>
#include <vector>
#include <array>
#include <chrono>

struct StructureOfArrays
{
    std::vector<int> m_x;
    std::vector<int> m_y;
    std::vector<int> m_z;
    std::vector<std::array<char, 128>> m_info;
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

    StructureOfArrays structure_of_arrays;
    structure_of_arrays.m_x.assign(iterations, 1);
    structure_of_arrays.m_y.assign(iterations, 1);
    structure_of_arrays.m_z.assign(iterations, 1);
    structure_of_arrays.m_info.resize(iterations);

    int total_x_sum = 0;
    int total_z_sum = 0;

    using Clock = std::chrono::steady_clock;

    auto start = Clock::now();

    for (std::uint32_t i = 0; i < iterations; ++i)
    {
        total_x_sum += structure_of_arrays.m_x[i];
        total_z_sum += structure_of_arrays.m_z[i];
    }

    auto end = Clock::now();

    auto time_taken = std::chrono::duration<double, std::nano>(end-start).count();

    std::cout << "total_x_sum = " << total_x_sum << " total_z_sum = " << total_z_sum << "\n"
        << "Total time to process StructureOfArrays = " << time_taken << "\n";
    return 0;
}