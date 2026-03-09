// Bounds Check Benchmark - C equivalent of BMB contract benchmark
// C with manual bounds checking (equivalent to --safe, no contract)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int64_t i64;

__attribute__((noinline)) static i64 get_checked(i64* arr, i64 len, i64 idx) {
    if (idx < 0 || idx >= len) {
        fprintf(stderr, "bounds error\n");
        exit(1);
    }
    return arr[idx + 2];
}

__attribute__((noinline)) static i64 get_unchecked(i64* arr, i64 idx) {
    return arr[idx + 2];
}

static i64 dynamic_sum_checked(i64* arr, i64 len, i64 n, i64 acc) {
    while (n > 0) {
        i64 idx = n % 10;
        i64 val = get_checked(arr, len, idx);
        acc += val;
        n--;
    }
    return acc;
}

static i64 dynamic_sum_unchecked(i64* arr, i64 n, i64 acc) {
    while (n > 0) {
        i64 idx = n % 10;
        i64 val = get_unchecked(arr, idx);
        acc += val;
        n--;
    }
    return acc;
}

int main(int argc, char** argv) {
    i64* arr = (i64*)calloc(12, sizeof(i64));
    arr[0] = 10;
    arr[1] = 10;
    for (i64 i = 0; i < 10; i++) arr[i + 2] = i + 1;

    int checked = (argc > 1 && argv[1][0] == 'c');
    i64 result;
    if (checked) {
        result = dynamic_sum_checked(arr, 10, 100000000, 0);
    } else {
        result = dynamic_sum_unchecked(arr, 100000000, 0);
    }
    printf("%lld\n", result);
    free(arr);
    return 0;
}
