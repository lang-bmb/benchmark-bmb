// csv-parse - CSV parsing benchmark
// Tests string processing, field extraction, quote handling
// Self-contained with embedded test data

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FIELD_LEN 256
#define MAX_FIELDS 100

typedef struct {
    int row_count;
    int field_count;
    int quoted_field_count;
    int total_chars;
} ParseStats;

// Parse a single CSV field starting at position, returns end position
// Handles quoted fields with escaped quotes ("")
int parse_field(const char *line, int start, char *field_buf, bool *is_quoted) {
    int pos = start;
    int field_pos = 0;
    *is_quoted = false;

    // Skip leading whitespace
    while (line[pos] == ' ' || line[pos] == '\t') pos++;

    if (line[pos] == '"') {
        // Quoted field
        *is_quoted = true;
        pos++;
        while (line[pos] != '\0') {
            if (line[pos] == '"') {
                if (line[pos + 1] == '"') {
                    // Escaped quote
                    field_buf[field_pos++] = '"';
                    pos += 2;
                } else {
                    // End of quoted field
                    pos++;
                    break;
                }
            } else {
                field_buf[field_pos++] = line[pos++];
            }
        }
    } else {
        // Unquoted field
        while (line[pos] != '\0' && line[pos] != ',' && line[pos] != '\n') {
            field_buf[field_pos++] = line[pos++];
        }
    }

    field_buf[field_pos] = '\0';

    // Skip to next field or end
    while (line[pos] == ' ' || line[pos] == '\t') pos++;
    if (line[pos] == ',') pos++;

    return pos;
}

// Parse a CSV line, count fields
int parse_line(const char *line, ParseStats *stats) {
    if (line[0] == '\0' || line[0] == '\n') return 0;

    char field_buf[MAX_FIELD_LEN];
    bool is_quoted;
    int pos = 0;
    int fields = 0;

    while (line[pos] != '\0' && line[pos] != '\n') {
        pos = parse_field(line, pos, field_buf, &is_quoted);
        fields++;
        stats->total_chars += strlen(field_buf);
        if (is_quoted) stats->quoted_field_count++;
    }

    stats->field_count += fields;
    stats->row_count++;
    return fields;
}

// Parse entire CSV data
void parse_csv(const char *data, ParseStats *stats) {
    stats->row_count = 0;
    stats->field_count = 0;
    stats->quoted_field_count = 0;
    stats->total_chars = 0;

    const char *line_start = data;
    const char *line_end;

    while (*line_start != '\0') {
        // Find end of line
        line_end = line_start;
        while (*line_end != '\0' && *line_end != '\n') line_end++;

        // Copy line to buffer
        char line_buf[1024];
        int len = line_end - line_start;
        if (len >= 1024) len = 1023;
        strncpy(line_buf, line_start, len);
        line_buf[len] = '\0';

        parse_line(line_buf, stats);

        // Move to next line
        line_start = line_end;
        if (*line_start == '\n') line_start++;
    }
}

// Test data - various CSV scenarios
const char *test_data =
    "name,age,city,salary\n"
    "John Doe,30,New York,50000\n"
    "Jane Smith,25,Los Angeles,60000\n"
    "\"Bob \"\"The Builder\"\" Jones\",45,Chicago,75000\n"
    "Alice,28,\"San Francisco, CA\",80000\n"
    "Charlie Brown,35,Boston,55000\n"
    "\"Diana, Princess\",40,London,90000\n"
    "Edward,22,Miami,45000\n"
    "\"Fiona \"\"Fi\"\" Green\",33,Seattle,70000\n"
    "George,29,Denver,52000\n"
    "Helen,31,Phoenix,58000\n";

// Larger dataset for benchmarking
const char *large_data_row =
    "field1,field2,field3,field4,field5,\"quoted,field\",field7,field8,field9,field10\n";

void generate_large_dataset(char *buf, int rows) {
    buf[0] = '\0';
    for (int i = 0; i < rows; i++) {
        strcat(buf, large_data_row);
    }
}

int main(void) {
    printf("CSV Parse Benchmark\n");

    // Parse test data
    ParseStats stats;
    parse_csv(test_data, &stats);

    printf("Small dataset:\n");
    printf("  Rows: %d\n", stats.row_count);
    printf("  Fields: %d\n", stats.field_count);
    printf("  Quoted fields: %d\n", stats.quoted_field_count);
    printf("  Total chars: %d\n", stats.total_chars);
    printf("\n");

    // Generate and parse larger dataset
    char large_buf[100000];
    generate_large_dataset(large_buf, 1000);

    parse_csv(large_buf, &stats);
    printf("Large dataset (1000 rows):\n");
    printf("  Rows: %d\n", stats.row_count);
    printf("  Fields: %d\n", stats.field_count);
    printf("  Quoted fields: %d\n", stats.quoted_field_count);
    printf("  Total chars: %d\n", stats.total_chars);

    printf("\nDone.\n");
    return 0;
}
