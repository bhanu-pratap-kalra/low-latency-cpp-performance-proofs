# 01 - `std::vector` vs `std::list`

This experiment compares sequential traversal of `std::vector<int>` with sequential traversal of `std::list<int>`.

Both loops perform the same logical work: they visit `N` integers, add each value to a sum, and therefore have **O(n)** traversal complexity.

The interesting difference is the memory layout.

## What the Example Does

The program creates both containers with the same number of elements and stores `1` in every element.

```text
std::vector
[1][1][1][1][1][1]...

std::list
[1] -> [1] -> [1] -> [1]...
```

`std::vector` stores its elements contiguously. Sequential traversal therefore tends to have good spatial locality, efficient cache line utilisation, and a predictable access pattern for hardware prefetchers.

`std::list` stores separately allocated nodes connected by pointers. Traversal requires pointer chasing, and consecutive logical elements may be far apart in memory.

## Why the Sum Is Calculated

The benchmark does more than simply iterate:

```cpp
vector_sum += num;
```

and:

```cpp
list_sum += num;
```

The sums are printed after the timing section so the compiler cannot trivially remove the traversal as unused work when compiling with `-O2`.

## Build

```bash
make
```

## Run

Default element count:

```bash
./SimpleIterationExample
```

Or provide the number of elements:

```bash
./SimpleIterationExample 100000
```

The program prints both sums and the measured traversal time in nanoseconds.

## What to Look For

The important comparison is not simply "vector is faster". The experiment demonstrates that:

```text
Algorithmic view

vector traversal -> O(n)
list traversal   -> O(n)

Hardware view

vector -> contiguous + predictable
list   -> pointer chasing + scattered nodes
```

The measured difference can vary significantly between machines and runs, but it illustrates why **Big-O complexity alone does not describe memory system performance**.

## Concepts Demonstrated

- contiguous storage
- pointer chasing
- spatial locality
- cache-line utilisation
- hardware prefetching
- O(n) complexity vs real execution cost
