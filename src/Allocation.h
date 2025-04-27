// #pragma once

// #include "Main.h"
// #include "Deallocation.h"

// // typedef struct AllocList {
// //     void *ptr;
// //     struct AllocList *next;
// // } AllocList;

// // static AllocList *allocations = NULL;

// // Function to get available memory in bytes
// size_t GetAvailableMemory()
// {
//     printf("Available memory: %zu bytes\n", memory_end - current);
//     return memory_end - current;  // Available memory is the difference between the end of memory and current pointer
// }

// // Custom/Simple malloc-like memory allocator
// void *CustomMemoryAllocate(size_t size)
// {
//     GetAvailableMemory();

//     // Ensure the block size is a multiple of sizeof(BlockHeader)
//     size = (size + sizeof(BlockHeader) - 1) & ~(sizeof(BlockHeader) - 1);

//     BlockHeader *prev = NULL;
//     BlockHeader *block = free_list;
    
//     while (block != NULL) {
//         if (block->size >= size) {
//             // Found a block large enough, remove it from the free list
//             if (prev != NULL) {
//                 prev->next = block->next;
//             } else {
//                 free_list = block->next;
//             }
//             return (void *)(block + 1); // Return the address after the block header
//         }

//         prev = block;
//         block = block->next;
//     }

//     if ((current + sizeof(BlockHeader) + size) > memory_end) {
//         return NULL; // Not enough memory
//     }


//     BlockHeader *new_block = (BlockHeader*)current;
//     new_block->size = size;
//     current += sizeof(BlockHeader) + size;
//     return (void *)(new_block + 1);
// }

// void AllocateMemoryForBlock1()
// {
//     void *block1 = CustomMemoryAllocate(100);
//     if (block1 != NULL) {
//         // Do something with block1
//         SUCCESS_PRINT("100 bytes allocated (block1)");
//     } else {
//         ERROR_PRINT("Failed to allocate 100 bytes (block1)");
//     }
// }

// // Should fail because 100 + 950 > 1024
// void AllocateMemoryForBlock2()
// {
//     void *block2 = CustomMemoryAllocate(950); 
//     if (block2 != NULL) {
//         SUCCESS_PRINT("950 bytes allocated (block2)");
//     } else {
//         ERROR_PRINT("Failed to allocate 950 bytes (block2)");
//     }
// }
