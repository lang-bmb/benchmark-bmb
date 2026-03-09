// Tower of Hanoi benchmark — iterative simulation
// Measures: loop performance, bitwise operations, modular arithmetic
// Workload: N=25 disks (2^25-1 moves), 30 iterations
// Uses iterative binary algorithm: move disk (lowest set bit of step)

#include <stdio.h>
#include <stdint.h>

static int64_t hanoi_iterative(int64_t n) {
    int64_t total = (1LL << n) - 1;
    int64_t move_sum = 0;
    for (int64_t step = 1; step <= total; step++) {
        // Find lowest set bit position = which disk to move
        int64_t disk = 0;
        int64_t tmp = step;
        while ((tmp & 1) == 0) {
            disk++;
            tmp >>= 1;
        }
        move_sum += disk;
    }
    return move_sum;
}

int main() {
    int64_t n = 25;
    int64_t iters = 30;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        int64_t result = hanoi_iterative(n);
        checksum += result;
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
