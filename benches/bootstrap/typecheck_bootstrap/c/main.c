// typecheck-bootstrap - BMB type checker throughput benchmark
// Measures: Type inference and checking for BMB expressions
// Implements simplified Hindley-Milner style type checking

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Type encoding: kind * 1000 + extra
// Kinds: 1=i32, 2=i64, 3=f64, 4=bool, 5=string, 6=unit, 10=error
#define TY_I32    1000
#define TY_I64    2000
#define TY_F64    3000
#define TY_BOOL   4000
#define TY_STRING 5000
#define TY_UNIT   6000
#define TY_ERROR  10000

static int type_kind(int ty) { return ty / 1000; }

static const char* type_name(int ty) {
    switch (type_kind(ty)) {
        case 1: return "i32";
        case 2: return "i64";
        case 3: return "f64";
        case 4: return "bool";
        case 5: return "String";
        case 6: return "()";
        case 10: return "error";
        default: return "unknown";
    }
}

// Expression types
typedef enum {
    EXPR_INT_LIT,
    EXPR_FLOAT_LIT,
    EXPR_BOOL_LIT,
    EXPR_STRING_LIT,
    EXPR_VAR,
    EXPR_BINOP,
    EXPR_UNARYOP,
    EXPR_IF,
    EXPR_LET,
    EXPR_CALL,
    EXPR_BLOCK
} ExprKind;

typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_EQ, OP_NE, OP_LT, OP_LE, OP_GT, OP_GE,
    OP_AND, OP_OR
} BinOpKind;

typedef enum {
    UOP_NEG, UOP_NOT
} UnaryOpKind;

typedef struct Expr Expr;

struct Expr {
    ExprKind kind;
    union {
        long int_val;
        double float_val;
        bool bool_val;
        char string_val[64];
        char var_name[32];
        struct { Expr* left; BinOpKind op; Expr* right; } binop;
        struct { UnaryOpKind op; Expr* operand; } unaryop;
        struct { Expr* cond; Expr* then_branch; Expr* else_branch; } if_expr;
        struct { char name[32]; Expr* value; Expr* body; } let_expr;
        struct { char name[32]; Expr* args[4]; int arg_count; } call_expr;
        struct { Expr* exprs[8]; int count; } block_expr;
    };
};

// Type environment
#define MAX_VARS 64
#define MAX_FUNCS 16

typedef struct {
    char names[MAX_VARS][32];
    int types[MAX_VARS];
    int var_count;

    char func_names[MAX_FUNCS][32];
    int func_ret_types[MAX_FUNCS];
    int func_param_types[MAX_FUNCS][4];
    int func_param_counts[MAX_FUNCS];
    int func_count;
} TypeEnv;

static void env_init(TypeEnv* env) {
    env->var_count = 0;
    env->func_count = 0;

    // Built-in functions
    strcpy(env->func_names[0], "print");
    env->func_ret_types[0] = TY_UNIT;
    env->func_param_types[0][0] = TY_STRING;
    env->func_param_counts[0] = 1;

    strcpy(env->func_names[1], "len");
    env->func_ret_types[1] = TY_I64;
    env->func_param_types[1][0] = TY_STRING;
    env->func_param_counts[1] = 1;

    strcpy(env->func_names[2], "int_to_string");
    env->func_ret_types[2] = TY_STRING;
    env->func_param_types[2][0] = TY_I64;
    env->func_param_counts[2] = 1;

    env->func_count = 3;
}

static int env_lookup_var(TypeEnv* env, const char* name) {
    for (int i = env->var_count - 1; i >= 0; i--) {
        if (strcmp(env->names[i], name) == 0) {
            return env->types[i];
        }
    }
    return TY_ERROR;
}

static int env_lookup_func(TypeEnv* env, const char* name, int* param_count, int** param_types) {
    for (int i = 0; i < env->func_count; i++) {
        if (strcmp(env->func_names[i], name) == 0) {
            *param_count = env->func_param_counts[i];
            *param_types = env->func_param_types[i];
            return env->func_ret_types[i];
        }
    }
    return TY_ERROR;
}

static void env_push_var(TypeEnv* env, const char* name, int ty) {
    if (env->var_count < MAX_VARS) {
        strcpy(env->names[env->var_count], name);
        env->types[env->var_count] = ty;
        env->var_count++;
    }
}

static void env_pop_var(TypeEnv* env) {
    if (env->var_count > 0) {
        env->var_count--;
    }
}

