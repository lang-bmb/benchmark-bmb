// Collatz Length — compute Collatz sequence length for each number
// Measures: conditional branches, integer arithmetic, unpredictable branching
// Workload: N=1000000, 100 iterations

#include <stdio.h>
#include <stdint.h>

static int64_t collatz_len(int64_t n) {
    int64_t len = 0;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        len++;
    }
    return len;
}

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 30;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 1; i <= N; i++) {
            checksum += collatz_len(i);
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
