// lexer — in-process timing harness (Cycle 2918)
// Mirrors BMB main_inproc.bmb: 50 iterations on 100x source, black_box start_pos.
// Output: total_tokens (checksum), elapsed_us

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
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

// Token types
typedef enum {
    TOK_EOF = 0, TOK_IDENT, TOK_NUMBER, TOK_STRING, TOK_KEYWORD,
    TOK_OPERATOR, TOK_PUNCT, TOK_COMMENT, TOK_UNKNOWN
} LexTokType;

static const char *keywords[] = {
    "fn", "let", "if", "else", "while", "for", "return",
    "true", "false", "null", "struct", "enum", "match", NULL
};

static bool is_keyword(const char *s, int len) {
    char buf[32];
    if (len >= 32) return false;
    strncpy(buf, s, len);
    buf[len] = '\0';
    for (int i = 0; keywords[i]; i++)
        if (strcmp(buf, keywords[i]) == 0) return true;
    return false;
}

typedef struct { const char *src; int pos; int len; } Lexer;

static void lexer_init(Lexer *l, const char *src, int start) {
    l->src = src; l->pos = start; l->len = (int)strlen(src);
}
static char lpeek(Lexer *l) { return l->pos < l->len ? l->src[l->pos] : '\0'; }
static char lpeek_next(Lexer *l) { return l->pos + 1 < l->len ? l->src[l->pos + 1] : '\0'; }
static void advance(Lexer *l) { if (l->pos < l->len) l->pos++; }
static void skip_whitespace(Lexer *l) { while (isspace(lpeek(l))) advance(l); }

static LexTokType next_token(Lexer *l) {
    skip_whitespace(l);
    if (l->pos >= l->len) return TOK_EOF;
    char c = lpeek(l);
    if (c == '-' && lpeek_next(l) == '-') {
        while (lpeek(l) && lpeek(l) != '\n') advance(l);
        return TOK_COMMENT;
    }
    if (isalpha(c) || c == '_') {
        int start = l->pos;
        while (isalnum(lpeek(l)) || lpeek(l) == '_') advance(l);
        return is_keyword(l->src + start, l->pos - start) ? TOK_KEYWORD : TOK_IDENT;
    }
    if (isdigit(c)) {
        while (isdigit(lpeek(l)) || lpeek(l) == '.') advance(l);
        return TOK_NUMBER;
    }
    if (c == '"') {
        advance(l);
        while (lpeek(l) && lpeek(l) != '"') {
            if (lpeek(l) == '\\') advance(l);
            advance(l);
        }
        advance(l);
        return TOK_STRING;
    }
    const char *ops = "+-*/%=<>!&|";
    if (strchr(ops, c)) {
        advance(l);
        char n = lpeek(l);
        if ((c == '=' || c == '!' || c == '<' || c == '>') && n == '=') advance(l);
        else if ((c == '&' && n == '&') || (c == '|' && n == '|')) advance(l);
        return TOK_OPERATOR;
    }
    const char *puncts = "(){}[];:,.";
    if (strchr(puncts, c)) { advance(l); return TOK_PUNCT; }
    advance(l);
    return TOK_UNKNOWN;
}

// Count non-EOF tokens from start_pos
static int64_t count_tokens_from(const char *src, int start_pos) {
    Lexer l;
    lexer_init(&l, src, start_pos);
    int64_t total = 0;
    LexTokType tok;
    while ((tok = next_token(&l)) != TOK_EOF) total++;
    return total;
}

static const char *test_source =
    "fn fibonacci(n: i64) -> i64 =\n"
    "    if n <= 1 { n }\n"
    "    else { fibonacci(n - 1) + fibonacci(n - 2) };\n"
    "\n"
    "fn main() -> i64 = {\n"
    "    let result = fibonacci(35);\n"
    "    -- This is a comment\n"
    "    let x = 42;\n"
    "    let y = 3.14159;\n"
    "    let s = \"Hello, World!\";\n"
    "    if x > 10 && y < 100.0 {\n"
    "        return result;\n"
    "    } else {\n"
    "        return 0;\n"
    "    }\n"
    "};\n";

// 100x source pre-built as global (matches BMB gen_large(100))
static char large_source[200000];

static void gen_large(int reps) {
    large_source[0] = '\0';
    size_t single_len = strlen(test_source);
    for (int i = 0; i < reps; i++)
        memcpy(large_source + i * single_len, test_source, single_len);
    large_source[reps * single_len] = '\0';
}

int main(void) {
    gen_large(100);

    // warmup
    (void)black_box(count_tokens_from(large_source, 0));

    int64_t t0 = time_ns();
    int64_t total = 0;
    for (int i = 0; i < 50; i++) {
        int start = (int)black_box(0);  // always 0, but opaque to optimizer
        total += black_box(count_tokens_from(large_source, start));
    }
    int64_t t1 = time_ns();
    int64_t elapsed_us = (t1 - t0) / 1000;

    printf("%lld\n", (long long)total);
    printf("%lld\n", (long long)elapsed_us);
    return 0;
}
