// System Call Benchmark: Syscall Overhead (C baseline)
// Goal: Measure minimal system call latency
//
// Uses stat() as a minimal syscall
// Measures overhead of crossing user/kernel boundary

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>

#define ITERATIONS 10000

// v0.51.2: Use _stat64 on Windows for consistent performance across compilers
// clang's default stat() maps to _stat64i32 which is ~3x slower than _stat64
#ifdef _WIN32
#define BMB_STAT _stat64
#define BMB_STAT_STRUCT struct __stat64
#else
#define BMB_STAT stat
#define BMB_STAT_STRUCT struct stat
#endif

// Minimal syscall - stat a path
int64_t check_exists(const char* path) {
    BMB_STAT_STRUCT st;
    return (BMB_STAT(path, &st) == 0) ? 1 : 0;
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
