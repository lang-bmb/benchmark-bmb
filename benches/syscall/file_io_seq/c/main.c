// System Call Benchmark: Sequential File I/O (C baseline)
// Goal: Measure sequential file read/write performance
//
// Tests write followed by read of data

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ITERATIONS 1000
#define CONTENT "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define CONTENT_LEN 72

// Write and read file
int64_t write_and_read(const char* path, const char* content) {
    // Write
    FILE* f = fopen(path, "w");
    if (!f) return 0;
    fwrite(content, 1, CONTENT_LEN, f);
    fclose(f);

    // Read
    f = fopen(path, "r");
    if (!f) return 0;
    char buffer[256];
    size_t len = fread(buffer, 1, sizeof(buffer), f);
    fclose(f);

    return (int64_t)len;
}

int main() {
    const char* path = "benchmark_test_file.tmp";
    int64_t total = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        total += write_and_read(path, CONTENT);
    }

    // Cleanup
    remove(path);

    printf("Total: %lld\n", (long long)total);
    return 0;
}
