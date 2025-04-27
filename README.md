# Simple C Memory Allocator

## Overview

This project implements a **simple memory allocator** in C. The allocator is designed to provide basic functionality for allocating and freeing memory dynamically from a predefined memory pool. It mimics the behavior of standard memory allocation functions such as `malloc()` and `free()`, but it's a **barebones** implementation designed for educational purposes.

### Current Status

**WIP (Work In Progress)**:  
- Currently, the allocator can allocate memory chunks from a predefined pool.
- Does not support **freeing** memory yet.
- Lacks advanced features like **block merging**, **reusing freed memory**, or **memory fragmentation handling**.
- Designed for educational purposes, to better understand how memory management works under the hood.

## Features

- **Memory Pool**: A statically allocated block of memory (`MEMORY_SIZE`) is used as a pool.
- **Basic Allocation**: A simple `my_malloc()` function to allocate memory blocks from the pool.
- **Fixed Size**: At the moment, the allocator operates with a fixed-size memory pool and doesn't grow or shrink dynamically.

## How It Works

1. **Memory Pool**: A predefined block of memory (`MEMORY_SIZE`) is allocated at the beginning of the program.
2. **Allocation**: The `my_malloc()` function allocates memory by moving a pointer (`current`) through the memory pool. When the requested size exceeds the remaining available memory, the allocation fails.
3. **No Freeing**: As of now, there is no implemented function to free memory blocks. Once allocated, memory remains unavailable for future allocations until the program terminates.

## Limitations

- **No Free Function**: Memory cannot be freed or reused yet. Once allocated, memory cannot be reclaimed or recycled.
- **No Fragmentation Handling**: The current design does not address fragmentation or compacting memory.
- **No Metadata**: There's no metadata stored alongside allocated blocks. Future improvements could involve storing block size and allocation status in headers.

## Future Improvements

The project is a work in progress, and there are many potential improvements. Some of the ideas for future work include:

- **Memory Freeing**: Implement a `my_free()` function that allows deallocating memory and adding it back to the available pool.
- **Block Merging**: When memory is freed, merge adjacent free blocks to prevent fragmentation and optimize space.
- **Reused Allocations**: Track freed blocks and allow for reusing freed memory for future allocations.
- **Memory Fragmentation Handling**: Implement techniques to reduce fragmentation and handle cases where the memory pool is inefficiently utilized.
- **Thread Safety**: Make the allocator thread-safe for concurrent allocations and deallocations.
- **Extended Memory Pool**: Implement the ability to expand the memory pool dynamically when more space is needed (e.g., when the initial pool is exhausted).

## Installation

### Prerequisites

- A C compiler such as `gcc` or `clang`.
- Make or CMake for project management (optional for advanced users).
