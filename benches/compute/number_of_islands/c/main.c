// Number of Islands — DFS flood fill on grid
// Measures: stack-based DFS, grid traversal
// Workload: 500x500 grid, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t ROWS = 500;
    int64_t COLS = 500;
    int64_t N = ROWS * COLS;
    int64_t ITERS = 200;
    int64_t* grid = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* stack = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            grid[i] = (seed % 3 == 0) ? 0 : 1; // ~67% land
        }

        int64_t islands = 0;

        for (int64_t i = 0; i < N; i++) {
            if (grid[i] == 1) {
                islands++;
                // DFS flood fill
                int64_t top = 0;
                stack[top] = i;
                grid[i] = 0;

                while (top >= 0) {
                    int64_t pos = stack[top];
                    top--;
                    int64_t r = pos / COLS;
                    int64_t c = pos % COLS;

                    // Up
                    if (r > 0 && grid[(r-1)*COLS + c] == 1) {
                        grid[(r-1)*COLS + c] = 0;
                        top++;
                        stack[top] = (r-1)*COLS + c;
                    }
                    // Down
                    if (r < ROWS-1 && grid[(r+1)*COLS + c] == 1) {
                        grid[(r+1)*COLS + c] = 0;
                        top++;
                        stack[top] = (r+1)*COLS + c;
                    }
                    // Left
                    if (c > 0 && grid[r*COLS + c-1] == 1) {
                        grid[r*COLS + c-1] = 0;
                        top++;
                        stack[top] = r*COLS + c-1;
                    }
                    // Right
                    if (c < COLS-1 && grid[r*COLS + c+1] == 1) {
                        grid[r*COLS + c+1] = 0;
                        top++;
                        stack[top] = r*COLS + c+1;
                    }
                }
            }
        }
        checksum += islands;
    }
    printf("%lld\n", (long long)checksum);
    free(grid);
    free(stack);
    return 0;
}
