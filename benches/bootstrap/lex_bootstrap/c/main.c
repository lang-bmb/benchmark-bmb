// lex-bootstrap - BMB lexer throughput benchmark
// Measures: Token generation for BMB source code
// Uses actual BMB syntax patterns from bootstrap compiler

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// Token types
typedef enum {
    TOK_EOF = 0,
    TOK_IDENT,
    TOK_NUMBER,
    TOK_STRING,
    TOK_KEYWORD,
    TOK_OPERATOR,
    TOK_PUNCT,
    TOK_COMMENT,
    TOK_ARROW,    // ->
    TOK_FAT_ARROW, // =>
    TOK_UNKNOWN
} TokenType;

// Lexer state
typedef struct {
    const char *src;
    int pos;
    int len;
} Lexer;

// BMB keywords
static const char *keywords[] = {
    "fn", "let", "if", "then", "else", "true", "false",
    "and", "or", "not", "pre", "post", "ret",
    "struct", "enum", "match", "new", "mut", "while",
    "for", "in", "return", "var", "type", "impl",
    "pub", "mod", "use", "as", "where", "trait",
    NULL
};

static bool is_keyword(const char *s, int len) {
    char buf[32];
    if (len >= 32) return false;
    strncpy(buf, s, len);
    buf[len] = '\0';
    for (int i = 0; keywords[i]; i++) {
        if (strcmp(buf, keywords[i]) == 0) return true;
    }
    return false;
}

static void lexer_init(Lexer *lex, const char *src) {
    lex->src = src;
    lex->pos = 0;
    lex->len = strlen(src);
}

static char peek(Lexer *lex) {
    return lex->pos < lex->len ? lex->src[lex->pos] : '\0';
}

static char peek_next(Lexer *lex) {
    return lex->pos + 1 < lex->len ? lex->src[lex->pos + 1] : '\0';
}

static void advance(Lexer *lex) {
    if (lex->pos < lex->len) lex->pos++;
}

static void skip_whitespace(Lexer *lex) {
    while (isspace(peek(lex))) advance(lex);
}

static TokenType next_token(Lexer *lex) {
    skip_whitespace(lex);

    if (lex->pos >= lex->len) return TOK_EOF;

    char c = peek(lex);

    // BMB comments: --
    if (c == '-' && peek_next(lex) == '-') {
        while (peek(lex) && peek(lex) != '\n') advance(lex);
        return TOK_COMMENT;
    }

    // Arrow: ->
    if (c == '-' && peek_next(lex) == '>') {
        advance(lex); advance(lex);
        return TOK_ARROW;
    }

    // Fat arrow: =>
    if (c == '=' && peek_next(lex) == '>') {
        advance(lex); advance(lex);
        return TOK_FAT_ARROW;
    }

    // Identifiers and keywords
    if (isalpha(c) || c == '_') {
        int start = lex->pos;
        while (isalnum(peek(lex)) || peek(lex) == '_') advance(lex);
        int len = lex->pos - start;
        return is_keyword(lex->src + start, len) ? TOK_KEYWORD : TOK_IDENT;
    }

    // Numbers (including floats)
    if (isdigit(c)) {
        while (isdigit(peek(lex))) advance(lex);
        if (peek(lex) == '.' && isdigit(peek_next(lex))) {
            advance(lex);
            while (isdigit(peek(lex))) advance(lex);
        }
        return TOK_NUMBER;
    }

    // Strings
    if (c == '"') {
        advance(lex);
        while (peek(lex) && peek(lex) != '"') {
            if (peek(lex) == '\\') advance(lex);
            advance(lex);
        }
        if (peek(lex) == '"') advance(lex);
        return TOK_STRING;
    }

    // Operators (2-char)
    if ((c == '=' || c == '!' || c == '<' || c == '>' || c == '&' || c == '|' || c == ':') &&
        (peek_next(lex) == '=' || peek_next(lex) == '&' || peek_next(lex) == '|' || peek_next(lex) == ':')) {
        advance(lex);
        advance(lex);
        return TOK_OPERATOR;
    }

    // Operators (1-char)
    if (strchr("+-*/%=<>!&|:.", c)) {
        advance(lex);
        return TOK_OPERATOR;
    }

    // Punctuation
    if (strchr("(){}[];,", c)) {
        advance(lex);
        return TOK_PUNCT;
    }

    // Unknown
    advance(lex);
    return TOK_UNKNOWN;
}

// Sample BMB source (representative bootstrap patterns)
static const char *sample_source =
    "-- BMB function definition\n"
    "fn fibonacci(n: i64) -> i64\n"
    "  pre n >= 0\n"
    "  post ret >= 0\n"
    "= if n <= 1 then n\n"
    "  else fibonacci(n - 1) + fibonacci(n - 2);\n"
    "\n"
    "-- Type definitions\n"
    "struct Token {\n"
    "    kind: i64,\n"
    "    start: i64,\n"
    "    end_pos: i64\n"
    "}\n"
    "\n"
    "enum Option<T> {\n"
    "    Some(T),\n"
    "    None\n"
    "}\n"
    "\n"
    "-- Pattern matching\n"
    "fn process(opt: Option<i64>) -> i64 =\n"
    "    match opt {\n"
    "        Some(x) => x * 2,\n"
    "        None => 0\n"
    "    };\n"
    "\n"
    "-- Let bindings\n"
    "fn compute(a: i64, b: i64) -> i64 = {\n"
    "    let x = a + b;\n"
    "    let y = a - b;\n"
    "    let z = x * y;\n"
    "    z + 1\n"
    "};\n";

// Generate larger source for benchmarking
static char large_source[500000];

static void generate_large_source(int reps) {
    large_source[0] = '\0';
    for (int i = 0; i < reps; i++) {
        strcat(large_source, sample_source);
    }
}

// Count tokens and return stats
static int count_tokens(const char *src) {
    Lexer lex;
    lexer_init(&lex, src);
    int count = 0;
    TokenType tok;
    while ((tok = next_token(&lex)) != TOK_EOF) {
        count++;
    }
    return count;
}

int main(void) {
    printf("Lex Bootstrap Benchmark\n");
    printf("Lexer for BMB source code\n\n");

    // Test small source
    int small_tokens = count_tokens(sample_source);
    printf("Sample source:\n");
    printf("  Length: %zu bytes\n", strlen(sample_source));
    printf("  Tokens: %d\n\n", small_tokens);

    // Benchmark with larger source
    generate_large_source(500);  // ~500KB of BMB source
    int large_len = strlen(large_source);

    clock_t start = clock();
    int large_tokens = count_tokens(large_source);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    double throughput = (large_len / 1024.0) / elapsed;  // KB/s

    printf("Large source (500x):\n");
    printf("  Length: %d bytes (%.1f KB)\n", large_len, large_len / 1024.0);
    printf("  Tokens: %d\n", large_tokens);
    printf("  Time: %.3f seconds\n", elapsed);
    printf("  Throughput: %.1f KB/s\n", throughput);

    printf("\nDone.\n");
    return 0;
}
