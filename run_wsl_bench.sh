#!/bin/bash
set -e

cd /mnt/d/data/lang-bmb/ecosystem/benchmark-bmb
BMB="/mnt/d/data/lang-bmb/target/release/bmb"
BUILD_DIR="./build_wsl"
RUNTIME="/mnt/d/data/lang-bmb/runtime/runtime.c"
mkdir -p "$BUILD_DIR"

echo "=========================================="
echo "Benchmark Fairness Check & Execution"
echo "=========================================="
echo ""

BENCHMARKS="fibonacci mandelbrot spectral_norm n_body fannkuch binary_trees fasta"

for bench in $BENCHMARKS; do
    BMB_SRC="benches/compute/$bench/bmb/main.bmb"
    C_SRC="benches/compute/$bench/c/main.c"

    if [ ! -f "$BMB_SRC" ] || [ ! -f "$C_SRC" ]; then
        echo "$bench: SKIP (missing source)"
        continue
    fi

    echo "=== $bench ==="

    # Compile C
    C_EXE="$BUILD_DIR/${bench}_c"
    if ! clang -O3 -march=native "$C_SRC" -o "$C_EXE" -lm 2>&1; then
        echo "  C compile FAILED"
        continue
    fi
    echo "  C: compiled"

    # Compile BMB (emit IR, then compile with clang)
    BMB_LL="$BUILD_DIR/${bench}_bmb.ll"
    BMB_EXE="$BUILD_DIR/${bench}_bmb"

    if ! "$BMB" build --aggressive "$BMB_SRC" --emit-ir -o "$BMB_LL" 2>&1; then
        echo "  BMB emit-ir FAILED"
        continue
    fi

    if ! clang -O3 -march=native "$BMB_LL" "$RUNTIME" -o "$BMB_EXE" -lm 2>&1; then
        echo "  BMB clang compile FAILED"
        cat "$BMB_LL" | head -50
        continue
    fi
    echo "  BMB: compiled"

    # Run C and capture output
    C_OUT=$("$C_EXE" 2>&1 || true)

    # Run BMB and capture output
    BMB_OUT=$("$BMB_EXE" 2>&1 || true)

    echo "  C output: $C_OUT"
    echo "  BMB output: $BMB_OUT"

    # Timing (5 runs each, take min)
    echo -n "  Timing: "

    C_MIN=999999
    for i in 1 2 3 4 5; do
        T=$( /usr/bin/time -f "%e" "$C_EXE" 2>&1 > /dev/null | tail -1 )
        if [ -n "$T" ] && [ $(echo "$T < $C_MIN" | bc -l) -eq 1 ]; then
            C_MIN=$T
        fi
    done

    BMB_MIN=999999
    for i in 1 2 3 4 5; do
        T=$( /usr/bin/time -f "%e" "$BMB_EXE" 2>&1 > /dev/null | tail -1 )
        if [ -n "$T" ] && [ $(echo "$T < $BMB_MIN" | bc -l) -eq 1 ]; then
            BMB_MIN=$T
        fi
    done

    if [ "$C_MIN" = "999999" ] || [ "$BMB_MIN" = "999999" ]; then
        echo "TIMING FAILED"
        continue
    fi

    # Handle very fast benchmarks (avoid division by zero)
    C_MIN_FLOAT=$(echo "$C_MIN" | bc -l)
    if [ -z "$C_MIN_FLOAT" ] || [ "$C_MIN_FLOAT" = "0" ] || [ $(echo "$C_MIN_FLOAT < 0.005" | bc -l) -eq 1 ]; then
        RATIO="~100 (too fast to measure)"
    else
        RATIO=$(awk "BEGIN {printf \"%.0f\", ($BMB_MIN / $C_MIN) * 100}")
    fi

    echo "C=${C_MIN}s, BMB=${BMB_MIN}s, Ratio=${RATIO}%"
    echo ""
done

echo "=========================================="
echo "Done"
echo "=========================================="
