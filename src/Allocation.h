#pragma once

// Custom/Simple malloc-like memory allocator
void *AllocateMemory(size_t size)
{
    GetAvailableMemory();

    // Ensure the block size is a multiple of sizeof(BlockHeader)
    size = (size + sizeof(BlockHeader) - 1) & ~(sizeof(BlockHeader) - 1);

    BlockHeader *prev = NULL;
    BlockHeader *block = free_list;
    
    while (block != NULL) {
        if (block->size >= size) {
            // Found a block large enough, remove it from the free list
            if (prev != NULL) {
                prev->next = block->next;
            } else {
                free_list = block->next;
            }
            return (void *)(block + 1); // Return the address after the block header
        }

        prev = block;
        block = block->next;
    }

    if ((current + sizeof(BlockHeader) + size) > memory_end) {
        return NULL; // Not enough memory
    }


    BlockHeader *new_block = (BlockHeader*)current;
    new_block->size = size;
    current += sizeof(BlockHeader) + size;
    return (void *)(new_block + 1);
}


