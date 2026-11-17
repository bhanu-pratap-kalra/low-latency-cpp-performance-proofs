# 03 - Hot / Cold Data Split

This experiment compares keeping frequently accessed and rarely used fields in one large object with splitting the hot fields into a compact structure.

The benchmark focuses on updating `m_counter` across many objects.

## Hot and Cold Data Together

`HotColdTogether.cpp` uses:

```cpp
struct HotColdTogether
{
    std::uint32_t m_id{0};
    std::uint32_t m_counter{0};
    char m_info[128]{};
};
```

The timed loop only updates:

```cpp
m_counter
```

but every object also contains the 128-byte `m_info` field.

Conceptually:

```text
[id][counter][------------ cold info ------------]
      ^
      hot
```

Walking the vector therefore moves through large objects even though the hot loop only needs a small part of each object.

## Hot and Cold Data Split

`HotColdSplit.cpp` separates the layouts:

```cpp
struct HotColdSplit_Hot
{
    std::uint32_t m_id{0};
    std::uint32_t m_counter{0};
};

struct HotColdSplit_Cold
{
    std::uint32_t m_id{0};
    char m_info[128]{};
};
```

The benchmark creates and processes only the hot vector:

```text
[id][counter][id][counter][id][counter]...
```

This packs the fields used by the hot path much more densely in memory.

The cold structure is defined to demonstrate the intended logical split, but the current benchmark does not allocate or process a cold data vector.

## Why This Can Matter

A cache line contains a fixed number of bytes. If each object contains a large cold field, fewer useful counters fit into each line.

With a compact hot representation:

```text
more hot objects per cache line
        ↓
better cache utilisation
        ↓
less unrelated data moved through the cache
```

## Build

```bash
make
```

This creates:

```text
HotColdTogether
HotColdSplit
```

## Run

Use the same number of objects for both executables:

```bash
./HotColdTogether 1000000
./HotColdSplit 1000000
```

Both programs print the calculated counter total and the measured update time in nanoseconds.

## What Is Timed

The timed section contains the loop that writes `m_counter` for every object.

A second loop calculates `counter_total` after the timing section so the written values are consumed and observable.

## Concepts Demonstrated

- hot vs cold data
- object size
- cache line utilisation
- data oriented layout
- contiguous traversal
- reducing unnecessary memory traffic
