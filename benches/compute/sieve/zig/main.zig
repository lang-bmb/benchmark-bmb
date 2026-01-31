// Sieve of Eratosthenes - Prime number benchmark
// Measures: array operations, loop performance
// Uses same algorithm as C/BMB version

const std = @import("std");

fn sieve(allocator: std.mem.Allocator, n: usize) !i64 {
    // Allocate array
    const arr = try allocator.alloc(u8, n + 1);
    defer allocator.free(arr);

    // Initialize all to 1
    @memset(arr, 1);
    arr[0] = 0;
    arr[1] = 0;

    // Sieve
    var i: usize = 2;
    while (i * i <= n) : (i += 1) {
        if (arr[i] == 1) {
            var j = i * i;
            while (j <= n) : (j += i) {
                arr[j] = 0;
            }
        }
    }

    // Count primes
    var count: i64 = 0;
    for (arr[2..]) |v| {
        if (v == 1) count += 1;
    }

    return count;
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    // 1500 iterations for stable measurement
    var result: i64 = 0;
    var i: usize = 0;
    while (i < 1500) : (i += 1) {
        result += try sieve(allocator, 100000);
    }

    try stdout.print("{d}\n", .{result});
}
