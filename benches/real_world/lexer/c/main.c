// lexer - Token generation benchmark
// Tests character processing, state machine, keyword matching
// Self-contained with embedded source code

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
    TOK_UNKNOWN
} TokenType;

// Lexer state
typedef struct {
    const char *src;
    int pos;
    int len;
} Lexer;

// Keywords
static const char *keywords[] = {
    "fn", "let", "if", "else", "while", "for", "return",
    "true", "false", "null", "struct", "enum", "match", NULL
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

    // Comments
    if (c == '-' && peek_next(lex) == '-') {
        while (peek(lex) && peek(lex) != '\n') advance(lex);
        return TOK_COMMENT;
    }

    // Identifiers and keywords
    if (isalpha(c) || c == '_') {
        int start = lex->pos;
        while (isalnum(peek(lex)) || peek(lex) == '_') advance(lex);
        int len = lex->pos - start;
        return is_keyword(lex->src + start, len) ? TOK_KEYWORD : TOK_IDENT;
    }

    // Numbers
    if (isdigit(c)) {
        while (isdigit(peek(lex)) || peek(lex) == '.') advance(lex);
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
    if ((c == '=' || c == '!' || c == '<' || c == '>' || c == '&' || c == '|') &&
        (peek_next(lex) == '=' || peek_next(lex) == '&' || peek_next(lex) == '|')) {
        advance(lex);
        advance(lex);
        return TOK_OPERATOR;
    }

    // Operators (1-char)
    if (strchr("+-*/%=<>!&|", c)) {
        advance(lex);
        return TOK_OPERATOR;
    }

    // Punctuation
    if (strchr("(){}[];:,.", c)) {
        advance(lex);
        return TOK_PUNCT;
    }

    // Unknown
    advance(lex);
    return TOK_UNKNOWN;
}

// Test source code
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

// Larger source for benchmarking
static char large_source[100000];

static void generate_large_source(int reps) {
    large_source[0] = '\0';
    for (int i = 0; i < reps; i++) {
        strcat(large_source, test_source);
    }
}

// Count tokens
static void count_tokens(const char *src, int *counts) {
    Lexer lex;
    lexer_init(&lex, src);

    for (int i = 0; i < 9; i++) counts[i] = 0;

    TokenType tok;
    while ((tok = next_token(&lex)) != TOK_EOF) {
        if (tok < 9) counts[tok]++;
    }
}

int main(void) {
    printf("Lexer Benchmark\n");

    // Test small source
    int counts[9];
    count_tokens(test_source, counts);

    printf("Small source:\n");
    printf("  Identifiers: %d\n", counts[TOK_IDENT]);
    printf("  Numbers: %d\n", counts[TOK_NUMBER]);
    printf("  Keywords: %d\n", counts[TOK_KEYWORD]);
    printf("  Strings: %d\n", counts[TOK_STRING]);
    printf("  Operators: %d\n", counts[TOK_OPERATOR]);
    printf("  Punctuation: %d\n", counts[TOK_PUNCT]);
    printf("  Comments: %d\n", counts[TOK_COMMENT]);
    printf("\n");

    // Benchmark with larger source (100x - matches BMB encoding limits)
    generate_large_source(100);
    count_tokens(large_source, counts);

    int total = 0;
    for (int i = 1; i < 8; i++) total += counts[i];

    printf("Large source (100x):\n");
    printf("  Total tokens: %d\n", total);

    printf("\nDone.\n");
    return 0;
}
