// 2D Kadane — Maximum sum submatrix
// Measures: prefix sum computation, nested loops, 1D Kadane's on columns
// Workload: N=200 matrix, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t kadane_1d(const int64_t* arr, int64_t n) {
    int64_t max_sum = arr[0];
    int64_t cur = arr[0];
    for (int64_t i = 1; i < n; i++) {
        if (cur + arr[i] > arr[i]) {
            cur = cur + arr[i];
        } else {
            cur = arr[i];
        }
        if (cur > max_sum) max_sum = cur;
    }
    return max_sum;
}

static int64_t max_submatrix(const int64_t* mat, int64_t n, int64_t* temp) {
    int64_t best = mat[0];

    for (int64_t left = 0; left < n; left++) {
        // Reset temp
        for (int64_t i = 0; i < n; i++) temp[i] = 0;

        for (int64_t right = left; right < n; right++) {
            // Add column 'right' to temp
            for (int64_t i = 0; i < n; i++) {
                temp[i] += mat[i * n + right];
            }
            // Apply 1D Kadane on temp
            int64_t cur = kadane_1d(temp, n);
            if (cur > best) best = cur;
        }
    }
    return best;
}

int main() {
    int64_t N = 200;
    int64_t ITERS = 100;

    int64_t* mat = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t* temp = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 31337 + iter;
        for (int64_t i = 0; i < N * N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            mat[i] = (seed % 201) - 100;  // range [-100, 100]
        }
        checksum += max_submatrix(mat, N, temp);
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    free(temp);
    return 0;
}
