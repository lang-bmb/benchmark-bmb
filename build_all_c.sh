#!/bin/bash
# Build all C benchmarks with proper optimization flags
# Usage: ./build_all_c.sh

CFLAGS="-O3 -march=native"

echo "Building compute benchmarks..."
for dir in benches/compute/*/c; do
    if [ -f "$dir/main.c" ]; then
        name=$(basename $(dirname "$dir"))
        echo "  Building $name..."
        gcc $CFLAGS -o "$dir/c_bench.exe" "$dir/main.c" -lm 2>/dev/null || \
        echo "    Warning: $name failed to build"
    fi
done

echo "Building real_world benchmarks..."
for dir in benches/real_world/*/c; do
    if [ -f "$dir/main.c" ]; then
        name=$(basename $(dirname "$dir"))
        echo "  Building $name..."
        gcc $CFLAGS -o "$dir/c_bench.exe" "$dir/main.c" -lm 2>/dev/null || \
        echo "    Warning: $name failed to build"
    fi
done

echo "Done!"