// Type checker stats
typedef struct {
    int literals;
    int binops;
    int unaryops;
    int vars;
    int ifs;
    int lets;
    int calls;
    int blocks;
    int unifications;
} CheckStats;

static int unify(CheckStats* stats, int t1, int t2) {
    stats->unifications++;
    if (t1 == t2) return t1;
    if (type_kind(t1) == 10) return t2;
    if (type_kind(t2) == 10) return t1;
    return TY_ERROR;
}

static int check_expr(Expr* expr, TypeEnv* env, CheckStats* stats) {
    switch (expr->kind) {
        case EXPR_INT_LIT:
            stats->literals++;
            return TY_I64;
        case EXPR_FLOAT_LIT:
            stats->literals++;
            return TY_F64;
        case EXPR_BOOL_LIT:
            stats->literals++;
            return TY_BOOL;
        case EXPR_STRING_LIT:
            stats->literals++;
            return TY_STRING;
        case EXPR_VAR:
            stats->vars++;
            return env_lookup_var(env, expr->var_name);
        case EXPR_BINOP: {
            stats->binops++;
            int t1 = check_expr(expr->binop.left, env, stats);
            int t2 = check_expr(expr->binop.right, env, stats);
            BinOpKind op = expr->binop.op;

            if (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV || op == OP_MOD) {
                if (type_kind(t1) == type_kind(t2) && (type_kind(t1) == 2 || type_kind(t1) == 3)) {
                    return t1;
                }
                return TY_ERROR;
            }
            if (op == OP_EQ || op == OP_NE || op == OP_LT || op == OP_LE || op == OP_GT || op == OP_GE) {
                if (type_kind(t1) == type_kind(t2)) {
                    return TY_BOOL;
                }
                return TY_ERROR;
            }
            if (op == OP_AND || op == OP_OR) {
                if (type_kind(t1) == 4 && type_kind(t2) == 4) {
                    return TY_BOOL;
                }
                return TY_ERROR;
            }
            return TY_ERROR;
        }
        case EXPR_UNARYOP: {
            stats->unaryops++;
            int t = check_expr(expr->unaryop.operand, env, stats);
            if (expr->unaryop.op == UOP_NEG) {
                if (type_kind(t) == 2 || type_kind(t) == 3) return t;
                return TY_ERROR;
            }
            if (expr->unaryop.op == UOP_NOT) {
                if (type_kind(t) == 4) return TY_BOOL;
                return TY_ERROR;
            }
            return TY_ERROR;
        }
        case EXPR_IF: {
            stats->ifs++;
            int t_cond = check_expr(expr->if_expr.cond, env, stats);
            if (type_kind(t_cond) != 4) return TY_ERROR;
            int t_then = check_expr(expr->if_expr.then_branch, env, stats);
            int t_else = check_expr(expr->if_expr.else_branch, env, stats);
            return unify(stats, t_then, t_else);
        }
        case EXPR_LET: {
            stats->lets++;
            int t_value = check_expr(expr->let_expr.value, env, stats);
            env_push_var(env, expr->let_expr.name, t_value);
            int t_body = check_expr(expr->let_expr.body, env, stats);
            env_pop_var(env);
            return t_body;
        }
        case EXPR_CALL: {
            stats->calls++;
            int param_count;
            int* param_types;
            int ret_ty = env_lookup_func(env, expr->call_expr.name, &param_count, &param_types);
            if (ret_ty == TY_ERROR) return TY_ERROR;
            if (expr->call_expr.arg_count != param_count) return TY_ERROR;
            for (int i = 0; i < expr->call_expr.arg_count; i++) {
                int arg_ty = check_expr(expr->call_expr.args[i], env, stats);
                if (unify(stats, arg_ty, param_types[i]) == TY_ERROR) {
                    return TY_ERROR;
                }
            }
            return ret_ty;
        }
        case EXPR_BLOCK: {
            stats->blocks++;
            int result = TY_UNIT;
            for (int i = 0; i < expr->block_expr.count; i++) {
                result = check_expr(expr->block_expr.exprs[i], env, stats);
            }
            return result;
        }
    }
    return TY_ERROR;
}

// Expression allocation pool
static Expr expr_pool[1000];
static int expr_pool_idx = 0;

static Expr* alloc_expr(void) {
    return &expr_pool[expr_pool_idx++];
}

static void reset_pool(void) {
    expr_pool_idx = 0;
}

