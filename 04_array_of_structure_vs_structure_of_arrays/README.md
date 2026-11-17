# 04 - Array of Structures vs Structure of Arrays

This experiment compares two ways of representing the same logical data:

- **Array of Structures (AoS)**
- **Structure of Arrays (SoA)**

The benchmark reads only the `x` and `z` values while deliberately keeping other data in the model.

## Array of Structures (AoS)

`ArrayOfStructure.cpp` stores complete objects in one `std::vector`:

```cpp
struct ArrayOfStructure
{
    int m_x{1};
    int m_y{1};
    int m_z{1};
    char m_info[128]{};
};
```

Memory is conceptually arranged like:

```text
[x y z info][x y z info][x y z info][x y z info]...
```

The timed loop only reads `m_x` and `m_z`:

```cpp
total_x_sum += array_of_structure[i].m_x;
total_z_sum += array_of_structure[i].m_z;
```

That means each logical object contains data the hot loop does not need, especially the 128 byte `m_info` field.

## Structure of Arrays (SoA)

`StructureOfArrays.cpp` stores each field in its own contiguous vector:

```cpp
struct StructureOfArrays
{
    std::vector<int> m_x;
    std::vector<int> m_y;
    std::vector<int> m_z;
    std::vector<std::array<char, 128>> m_info;
};
```

Memory is conceptually arranged like:

```text
[x x x x x x ...]
[y y y y y y ...]
[z z z z z z ...]
[info info info ...]
```

The timed loop reads only the `m_x` and `m_z` arrays.

## Why This Can Matter

If a hot computation uses only a subset of each object's fields, SoA can place more useful values next to each other in memory.

```text
AoS
[x y z cold][x y z cold]...
        ↓
cache lines contain both useful and unused fields

SoA
[x x x x ...]
[z z z z ...]
        ↓
hot fields are densely packed
```

This can improve cache line utilisation and can also produce layouts that are friendlier to vectorized/SIMD processing.

AoS is not inherently bad. It can be a good layout when code normally consumes most fields of each object together. The useful layout depends on the access pattern.

## Build

```bash
make
```

This creates:

```text
ArrayOfStructure
StructureOfArrays
```

## Run

Use the same number of logical elements for both:

```bash
./ArrayOfStructure 1000000
./StructureOfArrays 1000000
```

Each program measures the loop that sums `x` and `z` values and prints the elapsed time.

## Concepts Demonstrated

- Array of Structures (AoS)
- Structure of Arrays (SoA)
- cache locality
- cache line utilisation
- data oriented design
- SIMD friendly layouts
