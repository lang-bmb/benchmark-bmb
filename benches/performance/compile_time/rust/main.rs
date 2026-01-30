// Compile Time Benchmark
// Measures: Compilation speed for a representative codebase
//
// This benchmark is run differently than others:
// - We measure how long `rustc -O main.rs` takes
// - Contains multiple functions, types, and control flow for realistic workload

// Utility functions
fn abs_val(x: i64) -> i64 { if x < 0 { -x } else { x } }

fn min(a: i64, b: i64) -> i64 { if a < b { a } else { b } }

fn max(a: i64, b: i64) -> i64 { if a > b { a } else { b } }

fn clamp(x: i64, lo: i64, hi: i64) -> i64 { min(max(x, lo), hi) }

// Recursive algorithms
fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 { a } else { gcd(b, a % b) }
}

fn fib_iter(n: i64, a: i64, b: i64) -> i64 {
    if n <= 0 { a } else { fib_iter(n - 1, b, a + b) }
}

fn fibonacci(n: i64) -> i64 { fib_iter(n, 0, 1) }

fn factorial_iter(n: i64, acc: i64) -> i64 {
    if n <= 1 { acc } else { factorial_iter(n - 1, n * acc) }
}

fn factorial(n: i64) -> i64 { factorial_iter(n, 1) }

// Memory operations
fn array_sum(arr: &[i64]) -> i64 {
    arr.iter().sum()
}

fn fill_array(arr: &mut [i64]) {
    for i in 0..arr.len() {
        arr[i] = (i * i) as i64;
    }
}

// Search algorithm
fn binary_search(arr: &[i64], target: i64) -> i64 {
    let mut lo: i64 = 0;
    let mut hi: i64 = arr.len() as i64 - 1;
    while lo <= hi {
        let mid = lo + (hi - lo) / 2;
        let mid_val = arr[mid as usize];
        if mid_val == target { return mid; }
        else if mid_val < target { lo = mid + 1; }
        else { hi = mid - 1; }
    }
    -1
}

// Sorting (bubble sort for simplicity)
fn bubble_sort(arr: &mut [i64]) {
    let n = arr.len();
    for i in 0..n {
        let mut swapped = false;
        for j in 0..n - i - 1 {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
                swapped = true;
            }
        }
        if !swapped { break; }
    }
}

// Prime checking
fn is_prime(n: i64) -> bool {
    if n < 2 { return false; }
    if n == 2 { return true; }
    if n % 2 == 0 { return false; }
    let mut d: i64 = 3;
    while d * d <= n {
        if n % d == 0 { return false; }
        d += 2;
    }
    true
}

fn count_primes(n: i64) -> i64 {
    (2..=n).filter(|&i| is_prime(i)).count() as i64
}

// Main: Run all functions to verify correctness
fn main() {
    let g = gcd(48, 18);
    let f = fibonacci(20);
    let fact = factorial(10);
    let primes = count_primes(100);

    // Array operations
    let mut arr = vec![0i64; 10];
    fill_array(&mut arr);
    let sum = array_sum(&arr);
    bubble_sort(&mut arr);
    let found = binary_search(&arr, 16);

    // Verify results
    let ok = g == 6 && f == 6765 && fact == 3628800 && primes == 25 && sum == 285 && found != -1;

    println!("{}", if ok { 1 } else { 0 });
}
