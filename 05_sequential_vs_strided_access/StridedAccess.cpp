#include <iostream>
#include <chrono>

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Invalid usage\n"
                << "Use: SequentialAcess <num_iterations>\n";

        return -1;
    }
    
    std::uint32_t vector_size = 0;

    try
    {
        vector_size = static_cast<std::uint32_t>(std::stoi(argv[1]));
        if (std::uint32_t difference = vector_size % 1024; difference != 0)
        {
            vector_size += (1024 - difference);
            std::cout << "Adjusting vector size to " << vector_size << " making it exactly divisible by 1024\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    std::vector<int> int_vector;
    int_vector.assign(vector_size, 1);

    std::uint32_t vector_sum = 0;
    std::uint32_t vector_strides = vector_size / 1024;

    std::cout << "Vector Stride calculated as " << vector_strides << "\n";

    using Clock = std::chrono::steady_clock;

    auto start = Clock::now();

    for (std::uint32_t i = 0; i < vector_strides; ++i)
    {
        for (std::uint32_t j = i; j < vector_size; j += vector_strides)
        {
            vector_sum += int_vector[j];
        }
    }

    auto end = Clock::now();

    auto time_taken = std::chrono::duration<double, std::nano>(end - start).count();

    std::cout << "Vector sum calculated as " << vector_sum << " and took " << time_taken << " ns\n";
    return 0;
}