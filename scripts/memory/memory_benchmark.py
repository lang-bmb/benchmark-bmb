#!/usr/bin/env python3
"""
BMB Memory Benchmark Tool

Measures memory usage metrics for benchmark executables:
- Peak RSS (Resident Set Size)
- Heap allocations (if valgrind available)
- Allocation rate

Usage:
    python memory_benchmark.py --all
    python memory_benchmark.py --benchmark fibonacci
    python memory_benchmark.py --category compute
"""

import argparse
import json
import os
import platform
import re
import subprocess
import sys
from dataclasses import dataclass, asdict
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional


@dataclass
class MemoryResult:
    benchmark: str
    language: str
    peak_rss_kb: int
    heap_peak_bytes: Optional[int] = None
    total_allocs: Optional[int] = None
    execution_time_ms: Optional[float] = None


def find_executables(bench_dir: Path, benchmark: Optional[str] = None,
                     category: Optional[str] = None) -> List[tuple]:
    """Find all benchmark executables."""
    executables = []

    # Patterns for different languages
    patterns = {
        'gcc': 'main_gcc',
        'clang': 'main_clang',
        'rust': 'main_rust',
        'zig': 'main_zig',
        'msvc': 'main_msvc.exe',
        'mingw': 'main_mingw.exe',
    }

    # Search paths
    if category:
        search_paths = [bench_dir / category]
    else:
        search_paths = [bench_dir / 'compute', bench_dir / 'real_world']

    for search_path in search_paths:
        if not search_path.exists():
            continue

        for bench_path in search_path.iterdir():
            if not bench_path.is_dir():
                continue

            if benchmark and bench_path.name != benchmark:
                continue

            for lang_dir in bench_path.iterdir():
                if not lang_dir.is_dir():
                    continue

                for pattern_name, pattern in patterns.items():
                    exe_path = lang_dir / pattern
                    if exe_path.exists() and os.access(exe_path, os.X_OK):
                        executables.append((
                            bench_path.name,
                            pattern_name,
                            exe_path
                        ))

    return executables


def measure_peak_rss(exe_path: Path) -> Optional[int]:
    """Measure peak RSS using /usr/bin/time or platform-specific method."""
    system = platform.system()

    try:
        if system == 'Linux':
            # Use GNU time with -v
            result = subprocess.run(
                ['/usr/bin/time', '-v', str(exe_path)],
                capture_output=True,
                text=True,
                timeout=300
            )
            # Parse "Maximum resident set size (kbytes): XXXX"
            for line in result.stderr.split('\n'):
                if 'Maximum resident set size' in line:
                    match = re.search(r'(\d+)', line)
                    if match:
                        return int(match.group(1))

        elif system == 'Darwin':
            # macOS: use /usr/bin/time -l
            result = subprocess.run(
                ['/usr/bin/time', '-l', str(exe_path)],
                capture_output=True,
                text=True,
                timeout=300
            )
            # Parse "XXXX  maximum resident set size"
            for line in result.stderr.split('\n'):
                if 'maximum resident set size' in line:
                    match = re.search(r'(\d+)', line)
                    if match:
                        # macOS reports in bytes
                        return int(match.group(1)) // 1024

        elif system == 'Windows':
            # Windows: use PowerShell to measure
            ps_script = f'''
            $process = Start-Process -FilePath "{exe_path}" -PassThru -Wait
            $process.PeakWorkingSet64 / 1024
            '''
            result = subprocess.run(
                ['powershell', '-Command', ps_script],
                capture_output=True,
                text=True,
                timeout=300
            )
            try:
                return int(float(result.stdout.strip()))
            except ValueError:
                pass

    except subprocess.TimeoutExpired:
        print(f"  Timeout measuring {exe_path}")
    except Exception as e:
        print(f"  Error measuring {exe_path}: {e}")

    return None


def measure_with_valgrind(exe_path: Path, output_dir: Path) -> Dict:
    """Measure detailed heap usage with valgrind massif."""
    if platform.system() != 'Linux':
        return {}

    if not subprocess.run(['which', 'valgrind'], capture_output=True).returncode == 0:
        return {}

    massif_out = output_dir / f"{exe_path.stem}_massif.out"

    try:
        subprocess.run(
            ['valgrind', '--tool=massif', f'--massif-out-file={massif_out}', str(exe_path)],
            capture_output=True,
            timeout=600
        )

        if massif_out.exists():
            content = massif_out.read_text()
            # Parse peak heap
            peaks = re.findall(r'mem_heap_B=(\d+)', content)
            if peaks:
                return {'heap_peak_bytes': max(int(p) for p in peaks)}

    except Exception as e:
        print(f"  Valgrind error: {e}")

    return {}


