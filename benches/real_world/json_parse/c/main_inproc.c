// json_parse — in-process timing harness (Cycle 2920)
// Mirrors main.c algorithm: 100000 iterations on "[1,2,3,4,5,6,7,8,9,10]".
// black_box(is_valid + count) per iteration prevents DCE.
// Output: checksum, elapsed_us

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

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

static int skip_ws(const char *s, int pos) {
    while (s[pos] && isspace((unsigned char)s[pos])) pos++;
    return pos;
}

static int find_close(const char *s, int pos, char open, char close) {
    int depth = 0;
    while (s[pos]) {
        if (s[pos] == close && depth == 0) return pos;
        if (s[pos] == open) depth++;
        if (s[pos] == close) depth--;
        pos++;
    }
    return pos;
}

static int count_array(const char *s, int pos) {
    pos = skip_ws(s, pos);
    if (s[pos] != '[') return 0;
    pos = skip_ws(s, pos + 1);
    if (s[pos] == ']') return 0;
    int count = 1, depth = 0;
    while (s[pos]) {
        if (s[pos] == ']' && depth == 0) break;
        if (s[pos] == '[' || s[pos] == '{') depth++;
        if (s[pos] == ']' || s[pos] == '}') depth--;
        if (s[pos] == ',' && depth == 0) count++;
        pos++;
    }
    return count;
}

static int find_string_end(const char *s, int pos) {
    while (s[pos]) {
        if (s[pos] == '"') return pos;
        if (s[pos] == '\\') pos++;
        pos++;
    }
    return pos;
}

static int validate_json(const char *s, int pos) {
    pos = skip_ws(s, pos);
    if (!s[pos]) return 0;
    char c = s[pos];
    int slen = (int)strlen(s);
    if (c == '{') return find_close(s, pos + 1, '{', '}') < slen;
    if (c == '[') return find_close(s, pos + 1, '[', ']') < slen;
    if (c == '"') return find_string_end(s, pos + 1) < slen;
    if (isdigit((unsigned char)c) || c == '-') return 1;
    if (c == 't' || c == 'f' || c == 'n') return 1;
    return 0;
}

int main(void) {
    const char *json = "[1,2,3,4,5,6,7,8,9,10]";

    // warmup
    (void)black_box(count_array(json, 0));

    int64_t t0 = time_ns();
    int64_t total = 0;
    for (int i = 0; i < 100000; i++) {
        int is_valid = validate_json(json, 0);
        int cnt = count_array(json, 0);
        total += black_box(is_valid + cnt);
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n", (long long)total);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
