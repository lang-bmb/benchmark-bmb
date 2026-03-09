// Array Max Area Island — max area of island in grid (DFS)
// Measures: stack-based DFS, area tracking, grid traversal
// Workload: 300x300 grid, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t ROWS = 300;
    int64_t COLS = 300;
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

        int64_t max_area = 0;

        for (int64_t i = 0; i < N; i++) {
            if (grid[i] == 1) {
                // DFS flood fill, track area
                int64_t area = 0;
                int64_t top = 0;
                stack[top] = i;
                grid[i] = 0;

                while (top >= 0) {
                    int64_t pos = stack[top];
                    top--;
                    area++;
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
                if (area > max_area) max_area = area;
            }
        }
        checksum += max_area;
    }
    printf("%lld\n", (long long)checksum);
    free(grid);
    free(stack);
    return 0;
}
