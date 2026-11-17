# low-latency-cpp-performance-proofs

Small, measurable C++ experiments that demonstrate how memory layout, cache behaviour, concurrency, and access patterns can affect real world performance.

The goal of this repository is not to claim universal benchmark numbers. Each example isolates one idea, runs the same or comparable work in different layouts/access patterns, and makes the hardware effect visible through simple measurements.


## Build Requirements

The examples are intentionally small and use a simple `Makefile` in each folder.

- C++20-capable compiler
- GNU Make
- Linux/macOS environment capable of running the examples

The current Makefiles use:

```text
g++ -std=c++20 -O2 -Wall -Wextra
```

## Running an Experiment

Enter an experiment directory, build it, and run the generated executable(s).

Example:

```bash
cd 01_std_vector_vs_std_list
make
./SimpleIterationExample 100000
```

Clean generated binaries with:

```bash
make clean
```

Each experiment has its own README with the exact executables, arguments, and what the measurement is intended to show.

## Benchmarking Philosophy

These examples are deliberately small so the performance concept remains visible in the code.

A single measurement is evidence from that run, not a universal performance guarantee. For stronger conclusions, repeat runs, compare distributions, and use hardware performance counters where available.

## Concepts Covered

This repository currently touches on:

- cache locality
- cache lines
- spatial locality
- hardware prefetching
- pointer chasing
- false sharing
- cache-line alignment
- `std::hardware_destructive_interference_size`
- hot vs cold data
- Array of Structures (AoS)
- Structure of Arrays (SoA)
- sequential vs strided memory access

## Relationship to the Series

These experiments are practical performance proofs for concepts discussed in **Beyond the Kernel | Modern C++ & Linux** and complement the implementation-focused work in **Low Latency C++ Lab**.

The emphasis here is simple:

> Same high level algorithm does not always mean the same hardware behaviour.

## License

See [LICENSE](LICENSE).
