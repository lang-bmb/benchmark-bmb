// Array Majority Element 2 — Boyer-Moore voting for top-2 candidates
// Measures: register carry (cand1, cand2, count1, count2), branchy logic
// Workload: N=2000000 array, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t majority2_sum(int64_t* arr, int64_t n) {
    if (n == 0) return 0;
    int64_t cand1 = 0, cand2 = 1;
    int64_t cnt1 = 0, cnt2 = 0;

    for (int64_t i = 0; i < n; i++) {
        int64_t val = arr[i];
        if (val == cand1) {
            cnt1++;
        } else if (val == cand2) {
            cnt2++;
        } else if (cnt1 == 0) {
            cand1 = val;
            cnt1 = 1;
        } else if (cnt2 == 0) {
            cand2 = val;
            cnt2 = 1;
        } else {
            cnt1--;
            cnt2--;
        }
    }

    // Verify candidates
    cnt1 = 0;
    cnt2 = 0;
    for (int64_t i = 0; i < n; i++) {
        int64_t val = arr[i];
        if (val == cand1) cnt1++;
        else if (val == cand2) cnt2++;
    }

    int64_t threshold = n / 3;
    int64_t result = 0;
    if (cnt1 > threshold) result += cand1;
    if (cnt2 > threshold) result += cand2;
    return result;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10;
        }
        checksum += majority2_sum(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