// Create sample expressions
static Expr* make_int(long v) {
    Expr* e = alloc_expr();
    e->kind = EXPR_INT_LIT;
    e->int_val = v;
    return e;
}

static Expr* make_bool(bool v) {
    Expr* e = alloc_expr();
    e->kind = EXPR_BOOL_LIT;
    e->bool_val = v;
    return e;
}

static Expr* make_var(const char* name) {
    Expr* e = alloc_expr();
    e->kind = EXPR_VAR;
    strcpy(e->var_name, name);
    return e;
}

static Expr* make_binop(Expr* left, BinOpKind op, Expr* right) {
    Expr* e = alloc_expr();
    e->kind = EXPR_BINOP;
    e->binop.left = left;
    e->binop.op = op;
    e->binop.right = right;
    return e;
}

static Expr* make_unaryop(UnaryOpKind op, Expr* operand) {
    Expr* e = alloc_expr();
    e->kind = EXPR_UNARYOP;
    e->unaryop.op = op;
    e->unaryop.operand = operand;
    return e;
}

static Expr* make_if(Expr* cond, Expr* then_branch, Expr* else_branch) {
    Expr* e = alloc_expr();
    e->kind = EXPR_IF;
    e->if_expr.cond = cond;
    e->if_expr.then_branch = then_branch;
    e->if_expr.else_branch = else_branch;
    return e;
}

static Expr* make_let(const char* name, Expr* value, Expr* body) {
    Expr* e = alloc_expr();
    e->kind = EXPR_LET;
    strcpy(e->let_expr.name, name);
    e->let_expr.value = value;
    e->let_expr.body = body;
    return e;
}

static void generate_sample_exprs(Expr** exprs, int* count) {
    reset_pool();
    *count = 0;

    // Expr 1: (1 + 2) * 3
    exprs[(*count)++] = make_binop(
        make_binop(make_int(1), OP_ADD, make_int(2)),
        OP_MUL,
        make_int(3)
    );

    // Expr 2: let x = 5; x < 10
    exprs[(*count)++] = make_let("x", make_int(5),
        make_binop(make_var("x"), OP_LT, make_int(10))
    );

    // Expr 3: let x = 5; if x > 0 then x else -x
    exprs[(*count)++] = make_let("x", make_int(5),
        make_if(
            make_binop(make_var("x"), OP_GT, make_int(0)),
            make_var("x"),
            make_unaryop(UOP_NEG, make_var("x"))
        )
    );

    // Expr 4: let a = 1; let b = 2; a + b
    exprs[(*count)++] = make_let("a", make_int(1),
        make_let("b", make_int(2),
            make_binop(make_var("a"), OP_ADD, make_var("b"))
        )
    );

    // Expr 5: let a = true; let b = false; let c = true; (a and b) or (not c)
    exprs[(*count)++] = make_let("a", make_bool(true),
        make_let("b", make_bool(false),
            make_let("c", make_bool(true),
                make_binop(
                    make_binop(make_var("a"), OP_AND, make_var("b")),
                    OP_OR,
                    make_unaryop(UOP_NOT, make_var("c"))
                )
            )
        )
    );
}

int main(void) {
    printf("TypeCheck Bootstrap Benchmark\n");
    printf("Type checker for BMB expressions\n\n");

    Expr* exprs[10];
    int expr_count;
    generate_sample_exprs(exprs, &expr_count);

    TypeEnv env;
    CheckStats stats = {0};

    printf("Sample expressions:\n");
    for (int i = 0; i < expr_count; i++) {
        env_init(&env);
        memset(&stats, 0, sizeof(stats));
        int ty = check_expr(exprs[i], &env, &stats);
        printf("  Expr %d: type = %s\n", i + 1, type_name(ty));
    }
    printf("\n");

    // Benchmark
    int iterations = 100000;
    clock_t start = clock();
    int total_checks = 0;

    for (int iter = 0; iter < iterations; iter++) {
        env_init(&env);
        memset(&stats, 0, sizeof(stats));
        for (int i = 0; i < expr_count; i++) {
            check_expr(exprs[i], &env, &stats);
            total_checks++;
        }
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    double checks_per_sec = total_checks / elapsed;

    printf("Benchmark (%d iterations x %d exprs):\n", iterations, expr_count);
    printf("  Total checks: %d\n", total_checks);
    printf("  Time: %.3f seconds\n", elapsed);
    printf("  Throughput: %.0f checks/s\n", checks_per_sec);

    printf("\nDone.\n");
    return 0;
}
