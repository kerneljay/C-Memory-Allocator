#pragma once

#include "Deallocation.h"

void CoalesceBlocks() {
    BlockHeader *block = free_list;
    while (block != NULL && block->next != NULL) {
        // Check if the current block and the next block are adjacent
        if ((void *)block + block->size + sizeof(BlockHeader) == (void *)block->next) {
            // Merge the two adjacent blocks
            block->size += sizeof(BlockHeader) + block->next->size;
            block->next = block->next->next;  // Remove the next block from the free list
            INFO_PRINT("Blocks merged (CoalesceBlocks)");
        } else {
            // Move to the next block if no merging is required
            block = block->next;
            INFO_PRINT("No merging required (CoalesceBlocks)");
        }
    }
}
