// N-Queens Benchmark
// Measures: recursion, backtracking, bit manipulation

fn solve(n: i64, row: i64, cols: i64, diags1: i64, diags2: i64) -> i64 {
    if row == n {
        return 1;
    }
    let all_ones = (1i64 << n) - 1;
    let mut avail = all_ones & !cols & !diags1 & !diags2;
    let mut count: i64 = 0;
    while avail != 0 {
        let bit = avail & (-avail);
        avail -= bit;
        count += solve(n, row + 1, cols | bit, (diags1 | bit) << 1, (diags2 | bit) >> 1);
    }
    count
}

fn nqueens(n: i64) -> i64 {
    solve(n, 0, 0, 0, 0)
}

fn main() {
    let mut sum: i64 = 0;
    // Match BMB/C: nqueens(15) x 10
    for _ in 0..10 {
        sum += nqueens(15);
    }
    println!("{}", sum);
}
