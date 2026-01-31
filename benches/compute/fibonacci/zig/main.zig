// Fibonacci - FAIR COMPARISON benchmark
// Uses iterative O(n) algorithm matching the C/BMB version exactly.
// Measures: loop iteration, integer arithmetic, accumulator pattern

const std = @import("std");

fn fibonacci_iter(n: i64) i64 {
    var a: i64 = 0;
    var b: i64 = 1;
    var i: i64 = 0;
    while (i < n) : (i += 1) {
        const temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    // Run fibonacci(50) 1000000000 times for stable measurement
    var result: i64 = 0;
    var i: i64 = 0;
    while (i < 1000000000) : (i += 1) {
        result += fibonacci_iter(50);
    }

    try stdout.print("{d}\n", .{result});
}
