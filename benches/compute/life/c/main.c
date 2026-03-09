// Game of Life — Conway's cellular automaton
// Measures: 2D stencil, neighbor counting, conditional update
// Workload: 200x200 grid, 500 generations, 20 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define W 200
#define H 200
#define GENS 500
#define ITERS 20

static int64_t count_neighbors(int64_t* grid, int64_t r, int64_t c) {
    int64_t count = 0;
    for (int64_t dr = -1; dr <= 1; dr++) {
        for (int64_t dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int64_t nr = (r + dr + H) % H;
            int64_t nc = (c + dc + W) % W;
            count += grid[nr * W + nc];
        }
    }
    return count;
}

static int64_t simulate(int64_t* grid, int64_t* tmp) {
    for (int64_t gen = 0; gen < GENS; gen++) {
        for (int64_t r = 0; r < H; r++) {
            for (int64_t c = 0; c < W; c++) {
                int64_t n = count_neighbors(grid, r, c);
                int64_t alive = grid[r * W + c];
                if (alive) {
                    tmp[r * W + c] = (n == 2 || n == 3) ? 1 : 0;
                } else {
                    tmp[r * W + c] = (n == 3) ? 1 : 0;
                }
            }
        }
        // Swap grids
        int64_t* swap = grid;
        for (int64_t i = 0; i < H * W; i++) {
            grid[i] = tmp[i];
        }
        (void)swap;
    }
    // Count live cells
    int64_t live = 0;
    for (int64_t i = 0; i < H * W; i++) {
        live += grid[i];
    }
    return live;
}

int main() {
    int64_t* grid = (int64_t*)malloc(H * W * sizeof(int64_t));
    int64_t* tmp  = (int64_t*)malloc(H * W * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Initialize with LCG
        int64_t seed = 42 + iter;
        for (int64_t i = 0; i < H * W; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            grid[i] = (seed % 4 == 0) ? 1 : 0;
        }
        checksum += simulate(grid, tmp);
    }
    printf("%lld\n", (long long)checksum);
    free(grid);
    free(tmp);
    return 0;
}
