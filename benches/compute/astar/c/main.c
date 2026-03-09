// A* pathfinding benchmark — heuristic search on a grid
// Measures: priority queue, heuristic computation, grid traversal
// Workload: 200x200 grid, 500 path queries, random obstacles

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GRID_SIZE 200
#define TOTAL (GRID_SIZE * GRID_SIZE)
#define QUERIES 500
#define INF 999999999

static void heap_swap(int64_t* f, int64_t* n, int64_t a, int64_t b) {
    int64_t tf = f[a]; f[a] = f[b]; f[b] = tf;
    int64_t tn = n[a]; n[a] = n[b]; n[b] = tn;
}
static void heap_up(int64_t* f, int64_t* n, int64_t i) {
    while (i > 0) {
        int64_t p = (i - 1) / 2;
        if (f[i] < f[p]) { heap_swap(f, n, i, p); i = p; }
        else break;
    }
}
static void heap_down(int64_t* f, int64_t* n, int64_t sz, int64_t i) {
    while (1) {
        int64_t s = i, l = 2*i+1, r = 2*i+2;
        if (l < sz && f[l] < f[s]) s = l;
        if (r < sz && f[r] < f[s]) s = r;
        if (s == i) break;
        heap_swap(f, n, i, s);
        i = s;
    }
}

static int64_t abs64(int64_t x) { return x < 0 ? -x : x; }

static int64_t manhattan(int64_t a, int64_t b, int64_t w) {
    int64_t ar = a / w, ac = a % w;
    int64_t br = b / w, bc = b % w;
    return abs64(ar - br) + abs64(ac - bc);
}

static int64_t astar(const int64_t* grid, int64_t w, int64_t h,
                     int64_t src, int64_t dst,
                     int64_t* g, int64_t* heap_f, int64_t* heap_n) {
    int64_t total = w * h;
    for (int64_t i = 0; i < total; i++) g[i] = INF;
    g[src] = 0;

    int64_t hsz = 0;
    heap_f[0] = manhattan(src, dst, w);
    heap_n[0] = src;
    hsz = 1;

    int64_t dx[4] = {-1, 1, 0, 0};
    int64_t dy[4] = {0, 0, -1, 1};

    while (hsz > 0) {
        int64_t u = heap_n[0];
        hsz--;
        heap_f[0] = heap_f[hsz];
        heap_n[0] = heap_n[hsz];
        if (hsz > 0) heap_down(heap_f, heap_n, hsz, 0);

        if (u == dst) return g[dst];

        int64_t ur = u / w, uc = u % w;
        int64_t gu = g[u];

        for (int64_t d = 0; d < 4; d++) {
            int64_t nr = ur + dx[d];
            int64_t nc = uc + dy[d];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            int64_t v = nr * w + nc;
            if (grid[v] == 1) continue; // wall
            int64_t ng = gu + 1;
            if (ng < g[v]) {
                g[v] = ng;
                int64_t f = ng + manhattan(v, dst, w);
                heap_f[hsz] = f;
                heap_n[hsz] = v;
                heap_up(heap_f, heap_n, hsz);
                hsz++;
            }
        }
    }
    return -1; // no path
}

int main() {
    int64_t w = GRID_SIZE, h = GRID_SIZE;
    int64_t total = w * h;
    int64_t* grid = (int64_t*)calloc(total, sizeof(int64_t));
    int64_t* g = (int64_t*)malloc(total * sizeof(int64_t));
    int64_t* heap_f = (int64_t*)malloc(total * sizeof(int64_t));
    int64_t* heap_n = (int64_t*)malloc(total * sizeof(int64_t));

    // Generate random obstacles (~20% density)
    int64_t seed = 99999;
    for (int64_t i = 0; i < total; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        grid[i] = (seed % 100 < 20) ? 1 : 0;
    }
    // Ensure corners are clear
    grid[0] = 0;
    grid[total - 1] = 0;

    int64_t checksum = 0;
    for (int64_t q = 0; q < QUERIES; q++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t src = seed % total;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t dst = seed % total;
        // Clear src/dst cells
        grid[src] = 0;
        grid[dst] = 0;
        int64_t dist = astar(grid, w, h, src, dst, g, heap_f, heap_n);
        checksum += dist;
    }
    printf("%lld\n", (long long)checksum);
    free(grid); free(g); free(heap_f); free(heap_n);
    return 0;
}
