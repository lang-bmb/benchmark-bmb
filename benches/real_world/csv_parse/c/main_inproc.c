// csv_parse — in-process timing harness (Cycle 2919)
// Direct buffer parsing (no intermediate line copies); 50 iterations on 1000-row large data.
// Output: checksum, elapsed_us

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

typedef struct { int64_t rows; int64_t fields; int64_t quoted; int64_t total_chars; } CsvStats;

static CsvStats parse_csv(const char *data, int len) {
    CsvStats st = {0, 0, 0, 0};
    int pos = 0;
    while (pos < len) {
        int line_end = pos;
        while (line_end < len && data[line_end] != '\n' && data[line_end] != '\r') line_end++;
        if (line_end > pos) {
            int p = pos;
            while (p < line_end) {
                while (p < line_end && (data[p] == ' ' || data[p] == '\t')) p++;
                if (p >= line_end) break;
                st.fields++;
                if (data[p] == '"') {
                    st.quoted++;
                    p++;
                    while (p < len) {
                        if (data[p] == '"') {
                            if (p + 1 < len && data[p + 1] == '"') {
                                st.total_chars++;
                                p += 2;
                            } else { p++; break; }
                        } else { st.total_chars++; p++; }
                    }
                    while (p < line_end && (data[p] == ' ' || data[p] == '\t')) p++;
                    if (p < line_end && data[p] == ',') p++;
                } else {
                    while (p < line_end && data[p] != ',') { st.total_chars++; p++; }
                    if (p < line_end && data[p] == ',') p++;
                }
            }
            st.rows++;
        }
        pos = line_end;
        if (pos < len && data[pos] == '\r') pos++;
        if (pos < len && data[pos] == '\n') pos++;
    }
    return st;
}

static const char *large_row = "field1,field2,field3,field4,field5,\"quoted,field\",field7,field8,field9,field10\n";
static char large_buf[100000];

static void gen_large(int rows) {
    int row_len = (int)strlen(large_row);
    for (int i = 0; i < rows; i++)
        memcpy(large_buf + i * row_len, large_row, row_len);
    large_buf[rows * row_len] = '\0';
}

int main(void) {
    gen_large(1000);
    int data_len = (int)strlen(large_buf);

    // warmup
    CsvStats w = parse_csv(large_buf, data_len);
    (void)black_box(w.rows + w.fields);

    int64_t t0 = time_ns();
    int64_t total = 0;
    for (int i = 0; i < 50; i++) {
        CsvStats st = parse_csv(large_buf, data_len);
        total += black_box(st.rows + st.fields + st.quoted + st.total_chars);
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n", (long long)total);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
