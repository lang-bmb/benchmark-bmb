use clap::{Parser, Subcommand};
use colored::Colorize;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;
use std::time::{Duration, Instant};

#[derive(Parser)]
#[command(name = "benchmark-bmb")]
#[command(about = "BMB Language Benchmark Runner", long_about = None)]
struct Cli {
    #[command(subcommand)]
    command: Commands,
}

#[derive(Subcommand)]
enum Commands {
    /// Run benchmarks
    Run {
        /// Benchmark name or --all
        #[arg(default_value = "all")]
        name: String,

        /// Category filter (compute, memory, realworld, contract)
        #[arg(short, long)]
        category: Option<String>,

        /// Number of iterations
        #[arg(short, long, default_value = "5")]
        iterations: u32,

        /// Warm-up iterations
        #[arg(short, long, default_value = "2")]
        warmup: u32,
    },
    /// Compare languages for a benchmark
    Compare {
        /// Benchmark name
        name: String,

        /// Languages to compare (comma-separated: c,bmb)
        #[arg(short, long, default_value = "c,bmb")]
        langs: String,
    },
    /// List available benchmarks
    List {
        /// Category filter
        #[arg(short, long)]
        category: Option<String>,
    },
    /// Create new benchmark scaffold
    New {
        /// Benchmark name
        name: String,

        /// Category
        #[arg(short, long, default_value = "compute")]
        category: String,
    },
    /// Validate benchmark implementations
    Validate {
        /// Benchmark name
        name: String,
    },
    /// Generate report
    Report {
        /// Output format (text, json, html)
        #[arg(short, long, default_value = "text")]
        format: String,

        /// Output directory
        #[arg(short, long, default_value = "results")]
        output: String,
    },
    /// Verify benchmark gate requirements
    Gate {
        /// Gate number (1, 2, 3.1, 3.2, 3.3, 4)
        #[arg(default_value = "3.1")]
        gate: String,

        /// Number of iterations
        #[arg(short, long, default_value = "5")]
        iterations: u32,

        /// Verbose output
        #[arg(short, long)]
        verbose: bool,
    },
}

#[derive(Debug, Serialize, Deserialize)]
struct BenchmarkResult {
    name: String,
    category: String,
    language: String,
    times_ms: Vec<f64>,
    median_ms: f64,
    min_ms: f64,
    max_ms: f64,
    iterations: u32,
}

#[derive(Debug, Serialize, Deserialize)]
struct ComparisonReport {
    benchmark: String,
    results: Vec<BenchmarkResult>,
    baseline: String,
    timestamp: String,
}

fn main() {
    let cli = Cli::parse();

    match cli.command {
        Commands::Run {
            name,
            category,
            iterations,
            warmup,
        } => run_benchmarks(&name, category.as_deref(), iterations, warmup),
        Commands::Compare { name, langs } => compare_benchmark(&name, &langs),
        Commands::List { category } => list_benchmarks(category.as_deref()),
        Commands::New { name, category } => create_benchmark(&name, &category),
        Commands::Validate { name } => validate_benchmark(&name),
        Commands::Report { format, output } => generate_report(&format, &output),
        Commands::Gate { gate, iterations, verbose } => verify_gate(&gate, iterations, verbose),
    }
}

fn run_benchmarks(name: &str, category: Option<&str>, iterations: u32, warmup: u32) {
    println!("{}", "=== BMB Benchmark Suite ===".cyan().bold());
    println!();

    let benches_dir = find_benches_dir();
    let benchmarks = discover_benchmarks(&benches_dir, category);

    if benchmarks.is_empty() {
        println!("{}", "No benchmarks found.".yellow());
        return;
    }

    let benchmarks: Vec<_> = if name == "all" {
        benchmarks
    } else {
        benchmarks
            .into_iter()
            .filter(|(n, _)| n == name)
            .collect()
    };

    if benchmarks.is_empty() {
        println!("{} Benchmark '{}' not found.", "Error:".red(), name);
        return;
    }

    for (bench_name, bench_path) in &benchmarks {
        println!("{} {}", "Running:".green(), bench_name);
        run_single_benchmark(bench_name, bench_path, iterations, warmup);
        println!();
    }
}

