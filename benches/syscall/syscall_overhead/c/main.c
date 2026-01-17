// System Call Benchmark: Syscall Overhead (C baseline)
// Goal: Measure minimal system call latency
//
// Uses stat() as a minimal syscall
// Measures overhead of crossing user/kernel boundary

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>

#define ITERATIONS 10000

// Minimal syscall - stat a path
int64_t check_exists(const char* path) {
    struct stat st;
    return (stat(path, &st) == 0) ? 1 : 0;
}

int main() {
    const char* path = ".";
    int64_t total = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        total += check_exists(path);
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
