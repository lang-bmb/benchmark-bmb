// sorting — in-process timing harness (Cycle 2921)
// Mirrors main_inproc.bmb: 4 sorts × 200 sizes; 5 timed iterations.
// black_box(combined_cost) per inner size iteration prevents DCE.
// Output: checksum, elapsed_us

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
static int64_t time_ns(void) {
    static LARGE_INTEGER freq = {0};
    if (freq.QuadPart == 0) QueryPerformanceFrequency(&freq);
    LARGE_INTEGER c; QueryPerformanceCounter(&c);
    int64_t s = c.QuadPart / freq.QuadPart;
    int64_t r = c.QuadPart % freq.QuadPart;
    return s * 1000000000LL + (r * 1000000000LL) / freq.QuadPart;
}
#else
#include <time.h>
static int64_t time_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)(ts.tv_sec * 1000000000LL + ts.tv_nsec);
}
#endif

static volatile int64_t black_sink;
static int64_t black_box(int64_t v) { black_sink = v; return black_sink; }

static void init_reverse(int64_t *arr, int64_t size) {
    for (int64_t i = 0; i < size; i++) arr[i] = size - i;
}

static void sort_swap(int64_t *arr, int64_t i, int64_t j) {
    int64_t tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
}

static int64_t bubble_sort(int64_t *arr, int64_t n) {
    int64_t comparisons = 0;
    for (int64_t i = 0; i < n - 1; i++) {
        int64_t limit = n - i - 1;
        for (int64_t j = 0; j < limit; j++) {
            if (arr[j] > arr[j + 1]) sort_swap(arr, j, j + 1);
            comparisons++;
        }
    }
    return comparisons;
}

static int64_t insertion_sort(int64_t *arr, int64_t n) {
    int64_t cost = 0;
    for (int64_t i = 1; i < n; i++) {
        int64_t key = arr[i];
        int64_t k = i;
        while (k >= 1 && arr[k - 1] > key) {
            arr[k] = arr[k - 1];
            cost++; k--;
        }
        arr[k] = key;
        cost++;
    }
    return cost;
}

static int64_t merge_fn(int64_t *arr, int64_t l, int64_t m, int64_t r) {
    int64_t n1 = m - l + 1, n2 = r - m;
    int64_t *L = (int64_t *)malloc(n1 * sizeof(int64_t));
    int64_t *R = (int64_t *)malloc(n2 * sizeof(int64_t));
    for (int64_t i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int64_t j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int64_t i = 0, j = 0, k = l, cost = 0;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
        cost++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
    return cost;
}

static int64_t merge_sort_helper(int64_t *arr, int64_t l, int64_t r) {
    if (l >= r) return 0;
    int64_t m = l + (r - l) / 2;
    int64_t cl = merge_sort_helper(arr, l, m);
    int64_t cr = merge_sort_helper(arr, m + 1, r);
    return cl + cr + merge_fn(arr, l, m, r);
}

static int64_t merge_sort(int64_t *arr, int64_t n) {
    return merge_sort_helper(arr, 0, n - 1);
}

static int64_t partition(int64_t *arr, int64_t low, int64_t high, int64_t *cost_out) {
    int64_t pivot = arr[high];
    int64_t i = low - 1, cost = 0;
    for (int64_t j = low; j < high; j++) {
        if (arr[j] <= pivot) { i++; sort_swap(arr, i, j); }
        cost++;
    }
    sort_swap(arr, i + 1, high);
    *cost_out = cost;
    return i + 1;
}

static int64_t quick_sort_helper(int64_t *arr, int64_t low, int64_t high) {
    if (low >= high) return 0;
    int64_t pcost;
    int64_t pi = partition(arr, low, high, &pcost);
    return pcost + quick_sort_helper(arr, low, pi - 1) + quick_sort_helper(arr, pi + 1, high);
}

static int64_t quick_sort(int64_t *arr, int64_t n) {
    return quick_sort_helper(arr, 0, n - 1);
}

static int64_t run_once(void) {
    int64_t acc = 0;
    for (int sizes = 200; sizes > 0; sizes--) {
        int64_t size = (int64_t)sizes * 10;
        int64_t *arr = (int64_t *)malloc(size * sizeof(int64_t));

        init_reverse(arr, size);
        int64_t b = bubble_sort(arr, size);
        init_reverse(arr, size);
        int64_t ins = insertion_sort(arr, size);
        init_reverse(arr, size);
        int64_t mc = merge_sort(arr, size);
        init_reverse(arr, size);
        int64_t q = quick_sort(arr, size);
        free(arr);

        acc += black_box(b + ins + mc + q);
    }
    return acc;
}

int main(void) {
    // warmup
    (void)black_box(run_once());

    int64_t t0 = time_ns();
    int64_t total = 0;
    for (int i = 0; i < 5; i++) {
        total += black_box(run_once());
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n", (long long)total);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
