// Convex Hull — monotone chain algorithm
// Measures: sorting, cross product, stack operations
// Workload: N=5000 points, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void sort_points(int64_t* xs, int64_t* ys, int64_t n) {
    // Simple O(n^2) selection sort by x then y
    for (int64_t i = 0; i < n - 1; i++) {
        int64_t best = i;
        for (int64_t j = i + 1; j < n; j++) {
            if (xs[j] < xs[best] || (xs[j] == xs[best] && ys[j] < ys[best])) {
                best = j;
            }
        }
        if (best != i) {
            int64_t tmp_x = xs[i]; xs[i] = xs[best]; xs[best] = tmp_x;
            int64_t tmp_y = ys[i]; ys[i] = ys[best]; ys[best] = tmp_y;
        }
    }
}

static int64_t cross(int64_t ox, int64_t oy, int64_t ax, int64_t ay, int64_t bx, int64_t by) {
    return (ax - ox) * (by - oy) - (ay - oy) * (bx - ox);
}

static int64_t convex_hull(int64_t* xs, int64_t* ys, int64_t n, int64_t* hx, int64_t* hy) {
    sort_points(xs, ys, n);

    int64_t k = 0;

    // Build lower hull
    for (int64_t i = 0; i < n; i++) {
        while (k >= 2 && cross(hx[k-2], hy[k-2], hx[k-1], hy[k-1], xs[i], ys[i]) <= 0) {
            k--;
        }
        hx[k] = xs[i];
        hy[k] = ys[i];
        k++;
    }

    // Build upper hull
    int64_t lower_size = k + 1;
    for (int64_t i = n - 2; i >= 0; i--) {
        while (k >= lower_size && cross(hx[k-2], hy[k-2], hx[k-1], hy[k-1], xs[i], ys[i]) <= 0) {
            k--;
        }
        hx[k] = xs[i];
        hy[k] = ys[i];
        k++;
    }

    // k-1 because last point == first point
    return k - 1;
}

int main() {
    int64_t N = 1000;
    int64_t ITERS = 500;
    int64_t* xs = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* ys = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* hx = (int64_t*)malloc(2 * N * sizeof(int64_t));
    int64_t* hy = (int64_t*)malloc(2 * N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            xs[i] = seed % 100000;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            ys[i] = seed % 100000;
        }
        int64_t hull_size = convex_hull(xs, ys, N, hx, hy);
        checksum += hull_size;
    }

    printf("%lld\n", (long long)checksum);
    free(xs);
    free(ys);
    free(hx);
    free(hy);
    return 0;
}
