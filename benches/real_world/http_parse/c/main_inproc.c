// http_parse — in-process timing harness (Cycle 2919)
// Mirrors main.bmb parse_all_requests(); 10000 iterations x 5 requests.
// Output: checksum, elapsed_us

#include <stdio.h>
#include <string.h>
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

static int skip_ws(const char *s, int pos, int len) {
    while (pos < len && (s[pos] == ' ' || s[pos] == '\t')) pos++;
    return pos;
}
static int find_char(const char *s, int pos, int len, char c) {
    while (pos < len && s[pos] != c) pos++;
    return pos;
}
static int find_eol(const char *s, int pos, int len) {
    while (pos < len && s[pos] != '\n' && s[pos] != '\r') pos++;
    return pos;
}
static int skip_eol(const char *s, int pos, int len) {
    if (pos < len && s[pos] == '\r') pos++;
    if (pos < len && s[pos] == '\n') pos++;
    return pos;
}
static int str_eqi(const char *s, int pos, const char *m, int mlen) {
    for (int i = 0; i < mlen; i++) {
        char c1 = s[pos + i]; if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        char c2 = m[i];       if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return 0;
    }
    return 1;
}
static int parse_int_at(const char *s, int pos, int end) {
    int acc = 0;
    while (pos < end && s[pos] >= '0' && s[pos] <= '9') acc = acc * 10 + s[pos++] - '0';
    return acc;
}

// Returns header_count * 1000000 + content_length (mirrors BMB parse_request)
static int64_t parse_request(const char *s, int len) {
    // Skip request line
    int eol = find_eol(s, 0, len);
    int pos = skip_eol(s, eol, len);
    int header_count = 0;
    int content_length = 0;
    while (pos < len) {
        int line_start = pos;
        eol = find_eol(s, pos, len);
        if (eol == line_start) break;
        header_count++;
        int colon = find_char(s, pos, eol, ':');
        if (colon < eol) {
            int name_len = colon - pos;
            if (name_len == 14 && str_eqi(s, pos, "content-length", 14)) {
                int val_start = skip_ws(s, colon + 1, eol);
                content_length = parse_int_at(s, val_start, eol);
            }
        }
        pos = skip_eol(s, eol, len);
    }
    return (int64_t)header_count * 1000000 + content_length;
}

static const char *requests[5] = {
    "GET /index.html HTTP/1.1\r\nHost: example.com\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html\r\nConnection: keep-alive\r\n\r\n",
    "POST /api/users HTTP/1.1\r\nHost: api.example.com\r\nContent-Type: application/json\r\nContent-Length: 42\r\nAuthorization: Bearer token123\r\n\r\n",
    "PUT /api/resource/123 HTTP/1.1\r\nHost: api.example.com\r\nContent-Type: application/json\r\nContent-Length: 256\r\n\r\n",
    "DELETE /api/users/456 HTTP/1.1\r\nHost: api.example.com\r\nAuthorization: Bearer token456\r\n\r\n",
    "GET /static/style.css HTTP/1.1\r\nHost: cdn.example.com\r\nAccept: text/css\r\nCache-Control: max-age=3600\r\n\r\n"
};
static int req_lens[5];

static int64_t parse_all_requests(void) {
    int64_t h = 0, c = 0;
    for (int r = 0; r < 5; r++) {
        int64_t res = parse_request(requests[r], req_lens[r]);
        h += res / 1000000;
        c += res % 1000000;
    }
    return h * 1000000 + c;
}

int main(void) {
    for (int i = 0; i < 5; i++) req_lens[i] = (int)strlen(requests[i]);

    // warmup
    (void)black_box(parse_all_requests());

    int64_t t0 = time_ns();
    int64_t total = 0;
    for (int i = 0; i < 10000; i++) {
        total += black_box(parse_all_requests());
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n", (long long)total);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
