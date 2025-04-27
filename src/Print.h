#pragma once

#include "Colours.h"  // Assuming this contains color definitions
#include <stdio.h>

static void SUCCESS_PRINT(const char *message) {
    printf("%s%s %s\n", GREEN, message, RESET);  // Green text
}
static void ERROR_PRINT(const char *message) {
    printf("%s%s %s\n", RED, message, RESET);  // Red text
}
static void INFO_PRINT(const char *message) {
    printf("%s%s %s\n", YELLOW, message, RESET);  // Red text
}

static void CYAN_PRINT(const char *message) {
    printf("%s%s %s\n", CYAN, message, RESET);  // Cyan text
}

// namespace MemoryAllocatorPrint cant use these with C silly..

