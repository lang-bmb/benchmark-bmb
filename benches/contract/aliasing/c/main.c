// Aliasing optimization benchmark (C version)
// C requires restrict keyword for aliasing hints, less reliable

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

// Without restrict: compiler must assume potential aliasing
void process_arrays(long* a, long* b, int size) {
    for (int i = 0; i < size; i++) {
        long a_val = a[i];
        b[i] = a_val + 1;       // Store to b
        long a_val2 = a[i];     // Must reload - might alias with b
        b[i] += a_val2;
    }
}

// With restrict: compiler can optimize (but not verified)
void process_arrays_restrict(long* restrict a, long* restrict b, int size) {
    for (int i = 0; i < size; i++) {
        long a_val = a[i];
        b[i] = a_val + 1;
        long a_val2 = a[i];     // Can reuse cached value
        b[i] += a_val2;
    }
}

// Vector addition with potential aliasing issues
void vector_add(long* a, long* b, long* c, int size) {
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];  // If c aliases a or b, different result
    }
}

int main() {
    long* a = (long*)malloc(SIZE * sizeof(long));
    long* b = (long*)malloc(SIZE * sizeof(long));
    long* c = (long*)malloc(SIZE * sizeof(long));

    for (int i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = 0;
    }

    long total = 0;
    for (int iter = 0; iter < 100; iter++) {
        process_arrays(a, b, SIZE);
        for (int i = 0; i < SIZE; i++) {
            total += b[i];
        }
    }

    printf("%ld\n", total);

    free(a);
    free(b);
    free(c);
    return 0;
}
