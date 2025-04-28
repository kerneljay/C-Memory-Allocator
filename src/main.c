#include "Main.h"

#include "Deallocation.h"
#include "Allocation.h"
#include "Tests.h"


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
    // TEST_AllocateMemory_1();
    // TEST_AllocateMemory_2();
    TestDeallocation();
    CYAN_PRINT("-----------------------------------");
}

int main() 
{
    RealMain();
    return 0;
}