def run_memory_benchmarks(bench_dir: Path, output_dir: Path,
                          benchmark: Optional[str] = None,
                          category: Optional[str] = None,
                          use_valgrind: bool = False) -> List[MemoryResult]:
    """Run memory benchmarks and collect results."""

    output_dir.mkdir(parents=True, exist_ok=True)

    executables = find_executables(bench_dir, benchmark, category)
    results = []

    print(f"Found {len(executables)} executables to profile")
    print()

    for bench_name, lang, exe_path in executables:
        print(f"Profiling: {bench_name} ({lang})")

        # Measure peak RSS
        peak_rss = measure_peak_rss(exe_path)

        result = MemoryResult(
            benchmark=bench_name,
            language=lang,
            peak_rss_kb=peak_rss or 0
        )

        # Optional valgrind profiling
        if use_valgrind:
            valgrind_data = measure_with_valgrind(exe_path, output_dir)
            if 'heap_peak_bytes' in valgrind_data:
                result.heap_peak_bytes = valgrind_data['heap_peak_bytes']

        print(f"  Peak RSS: {result.peak_rss_kb} KB")
        if result.heap_peak_bytes:
            print(f"  Heap Peak: {result.heap_peak_bytes // 1024} KB")

        results.append(result)

    return results


def generate_report(results: List[MemoryResult], output_dir: Path):
    """Generate memory profiling report."""

    # JSON output
    json_path = output_dir / 'memory_results.json'
    with open(json_path, 'w') as f:
        json.dump({
            'generated': datetime.utcnow().isoformat(),
            'platform': platform.platform(),
            'results': [asdict(r) for r in results]
        }, f, indent=2)

    # Markdown report
    md_path = output_dir / 'memory_report.md'
    with open(md_path, 'w') as f:
        f.write("# BMB Memory Profiling Report\n\n")
        f.write(f"**Generated:** {datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S UTC')}\n")
        f.write(f"**Platform:** {platform.platform()}\n\n")

        f.write("## Peak RSS by Benchmark\n\n")
        f.write("| Benchmark | Language | Peak RSS (KB) |\n")
        f.write("|-----------|----------|---------------|\n")

        for r in sorted(results, key=lambda x: (x.benchmark, x.language)):
            f.write(f"| {r.benchmark} | {r.language} | {r.peak_rss_kb:,} |\n")

        # Summary by language
        f.write("\n## Summary by Language\n\n")
        lang_totals: Dict[str, List[int]] = {}
        for r in results:
            if r.language not in lang_totals:
                lang_totals[r.language] = []
            lang_totals[r.language].append(r.peak_rss_kb)

        f.write("| Language | Avg Peak RSS (KB) | Max Peak RSS (KB) |\n")
        f.write("|----------|-------------------|-------------------|\n")
        for lang, values in sorted(lang_totals.items()):
            avg = sum(values) // len(values)
            max_val = max(values)
            f.write(f"| {lang} | {avg:,} | {max_val:,} |\n")

    # CSV output
    csv_path = output_dir / 'memory_results.csv'
    with open(csv_path, 'w') as f:
        f.write("benchmark,language,peak_rss_kb,heap_peak_bytes\n")
        for r in results:
            heap = r.heap_peak_bytes or ''
            f.write(f"{r.benchmark},{r.language},{r.peak_rss_kb},{heap}\n")

    print(f"\nReports generated:")
    print(f"  - {json_path}")
    print(f"  - {md_path}")
    print(f"  - {csv_path}")


def main():
    parser = argparse.ArgumentParser(description='BMB Memory Benchmark Tool')
    parser.add_argument('--all', action='store_true', help='Profile all benchmarks')
    parser.add_argument('--benchmark', '-b', help='Profile specific benchmark')
    parser.add_argument('--category', '-c', help='Profile specific category')
    parser.add_argument('--valgrind', action='store_true', help='Use valgrind for detailed heap profiling')
    parser.add_argument('--output', '-o', default='results/memory', help='Output directory')

    args = parser.parse_args()

    # Find benchmark directory
    script_dir = Path(__file__).parent
    bench_dir = script_dir.parent.parent / 'benches'
    output_dir = script_dir.parent.parent / args.output

    if not bench_dir.exists():
        print(f"Error: Benchmark directory not found: {bench_dir}")
        sys.exit(1)

    print("=" * 50)
    print("BMB Memory Benchmark Tool")
    print("=" * 50)
    print(f"Platform: {platform.platform()}")
    print(f"Benchmark dir: {bench_dir}")
    print(f"Output dir: {output_dir}")
    print()

    results = run_memory_benchmarks(
        bench_dir=bench_dir,
        output_dir=output_dir,
        benchmark=args.benchmark,
        category=args.category,
        use_valgrind=args.valgrind
    )

    if results:
        generate_report(results, output_dir)
    else:
        print("No benchmarks found to profile")


if __name__ == '__main__':
    main()
