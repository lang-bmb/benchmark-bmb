// json-serialize - JSON serialization benchmark
// Tests string building, escaping, formatting
// Self-contained with embedded test structures
// v0.55: FAIR VERSION - Uses integer salary like BMB (no float-to-string)

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define BUF_SIZE 65536

// Output buffer
static char buffer[BUF_SIZE];
static int buf_pos = 0;

static void buf_reset(void) { buf_pos = 0; buffer[0] = '\0'; }
static void buf_char(char c) { if (buf_pos < BUF_SIZE - 1) buffer[buf_pos++] = c; buffer[buf_pos] = '\0'; }
static void buf_str(const char *s) { while (*s && buf_pos < BUF_SIZE - 1) buffer[buf_pos++] = *s++; buffer[buf_pos] = '\0'; }

// Escape and write string
static void write_string(const char *s) {
    buf_char('"');
    while (*s) {
        char c = *s++;
        switch (c) {
            case '"':  buf_str("\\\""); break;
            case '\\': buf_str("\\\\"); break;
            case '\n': buf_str("\\n"); break;
            case '\r': buf_str("\\r"); break;
            case '\t': buf_str("\\t"); break;
            default:
                if (c >= 32 && c < 127) buf_char(c);
                else {
                    // Unicode escape
                    char hex[8];
                    snprintf(hex, sizeof(hex), "\\u%04x", (unsigned char)c);
                    buf_str(hex);
                }
        }
    }
    buf_char('"');
}

// Write integer
static void write_int(int64_t n) {
    char num[32];
    snprintf(num, sizeof(num), "%lld", (long long)n);
    buf_str(num);
}

// Serialize a simple object (salary is now integer like BMB)
static void serialize_person(const char *name, int age, const char *city, int64_t salary) {
    buf_char('{');
    buf_str("\"name\":");
    write_string(name);
    buf_char(',');
    buf_str("\"age\":");
    write_int(age);
    buf_char(',');
    buf_str("\"city\":");
    write_string(city);
    buf_char(',');
    buf_str("\"salary\":");
    write_int(salary);  // Integer, not float
    buf_char('}');
}

// Serialize array of integers
static void serialize_int_array(int *arr, int len) {
    buf_char('[');
    for (int i = 0; i < len; i++) {
        if (i > 0) buf_char(',');
        write_int(arr[i]);
    }
    buf_char(']');
}

// Benchmark: serialize many structures
static int run_benchmark(int iterations) {
    int total_len = 0;

    for (int i = 0; i < iterations; i++) {
        buf_reset();

        // Serialize person object (integer salary like BMB)
        serialize_person("John Doe", 30, "New York", 50000);
        total_len += buf_pos;

        buf_reset();

        // Serialize array
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        serialize_int_array(arr, 10);
        total_len += buf_pos;

        buf_reset();

        // Serialize with special characters (integer salary like BMB)
        serialize_person("Alice \"The Great\"", 25, "Los\nAngeles", 60000);
        total_len += buf_pos;
    }

    return total_len;
}

int main(void) {
    printf("JSON Serialize Benchmark\n");

    // Warm up
    run_benchmark(100);

    // Benchmark
    int total = run_benchmark(10000);

    printf("Total characters: %d\n", total);
    printf("Sample output:\n");

    buf_reset();
    serialize_person("Test User", 42, "Boston", 75000);
    printf("  Object: %s\n", buffer);

    buf_reset();
    int arr[] = {1, 2, 3, 4, 5};
    serialize_int_array(arr, 5);
    printf("  Array: %s\n", buffer);

    printf("Done.\n");
    return 0;
}
