#pragma once

#include "Main.h"
#include "Defragmentation.h"

// Function to get available memory in bytes
size_t GetAvailableMemory()
{
    printf("Available memory: %zu bytes\n", memory_end - current);
    return memory_end - current;  // Available memory is the difference between the end of memory and current pointer
}


// Deallocation function to return memory to the free list
bool FreeMemory(void *pointer)
{
    if (pointer == NULL)
        return false;

    // Get the block header by moving back from the user pointer
    BlockHeader *block = (BlockHeader*)pointer - 1;

    // Add the block to the free list
    block->next = free_list;
    free_list = block;

    // Defragment the free list
    CoalesceBlocks();
    GetAvailableMemory();
    return true;
}
