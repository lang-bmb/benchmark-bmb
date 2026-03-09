// Array Stock Span — compute stock span using stack
// Measures: stack operations, sequential access
// Workload: N=500000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 1000;
    int64_t* prices = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* span = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* stack = (int64_t*)malloc(N * sizeof(int64_t));  // stack of indices
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            prices[i] = seed % 10000;
        }

        int64_t top = -1;
        for (int64_t i = 0; i < N; i++) {
            while (top >= 0 && prices[stack[top]] <= prices[i]) {
                top--;
            }
            span[i] = (top < 0) ? (i + 1) : (i - stack[top]);
            stack[++top] = i;
        }

        int64_t sum = 0;
        for (int64_t i = 0; i < N; i++) sum += span[i];
        checksum += sum;
    }
    printf("%lld\n", (long long)checksum);
    free(prices);
    free(span);
    free(stack);
    return 0;
}
