#include <stdio.h>

// Fibonacci - FAIR iterative version
// Both C and BMB use same O(n) iterative algorithm
// This measures pure loop performance, not algorithmic optimization

long long fibonacci_iter(int n) {
    long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        long long temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    // Run many iterations to get measurable time
    long long total = 0;
    for (int j = 0; j < 10000000; j++) {
        total += fibonacci_iter(42);
    }
    printf("%lld\n", total);
    return 0;
}
