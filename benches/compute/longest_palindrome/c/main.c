// Longest Palindrome — expand-around-center
// Measures: symmetric array access, conditional branching
// Workload: N=5000 strings, 20000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t longest_palindrome(const int64_t* s, int64_t n) {
    int64_t best = 1;

    // Odd-length palindromes
    for (int64_t c = 0; c < n; c++) {
        int64_t lo = c - 1;
        int64_t hi = c + 1;
        while (lo >= 0 && hi < n && s[lo] == s[hi]) {
            lo--;
            hi++;
        }
        int64_t len = hi - lo - 1;
        if (len > best) best = len;
    }

    // Even-length palindromes
    for (int64_t c = 0; c < n - 1; c++) {
        int64_t lo = c;
        int64_t hi = c + 1;
        while (lo >= 0 && hi < n && s[lo] == s[hi]) {
            lo--;
            hi++;
        }
        int64_t len = hi - lo - 1;
        if (len > best) best = len;
    }

    return best;
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 20000;

    int64_t* s = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 54321 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            s[i] = (seed % 26) + 97;
        }
        checksum += longest_palindrome(s, N);
    }

    printf("%lld\n", (long long)checksum);
    free(s);
    return 0;
}