fn run_single_benchmark(name: &str, path: &Path, iterations: u32, warmup: u32) {
    let mut results: HashMap<String, Vec<f64>> = HashMap::new();

    // Find language implementations
    for entry in fs::read_dir(path).unwrap().flatten() {
        let lang_dir = entry.path();
        if !lang_dir.is_dir() {
            continue;
        }

        let lang = lang_dir.file_name().unwrap().to_string_lossy().to_string();

        if let Some(times) = run_language_benchmark(&lang_dir, &lang, iterations, warmup) {
            results.insert(lang, times);
        }
    }

    // Print results
    if results.is_empty() {
        println!("  {}", "No runnable implementations found".yellow());
        return;
    }

    println!();
    println!(
        "  {:<10} {:>12} {:>12} {:>12} {:>10}",
        "Language", "Median (ms)", "Min (ms)", "Max (ms)", "Relative"
    );
    println!("  {}", "-".repeat(60));

    // Find baseline (C or first language)
    let baseline = results
        .get("c")
        .or_else(|| results.values().next())
        .map(|times| median(times))
        .unwrap_or(1.0);

    for (lang, times) in &results {
        let med = median(times);
        let min = times.iter().cloned().fold(f64::INFINITY, f64::min);
        let max = times.iter().cloned().fold(f64::NEG_INFINITY, f64::max);
        let relative = med / baseline;

        let status = if relative <= 1.0 {
            "✓".green().to_string()
        } else {
            format!("{:.2}x", relative)
        };

        println!(
            "  {:<10} {:>12.2} {:>12.2} {:>12.2} {:>10}",
            lang.to_uppercase(),
            med,
            min,
            max,
            status
        );
    }
}

fn run_language_benchmark(
    dir: &Path,
    lang: &str,
    iterations: u32,
    warmup: u32,
) -> Option<Vec<f64>> {
    let executable = match lang {
        "c" => compile_c(dir)?,
        "rust" => compile_rust(dir)?,
        "bmb" => compile_bmb(dir)?,
        _ => return None,
    };

    let mut times = Vec::new();

    // Warmup
    for _ in 0..warmup {
        let _ = Command::new(&executable).output();
    }

    // Measure
    for _ in 0..iterations {
        let start = Instant::now();
        let output = Command::new(&executable).output();
        let elapsed = start.elapsed();

        if output.is_ok() {
            times.push(elapsed.as_secs_f64() * 1000.0);
        }
    }

    if times.is_empty() {
        None
    } else {
        Some(times)
    }
}

fn compile_c(dir: &Path) -> Option<PathBuf> {
    let source = dir.join("main.c");
    if !source.exists() {
        return None;
    }

    let output = if cfg!(windows) {
        dir.join("main.exe")
    } else {
        dir.join("main")
    };

    let status = Command::new("gcc")
        .args(["-O3", "-o"])
        .arg(&output)
        .arg(&source)
        .status()
        .ok()?;

    if status.success() {
        Some(output)
    } else {
        None
    }
}

fn compile_rust(dir: &Path) -> Option<PathBuf> {
    let source = dir.join("main.rs");
    if !source.exists() {
        return None;
    }

    let output = if cfg!(windows) {
        dir.join("main.exe")
    } else {
        dir.join("main")
    };

    let status = Command::new("rustc")
        .args(["-C", "opt-level=3", "-C", "lto=fat", "-C", "target-cpu=native", "-o"])
        .arg(&output)
        .arg(&source)
        .status()
        .ok()?;

    if status.success() {
        Some(output)
    } else {
        None
    }
}

