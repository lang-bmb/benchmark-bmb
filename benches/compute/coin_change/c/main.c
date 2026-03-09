// Coin Change — classic DP, minimize coins for amount
// Measures: 1D DP array access, min operation in loop
// Workload: 6 coins, amount=50000, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t coin_change(int64_t* coins, int64_t num_coins, int64_t amount, int64_t* dp) {
    int64_t inf = amount + 1;
    for (int64_t i = 0; i <= amount; i++) dp[i] = inf;
    dp[0] = 0;
    for (int64_t i = 1; i <= amount; i++) {
        for (int64_t c = 0; c < num_coins; c++) {
            int64_t coin = coins[c];
            if (coin <= i) {
                int64_t candidate = dp[i - coin] + 1;
                if (candidate < dp[i]) dp[i] = candidate;
            }
        }
    }
    return dp[amount];
}

int main() {
    int64_t num_coins = 6;
    int64_t coins[] = {1, 5, 10, 25, 50, 100};
    int64_t amount = 50000;
    int64_t ITERS = 200;
    int64_t* dp = (int64_t*)malloc((amount + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        checksum += coin_change(coins, num_coins, amount + iter, dp);
    }

    printf("%lld\n", (long long)checksum);
    free(dp);
    return 0;
}