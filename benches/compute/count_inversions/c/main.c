// Count inversions benchmark — iterative bottom-up merge sort variant
// Measures: merge-based counting, sequential memory access, branch prediction
// Workload: 50K elements, 200 iterations with different seeds

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t count_inversions(int64_t* arr, int64_t* temp, int64_t n) {
    int64_t total_inv = 0;
    int64_t width = 1;
    while (width < n) {
        int64_t left = 0;
        while (left < n) {
            int64_t mid = left + width;
            int64_t right = mid + width;
            if (right > n) right = n;
            if (mid < n) {
                // Merge [left..mid) and [mid..right), counting inversions
                int64_t i = left;
                int64_t j = mid;
                int64_t k = left;
                while (k < right) {
                    if (i >= mid) {
                        // Left exhausted, take from right
                        temp[k] = arr[j];
                        j++;
                    } else if (j >= right) {
                        // Right exhausted, take from left
                        temp[k] = arr[i];
                        i++;
                    } else if (arr[i] <= arr[j]) {
                        temp[k] = arr[i];
                        i++;
                    } else {
                        // Right element is smaller — count inversions
                        total_inv += (mid - i);
                        temp[k] = arr[j];
                        j++;
                    }
                    k++;
                }
                // Copy merged result back to arr
                for (k = left; k < right; k++) {
                    arr[k] = temp[k];
                }
            }
            left += width * 2;
        }
        width *= 2;
    }
    return total_inv;
}

int main() {
    int64_t N = 50000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* temp = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill array with PRNG values
        int64_t seed = 54321 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        int64_t inv = count_inversions(arr, temp, N);
        checksum += inv;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(temp);
    return 0;
}
