// Invariant hoisting benchmark
// Measures: loop invariant code motion optimization
// In Rust: compiler may hoist invariant computations with optimization
// In BMB: contracts can prove invariance, enabling guaranteed hoisting

// Expensive computation that is loop-invariant
fn expensive_compute(x: i64, y: i64) -> i64 {
    let mut result = 0i64;
    for i in 0..100 {
        result += (x * x + y * y) / (i + 1);
    }
    result
}

// Loop with invariant computation (can be hoisted)
fn loop_with_invariant(n: i64, constant_x: i64, constant_y: i64) -> i64 {
    let mut sum = 0i64;
    for i in 0..n {
        // This computation is loop-invariant (depends only on constants)
        let invariant = expensive_compute(constant_x, constant_y);
        sum += invariant + i;
    }
    sum
}

// Nested loop with outer-loop invariant
fn nested_with_invariant(outer_n: i64, inner_n: i64, constant: i64) -> i64 {
    let mut sum = 0i64;
    for i in 0..outer_n {
        // Outer-loop invariant (can be hoisted outside outer loop)
        let outer_invariant = expensive_compute(constant, constant);
        for j in 0..inner_n {
            // Inner-loop invariant (can be hoisted to outer loop)
            let inner_invariant = i * i;
            sum += outer_invariant + inner_invariant + j;
        }
    }
    sum
}

// Multiple invariants in same loop
fn multiple_invariants(n: i64, a: i64, b: i64, c: i64) -> i64 {
    let mut sum = 0i64;
    for i in 0..n {
        let inv1 = a * a + b * b;            // Invariant 1
        let inv2 = b * c + c * a;            // Invariant 2
        let inv3 = expensive_compute(a, b);  // Invariant 3
        sum += inv1 + inv2 + inv3 + i;
    }
    sum
}

fn main() {
    println!("Invariant Hoist Benchmark\n");

    // Test loop with invariant
    let result1 = loop_with_invariant(100, 5, 7);
    println!("Loop with invariant: {}", result1);

    // Test nested with invariant
    let result2 = nested_with_invariant(10, 10, 3);
    println!("Nested with invariant: {}", result2);

    // Test multiple invariants
    let result3 = multiple_invariants(100, 3, 5, 7);
    println!("Multiple invariants: {}", result3);

    let total = result1 + result2 + result3;
    println!("\nTotal: {}", total);
    println!("Done.");
}
