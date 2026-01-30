// Ackermann Function Benchmark - Partial TCO Version
// Matches BMB's automatic optimization:
// ackermann(m-1, ackermann(m, n-1)) becomes:
//   temp = ackermann(m, n-1)  // one recursive call
//   then loop with m-1, temp  // second call is a loop

#include <stdio.h>
#include <stdint.h>

int64_t ackermann_ptco(int64_t m, int64_t n) {
    while (1) {
        if (m == 0) {
            return n + 1;
        } else if (n == 0) {
            // ackermann(m - 1, 1) -> loop
            m = m - 1;
            n = 1;
            // continue loop
        } else {
            // ackermann(m - 1, ackermann(m, n - 1))
            // First compute inner: ackermann(m, n - 1)
            int64_t inner = ackermann_ptco(m, n - 1);
            // Then outer becomes loop: ackermann(m - 1, inner)
            m = m - 1;
            n = inner;
            // continue loop
        }
    }
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 1000; i++) {
        result += ackermann_ptco(3, 10);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
