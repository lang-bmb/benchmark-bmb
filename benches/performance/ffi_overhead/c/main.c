// FFI Overhead Benchmark (C baseline)
// Measures: Direct C function call overhead (baseline for BMB FFI comparison)
//
// This is the C baseline - it shows the raw cost without FFI overhead

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Test 1: Memory allocation cycles
int64_t test_malloc_cycles(int64_t iterations) {
    int64_t sum = 0;
    for (int64_t i = 0; i < iterations; i++) {
        void* ptr = malloc(1024);  // 1KB allocation
        free(ptr);
        sum++;
    }
    return sum;
}

// Test 2: Memory read/write cycles
int64_t test_memory_ops(int64_t iterations) {
    int64_t sum = 0;
    for (int64_t i = 0; i < iterations; i++) {
        int64_t* ptr = (int64_t*)malloc(64);
        // Write 8 values
        ptr[0] = i;
        ptr[1] = i + 1;
        ptr[2] = i + 2;
        ptr[3] = i + 3;
        ptr[4] = i + 4;
        ptr[5] = i + 5;
        ptr[6] = i + 6;
        ptr[7] = i + 7;
        // Read them back
        int64_t v0 = ptr[0];
        int64_t v1 = ptr[1];
        int64_t v2 = ptr[2];
        int64_t v3 = ptr[3];
        int64_t v4 = ptr[4];
        int64_t v5 = ptr[5];
        int64_t v6 = ptr[6];
        int64_t v7 = ptr[7];
        free(ptr);
        sum += v0 + v1 + v2 + v3 + v4 + v5 + v6 + v7;
    }
    return sum;
}

// Test 3: Mixed operations (realistic workload)
int64_t test_mixed(int64_t iterations) {
    int64_t sum = 0;
    for (int64_t i = 0; i < iterations; i++) {
        // Allocate different sizes
        int64_t* p1 = (int64_t*)malloc(32);
        int64_t* p2 = (int64_t*)malloc(64);
        int64_t* p3 = (int64_t*)malloc(128);
        // Compute and store
        int64_t val = i * i;
        *p1 = val;
        *p2 = val + 1;
        *p3 = val + 2;
        // Read back
        int64_t r1 = *p1;
        int64_t r2 = *p2;
        int64_t r3 = *p3;
        // Free
        free(p1);
        free(p2);
        free(p3);
        sum += r1 + r2 + r3;
    }
    return sum;
}

int main() {
    // Run each test with sufficient iterations for stable measurement
    // Target: ~50ms per test, ~150ms total
    int64_t malloc_result = test_malloc_cycles(1000000);
    int64_t memory_result = test_memory_ops(500000);
    int64_t mixed_result = test_mixed(500000);

    // Output verification
    printf("%lld\n", (long long)malloc_result);
    printf("%lld\n", (long long)memory_result);
    printf("%lld\n", (long long)mixed_result);

    return 0;
}
