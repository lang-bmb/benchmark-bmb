// typecheck-bootstrap - BMB type checker throughput benchmark
// Measures: Type inference and checking for BMB expressions
// Implements simplified Hindley-Milner style type checking

use std::time::Instant;

// Type encoding: kind * 1000 + extra
// Kinds: 1=i32, 2=i64, 3=f64, 4=bool, 5=string, 6=unit, 10=error, 20=generic
const TY_I32: i64 = 1000;
const TY_I64: i64 = 2000;
const TY_F64: i64 = 3000;
const TY_BOOL: i64 = 4000;
const TY_STRING: i64 = 5000;
const TY_UNIT: i64 = 6000;
const TY_ERROR: i64 = 10000;

fn type_kind(ty: i64) -> i64 {
    ty / 1000
}

fn type_name(ty: i64) -> &'static str {
    match type_kind(ty) {
        1 => "i32",
        2 => "i64",
        3 => "f64",
        4 => "bool",
        5 => "String",
        6 => "()",
        10 => "error",
        _ => "unknown",
    }
}

// Expression types for AST representation
#[derive(Clone, Debug)]
enum Expr {
    IntLit(i64),
    FloatLit(f64),
    BoolLit(bool),
    StringLit(String),
    Var(String),
    BinOp(Box<Expr>, BinOpKind, Box<Expr>),
    UnaryOp(UnaryOpKind, Box<Expr>),
    If(Box<Expr>, Box<Expr>, Box<Expr>),
    Let(String, Box<Expr>, Box<Expr>),
    Call(String, Vec<Expr>),
    Block(Vec<Expr>),
}

#[derive(Clone, Copy, Debug)]
enum BinOpKind {
    Add, Sub, Mul, Div, Mod,
    Eq, Ne, Lt, Le, Gt, Ge,
    And, Or,
}

#[derive(Clone, Copy, Debug)]
enum UnaryOpKind {
    Neg, Not,
}

// Type environment
struct TypeEnv {
    vars: Vec<(String, i64)>,
    funcs: Vec<(String, i64, Vec<i64>)>, // name, return_type, param_types
}

impl TypeEnv {
    fn new() -> Self {
        let mut env = TypeEnv {
            vars: Vec::new(),
            funcs: Vec::new(),
        };
        // Built-in functions
        env.funcs.push(("print".to_string(), TY_UNIT, vec![TY_STRING]));
        env.funcs.push(("len".to_string(), TY_I64, vec![TY_STRING]));
        env.funcs.push(("int_to_string".to_string(), TY_STRING, vec![TY_I64]));
        env
    }

    fn lookup_var(&self, name: &str) -> Option<i64> {
        for (n, ty) in self.vars.iter().rev() {
            if n == name {
                return Some(*ty);
            }
        }
        None
    }

    fn lookup_func(&self, name: &str) -> Option<(i64, &[i64])> {
        for (n, ret, params) in &self.funcs {
            if n == name {
                return Some((*ret, params));
            }
        }
        None
    }

    fn push_var(&mut self, name: String, ty: i64) {
        self.vars.push((name, ty));
    }

    fn pop_var(&mut self) {
        self.vars.pop();
    }
}

// Type checker
struct TypeChecker {
    stats: CheckStats,
}

#[derive(Default)]
struct CheckStats {
    literals: usize,
    binops: usize,
    unaryops: usize,
    vars: usize,
    ifs: usize,
    lets: usize,
    calls: usize,
    blocks: usize,
    unifications: usize,
}

impl TypeChecker {
    fn new() -> Self {
        TypeChecker {
            stats: CheckStats::default(),
        }
    }

    fn unify(&mut self, t1: i64, t2: i64) -> i64 {
        self.stats.unifications += 1;
        if t1 == t2 {
            t1
        } else if type_kind(t1) == 10 {
            t2
        } else if type_kind(t2) == 10 {
            t1
        } else {
            TY_ERROR
        }
    }

