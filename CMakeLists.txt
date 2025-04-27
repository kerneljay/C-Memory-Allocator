cmake_minimum_required(VERSION 3.10)
project(c-memory-allocator)

set(CMAKE_CXX_STANDARD 17)

# Define the executable
add_executable(main src/main.cpp)

target_include_directories(main PRIVATE)

# Link against Windows shlwapi library
if(WIN32)
    target_link_libraries(main PRIVATE shlwapi)
endif()
