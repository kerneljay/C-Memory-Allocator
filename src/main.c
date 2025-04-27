#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#define MEMORY_SIZE 1024

// Simple memory pool
static char memory[MEMORY_SIZE];
static char *memory_start = memory;
static char *memory_end = memory + MEMORY_SIZE;
static char *current;

// Initialize the memory pool
bool InitAllocator()
{
    if (memory == 0)
    {
        printf("Failed to allocate memory");
        return false;
    }

    current = memory;
    return true;
}

// Custom/Simple malloc-like memory allocator
void *CustomMemoryAllocate(size_t size)
{
    if ((current + size) > memory_end) {
        return NULL; // Not enough memory
    }

    void *pointer = current;
    current += size; // Move the current pointer forward
    return pointer;
}


void AllocateMemoryForBlock1()
{
    void *block1 = CustomMemoryAllocate(100);
    if (block1 != NULL) {
        // Do something with block1
        printf("Success: Block 1 allocated at address %p\n", block1);
    } else {
        printf("Failed: Not enough memory for block 1\n");
    }
}

void AllocateMemoryForBlock2()
{
    void *block2 = CustomMemoryAllocate(950); // Should fail because 100 + 950 > 1024
    if (block2 != NULL) {
        // Do something with block2
        printf("Success: Block 2 allocated at address %p\n", block2);
    } else {
        printf("Failed: Not enough memory for block 2\n");
    }
}


void RealMain()
{
    printf("C Memory Allocator\n");
    assert(InitAllocator());
    AllocateMemoryForBlock1();
    AllocateMemoryForBlock2();
}





int main() 
{
    RealMain();
    return 0;
}

