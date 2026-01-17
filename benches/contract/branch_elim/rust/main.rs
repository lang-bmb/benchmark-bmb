// Branch elimination benchmark
// Measures: dead branch removal based on value constraints
// In Rust: compiler may eliminate branches with optimization
// In BMB: contracts prove branch impossibility, enabling guaranteed elimination

// Always returns positive (in BMB: post ret > 0)
fn always_positive(x: i64) -> i64 {
    if x > 0 { x } else { 1 }
}

// Always returns non-negative (in BMB: post ret >= 0)
fn always_non_negative(x: i64) -> i64 {
    if x >= 0 { x } else { -x }
}

// Process with unreachable negative branch
fn process_positive(n: i64, sum: i64) -> i64 {
    if n <= 0 {
        return sum;
    }

    let value = always_positive(n);
    // The negative branch below is dead code (value is always > 0)
    let processed = if value > 0 {
        value * 2
    } else {
        // Dead branch - never executed
        0
    };
    process_positive(n - 1, sum + processed)
}

// Process with multiple dead branches
fn process_abs(n: i64, sum: i64) -> i64 {
    if n <= 0 {
        return sum;
    }

    let value = always_non_negative(n);
    // Multiple dead branches (value is always >= 0)
    let processed = if value >= 0 {
        if value > 1000000 {
            // Unlikely but possible
            value / 2
        } else {
            value * 3
        }
    } else {
        // Dead branch - never executed
        -value
    };
    process_abs(n - 1, sum + processed)
}

// Chained conditions with provable outcomes
fn chained_positive(x: i64) -> i64 {
    let a = always_positive(x);
    let b = always_positive(a);  // a > 0, so b > 0
    let c = always_positive(b);  // b > 0, so c > 0

    // All these negative checks are dead branches
    let mut result = 0;
    if a > 0 { result += a; }
    if b > 0 { result += b; }
    if c > 0 { result += c; }

    result
}

// Benchmark: many operations with dead branches
fn run_benchmark(iterations: i64, sum: i64) -> i64 {
    if iterations <= 0 {
        return sum;
    }

    let r1 = process_positive(100, 0);
    let r2 = process_abs(100, 0);
    let r3 = chained_positive(iterations);

    run_benchmark(iterations - 1, sum + r1 + r2 + r3)
}

fn main() {
    println!("Branch Elimination Benchmark\n");

    let result1 = process_positive(100, 0);
    println!("Process positive: {}", result1);

    let result2 = process_abs(100, 0);
    println!("Process abs: {}", result2);

    let result3 = chained_positive(50);
    println!("Chained positive: {}", result3);

    // Benchmark
    let bench = run_benchmark(100, 0);
    println!("\nBenchmark (100 iterations): {}", bench);

    println!("Done.");
}
