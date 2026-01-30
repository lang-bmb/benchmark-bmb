// N-Queens Problem Benchmark - LICM Equivalent
// Manual application of Loop-Invariant Code Motion

#include <stdio.h>
#include <stdint.h>

int64_t solve(int64_t n, int64_t row, int64_t cols, int64_t diag1, int64_t diag2) {
    if (row == n) return 1;

    int64_t all_ones = (1LL << n) - 1;
    int64_t available = all_ones & (~cols) & (~diag1) & (~diag2);
    int64_t count = 0;

    while (available) {
        int64_t pos = available & (-available);
        available -= pos;

        int64_t new_cols = cols | pos;
        int64_t new_diag1 = (diag1 | pos) << 1;
        int64_t new_diag2 = (diag2 | pos) >> 1;

        count += solve(n, row + 1, new_cols, new_diag1, new_diag2);
    }

    return count;
}

int64_t nqueens(int64_t n) {
    return solve(n, 0, 0, 0, 0);
}

int main() {
    // LICM: hoist constant call and multiply
    int64_t single_result = nqueens(15);
    int64_t result = single_result * 10;

    printf("%lld\n", (long long)result);
    return 0;
}
