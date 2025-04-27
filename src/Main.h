#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "Print.h"

#define MEMORY_SIZE 1024

// Simple memory pool
static char memory[MEMORY_SIZE];
static char *memory_start = memory;
static char *memory_end = memory + MEMORY_SIZE;
static char *current;

// Define a block header structure to hold size of the allocated block
typedef struct BlockHeader
{
    size_t size;
    struct BlockHeader *next; // Points to the next free block 
} BlockHeader;

// Free list to keep track of available memory blocks
static BlockHeader *free_list = NULL;

bool InitAllocator();
void AllocateMemoryForBlock1();
void AllocateMemoryForBlock2();
void RealMain();
