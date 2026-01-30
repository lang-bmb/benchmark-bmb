// Ackermann Function Benchmark - Iterative Version
// For fair comparison with BMB's automatic TCO
// Uses explicit stack to simulate recursion

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STACK_SIZE 100000

int64_t ackermann_iter(int64_t m, int64_t n) {
    // Stack to hold pending (m, n) pairs
    int64_t* stack_m = malloc(STACK_SIZE * sizeof(int64_t));
    int64_t* stack_n = malloc(STACK_SIZE * sizeof(int64_t));
    int top = 0;

    stack_m[top] = m;
    stack_n[top] = n;
    top++;

    int64_t result = 0;

    while (top > 0) {
        top--;
        m = stack_m[top];
        n = stack_n[top];

        while (1) {
            if (m == 0) {
                result = n + 1;
                break;
            } else if (n == 0) {
                m = m - 1;
                n = 1;
                // Continue loop (tail call optimization)
            } else {
                // Need to compute ackermann(m, n-1) first
                // Push ackermann(m-1, ?) for later
                stack_m[top] = m - 1;
                stack_n[top] = -1;  // Placeholder, will use result
                top++;
                // Continue with ackermann(m, n-1)
                n = n - 1;
            }
        }

        // Process pending calls that need result
        while (top > 0 && stack_n[top - 1] == -1) {
            top--;
            m = stack_m[top];
            n = result;

            while (1) {
                if (m == 0) {
                    result = n + 1;
                    break;
                } else if (n == 0) {
                    m = m - 1;
                    n = 1;
                } else {
                    stack_m[top] = m - 1;
                    stack_n[top] = -1;
                    top++;
                    n = n - 1;
                }
            }
        }
    }

    free(stack_m);
    free(stack_n);
    return result;
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 1000; i++) {
        result += ackermann_iter(3, 10);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