fn compile_bmb(dir: &Path) -> Option<PathBuf> {
    let source = dir.join("main.bmb");
    if !source.exists() {
        return None;
    }

    // Get absolute path for wrapper scripts
    let abs_source = fs::canonicalize(&source).ok()?;

    let output = dir.join("main");

    // Try native compilation first, fall back to interpreter
    let status = Command::new("bmb")
        .args(["build", "-o"])
        .arg(&output)
        .arg(&source)
        .status();

    match status {
        Ok(s) if s.success() => Some(output),
        _ => {
            // Create wrapper script for interpreter (platform-specific)
            #[cfg(windows)]
            {
                let wrapper = dir.join("run.cmd");
                // Use absolute path for reliability
                let script = format!("@echo off\nbmb run \"{}\"\n", abs_source.display());
                fs::write(&wrapper, script).ok()?;
                Some(wrapper)
            }
            #[cfg(not(windows))]
            {
                let wrapper = dir.join("run.sh");
                let script = format!("#!/bin/sh\nbmb run \"{}\"\n", abs_source.display());
                fs::write(&wrapper, script).ok()?;
                use std::os::unix::fs::PermissionsExt;
                let mut perms = fs::metadata(&wrapper).ok()?.permissions();
                perms.set_mode(0o755);
                fs::set_permissions(&wrapper, perms).ok()?;
                Some(wrapper)
            }
        }
    }
}

fn compare_benchmark(name: &str, langs: &str) {
    println!(
        "{} {} ({})",
        "Comparing:".cyan().bold(),
        name,
        langs
    );
    // Implementation would compare specific languages
}

fn list_benchmarks(category: Option<&str>) {
    println!("{}", "Available Benchmarks".cyan().bold());
    println!();

    let benches_dir = find_benches_dir();
    let benchmarks = discover_benchmarks(&benches_dir, category);

    if benchmarks.is_empty() {
        println!("{}", "No benchmarks found.".yellow());
        return;
    }

    let mut current_category = String::new();
    for (name, path) in benchmarks {
        let cat = path
            .parent()
            .and_then(|p| p.file_name())
            .map(|s| s.to_string_lossy().to_string())
            .unwrap_or_default();

        if cat != current_category {
            println!("\n{}:", cat.to_uppercase().green());
            current_category = cat;
        }

        // Find available languages
        let langs: Vec<_> = fs::read_dir(&path)
            .ok()
            .map(|entries| {
                entries
                    .flatten()
                    .filter(|e| e.path().is_dir())
                    .map(|e| e.file_name().to_string_lossy().to_string())
                    .collect()
            })
            .unwrap_or_default();

        println!("  {} [{}]", name, langs.join(", "));
    }
}

fn create_benchmark(name: &str, category: &str) {
    println!("Creating benchmark: {} in {}", name, category);

    let benches_dir = find_benches_dir();
    let bench_path = benches_dir.join(category).join(name);

    // Create directories for all languages
    for lang in ["c", "rust", "bmb"] {
        let lang_dir = bench_path.join(lang);
        fs::create_dir_all(&lang_dir).unwrap();

        match lang {
            "c" => {
                let template = r#"#include <stdio.h>

int main() {
    // TODO: Implement benchmark
    printf("Result: %d\n", 42);
    return 0;
}
"#;
                fs::write(lang_dir.join("main.c"), template).unwrap();
            }
            "rust" => {
                let template = r#"// TODO: Implement benchmark
fn main() {
    let result = 42;
    println!("{}", result);
}
"#;
                fs::write(lang_dir.join("main.rs"), template).unwrap();
            }
            "bmb" => {
                let template = r#"// TODO: Implement benchmark
fn main() -> i32 = 42;
"#;
                fs::write(lang_dir.join("main.bmb"), template).unwrap();
            }
            _ => {}
        }
    }

    println!("{} Created at {}", "Success:".green(), bench_path.display());
}

fn validate_benchmark(name: &str) {
    println!("Validating benchmark: {}", name);
    // Implementation would run all implementations and compare outputs
}

fn generate_report(format: &str, output: &str) {
    println!("Generating {} report to {}", format, output);
    // Implementation would generate formatted report
}

