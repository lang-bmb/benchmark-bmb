// parse-bootstrap - BMB parser throughput benchmark
// Measures: AST construction from BMB source code
// Parses function definitions, expressions, statements

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

// AST node types
typedef enum {
    NODE_FUNC,
    NODE_LET,
    NODE_IF,
    NODE_BINARY,
    NODE_CALL,
    NODE_IDENT,
    NODE_NUMBER,
    NODE_BLOCK,
    NODE_STRUCT,
    NODE_ENUM,
    NODE_MATCH
} NodeType;

// Simple AST node count tracking
typedef struct {
    int functions;
    int let_bindings;
    int if_exprs;
    int binary_ops;
    int calls;
    int idents;
    int numbers;
    int blocks;
    int structs;
    int enums;
    int matches;
} ParseStats;

// Parser state
typedef struct {
    const char *src;
    int pos;
    int len;
    ParseStats stats;
} Parser;

// Character helpers
static bool is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
static bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
static bool is_digit(char c) { return c >= '0' && c <= '9'; }
static bool is_alnum(char c) { return is_alpha(c) || is_digit(c) || c == '_'; }

static char peek(Parser *p) { return p->pos < p->len ? p->src[p->pos] : '\0'; }
static char peek_n(Parser *p, int n) { return p->pos + n < p->len ? p->src[p->pos + n] : '\0'; }
static void advance(Parser *p) { if (p->pos < p->len) p->pos++; }

static void skip_ws(Parser *p) {
    while (p->pos < p->len) {
        if (is_ws(peek(p))) {
            advance(p);
        } else if (peek(p) == '-' && peek_n(p, 1) == '-') {
            while (peek(p) && peek(p) != '\n') advance(p);
        } else {
            break;
        }
    }
}

static bool match_keyword(Parser *p, const char *kw) {
    skip_ws(p);
    int len = strlen(kw);
    if (p->pos + len > p->len) return false;
    if (strncmp(p->src + p->pos, kw, len) != 0) return false;
    if (p->pos + len < p->len && is_alnum(p->src[p->pos + len])) return false;
    p->pos += len;
    return true;
}

static void skip_to_char(Parser *p, char c) {
    while (peek(p) && peek(p) != c) advance(p);
    if (peek(p) == c) advance(p);
}

static void skip_identifier(Parser *p) {
    skip_ws(p);
    while (is_alnum(peek(p))) advance(p);
}

static void skip_balanced(Parser *p, char open, char close) {
    int depth = 1;
    advance(p);  // skip opening
    while (p->pos < p->len && depth > 0) {
        char c = peek(p);
        if (c == open) depth++;
        else if (c == close) depth--;
        advance(p);
    }
}

// Forward declarations
static void parse_expr(Parser *p);
static void parse_block(Parser *p);

static void parse_primary(Parser *p) {
    skip_ws(p);
    char c = peek(p);

    if (c == '(') {
        advance(p);
        parse_expr(p);
        skip_ws(p);
        if (peek(p) == ')') advance(p);
    } else if (c == '{') {
        parse_block(p);
    } else if (is_digit(c)) {
        while (is_digit(peek(p)) || peek(p) == '.') advance(p);
        p->stats.numbers++;
    } else if (is_alpha(c) || c == '_') {
        skip_identifier(p);
        p->stats.idents++;
        skip_ws(p);
        if (peek(p) == '(') {
            p->stats.calls++;
            skip_balanced(p, '(', ')');
        }
    }
}

static void parse_expr(Parser *p) {
    skip_ws(p);

    if (match_keyword(p, "if")) {
        p->stats.if_exprs++;
        parse_expr(p);  // condition
        skip_ws(p);
        if (match_keyword(p, "then") || peek(p) == '{') {
            parse_expr(p);  // then branch
        }
        skip_ws(p);
        if (match_keyword(p, "else")) {
            parse_expr(p);  // else branch
        }
        return;
    }

    if (match_keyword(p, "match")) {
        p->stats.matches++;
        parse_expr(p);  // scrutinee
        skip_ws(p);
        if (peek(p) == '{') {
            skip_balanced(p, '{', '}');
        }
        return;
    }

    parse_primary(p);

    // Binary operators
    skip_ws(p);
    while (peek(p) == '+' || peek(p) == '-' || peek(p) == '*' || peek(p) == '/' ||
           peek(p) == '<' || peek(p) == '>' || peek(p) == '=' || peek(p) == '&' || peek(p) == '|') {
        p->stats.binary_ops++;
        advance(p);
        if (peek(p) == '=' || peek(p) == '>' || peek(p) == '&' || peek(p) == '|') advance(p);
        parse_primary(p);
        skip_ws(p);
    }
}

static void parse_block(Parser *p) {
    skip_ws(p);
    if (peek(p) != '{') return;
    p->stats.blocks++;
    advance(p);

    while (peek(p) && peek(p) != '}') {
        skip_ws(p);
        if (match_keyword(p, "let")) {
            p->stats.let_bindings++;
            skip_identifier(p);
            skip_ws(p);
            if (peek(p) == ':') {
                skip_to_char(p, '=');
            }
            if (peek(p) == '=') advance(p);
            parse_expr(p);
            skip_ws(p);
            if (peek(p) == ';') advance(p);
        } else if (peek(p) == '}') {
            break;
        } else {
            parse_expr(p);
            skip_ws(p);
            if (peek(p) == ';') advance(p);
        }
    }
    if (peek(p) == '}') advance(p);
}

