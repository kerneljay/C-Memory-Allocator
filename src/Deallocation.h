#pragma once

#include "Main.h"

// Deallocation function to return memory to the free list
void CustomMemoryFree(void *pointer)
{
    if (pointer == NULL)
        return;

    // Get the block header by moving back from the user pointer
    BlockHeader *block = (BlockHeader*)pointer - 1;

    // Add the block to the free list
    block->next = free_list;
    free_list = block;
}


void TestDeallocation()
{
   // Allocate and deallocate a block
    void *block1 = CustomMemoryAllocate(100);
    if (block1 != NULL) {
        printf("Allocated Block 1 at %p\n", block1);
        CustomMemoryFree(block1);  // Deallocate Block 1
        printf("Freed Block 1\n");
    }

    // Allocate again to see if we reuse freed memory
    void *block2 = CustomMemoryAllocate(100);
    if (block2 != NULL) {
        printf("Allocated Block 2 at %p (should be reused)\n", block2);
    } else {
        printf("Failed to allocate Block 2\n");
    }
}
