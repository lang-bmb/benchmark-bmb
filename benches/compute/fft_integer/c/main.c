// Integer FFT (Cooley-Tukey) benchmark — butterfly operations on scaled integers
// Measures: bit-reversal permutation, butterfly pattern, integer arithmetic
// Workload: N=1024, 5000 iterations, scaled by 1000

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Pre-computed sine table (sin * 1000) for N=1024
// We only need sin(2*pi*k/N) for k=0..N/2-1
// Approximation: sin(x) ~ x - x^3/6 + x^5/120 for small x (scaled)
// For simplicity, use a lookup approach with LCG-seeded values won't work.
// Instead, use integer approximation of twiddle factors.

// Bit-reverse an index for log2(N) bits
static int64_t bit_reverse(int64_t x, int64_t bits) {
    int64_t result = 0;
    for (int64_t i = 0; i < bits; i++) {
        result = (result << 1) | (x & 1);
        x >>= 1;
    }
    return result;
}

// Integer FFT with scaled arithmetic (scale = 1000)
// real[] and imag[] are the real and imaginary parts
// cos_table[] and sin_table[] hold cos(2*pi*k/N)*1000 and sin(2*pi*k/N)*1000
static void fft(int64_t* real, int64_t* imag, int64_t n, int64_t bits,
                const int64_t* cos_table, const int64_t* sin_table) {
    // Bit-reversal permutation
    for (int64_t i = 0; i < n; i++) {
        int64_t j = bit_reverse(i, bits);
        if (j > i) {
            int64_t tmp;
            tmp = real[i]; real[i] = real[j]; real[j] = tmp;
            tmp = imag[i]; imag[i] = imag[j]; imag[j] = tmp;
        }
    }

    // Butterfly operations
    for (int64_t len = 2; len <= n; len *= 2) {
        int64_t half = len / 2;
        int64_t step = n / len;
        for (int64_t i = 0; i < n; i += len) {
            for (int64_t j = 0; j < half; j++) {
                int64_t idx = j * step;
                int64_t wr = cos_table[idx];  // cos * 1000
                int64_t wi = sin_table[idx];   // -sin * 1000

                int64_t ur = real[i + j];
                int64_t ui = imag[i + j];
                // t = w * data[i+j+half], scaled: divide by 1000
                int64_t tr = (wr * real[i + j + half] - wi * imag[i + j + half]) / 1000;
                int64_t ti = (wr * imag[i + j + half] + wi * real[i + j + half]) / 1000;

                real[i + j] = ur + tr;
                imag[i + j] = ui + ti;
                real[i + j + half] = ur - tr;
                imag[i + j + half] = ui - ti;
            }
        }
    }
}

int main() {
    int64_t N = 1024;
    int64_t BITS = 10;  // log2(1024)
    int64_t ITERS = 5000;
    int64_t SCALE = 1000;

    int64_t* real_arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* imag_arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* cos_table = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* sin_table = (int64_t*)malloc(N * sizeof(int64_t));

    // Build twiddle factor tables using integer approximation
    // cos(2*pi*k/N) and -sin(2*pi*k/N) scaled by 1000
    // Use Taylor series: cos(x) ~ 1 - x^2/2 + x^4/24, sin(x) ~ x - x^3/6 + x^5/120
    // where x = 2*pi*k/N, but we work in fixed-point (pi*1000000 = 3141592)
    // Simpler: precompute using integer recurrence
    // For reproducibility, use a well-known integer approximation:
    // angle = 2*pi*k/N in units of 1/N full turns
    // cos(2*pi*k/N)*1000 via Chebyshev/lookup
    // To keep it simple and deterministic, compute via:
    //   sin(a) ~ a - a^3/6 where a in radians*1000000
    //   cos(a) ~ 1000 - a^2/2000 where a in radians*1000000
    // Actually let's just use a simple integer cordic-like approach
    // For exact reproducibility, hardcode using the recurrence with scaling

    // Use integer-scaled angle: theta_k = 2 * PI * k / N
    // PI_SCALED = 3141593 (pi * 10^6)
    // theta_k_scaled = 2 * 3141593 * k / N  (in units of 10^-6 radians)
    // sin(theta) * 1000: use 4th order Taylor
    for (int64_t k = 0; k < N; k++) {
        // angle in micro-radians: 2 * pi * k / N * 10^6
        // = 2 * 3141593 * k / 1024
        int64_t a = 2 * 3141593 * k / N;  // micro-radians
        // Normalize to [-pi, pi] in micro-radians
        while (a > 3141593) a -= 2 * 3141593;
        while (a < -3141593) a += 2 * 3141593;
        // sin(a) * 1000 where a is in micro-radians (a * 10^-6 radians)
        // sin(x) ~ x - x^3/6 + x^5/120
        // x = a / 10^6
        // sin(x)*1000 = a/1000 - a^3/(6*10^15) + ...
        // To avoid overflow with i64, be careful:
        // Term1 = a / 1000
        // Term2 = (a/1000) * (a/1000) * (a/1000) / 6  -- but this loses precision
        // Better: sin(x)*1000 = (a - a^3/6000000000000 + ...) / 1000
        // Let's use: x_milli = a / 1000  (milli-radians)
        // sin(x)*1000 ~ x_milli - x_milli^3 / 6000000 + x_milli^5 / 120000000000
        int64_t xm = a / 1000;  // milli-radians
        int64_t xm2 = xm * xm; // micro-radians^2.. actually milli^2
        int64_t xm3 = xm2 * xm / 1000; // scale back
        int64_t xm5 = xm3 * xm2 / 1000000;
        int64_t s = xm - xm3 / 6 + xm5 / 120;
        // cos(x)*1000 ~ 1000 - x_milli^2/2000 + x_milli^4/24000000
        int64_t xm4 = xm2 * xm2 / 1000000;
        int64_t c = 1000 - xm2 / 2000 + xm4 / 24000;

        cos_table[k] = c;
        sin_table[k] = -s;  // negative for FFT convention
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 9999 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            real_arr[i] = (seed % 2001) - 1000;  // range [-1000, 1000]
            imag_arr[i] = 0;
        }

        fft(real_arr, imag_arr, N, BITS, cos_table, sin_table);

        // Checksum: sum of absolute values of first 16 elements
        int64_t sum = 0;
        for (int64_t i = 0; i < 16; i++) {
            int64_t r = real_arr[i];
            int64_t im = imag_arr[i];
            if (r < 0) r = -r;
            if (im < 0) im = -im;
            sum += r + im;
        }
        checksum += sum;
    }

    printf("%lld\n", (long long)checksum);
    free(real_arr);
    free(imag_arr);
    free(cos_table);
    free(sin_table);
    return 0;
}
