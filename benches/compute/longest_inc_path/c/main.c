// Longest Increasing Path — DFS with memoization
// Measures: graph DFS, memoization, 2D grid traversal
// Workload: 100x100 grid, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 100
#define ITERS 1000

static int64_t solve(int64_t* grid, int64_t* dp, int64_t* stack_r,
                     int64_t* stack_c, int64_t* stack_di, int64_t n) {
    // directions: up, down, left, right
    int64_t dr[4] = {-1, 1, 0, 0};
    int64_t dc[4] = {0, 0, -1, 1};

    // Initialize dp to 0
    for (int64_t i = 0; i < n * n; i++) {
        dp[i] = 0;
    }

    int64_t max_path = 0;

    for (int64_t sr = 0; sr < n; sr++) {
        for (int64_t sc = 0; sc < n; sc++) {
            if (dp[sr * n + sc] > 0) continue;

            // Iterative DFS with stack
            int64_t sp = 0;
            stack_r[sp] = sr;
            stack_c[sp] = sc;
            stack_di[sp] = 0;
            sp = 1;

            while (sp > 0) {
                int64_t top = sp - 1;
                int64_t r = stack_r[top];
                int64_t c = stack_c[top];
                int64_t di = stack_di[top];

                if (di < 4) {
                    int64_t nr = r + dr[di];
                    int64_t nc = c + dc[di];
                    stack_di[top] = di + 1;

                    if (nr >= 0 && nr < n && nc >= 0 && nc < n &&
                        grid[nr * n + nc] > grid[r * n + c]) {
                        if (dp[nr * n + nc] == 0) {
                            // Not yet computed, push onto stack
                            stack_r[sp] = nr;
                            stack_c[sp] = nc;
                            stack_di[sp] = 0;
                            sp++;
                        } else {
                            // Already computed, update current
                            int64_t candidate = 1 + dp[nr * n + nc];
                            if (candidate > dp[r * n + c]) {
                                dp[r * n + c] = candidate;
                            }
                        }
                    }
                } else {
                    // All directions explored
                    if (dp[r * n + c] == 0) {
                        dp[r * n + c] = 1;
                    }
                    sp--;
                    // Update parent
                    if (sp > 0) {
                        int64_t pr = stack_r[sp - 1];
                        int64_t pc = stack_c[sp - 1];
                        int64_t candidate = 1 + dp[r * n + c];
                        if (candidate > dp[pr * n + pc]) {
                            dp[pr * n + pc] = candidate;
                        }
                    }
                }
            }

            if (dp[sr * n + sc] > max_path) {
                max_path = dp[sr * n + sc];
            }
        }
    }
    return max_path;
}

int main() {
    int64_t n = N;
    int64_t iters = ITERS;
    int64_t* grid = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* stack_r = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* stack_c = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* stack_di = (int64_t*)malloc(n * n * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        // Fill grid with LCG random values
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < n * n; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            grid[i] = seed % 10000;
        }
        checksum += solve(grid, dp, stack_r, stack_c, stack_di, n);
    }
    printf("%lld\n", (long long)checksum);
    free(grid);
    free(dp);
    free(stack_r);
    free(stack_c);
    free(stack_di);
    return 0;
}
