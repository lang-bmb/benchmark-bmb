// Monotone Stack — next smaller element for each position
// Measures: stack operations, register tracking
// Workload: N=500000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* result = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* stack = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }

        int64_t top = -1;
        for (int64_t i = 0; i < N; i++) {
            while (top >= 0 && arr[stack[top]] >= arr[i]) {
                result[stack[top]] = i;
                top--;
            }
            top++;
            stack[top] = i;
        }
        while (top >= 0) {
            result[stack[top]] = -1;
            top--;
        }

        int64_t sum = 0;
        for (int64_t i = 0; i < N; i++) {
            sum += result[i];
        }
        checksum += sum;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(result);
    free(stack);
    return 0;
}
