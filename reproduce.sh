#!/bin/bash
# One-click benchmark reproduction script
# Usage: ./reproduce.sh [--build] [--all|--compute|--realworld]

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMAGE_NAME="bmb-benchmark"
BUILD_IMAGE=false
BENCH_ARGS="--all"

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --build)
            BUILD_IMAGE=true
            shift
            ;;
        --all|--compute|--realworld)
            BENCH_ARGS="$1"
            shift
            ;;
        --help)
            echo "Usage: ./reproduce.sh [--build] [--all|--compute|--realworld]"
            echo ""
            echo "Options:"
            echo "  --build      Force rebuild Docker image"
            echo "  --all        Run all benchmarks (default)"
            echo "  --compute    Run compute benchmarks only"
            echo "  --realworld  Run real-world benchmarks only"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

echo "=========================================="
echo "BMB Benchmark Suite - Reproduction Script"
echo "=========================================="
echo ""

# Check Docker
if ! command -v docker &> /dev/null; then
    echo "Error: Docker is not installed"
    echo "Please install Docker: https://docs.docker.com/get-docker/"
    exit 1
fi

# Build image if needed
if [ "$BUILD_IMAGE" = true ] || ! docker image inspect "$IMAGE_NAME" &> /dev/null; then
    echo "Building Docker image..."
    docker build -t "$IMAGE_NAME" "$SCRIPT_DIR"
    echo ""
fi

# Create results directory
mkdir -p "$SCRIPT_DIR/results"

# Run benchmarks
echo "Running benchmarks in Docker container..."
echo ""

docker run --rm \
    -v "$SCRIPT_DIR/results:/benchmark/results" \
    "$IMAGE_NAME" \
    $BENCH_ARGS

echo ""
echo "=========================================="
echo "Done! Results saved to: $SCRIPT_DIR/results/"
echo "=========================================="

# List results
echo ""
echo "Generated files:"
ls -la "$SCRIPT_DIR/results/"