    fn check_expr(&mut self, expr: &Expr, env: &mut TypeEnv) -> i64 {
        match expr {
            Expr::IntLit(_) => {
                self.stats.literals += 1;
                TY_I64
            }
            Expr::FloatLit(_) => {
                self.stats.literals += 1;
                TY_F64
            }
            Expr::BoolLit(_) => {
                self.stats.literals += 1;
                TY_BOOL
            }
            Expr::StringLit(_) => {
                self.stats.literals += 1;
                TY_STRING
            }
            Expr::Var(name) => {
                self.stats.vars += 1;
                env.lookup_var(name).unwrap_or(TY_ERROR)
            }
            Expr::BinOp(left, op, right) => {
                self.stats.binops += 1;
                let t1 = self.check_expr(left, env);
                let t2 = self.check_expr(right, env);

                match op {
                    BinOpKind::Add | BinOpKind::Sub | BinOpKind::Mul | BinOpKind::Div | BinOpKind::Mod => {
                        if type_kind(t1) == type_kind(t2) && (type_kind(t1) == 2 || type_kind(t1) == 3) {
                            t1
                        } else {
                            TY_ERROR
                        }
                    }
                    BinOpKind::Eq | BinOpKind::Ne | BinOpKind::Lt | BinOpKind::Le | BinOpKind::Gt | BinOpKind::Ge => {
                        if type_kind(t1) == type_kind(t2) {
                            TY_BOOL
                        } else {
                            TY_ERROR
                        }
                    }
                    BinOpKind::And | BinOpKind::Or => {
                        if type_kind(t1) == 4 && type_kind(t2) == 4 {
                            TY_BOOL
                        } else {
                            TY_ERROR
                        }
                    }
                }
            }
            Expr::UnaryOp(op, operand) => {
                self.stats.unaryops += 1;
                let t = self.check_expr(operand, env);
                match op {
                    UnaryOpKind::Neg => {
                        if type_kind(t) == 2 || type_kind(t) == 3 {
                            t
                        } else {
                            TY_ERROR
                        }
                    }
                    UnaryOpKind::Not => {
                        if type_kind(t) == 4 {
                            TY_BOOL
                        } else {
                            TY_ERROR
                        }
                    }
                }
            }
            Expr::If(cond, then_branch, else_branch) => {
                self.stats.ifs += 1;
                let t_cond = self.check_expr(cond, env);
                if type_kind(t_cond) != 4 {
                    return TY_ERROR;
                }
                let t_then = self.check_expr(then_branch, env);
                let t_else = self.check_expr(else_branch, env);
                self.unify(t_then, t_else)
            }
            Expr::Let(name, value, body) => {
                self.stats.lets += 1;
                let t_value = self.check_expr(value, env);
                env.push_var(name.clone(), t_value);
                let t_body = self.check_expr(body, env);
                env.pop_var();
                t_body
            }
            Expr::Call(name, args) => {
                self.stats.calls += 1;
                // Copy function info to avoid borrow conflict
                let func_info = env.lookup_func(name).map(|(ret, params)| {
                    (ret, params.to_vec())
                });
                if let Some((ret_ty, param_tys)) = func_info {
                    if args.len() != param_tys.len() {
                        return TY_ERROR;
                    }
                    for (arg, &param_ty) in args.iter().zip(param_tys.iter()) {
                        let arg_ty = self.check_expr(arg, env);
                        if self.unify(arg_ty, param_ty) == TY_ERROR {
                            return TY_ERROR;
                        }
                    }
                    ret_ty
                } else {
                    TY_ERROR
                }
            }
            Expr::Block(exprs) => {
                self.stats.blocks += 1;
                let mut result = TY_UNIT;
                for e in exprs {
                    result = self.check_expr(e, env);
                }
                result
            }
        }
    }
}