static void parse_function(Parser *p) {
    if (!match_keyword(p, "fn")) return;
    p->stats.functions++;

    skip_identifier(p);  // function name
    skip_ws(p);

    // Parameters
    if (peek(p) == '(') {
        skip_balanced(p, '(', ')');
    }

    // Return type
    skip_ws(p);
    if (peek(p) == '-' && peek_n(p, 1) == '>') {
        advance(p); advance(p);
        skip_identifier(p);
        // Handle generic types
        if (peek(p) == '<') skip_balanced(p, '<', '>');
    }

    // Contracts
    skip_ws(p);
    while (match_keyword(p, "pre") || match_keyword(p, "post")) {
        parse_expr(p);
        skip_ws(p);
    }

    // Body
    skip_ws(p);
    if (peek(p) == '=') {
        advance(p);
        parse_expr(p);
    }

    skip_ws(p);
    if (peek(p) == ';') advance(p);
}

static void parse_struct(Parser *p) {
    if (!match_keyword(p, "struct")) return;
    p->stats.structs++;
    skip_identifier(p);
    skip_ws(p);
    if (peek(p) == '<') skip_balanced(p, '<', '>');
    skip_ws(p);
    if (peek(p) == '{') skip_balanced(p, '{', '}');
}

static void parse_enum(Parser *p) {
    if (!match_keyword(p, "enum")) return;
    p->stats.enums++;
    skip_identifier(p);
    skip_ws(p);
    if (peek(p) == '<') skip_balanced(p, '<', '>');
    skip_ws(p);
    if (peek(p) == '{') skip_balanced(p, '{', '}');
}

static void parse_program(Parser *p) {
    while (p->pos < p->len) {
        skip_ws(p);
        if (p->pos >= p->len) break;

        int old_pos = p->pos;
        if (peek(p) == 'f' && peek_n(p, 1) == 'n' && !is_alnum(peek_n(p, 2))) {
            parse_function(p);
        } else if (peek(p) == 's' && peek_n(p, 1) == 't' && peek_n(p, 2) == 'r') {
            parse_struct(p);
        } else if (peek(p) == 'e' && peek_n(p, 1) == 'n' && peek_n(p, 2) == 'u') {
            parse_enum(p);
        }
        // Ensure we always make progress
        if (p->pos == old_pos) {
            advance(p);
        }
    }
}

static void init_parser(Parser *p, const char *src) {
    p->src = src;
    p->pos = 0;
    p->len = strlen(src);
    memset(&p->stats, 0, sizeof(ParseStats));
}

// Sample BMB source
static const char *sample_source =
    "-- BMB function definitions\n"
    "fn fibonacci(n: i64) -> i64\n"
    "  pre n >= 0\n"
    "  post ret >= 0\n"
    "= if n <= 1 then n\n"
    "  else fibonacci(n - 1) + fibonacci(n - 2);\n"
    "\n"
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
    "fn compute(a: i64, b: i64) -> i64 = {\n"
    "    let x = a + b;\n"
    "    let y = a - b;\n"
    "    x * y\n"
    "};\n"
    "\n"
    "fn process(opt: Option<i64>) -> i64 =\n"
    "    match opt {\n"
    "        Some(x) => x * 2,\n"
    "        None => 0\n"
    "    };\n";

static char large_source[500000];

static void generate_large_source(int reps) {
    large_source[0] = '\0';
    for (int i = 0; i < reps; i++) {
        strcat(large_source, sample_source);
    }
}

int main(void) {
    printf("Parse Bootstrap Benchmark\n");
    printf("Parser for BMB source code\n\n");

    // Test small source
    Parser p;
    init_parser(&p, sample_source);
    parse_program(&p);

    printf("Sample source:\n");
    printf("  Length: %zu bytes\n", strlen(sample_source));
    printf("  Functions: %d\n", p.stats.functions);
    printf("  Structs: %d\n", p.stats.structs);
    printf("  Enums: %d\n", p.stats.enums);
    printf("  Let bindings: %d\n", p.stats.let_bindings);
    printf("  If expressions: %d\n", p.stats.if_exprs);
    printf("  Match expressions: %d\n", p.stats.matches);
    printf("\n");

    // Benchmark with larger source (100x for reasonable benchmark time)
    generate_large_source(100);
    int large_len = strlen(large_source);

    clock_t start = clock();
    init_parser(&p, large_source);
    parse_program(&p);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    double throughput = (large_len / 1024.0) / elapsed;

    printf("Large source (100x):\n");
    printf("  Length: %d bytes (%.1f KB)\n", large_len, large_len / 1024.0);
    printf("  Functions: %d\n", p.stats.functions);
    printf("  Total nodes: %d\n",
           p.stats.functions + p.stats.structs + p.stats.enums +
           p.stats.let_bindings + p.stats.if_exprs + p.stats.matches);
    printf("  Time: %.3f seconds\n", elapsed);
    printf("  Throughput: %.1f KB/s\n", throughput);

    printf("\nDone.\n");
    return 0;
}
