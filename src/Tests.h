#pragma once

#include "Main.h"
#include "Deallocation.h"
#include "Allocation.h"

void TestBasicAllocateAndFree() 
{
    void *block1 = AllocateMemory(100);
    if (block1 == NULL) {
        ERROR_PRINT("Failed to allocate 100 bytes");
        return;
    }
    SUCCESS_PRINT("Successfully allocated 100 bytes");

    if (FreeMemory(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
}

void TestMultipleAllocations() 
{
    void *block1 = AllocateMemory(100);
    assert(block1 != NULL);
    SUCCESS_PRINT("Successfully allocated 100 bytes for block1");

    void *block2 = AllocateMemory(200);
    assert(block2 != NULL);
    SUCCESS_PRINT("Successfully allocated 200 bytes for block2");

    void *block3 = AllocateMemory(50);
    assert(block3 != NULL);
    SUCCESS_PRINT("Successfully allocated 50 bytes for block3");

    // Now deallocate the blocks
    if (FreeMemory(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
    if (FreeMemory(block2)) {
        SUCCESS_PRINT("Successfully deallocated block2");
    }
    else {
        ERROR_PRINT("Failed to deallocate block2");
    }
    if (FreeMemory(block3)) {
        SUCCESS_PRINT("Successfully deallocated block3");
    }
    else {
        ERROR_PRINT("Failed to deallocate block3");
    }
}

void TestExceedingMemoryPool()
{
    void *block1 = AllocateMemory(MEMORY_SIZE + 1);  // Trying to allocate more than the available memory
    if (block1 == NULL) {
        ERROR_PRINT("Attempted to allocate more memory than the pool size.");
        return;
    }
}

// Will always fail!!
void TestMemoryPool()
{
    void *block1 = AllocateMemory(MEMORY_SIZE);  
    if (block1 == NULL) {
        ERROR_PRINT("Attempted to allocate memory_size and failed.");
        return;
    }
    SUCCESS_PRINT("Successfully allocated MEMORY_SIZE bytes.");
}

void TestDeallocateInvalidMemory() // TODO: Fix
{
    void *invalidPtr = (void *)0x7f6f58b2a100;  // Some arbitrary address that wasn’t allocated (could be used by a cheater?)
    FreeMemory(invalidPtr);  // It should safely do nothing without crashing

    // Optionally, you can also assert if any "error" messages are printed if you have error handling mechanisms
    SUCCESS_PRINT("Deallocated invalid memory (should have done nothing).");
}

void TestReallocateFreedMemory() // TODO: Fix
{
    void *block1 = AllocateMemory(100);
    assert(block1 != NULL);
    SUCCESS_PRINT("Successfully allocated 100 bytes for block1");

    if (FreeMemory(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
    SUCCESS_PRINT("Successfully deallocated block1");

    // Reallocate and check if we get the same or a new block
    void *block2 = AllocateMemory(100);
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
    void *block1 = AllocateMemory(200);
    void *block2 = AllocateMemory(100);
    void *block3 = AllocateMemory(50);

    if (FreeMemory(block1)) {
        SUCCESS_PRINT("Successfully deallocated block1");
    }
    else {
        ERROR_PRINT("Failed to deallocate block1");
    }
    if (FreeMemory(block2)) {
        SUCCESS_PRINT("Successfully deallocated block2");
    }
    else {
        ERROR_PRINT("Failed to deallocate block2");
    }

    // After freeing some blocks, try allocating a larger block and see if it works
    void *block4 = AllocateMemory(250);  // Should succeed if coalescing works
    assert(block4 != NULL);
    SUCCESS_PRINT("Successfully allocated 250 bytes after freeing blocks 1 and 2");

    if (FreeMemory(block3)) {
        SUCCESS_PRINT("Successfully deallocated block3");
    }
    else {
        ERROR_PRINT("Failed to deallocate block3");
    }
    if (FreeMemory(block4)) {
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
            void *block = AllocateMemory(size);
            
            if (block != NULL) {
                printf("Allocated %zu bytes at %p\n", size, block);
                allocations[num_allocations++] = block;
            } else {
                printf("Allocation failed for %zu bytes\n", size);
            }
        } else if (num_allocations > 0) {
            // Perform deallocation
            int idx = rand() % num_allocations;
            FreeMemory(allocations[idx]);
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

// Allocation Tests
void TEST_AllocateMemory_1()
{
    void *block1 = AllocateMemory(100);
    if (block1 != NULL) {
        SUCCESS_PRINT("100 bytes allocated (block1)");
    } else {
        ERROR_PRINT("Failed to allocate 100 bytes (block1)");
    }
}

// Should fail because 100 + 950 > 1024
void TEST_AllocateMemory_2()
{
    void *block2 = AllocateMemory(950); 
    if (block2 != NULL) {
        SUCCESS_PRINT("950 bytes allocated (block2)");
    } else {
        ERROR_PRINT("Failed to allocate 950 bytes (block2)");
    }
}


