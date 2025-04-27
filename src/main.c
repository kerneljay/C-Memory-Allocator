#include "Main.h"

#include "Deallocation.h"

// Initialize the memory pool
bool InitAllocator()
{
    if (memory == 0)
    {
        ERROR_PRINT("Failed to allocate memory (init)");
        return false;
    }

    current = memory;
    CYAN_PRINT("Jay's Memory Allocator Initialised");
    CYAN_PRINT("-----------------------------------");
    return true;
}


void RealMain()
{
    assert(InitAllocator());
    // AllocateMemoryForBlock1();
    // AllocateMemoryForBlock2();
    TestDeallocation();
}

int main() 
{
    RealMain();
    CYAN_PRINT("-----------------------------------");
    return 0;
}
