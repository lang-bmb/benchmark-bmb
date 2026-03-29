// Separate compilation unit: library function (no purity info)
// Compiled separately: clang -c -O3 lib.c -o lib.o
// Without LTO, the caller cannot know this function is pure.

#include <stdint.h>

int64_t compute_heavy(int64_t x) {
    int64_t acc = x;
    for (int i = 0; i < 100; i++) {
        acc = ((acc * 1103515245 + 12345) >> 16) & 32767;
    }
    return acc;
}