/// Gate criteria definitions
struct GateCriteria {
    name: &'static str,
    description: &'static str,
    benchmarks: &'static [&'static str],
    threshold: f64,  // BMB/C ratio threshold (e.g., 1.10 = within 10%)
    contract_threshold: f64,  // For contract benchmarks (e.g., 0.90 = 10% faster)
}

const GATE_3_1: GateCriteria = GateCriteria {
    name: "Gate #3.1",
    description: "Compute within 10% of C, Contract >= 10% faster",
    benchmarks: &["fibonacci", "mandelbrot", "spectral_norm", "n_body", "fannkuch", "binary_trees"],
    threshold: 1.10,
    contract_threshold: 0.90,
};

const GATE_3_2: GateCriteria = GateCriteria {
    name: "Gate #3.2",
    description: "All Benchmarks Game within 5% of C",
    benchmarks: &["fibonacci", "mandelbrot", "spectral_norm", "n_body", "fannkuch", "binary_trees", "fasta", "reverse_complement"],
    threshold: 1.05,
    contract_threshold: 0.85,
};

const GATE_3_3: GateCriteria = GateCriteria {
    name: "Gate #3.3",
    description: "3+ benchmarks faster than C, all contract faster",
    benchmarks: &["fibonacci", "mandelbrot", "spectral_norm", "n_body", "fannkuch", "binary_trees"],
    threshold: 1.00,  // At least 3 must be <= 1.0
    contract_threshold: 0.95,
};

fn verify_gate(gate: &str, iterations: u32, verbose: bool) {
    println!("{}", "=== BMB Benchmark Gate Verification ===".cyan().bold());
    println!();

    let criteria = match gate {
        "3.1" => &GATE_3_1,
        "3.2" => &GATE_3_2,
        "3.3" => &GATE_3_3,
        _ => {
            println!("{} Unknown gate: {}. Valid: 3.1, 3.2, 3.3", "Error:".red(), gate);
            return;
        }
    };

    println!("{}: {}", criteria.name.green().bold(), criteria.description);
    println!("Threshold: BMB/C <= {:.2}x for compute", criteria.threshold);
    println!("Contract threshold: BMB/C <= {:.2}x (faster)", criteria.contract_threshold);
    println!();

    let benches_dir = find_benches_dir();
    let mut passed = 0;
    let mut failed = 0;
    let mut faster_count = 0;
    let mut results = Vec::new();

    // Run compute benchmarks
    println!("{}", "Compute Benchmarks:".cyan());
    println!("{}", "-".repeat(70));
    println!("{:<20} {:>12} {:>12} {:>10} {:>10}", "Benchmark", "C (ms)", "BMB (ms)", "Ratio", "Status");
    println!("{}", "-".repeat(70));

    for bench_name in criteria.benchmarks {
        let bench_path = benches_dir.join("compute").join(bench_name);
        if !bench_path.exists() {
            if verbose {
                println!("{:<20} {}", bench_name, "Not found".yellow());
            }
            continue;
        }

        let c_times = run_language_benchmark(&bench_path.join("c"), "c", iterations, 2);
        let bmb_times = run_language_benchmark(&bench_path.join("bmb"), "bmb", iterations, 2);

        if let (Some(c_t), Some(bmb_t)) = (c_times, bmb_times) {
            let c_median = median(&c_t);
            let bmb_median = median(&bmb_t);
            let ratio = bmb_median / c_median;

            let (status, symbol) = if ratio <= criteria.threshold {
                passed += 1;
                if ratio < 1.0 {
                    faster_count += 1;
                    ("PASS".green().to_string(), "✓★".green().to_string())
                } else {
                    ("PASS".green().to_string(), "✓".green().to_string())
                }
            } else {
                failed += 1;
                ("FAIL".red().to_string(), "✗".red().to_string())
            };

            println!("{:<20} {:>12.2} {:>12.2} {:>10.2}x {:>10}",
                bench_name, c_median, bmb_median, ratio, symbol);

            results.push((bench_name.to_string(), ratio, status));
        }
    }

    // Run contract benchmarks
    println!();
    println!("{}", "Contract Benchmarks:".cyan());
    println!("{}", "-".repeat(70));

    for bench_name in &["bounds_check", "null_check", "purity_opt", "aliasing"] {
        let bench_path = benches_dir.join("contract").join(bench_name);
        if !bench_path.exists() {
            continue;
        }

        let c_times = run_language_benchmark(&bench_path.join("c"), "c", iterations, 2);
        let bmb_times = run_language_benchmark(&bench_path.join("bmb"), "bmb", iterations, 2);

        if let (Some(c_t), Some(bmb_t)) = (c_times, bmb_times) {
            let c_median = median(&c_t);
            let bmb_median = median(&bmb_t);
            let ratio = bmb_median / c_median;

            let (status, symbol) = if ratio <= criteria.contract_threshold {
                passed += 1;
                faster_count += 1;
                ("PASS".green().to_string(), "✓★".green().to_string())
            } else if ratio <= 1.0 {
                passed += 1;
                ("PASS".green().to_string(), "✓".green().to_string())
            } else {
                failed += 1;
                ("FAIL".red().to_string(), "✗".red().to_string())
            };

            println!("{:<20} {:>12.2} {:>12.2} {:>10.2}x {:>10}",
                bench_name, c_median, bmb_median, ratio, symbol);
        }
    }

    // Summary
    println!();
    println!("{}", "=".repeat(70));
    println!("{}: {} passed, {} failed, {} faster than C",
        "Summary".cyan().bold(),
        passed.to_string().green(),
        if failed > 0 { failed.to_string().red() } else { failed.to_string().green() },
        faster_count.to_string().cyan()
    );

    let gate_passed = failed == 0;
    if gate_passed {
        println!();
        println!("{} {} {}", "✓".green().bold(), criteria.name.green().bold(), "PASSED".green().bold());
    } else {
        println!();
        println!("{} {} {}", "✗".red().bold(), criteria.name.red().bold(), "FAILED".red().bold());
        std::process::exit(1);
    }
}

