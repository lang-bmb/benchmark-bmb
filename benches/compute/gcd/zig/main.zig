// GCD (Greatest Common Divisor) Benchmark
// Measures: loop, modulo operations, integer arithmetic
// Uses same algorithm as C/BMB version

const std = @import("std");

fn gcd(initial_a: i64, initial_b: i64) i64 {
    var a = initial_a;
    var b = initial_b;
    while (b != 0) {
        const t = b;
        b = @mod(a, b);
        a = t;
    }
    return a;
}

fn sum_gcds(n: i64) i64 {
    var acc: i64 = 0;
    var i: i64 = 1;
    while (i <= n) : (i += 1) {
        var j: i64 = 1;
        while (j <= n) : (j += 1) {
            acc += gcd(i, j);
        }
    }
    return acc;
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    // 100 iterations for stable measurement
    var result: i64 = 0;
    var i: usize = 0;
    while (i < 100) : (i += 1) {
        result += sum_gcds(300);
    }

    try stdout.print("{d}\n", .{result});
}
