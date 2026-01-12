#!/bin/bash
# Fibonacci(40) benchmark - BMB vs C

set -e

PROJECT_ROOT="/mnt/d/data/lang-bmb"
BMB="$PROJECT_ROOT/target/release/bmb"
RUNTIME="$PROJECT_ROOT/bmb/runtime/libbmb_runtime.a"

export BMB_RUNTIME_PATH="$RUNTIME"

# Create BMB source
cat > /tmp/fib40.bmb << 'EOF'
-- Fibonacci benchmark (fib 40)
fn fib(n: i64) -> i64 = if n <= 1 { n } else { fib(n-1) + fib(n-2) };
fn main() -> i64 = fib(40);
EOF

# Create C source
cat > /tmp/fib40.c << 'EOF'
#include <stdio.h>
long long fib(int n) { return n <= 1 ? n : fib(n-1) + fib(n-2); }
int main() { printf("%lld", fib(40)); return 0; }
EOF

echo "=== Fibonacci(40) Benchmark ==="
echo ""

# Compile BMB
echo "Compiling BMB..."
"$BMB" build /tmp/fib40.bmb --emit-ir -o /tmp/fib40.ll
clang -O3 /tmp/fib40.ll "$RUNTIME" -o /tmp/fib40_bmb -lm -no-pie

# Compile C
echo "Compiling C..."
clang -O3 /tmp/fib40.c -o /tmp/fib40_c

echo ""
echo "Running C (-O3)..."
time /tmp/fib40_c
echo ""

echo ""
echo "Running BMB (IR + clang -O3)..."
time /tmp/fib40_bmb
echo ""

echo ""
echo "=== Done ==="
