// http-parse - HTTP request parsing benchmark
// Tests protocol parsing, header extraction, string matching
// Self-contained with embedded test requests

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// HTTP methods
typedef enum {
    METHOD_GET = 0,
    METHOD_POST,
    METHOD_PUT,
    METHOD_DELETE,
    METHOD_HEAD,
    METHOD_OPTIONS,
    METHOD_UNKNOWN
} HttpMethod;

// Parsed request info
typedef struct {
    HttpMethod method;
    int path_start;
    int path_len;
    int version_major;
    int version_minor;
    int header_count;
    int content_length;
    int host_start;
    int host_len;
} HttpRequest;

// Skip whitespace
static int skip_ws(const char *s, int pos, int len) {
    while (pos < len && (s[pos] == ' ' || s[pos] == '\t')) {
        pos++;
    }
    return pos;
}

// Find character
static int find_char(const char *s, int pos, int len, char c) {
    while (pos < len && s[pos] != c) {
        pos++;
    }
    return pos;
}

// Find CRLF or LF
static int find_eol(const char *s, int pos, int len) {
    while (pos < len) {
        if (s[pos] == '\n') return pos;
        if (s[pos] == '\r' && pos + 1 < len && s[pos + 1] == '\n') return pos;
        pos++;
    }
    return pos;
}

// Skip past EOL
static int skip_eol(const char *s, int pos, int len) {
    if (pos < len && s[pos] == '\r') pos++;
    if (pos < len && s[pos] == '\n') pos++;
    return pos;
}

// Compare string at position (case-insensitive for headers)
static bool str_eq(const char *s, int pos, const char *match, int match_len) {
    for (int i = 0; i < match_len; i++) {
        char c1 = s[pos + i];
        char c2 = match[i];
        // Simple lowercase for A-Z
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return false;
    }
    return true;
}

// Parse HTTP method
static HttpMethod parse_method(const char *s, int pos, int len) {
    if (len >= 3 && s[pos] == 'G' && s[pos+1] == 'E' && s[pos+2] == 'T') return METHOD_GET;
    if (len >= 4 && s[pos] == 'P' && s[pos+1] == 'O' && s[pos+2] == 'S' && s[pos+3] == 'T') return METHOD_POST;
    if (len >= 3 && s[pos] == 'P' && s[pos+1] == 'U' && s[pos+2] == 'T') return METHOD_PUT;
    if (len >= 6 && s[pos] == 'D' && s[pos+1] == 'E' && s[pos+2] == 'L') return METHOD_DELETE;
    if (len >= 4 && s[pos] == 'H' && s[pos+1] == 'E' && s[pos+2] == 'A' && s[pos+3] == 'D') return METHOD_HEAD;
    return METHOD_UNKNOWN;
}

// Parse integer from string
static int parse_int(const char *s, int pos, int len) {
    int result = 0;
    while (pos < len && s[pos] >= '0' && s[pos] <= '9') {
        result = result * 10 + (s[pos] - '0');
        pos++;
    }
    return result;
}

