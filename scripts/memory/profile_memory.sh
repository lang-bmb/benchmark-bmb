#!/bin/bash
# Memory profiling script for BMB benchmarks
# Usage: ./profile_memory.sh [benchmark_name] [--all]
#
# Requires: valgrind (Linux), /usr/bin/time with -v flag
# On macOS: uses /usr/bin/time without detailed memory stats

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BENCH_DIR="$SCRIPT_DIR/../../benches"
RESULTS_DIR="$SCRIPT_DIR/../../results/memory"

mkdir -p "$RESULTS_DIR"

# Detect OS and available tools
OS="$(uname -s)"
HAS_VALGRIND=false
HAS_TIME_V=false

if command -v valgrind &> /dev/null; then
    HAS_VALGRIND=true
fi

if /usr/bin/time -v true 2>/dev/null; then
    HAS_TIME_V=true
fi

echo "=========================================="
echo "BMB Memory Profiler"
echo "=========================================="
echo "OS: $OS"
echo "Valgrind: $HAS_VALGRIND"
echo "GNU time -v: $HAS_TIME_V"
echo ""

# Function to get peak memory using /usr/bin/time
get_peak_memory() {
    local exe="$1"
    local name="$2"

    if [ "$HAS_TIME_V" = true ]; then
        # GNU time with -v gives "Maximum resident set size (kbytes)"
        result=$(/usr/bin/time -v "$exe" 2>&1 | grep "Maximum resident set size" | awk '{print $NF}')
        echo "$result"
    elif [ "$OS" = "Darwin" ]; then
        # macOS - use /usr/bin/time -l
        result=$(/usr/bin/time -l "$exe" 2>&1 | grep "maximum resident set size" | awk '{print $1}')
        # macOS reports in bytes, convert to KB
        echo $((result / 1024))
    else
        echo "N/A"
    fi
}

# Function to run valgrind massif
run_massif() {
    local exe="$1"
    local name="$2"
    local output="$RESULTS_DIR/${name}_massif.out"

    if [ "$HAS_VALGRIND" = true ]; then
        echo "  Running valgrind massif..."
        valgrind --tool=massif --massif-out-file="$output" "$exe" > /dev/null 2>&1

        # Extract peak memory from massif output
        peak=$(grep "mem_heap_B=" "$output" | sed 's/mem_heap_B=//' | sort -n | tail -1)
        echo "$peak"
    else
        echo "N/A"
    fi
}

# Function to profile a single benchmark
profile_benchmark() {
    local bench_path="$1"
    local bench_name="$(basename "$(dirname "$bench_path")")"
    local lang="$(basename "$bench_path" | sed 's/main_//' | sed 's/\.exe$//')"

    echo "Profiling: $bench_name ($lang)"

    # Get peak RSS
    peak_kb=$(get_peak_memory "$bench_path" "${bench_name}_${lang}")

    # Output result
    echo "  Peak RSS: ${peak_kb} KB"

    # Store result
    echo "${bench_name},${lang},${peak_kb}" >> "$RESULTS_DIR/memory_results.csv"
}

# Initialize results file
echo "benchmark,language,peak_rss_kb" > "$RESULTS_DIR/memory_results.csv"

# Find and profile benchmarks
if [ "$1" = "--all" ] || [ -z "$1" ]; then
    echo "Profiling all benchmarks..."
    echo ""

    # Profile C (GCC) benchmarks
    for exe in "$BENCH_DIR"/*/c/main_gcc "$BENCH_DIR"/*/*/c/main_gcc; do
        if [ -x "$exe" ]; then
            profile_benchmark "$exe"
        fi
    done

    # Profile C (Clang) benchmarks
    for exe in "$BENCH_DIR"/*/c/main_clang "$BENCH_DIR"/*/*/c/main_clang; do
        if [ -x "$exe" ]; then
            profile_benchmark "$exe"
        fi
    done

    # Profile Rust benchmarks
    for exe in "$BENCH_DIR"/*/rust/main_rust "$BENCH_DIR"/*/*/rust/main_rust; do
        if [ -x "$exe" ]; then
            profile_benchmark "$exe"
        fi
    done

    # Profile Zig benchmarks
    for exe in "$BENCH_DIR"/*/zig/main_zig "$BENCH_DIR"/*/*/zig/main_zig; do
        if [ -x "$exe" ]; then
            profile_benchmark "$exe"
        fi
    done
else
    # Profile specific benchmark
    bench_name="$1"
    echo "Profiling benchmark: $bench_name"
    echo ""

    for lang_dir in "$BENCH_DIR"/*/"$bench_name"/* "$BENCH_DIR"/*/*/"$bench_name"/*; do
        for exe in "$lang_dir"/main_*; do
            if [ -x "$exe" ]; then
                profile_benchmark "$exe"
            fi
        done
    done
fi

echo ""
echo "=========================================="
echo "Results saved to: $RESULTS_DIR/memory_results.csv"
echo "=========================================="

# Generate summary report
echo ""
echo "=== Memory Usage Summary ==="
echo ""
if [ -f "$RESULTS_DIR/memory_results.csv" ]; then
    echo "| Benchmark | Language | Peak RSS (KB) |"
    echo "|-----------|----------|---------------|"
    tail -n +2 "$RESULTS_DIR/memory_results.csv" | while IFS=, read -r bench lang peak; do
        printf "| %-20s | %-8s | %13s |\n" "$bench" "$lang" "$peak"
    done
fi