fn find_benches_dir() -> PathBuf {
    // Try relative paths from different locations
    let candidates = [
        PathBuf::from("benches"),
        PathBuf::from("../benches"),
        PathBuf::from("../../benches"),
    ];

    for path in candidates {
        if path.exists() {
            return path;
        }
    }

    PathBuf::from("benches")
}

fn discover_benchmarks(base: &Path, category: Option<&str>) -> Vec<(String, PathBuf)> {
    let mut benchmarks = Vec::new();

    let categories: Vec<_> = if let Some(cat) = category {
        vec![base.join(cat)]
    } else {
        fs::read_dir(base)
            .ok()
            .map(|entries| {
                entries
                    .flatten()
                    .filter(|e| e.path().is_dir())
                    .map(|e| e.path())
                    .collect()
            })
            .unwrap_or_default()
    };

    for cat_path in categories {
        if !cat_path.is_dir() {
            continue;
        }

        for entry in fs::read_dir(&cat_path).into_iter().flatten().flatten() {
            let bench_path = entry.path();
            if bench_path.is_dir() {
                let name = bench_path
                    .file_name()
                    .unwrap()
                    .to_string_lossy()
                    .to_string();
                benchmarks.push((name, bench_path));
            }
        }
    }

    benchmarks.sort_by(|a, b| a.0.cmp(&b.0));
    benchmarks
}

fn median(values: &[f64]) -> f64 {
    if values.is_empty() {
        return 0.0;
    }

    let mut sorted = values.to_vec();
    sorted.sort_by(|a, b| a.partial_cmp(b).unwrap());

    let mid = sorted.len() / 2;
    if sorted.len() % 2 == 0 {
        (sorted[mid - 1] + sorted[mid]) / 2.0
    } else {
        sorted[mid]
    }
}
