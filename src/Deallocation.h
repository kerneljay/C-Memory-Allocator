#pragma once

#include "Main.h"
#include "Defragmentation.h"

// typedef struct AllocList {
//     void *ptr;
//     struct AllocList *next;
// } AllocList;

// static AllocList *allocations = NULL;

// Function to get available memory in bytes
size_t GetAvailableMemory()
{
    printf("Available memory: %zu bytes\n", memory_end - current);
    return memory_end - current;  // Available memory is the difference between the end of memory and current pointer
}

// Custom/Simple malloc-like memory allocator
void *CustomMemoryAllocate(size_t size)
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

void AllocateMemoryForBlock1()
{
    void *block1 = CustomMemoryAllocate(100);
    if (block1 != NULL) {
        // Do something with block1
        SUCCESS_PRINT("100 bytes allocated (block1)");
    } else {
        ERROR_PRINT("Failed to allocate 100 bytes (block1)");
    }
}

// Should fail because 100 + 950 > 1024
void AllocateMemoryForBlock2()
{
    void *block2 = CustomMemoryAllocate(950); 
    if (block2 != NULL) {
        SUCCESS_PRINT("950 bytes allocated (block2)");
    } else {
        ERROR_PRINT("Failed to allocate 950 bytes (block2)");
    }
}



// Deallocation function to return memory to the free list
bool CustomMemoryFree(void *pointer)
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

void TestBasicAllocateAndFree() 
{
    void *block1 = CustomMemoryAllocate(100);
    if (block1 == NULL) {
        ERROR_PRINT("Failed to allocate 100 bytes");
        return;
    }
    SUCCESS_PRINT("Successfully allocated 100 bytes");

    if (CustomMemoryFree(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
}

void TestMultipleAllocations() 
{
    void *block1 = CustomMemoryAllocate(100);
    assert(block1 != NULL);
    SUCCESS_PRINT("Successfully allocated 100 bytes for block1");

    void *block2 = CustomMemoryAllocate(200);
    assert(block2 != NULL);
    SUCCESS_PRINT("Successfully allocated 200 bytes for block2");

    void *block3 = CustomMemoryAllocate(50);
    assert(block3 != NULL);
    SUCCESS_PRINT("Successfully allocated 50 bytes for block3");

    // Now deallocate the blocks
    if (CustomMemoryFree(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
    if (CustomMemoryFree(block2)) {
        SUCCESS_PRINT("Successfully deallocated block2");
    }
    else {
        ERROR_PRINT("Failed to deallocate block2");
    }
    if (CustomMemoryFree(block3)) {
        SUCCESS_PRINT("Successfully deallocated block3");
    }
    else {
        ERROR_PRINT("Failed to deallocate block3");
    }
}

void TestExceedingMemoryPool()
{
    void *block1 = CustomMemoryAllocate(MEMORY_SIZE + 1);  // Trying to allocate more than the available memory
    if (block1 == NULL) {
        ERROR_PRINT("Attempted to allocate more memory than the pool size.");
        return;
    }
}

// Will always fail!!
void TestMemoryPool()
{
    void *block1 = CustomMemoryAllocate(MEMORY_SIZE);  
    if (block1 == NULL) {
        ERROR_PRINT("Attempted to allocate memory_size and failed.");
        return;
    }
    SUCCESS_PRINT("Successfully allocated MEMORY_SIZE bytes.");
}

void TestDeallocateInvalidMemory() // TODO: Fix
{
    void *invalidPtr = (void *)0x7f6f58b2a100;  // Some arbitrary address that wasn’t allocated (could be used by a cheater?)
    CustomMemoryFree(invalidPtr);  // It should safely do nothing without crashing

    // Optionally, you can also assert if any "error" messages are printed if you have error handling mechanisms
    SUCCESS_PRINT("Deallocated invalid memory (should have done nothing).");
}

void TestReallocateFreedMemory() // TODO: Fix
{
    void *block1 = CustomMemoryAllocate(100);
    assert(block1 != NULL);
    SUCCESS_PRINT("Successfully allocated 100 bytes for block1");

    if (CustomMemoryFree(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
    SUCCESS_PRINT("Successfully deallocated block1");

    // Reallocate and check if we get the same or a new block
    void *block2 = CustomMemoryAllocate(100);
    assert(block2 != NULL);
    SUCCESS_PRINT("Successfully reallocated 100 bytes (block2)");

    if (block1 != block2) {
        SUCCESS_PRINT("Block1 and Block2 are different blocks (valid case).");
    } else {
        ERROR_PRINT("Block1 and Block2 are the same block (invalid case).");
    }
}

void TestFragmentation()
{
    void *block1 = CustomMemoryAllocate(200);
    void *block2 = CustomMemoryAllocate(100);
    void *block3 = CustomMemoryAllocate(50);

    if (CustomMemoryFree(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
    if (CustomMemoryFree(block2)) {
        SUCCESS_PRINT("Successfully deallocated block2");
    }
    else {
        ERROR_PRINT("Failed to deallocate block2");
    }

    // After freeing some blocks, try allocating a larger block and see if it works
    void *block4 = CustomMemoryAllocate(250);  // Should succeed if coalescing works
    assert(block4 != NULL);
    SUCCESS_PRINT("Successfully allocated 250 bytes after freeing blocks 1 and 2");

    if (CustomMemoryFree(block3)) {
        SUCCESS_PRINT("Successfully deallocated block3");
    }
    else {
        ERROR_PRINT("Failed to deallocate block3");
    }
    if (CustomMemoryFree(block4)) {
        SUCCESS_PRINT("Successfully deallocated block4");
    }
    else {
        ERROR_PRINT("Failed to deallocate block4");
    }
}


#define MAX_ALLOCATION_SIZE 512  // Max allocation size (can be adjusted)
#define NUM_OPERATIONS 1000      // Number of allocations and deallocations to perform
void StressTestMemoryAllocator() 
{
    void *allocations[NUM_OPERATIONS];  // Store pointers to track memory allocated
    int num_allocations = 0;

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Randomly choose whether to allocate or deallocate
        if (rand() % 2 == 0 && num_allocations < NUM_OPERATIONS) {
            // Perform allocation
            size_t size = rand() % MAX_ALLOCATION_SIZE + 1;  // Random size between 1 and MAX_ALLOCATION_SIZE
            void *block = CustomMemoryAllocate(size);
            
            if (block != NULL) {
                printf("Allocated %zu bytes at %p\n", size, block);
                allocations[num_allocations++] = block;
            } else {
                printf("Allocation failed for %zu bytes\n", size);
            }
        } else if (num_allocations > 0) {
            // Perform deallocation
            int idx = rand() % num_allocations;
            CustomMemoryFree(allocations[idx]);
            printf("Freed memory at %p\n", allocations[idx]);
            
            // Move the last allocation to the freed spot (remove the element from the list)
            allocations[idx] = allocations[num_allocations - 1];
            num_allocations--;
        }
    }

    printf("Stress test complete.\n");
}



void TestDeallocation()
{
    // ALLOCATION TESTS
    // TestBasicAllocateAndFree();
    // TestMultipleAllocations();
    // TestReallocateFreedMemory();

    // POOL TESTS
    // TestExceedingMemoryPool();
    // TestMemoryPool();

    // MEMORY TESTS
    // GetAvailableMemory();
    // TestDeallocateInvalidMemory();

    // FRAGMENTATION TESTS
    // TestFragmentation();

    // STRESS TESTS
    StressTestMemoryAllocator();
}
