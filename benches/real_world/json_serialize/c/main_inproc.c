// json_serialize — in-process timing harness (Cycle 2920)
// Mirrors main.bmb run_benchmark: 10000 iterations, heap buf, manual write_int.
// black_box(len1+len2+len3) per iteration. Output: checksum, elapsed_us

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

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

static int buf_char(char *buf, int pos, char c) { buf[pos] = c; return pos + 1; }

static int buf_str_n(char *buf, int pos, const char *s, int slen) {
    memcpy(buf + pos, s, slen);
    return pos + slen;
}

static int write_string(char *buf, int pos, const char *s) {
    buf[pos++] = '"';
    while (*s) {
        char c = *s++;
        if (c == '"')       { buf[pos++] = '\\'; buf[pos++] = '"'; }
        else if (c == '\\') { buf[pos++] = '\\'; buf[pos++] = '\\'; }
        else if (c == '\n') { buf[pos++] = '\\'; buf[pos++] = 'n'; }
        else if (c == '\r') { buf[pos++] = '\\'; buf[pos++] = 'r'; }
        else if (c == '\t') { buf[pos++] = '\\'; buf[pos++] = 't'; }
        else                { buf[pos++] = c; }
    }
    buf[pos++] = '"';
    return pos;
}

static int write_int(char *buf, int pos, int64_t n) {
    if (n < 0) { buf[pos++] = '-'; return write_int(buf, pos, -n); }
    if (n < 10) { buf[pos++] = '0' + (int)n; return pos; }
    pos = write_int(buf, pos, n / 10);
    buf[pos++] = '0' + (int)(n % 10);
    return pos;
}

static int serialize_person(char *buf, int pos, const char *name, int age, const char *city, int64_t salary) {
    pos = buf_str_n(buf, pos, "{\"name\":", 8);
    pos = write_string(buf, pos, name);
    pos = buf_str_n(buf, pos, ",\"age\":", 7);
    pos = write_int(buf, pos, age);
    pos = buf_str_n(buf, pos, ",\"city\":", 8);
    pos = write_string(buf, pos, city);
    pos = buf_str_n(buf, pos, ",\"salary\":", 10);
    pos = write_int(buf, pos, salary);
    buf[pos++] = '}';
    return pos;
}

static int serialize_int_array(char *buf, int pos, const int64_t *arr, int len) {
    buf[pos++] = '[';
    for (int i = 0; i < len; i++) {
        if (i > 0) buf[pos++] = ',';
        pos = write_int(buf, pos, arr[i]);
    }
    buf[pos++] = ']';
    return pos;
}

int main(void) {
    char *buf = (char *)calloc(65536, 1);
    int64_t arr[10];
    for (int i = 0; i < 10; i++) arr[i] = i + 1;

    // warmup
    (void)black_box(serialize_person(buf, 0, "Test", 1, "X", 1));

    int64_t t0 = time_ns();
    int64_t total = 0;
    for (int i = 0; i < 10000; i++) {
        int len1 = serialize_person(buf, 0, "John Doe", 30, "New York", 50000);
        int len2 = serialize_int_array(buf, 0, arr, 10);
        int len3 = serialize_person(buf, 0, "Alice \"The Great\"", 25, "Los\nAngeles", 60000);
        total += black_box(len1 + len2 + len3);
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    free(buf);
    printf("%lld\n", (long long)total);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