// Generate sample expressions for benchmarking
fn generate_sample_exprs() -> Vec<Expr> {
    vec![
        // Arithmetic expression: (1 + 2) * 3
        Expr::BinOp(
            Box::new(Expr::BinOp(
                Box::new(Expr::IntLit(1)),
                BinOpKind::Add,
                Box::new(Expr::IntLit(2)),
            )),
            BinOpKind::Mul,
            Box::new(Expr::IntLit(3)),
        ),
        // Comparison: x < 10
        Expr::Let(
            "x".to_string(),
            Box::new(Expr::IntLit(5)),
            Box::new(Expr::BinOp(
                Box::new(Expr::Var("x".to_string())),
                BinOpKind::Lt,
                Box::new(Expr::IntLit(10)),
            )),
        ),
        // If expression: if x > 0 then x else -x
        Expr::Let(
            "x".to_string(),
            Box::new(Expr::IntLit(5)),
            Box::new(Expr::If(
                Box::new(Expr::BinOp(
                    Box::new(Expr::Var("x".to_string())),
                    BinOpKind::Gt,
                    Box::new(Expr::IntLit(0)),
                )),
                Box::new(Expr::Var("x".to_string())),
                Box::new(Expr::UnaryOp(
                    UnaryOpKind::Neg,
                    Box::new(Expr::Var("x".to_string())),
                )),
            )),
        ),
        // Nested let: let a = 1; let b = 2; a + b
        Expr::Let(
            "a".to_string(),
            Box::new(Expr::IntLit(1)),
            Box::new(Expr::Let(
                "b".to_string(),
                Box::new(Expr::IntLit(2)),
                Box::new(Expr::BinOp(
                    Box::new(Expr::Var("a".to_string())),
                    BinOpKind::Add,
                    Box::new(Expr::Var("b".to_string())),
                )),
            )),
        ),
        // Boolean logic: (a and b) or (not c)
        Expr::Let(
            "a".to_string(),
            Box::new(Expr::BoolLit(true)),
            Box::new(Expr::Let(
                "b".to_string(),
                Box::new(Expr::BoolLit(false)),
                Box::new(Expr::Let(
                    "c".to_string(),
                    Box::new(Expr::BoolLit(true)),
                    Box::new(Expr::BinOp(
                        Box::new(Expr::BinOp(
                            Box::new(Expr::Var("a".to_string())),
                            BinOpKind::And,
                            Box::new(Expr::Var("b".to_string())),
                        )),
                        BinOpKind::Or,
                        Box::new(Expr::UnaryOp(
                            UnaryOpKind::Not,
                            Box::new(Expr::Var("c".to_string())),
                        )),
                    )),
                )),
            )),
        ),
    ]
}

fn main() {
    println!("TypeCheck Bootstrap Benchmark");
    println!("Type checker for BMB expressions\n");

    // Test sample expressions
    let exprs = generate_sample_exprs();
    let mut checker = TypeChecker::new();
    let mut env = TypeEnv::new();

    println!("Sample expressions:");
    for (i, expr) in exprs.iter().enumerate() {
        let ty = checker.check_expr(expr, &mut env);
        println!("  Expr {}: type = {}", i + 1, type_name(ty));
    }
    println!();

    // Benchmark with repeated checks
    let iterations = 100000;
    let exprs = generate_sample_exprs();

    let start = Instant::now();
    let mut total_checks = 0;
    for _ in 0..iterations {
        let mut checker = TypeChecker::new();
        let mut env = TypeEnv::new();
        for expr in &exprs {
            checker.check_expr(expr, &mut env);
            total_checks += 1;
        }
    }
    let elapsed = start.elapsed();

    let elapsed_secs = elapsed.as_secs_f64();
    let checks_per_sec = total_checks as f64 / elapsed_secs;

    println!("Benchmark ({} iterations x {} exprs):", iterations, exprs.len());
    println!("  Total checks: {}", total_checks);
    println!("  Time: {:.3} seconds", elapsed_secs);
    println!("  Throughput: {:.0} checks/s", checks_per_sec);

    println!("\nDone.");
}
