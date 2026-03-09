// Stock Buy/Sell — max profit with single transaction
// Measures: register tracking (min_price, max_profit), sequential scan
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* prices = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            prices[i] = seed % 10000;
        }

        int64_t min_price = prices[0];
        int64_t max_profit = 0;

        for (int64_t i = 1; i < N; i++) {
            int64_t price = prices[i];
            int64_t profit = price - min_price;
            if (profit > max_profit) max_profit = profit;
            if (price < min_price) min_price = price;
        }
        checksum += max_profit;
    }
    printf("%lld\n", (long long)checksum);
    free(prices);
    return 0;
}
