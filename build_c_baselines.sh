#!/bin/bash
# Build all C baselines with proper optimization flags
# This ensures fair comparison with BMB

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BENCHES_DIR="$SCRIPT_DIR/benches"

# Compiler flags for optimized builds
CFLAGS="-O3 -march=native"
LDFLAGS="-lm"

echo "Building C baselines with: gcc $CFLAGS"
echo ""

count=0
failed=0

# Find all C benchmark directories
for c_main in $(find "$BENCHES_DIR" -path "*/c/main.c" -type f); do
    c_dir=$(dirname "$c_main")
    bench_name=$(basename $(dirname $(dirname "$c_main")))
    category=$(basename $(dirname $(dirname $(dirname "$c_main"))))

    echo "Building: $category/$bench_name"

    output="$c_dir/c_bench.exe"

    # Build with optimization
    if gcc $CFLAGS -o "$output" "$c_main" $LDFLAGS 2>/dev/null; then
        echo "  -> OK: $output"
        ((count++))
    else
        # Try without -march=native (for portability)
        if gcc -O3 -o "$output" "$c_main" $LDFLAGS 2>/dev/null; then
            echo "  -> OK (no -march): $output"
            ((count++))
        else
            echo "  -> FAILED"
            ((failed++))
        fi
    fi
done

echo ""
echo "Build complete: $count succeeded, $failed failed"
