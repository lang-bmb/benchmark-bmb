// Aliasing optimization benchmark (C version)
// C requires restrict keyword for aliasing hints, less reliable

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE 1000

// Without restrict: compiler must assume potential aliasing
void process_arrays(int64_t* a, int64_t* b, int size) {
    for (int i = 0; i < size; i++) {
        int64_t a_val = a[i];
        b[i] = a_val + 1;       // Store to b
        int64_t a_val2 = a[i];     // Must reload - might alias with b
        b[i] += a_val2;
    }
}

// With restrict: compiler can optimize (but not verified)
void process_arrays_restrict(int64_t* restrict a, int64_t* restrict b, int size) {
    for (int i = 0; i < size; i++) {
        int64_t a_val = a[i];
        b[i] = a_val + 1;
        int64_t a_val2 = a[i];     // Can reuse cached value
        b[i] += a_val2;
    }
}

// Vector addition with potential aliasing issues
void vector_add(int64_t* a, int64_t* b, int64_t* c, int size) {
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];  // If c aliases a or b, different result
    }
}

int main() {
    int64_t* a = (int64_t*)malloc(SIZE * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(SIZE * sizeof(int64_t));
    int64_t* c = (int64_t*)malloc(SIZE * sizeof(int64_t));

    for (int i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = 0;
    }

    int64_t total = 0;
    for (int iter = 0; iter < 100; iter++) {
        process_arrays(a, b, SIZE);
        for (int i = 0; i < SIZE; i++) {
            total += b[i];
        }
    }

    printf("%lld\n", (long long)total);

    free(a);
    free(b);
    free(c);
    return 0;
}
