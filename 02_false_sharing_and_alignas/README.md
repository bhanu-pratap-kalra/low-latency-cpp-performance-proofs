# 02 - False Sharing and `alignas`

This experiment compares three layouts for two independently updated per thread atomic counters.

The threads do not update the same variable. The performance question is whether their counters occupy the same cache line and therefore interfere through the cache coherence mechanism.

## Variants

### 1. No Explicit Alignment

`SimpleNoAlignmentExample.cpp`

```cpp
struct PerThreadCounterNoAlignment
{
    std::atomic<int> counter;
};
```

Two objects are stored next to each other in a `std::vector`. Because the objects are small, their counters can potentially occupy the same cache line.

Conceptually:

```text
One cache line
[counter 0][counter 1]...
     ^          ^
  Thread 0   Thread 1
```

Even though the variables are logically independent, writes by different cores can cause the shared cache line to move between cores. This is false sharing.

### 2. `alignas(64)`

`SimpleAlignas64Example.cpp`

```cpp
struct alignas(64) PerThreadCounterAlign64
{
    std::atomic<int> counter;
};
```

This explicitly requests 64 byte alignment for each counter object, a common cache line size assumption, but not a guaranteed cache line size. Make sure you are aware of the cache line size on your machine before using any hardcoded value.

### 3. `std::hardware_destructive_interference_size`

`SimpleAlignasExampleHDIS.cpp`

```cpp
struct alignas(std::hardware_destructive_interference_size)
PerThreadCounterAlignasHDIS
{
    std::atomic<int> counter;
};
```

C++17 introduced `std::hardware_destructive_interference_size` as an implementation provided separation intended to help avoid destructive interference between independently accessed objects.

The program also prints the value selected by the current C++ implementation.

## What Each Thread Does

Each `std::jthread` increments only its own counter for the requested number of iterations:

```text
Thread 1 -> Counter 1
Thread 2 -> Counter 2
```

The elapsed time for each thread is measured independently.

## Build

```bash
make
```

This creates:

```text
SimpleNoAlignmentExample
SimpleAlignas64Example
SimpleAlignasExampleHDIS
```

## Run

Use the same iteration count for each executable, for example:

```bash
./SimpleNoAlignmentExample 10000000
./SimpleAlignas64Example 10000000
./SimpleAlignasExampleHDIS 10000000
```

## What to Look For

Compare how long the two threads take under each layout.

The conceptual progression is:

```text
per thread counters
        ↓
avoid true sharing of one counter
        ↓
cache line separation
        ↓
reduce false sharing
```

An important point is that **more alignment does not automatically mean more performance**. Once the destructive interference has been removed for a workload, additional spacing may provide no further speedup while increasing object size and memory usage.

## Concepts Demonstrated

- false sharing
- per thread counters
- atomic updates
- cache coherence
- `alignas`
- `std::hardware_destructive_interference_size`
- portability vs hardcoded alignment
