// JSON parsing benchmark
// Measures: string processing, recursive descent parsing

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int skip_ws(const char* s, int pos) {
    while (s[pos] && isspace(s[pos])) pos++;
    return pos;
}

int parse_number(const char* s, int pos, long* value) {
    *value = 0;
    int neg = 0;
    if (s[pos] == '-') { neg = 1; pos++; }
    while (s[pos] && isdigit(s[pos])) {
        *value = *value * 10 + (s[pos] - '0');
        pos++;
    }
    if (neg) *value = -*value;
    return pos;
}

int find_close(const char* s, int pos, char open, char close) {
    int depth = 0;
    while (s[pos]) {
        if (s[pos] == close && depth == 0) return pos;
        if (s[pos] == open) depth++;
        if (s[pos] == close) depth--;
        pos++;
    }
    return pos;
}

int count_array(const char* s, int pos) {
    pos = skip_ws(s, pos);
    if (s[pos] != '[') return 0;
    pos = skip_ws(s, pos + 1);
    if (s[pos] == ']') return 0;

    int count = 1;
    int depth = 0;
    while (s[pos]) {
        if (s[pos] == ']' && depth == 0) break;
        if (s[pos] == '[' || s[pos] == '{') depth++;
        if (s[pos] == ']' || s[pos] == '}') depth--;
        if (s[pos] == ',' && depth == 0) count++;
        pos++;
    }
    return count;
}

int validate_json(const char* s, int pos);

int validate_object(const char* s, int pos) {
    return find_close(s, pos + 1, '{', '}') < strlen(s);
}

int validate_array(const char* s, int pos) {
    return find_close(s, pos + 1, '[', ']') < strlen(s);
}

int find_string_end(const char* s, int pos) {
    while (s[pos]) {
        if (s[pos] == '"') return pos;
        if (s[pos] == '\\') pos++;
        pos++;
    }
    return pos;
}

int validate_string(const char* s, int pos) {
    return find_string_end(s, pos + 1) < strlen(s);
}

int validate_json(const char* s, int pos) {
    pos = skip_ws(s, pos);
    if (!s[pos]) return 0;
    char c = s[pos];
    if (c == '{') return validate_object(s, pos);
    if (c == '[') return validate_array(s, pos);
    if (c == '"') return validate_string(s, pos);
    if (isdigit(c) || c == '-') return 1;
    if (c == 't' || c == 'f' || c == 'n') return 1;
    return 0;
}

int main() {
    const char* json = "[1,2,3,4,5,6,7,8,9,10]";
    long valid_count = 0;

    for (int i = 0; i < 10000; i++) {
        valid_count += validate_json(json, 0);
        valid_count += count_array(json, 0);
    }

    printf("%ld\n", valid_count);
    return 0;
}
