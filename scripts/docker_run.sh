#!/bin/bash
# Docker benchmark runner script
# Usage: docker run bmb-benchmark [--all|--compute|--realworld] [--json]

set -e

CATEGORY="all"
FORMAT="text"
ITERATIONS=5
WARMUP=2
MEMORY_PROFILE=false

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --all)
            CATEGORY="all"
            shift
            ;;
        --compute)
            CATEGORY="compute"
            shift
            ;;
        --realworld)
            CATEGORY="real_world"
            shift
            ;;
        --json)
            FORMAT="json"
            shift
            ;;
        --memory)
            MEMORY_PROFILE=true
            shift
            ;;
        --iterations)
            ITERATIONS="$2"
            shift 2
            ;;
        --warmup)
            WARMUP="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

echo "=========================================="
echo "BMB Benchmark Suite - Docker Runner"
echo "=========================================="
echo ""
echo "Environment:"
echo "  GCC:    $(gcc --version | head -1)"
echo "  Clang:  $(clang --version | head -1)"
echo "  Rust:   $(rustc --version)"
echo "  Date:   $(date -u '+%Y-%m-%d %H:%M:%S UTC')"
echo ""

# Generate timestamp for results
TIMESTAMP=$(date -u '+%Y%m%d_%H%M%S')
RESULT_FILE="/benchmark/results/benchmark_${TIMESTAMP}.md"

{
    echo "# BMB Benchmark Results"
    echo ""
    echo "**Generated:** $(date -u '+%Y-%m-%d %H:%M:%S UTC')"
    echo "**Docker Image:** bmb-benchmark"
    echo ""
    echo "## Environment"
    echo ""
    echo "| Component | Version |"
    echo "|-----------|---------|"
    echo "| GCC | $(gcc --version | head -1 | sed 's/gcc (Ubuntu [^)]*) //')" |"
    echo "| Clang | $(clang --version | head -1 | sed 's/.*version //' | cut -d' ' -f1) |"
    echo "| Rust | $(rustc --version | cut -d' ' -f2) |"
    echo "| OS | Ubuntu 22.04 |"
    echo ""
} > "$RESULT_FILE"

# Run benchmarks
echo "Running benchmarks (category: $CATEGORY, iterations: $ITERATIONS, warmup: $WARMUP)..."
echo ""

cd /benchmark/runner

if [ "$CATEGORY" = "all" ]; then
    CATEGORIES="compute real_world"
else
    CATEGORIES="$CATEGORY"
fi

for cat in $CATEGORIES; do
    echo "=== Category: $cat ==="

    {
        echo "## $cat"
        echo ""
        echo "| Benchmark | GCC | Clang | Rust | BMB |"
        echo "|-----------|-----|-------|------|-----|"
    } >> "$RESULT_FILE"

    ./target/release/benchmark-bmb run --category "$cat" --iterations "$ITERATIONS" --warmup "$WARMUP" 2>/dev/null || true

    echo "" >> "$RESULT_FILE"
done

echo ""
echo "=========================================="
echo "Results saved to: $RESULT_FILE"
echo "=========================================="

# If JSON format requested, also generate JSON
if [ "$FORMAT" = "json" ]; then
    JSON_FILE="/benchmark/results/benchmark_${TIMESTAMP}.json"
    ./target/release/benchmark-bmb run --category compute --iterations "$ITERATIONS" --warmup "$WARMUP" --json > "$JSON_FILE" 2>/dev/null || true
    echo "JSON results: $JSON_FILE"
fi

# Run memory profiling if requested
if [ "$MEMORY_PROFILE" = true ]; then
    echo ""
    echo "=========================================="
    echo "Running Memory Profiling..."
    echo "=========================================="

    python3 /benchmark/scripts/memory/memory_benchmark.py --all --output /benchmark/results/memory

    echo ""
    echo "Memory profiling complete. See /benchmark/results/memory/"
fi

# Copy results to mounted volume if available
if [ -d "/benchmark/results" ]; then
    echo "Results available in /benchmark/results/"
fi
