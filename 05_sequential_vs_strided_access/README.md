# 05 - Sequential vs Strided Access

This experiment keeps the data and arithmetic essentially the same while changing the **order in which memory is visited**.

Both programs create a `std::vector<int>` filled with `1`, touch the full vector, and calculate the same final sum.

The performance difference is therefore intended to highlight memory access order rather than different useful work.

## Sequential Access

`SequentialAccess.cpp` visits elements in normal contiguous order:

```text
0, 1, 2, 3, 4, 5, 6, 7, ...
```

The timed loop is equivalent to:

```cpp
for (std::uint32_t i = 0; i < vector_size; ++i)
{
    vector_sum += int_vector[i];
}
```

This pattern has strong spatial locality:

```text
[0][1][2][3][4][5][6][7]...
 ↑  ↑  ↑  ↑  ↑  ↑  ↑  ↑
```

Nearby elements are used soon after each other, cache lines are consumed efficiently, and the access stream is predictable for hardware prefetching.

## Strided Access

`StridedAccess.cpp` visits the same vector in a different order.

The program first calculates:

```cpp
vector_strides = vector_size / 1024;
```

and then walks the vector by that stride for each starting offset:

```cpp
for (std::uint32_t i = 0; i < vector_strides; ++i)
{
    for (std::uint32_t j = i; j < vector_size; j += vector_strides)
    {
        vector_sum += int_vector[j];
    }
}
```

For a large vector where `vector_strides == 10`, the order begins conceptually like:

```text
0, 10, 20, 30, ...
1, 11, 21, 22, ...
2, 12, 22, 32, ...
```

The same elements are eventually processed, but neighbouring logical accesses are now much farther apart in memory.

## Why the Vector Size Is Adjusted

Both programs round the requested vector size up so it is exactly divisible by `1024`.

This keeps the strided traversal regular and makes it easier for the nested loops to cover the vector consistently.

## What This Demonstrates

```text
Sequential access
        ↓
strong spatial locality
        ↓
good cache line utilisation
        ↓
prefetcher friendly

Strided access
        ↓
distant consecutive accesses
        ↓
less immediate cache line reuse
        ↓
more pressure on the memory hierarchy
```

This is a practical performance proof of the spatial locality idea:

> If you use one memory location, using its neighbours soon afterwards is often much cheaper than jumping far away and returning later.

## Build

```bash
make
```

This creates:

```text
SequentialAccess
StridedAccess
```

## Run

Use the same requested vector size for both programs, for example:

```bash
./SequentialAccess 1048576
./StridedAccess 1048576
```

Both print the calculated sum and elapsed time in nanoseconds.

## Concepts Demonstrated

- sequential access
- strided access
- spatial locality
- cache line reuse
- hardware prefetching
- memory access order
