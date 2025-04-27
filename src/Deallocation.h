#pragma once

#include "Main.h"
#include "Print.h"

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
        SUCCESS_PRINT("100 bytes allocated (TestDeallocation block1)");
        CustomMemoryFree(block1);  // Deallocate Block 1
        SUCCESS_PRINT("100 bytes freed (TestDeallocation block1)");
    }

    // Allocate again to see if we reuse freed memory
    void *block2 = CustomMemoryAllocate(100);
    if (block2 != NULL) {
        SUCCESS_PRINT("100 bytes freed - should be reused? (TestDeallocation block2)");
    } else {
        ERROR_PRINT("Failed to allocate 100 bytes (TestDeallocation block2)");
    }
}
