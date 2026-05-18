// brainfuck — in-process timing harness (Cycle 2918)
// Mirrors BMB main_inproc.bmb: 1000 iterations of compute_only (no output).
// interpret_silent returns tape[0] as checksum.
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

#define TAPE_SIZE 30000

// Silent interpreter: no '.' output, returns tape[0] as checksum
static int64_t interpret_silent(const char *program) {
    unsigned char tape[TAPE_SIZE];
    memset(tape, 0, sizeof(tape));
    int ptr = 0, pc = 0, len = (int)strlen(program);

    while (pc < len) {
        char c = program[pc];
        switch (c) {
            case '>': ptr = (ptr + 1 >= TAPE_SIZE) ? 0 : ptr + 1; break;
            case '<': ptr = (ptr == 0) ? TAPE_SIZE - 1 : ptr - 1; break;
            case '+': tape[ptr] = (unsigned char)((tape[ptr] + 1) % 256); break;
            case '-': tape[ptr] = (unsigned char)((tape[ptr] == 0) ? 255 : tape[ptr] - 1); break;
            case '.': break;  // silent: skip output
            case ',': break;  // silent: skip input
            case '[':
                if (tape[ptr] == 0) {
                    int depth = 1;
                    while (depth > 0) {
                        pc++;
                        if (program[pc] == '[') depth++;
                        else if (program[pc] == ']') depth--;
                    }
                }
                break;
            case ']':
                if (tape[ptr] != 0) {
                    int depth = 1;
                    while (depth > 0) {
                        pc--;
                        if (program[pc] == ']') depth++;
                        else if (program[pc] == '[') depth--;
                    }
                }
                break;
        }
        pc++;
    }
    return (int64_t)tape[0];
}

// Pure computation (no output) — 3×10 nested loops = 1000 inner iterations
static const char *compute_only =
    "++++++++++[>++++++++++[>++++++++++[>+<-]<-]<-]";

int main(void) {
    // warmup
    (void)black_box(interpret_silent(compute_only));

    int64_t t0 = time_ns();
    int64_t total = 0;
    for (int i = 0; i < 1000; i++) {
        total += black_box(interpret_silent(compute_only));
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n", (long long)total);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
