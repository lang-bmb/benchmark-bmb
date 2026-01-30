// Compile Time Benchmark
// Measures: Compilation speed for a representative codebase
//
// This benchmark is run differently than others:
// - We measure how long `gcc -O3 main.c` takes
// - Contains multiple functions, types, and control flow for realistic workload

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Utility functions
int64_t abs_val(int64_t x) { return x < 0 ? -x : x; }

int64_t min(int64_t a, int64_t b) { return a < b ? a : b; }

int64_t max(int64_t a, int64_t b) { return a > b ? a : b; }

int64_t clamp(int64_t x, int64_t lo, int64_t hi) { return min(max(x, lo), hi); }

// Recursive algorithms
int64_t gcd(int64_t a, int64_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

int64_t fib_iter(int64_t n, int64_t a, int64_t b) {
    return n <= 0 ? a : fib_iter(n - 1, b, a + b);
}

int64_t fibonacci(int64_t n) { return fib_iter(n, 0, 1); }

int64_t factorial_iter(int64_t n, int64_t acc) {
    return n <= 1 ? acc : factorial_iter(n - 1, n * acc);
}

int64_t factorial(int64_t n) { return factorial_iter(n, 1); }

// Memory operations
int64_t array_sum(int64_t* arr, int64_t n) {
    int64_t sum = 0;
    for (int64_t i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

void fill_array(int64_t* arr, int64_t n) {
    for (int64_t i = 0; i < n; i++) {
        arr[i] = i * i;
    }
}

// Search algorithm
int64_t binary_search(int64_t* arr, int64_t n, int64_t target) {
    int64_t lo = 0, hi = n - 1;
    while (lo <= hi) {
        int64_t mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// Sorting (bubble sort for simplicity)
void bubble_sort(int64_t* arr, int64_t n) {
    for (int64_t i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int64_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int64_t temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Prime checking
bool is_prime(int64_t n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int64_t d = 3; d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

int64_t count_primes(int64_t n) {
    int64_t count = 0;
    for (int64_t i = 2; i <= n; i++) {
        if (is_prime(i)) count++;
    }
    return count;
}

// Main: Run all functions to verify correctness
int main() {
    int64_t g = gcd(48, 18);
    int64_t f = fibonacci(20);
    int64_t fact = factorial(10);
    int64_t primes = count_primes(100);

    // Array operations
    int64_t* arr = malloc(10 * sizeof(int64_t));
    fill_array(arr, 10);
    int64_t sum = array_sum(arr, 10);
    bubble_sort(arr, 10);
    int64_t found = binary_search(arr, 10, 16);
    free(arr);

    // Verify results
    int ok = g == 6 && f == 6765 && fact == 3628800 && primes == 25 && sum == 285 && found != -1;

    printf("%d\n", ok ? 1 : 0);
    return 0;
}