// Parse a single HTTP request
static void parse_request(const char *s, int len, HttpRequest *req) {
    req->method = METHOD_UNKNOWN;
    req->path_start = 0;
    req->path_len = 0;
    req->version_major = 1;
    req->version_minor = 1;
    req->header_count = 0;
    req->content_length = 0;
    req->host_start = 0;
    req->host_len = 0;

    int pos = 0;

    // Parse request line: METHOD PATH HTTP/X.Y
    req->method = parse_method(s, pos, len);

    // Skip to first space (after method)
    pos = find_char(s, pos, len, ' ');
    pos = skip_ws(s, pos, len);

    // Parse path
    req->path_start = pos;
    pos = find_char(s, pos, len, ' ');
    req->path_len = pos - req->path_start;

    pos = skip_ws(s, pos, len);

    // Parse HTTP version (HTTP/1.1)
    if (pos + 7 < len && s[pos] == 'H' && s[pos+1] == 'T' && s[pos+2] == 'T' && s[pos+3] == 'P' && s[pos+4] == '/') {
        req->version_major = s[pos + 5] - '0';
        if (pos + 7 < len && s[pos + 6] == '.') {
            req->version_minor = s[pos + 7] - '0';
        }
    }

    // Skip to end of request line
    pos = find_eol(s, pos, len);
    pos = skip_eol(s, pos, len);

    // Parse headers
    while (pos < len) {
        int line_start = pos;
        int eol = find_eol(s, pos, len);

        // Empty line = end of headers
        if (eol == line_start) break;

        req->header_count++;

        // Find colon
        int colon = find_char(s, pos, eol, ':');
        if (colon < eol) {
            int name_len = colon - pos;

            // Check for specific headers
            if (name_len == 4 && str_eq(s, pos, "host", 4)) {
                int val_start = skip_ws(s, colon + 1, eol);
                req->host_start = val_start;
                req->host_len = eol - val_start;
            }
            else if (name_len == 14 && str_eq(s, pos, "content-length", 14)) {
                int val_start = skip_ws(s, colon + 1, eol);
                req->content_length = parse_int(s, val_start, eol);
            }
        }

        pos = skip_eol(s, eol, len);
    }
}

// Test HTTP requests
static const char *test_requests[] = {
    "GET /index.html HTTP/1.1\r\n"
    "Host: example.com\r\n"
    "User-Agent: Mozilla/5.0\r\n"
    "Accept: text/html\r\n"
    "Connection: keep-alive\r\n"
    "\r\n",

    "POST /api/users HTTP/1.1\r\n"
    "Host: api.example.com\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: 42\r\n"
    "Authorization: Bearer token123\r\n"
    "\r\n",

    "PUT /api/resource/123 HTTP/1.1\r\n"
    "Host: api.example.com\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: 256\r\n"
    "\r\n",

    "DELETE /api/users/456 HTTP/1.1\r\n"
    "Host: api.example.com\r\n"
    "Authorization: Bearer token456\r\n"
    "\r\n",

    "GET /static/style.css HTTP/1.1\r\n"
    "Host: cdn.example.com\r\n"
    "Accept: text/css\r\n"
    "Cache-Control: max-age=3600\r\n"
    "\r\n"
};

static const int NUM_REQUESTS = 5;

// Run benchmark
static void run_benchmark(int iterations, int *total_headers, int *total_content_len) {
    *total_headers = 0;
    *total_content_len = 0;

    for (int i = 0; i < iterations; i++) {
        for (int r = 0; r < NUM_REQUESTS; r++) {
            HttpRequest req;
            parse_request(test_requests[r], strlen(test_requests[r]), &req);
            *total_headers += req.header_count;
            *total_content_len += req.content_length;
        }
    }
}

static const char *method_name(HttpMethod m) {
    switch (m) {
        case METHOD_GET: return "GET";
        case METHOD_POST: return "POST";
        case METHOD_PUT: return "PUT";
        case METHOD_DELETE: return "DELETE";
        case METHOD_HEAD: return "HEAD";
        case METHOD_OPTIONS: return "OPTIONS";
        default: return "UNKNOWN";
    }
}

int main(void) {
    printf("HTTP Parse Benchmark\n\n");

    // Parse sample request
    HttpRequest req;
    parse_request(test_requests[0], strlen(test_requests[0]), &req);

    printf("Sample request:\n");
    printf("  Method: %s\n", method_name(req.method));
    printf("  Path length: %d\n", req.path_len);
    printf("  Version: HTTP/%d.%d\n", req.version_major, req.version_minor);
    printf("  Headers: %d\n", req.header_count);
    printf("\n");

    // Benchmark
    int total_headers, total_content_len;
    run_benchmark(10000, &total_headers, &total_content_len);

    printf("Benchmark (10000 iterations x 5 requests):\n");
    printf("  Total headers parsed: %d\n", total_headers);
    printf("  Total content-length: %d\n", total_content_len);

    printf("\nDone.\n");
    return 0;
}
