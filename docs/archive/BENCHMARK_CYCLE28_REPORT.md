# BMB Benchmark Report - Cycle 28 (v0.60.43)

## Summary

### Infrastructure Improvement: llc -O3 Fallback

Added `llc -O3` as automatic fallback when `opt` is blocked by Application Control policy.

### Changes Made

1. **Fixed Runtime Path Resolution** (v0.60.42)
   - `find_runtime()` now properly handles directory paths from `BMB_RUNTIME_PATH`
   - Automatically looks for `libbmb_runtime.a` inside the specified directory

2. **Added llc Fallback** (v0.60.42)
   - When `opt` fails or is blocked, automatically tries `llc -O3`
   - Provides codegen-level optimizations without LLVM IR passes

3. **Upgraded llc to -O3** (v0.60.43)
   - Changed Release mode from `-O2` to `-O3` for best available codegen

---

## Performance Results

### With Current Infrastructure (llc -O3 fallback)

| Benchmark | BMB (llc -O3) | C (gcc) | Ratio |
|-----------|---------------|---------|-------|
| spectral_norm | ~73ms | ~33ms | 221% |
| binary_trees | 1339ms | 1183ms | 113% |
| mandelbrot | 3030ms | 2004ms | 151% |

### Reference: Previous Results (with opt)

| Benchmark | BMB (opt -O3) | C (gcc) | Ratio |
|-----------|---------------|---------|-------|
| spectral_norm | ~40ms | ~33ms | 121% |
| binary_trees | ~1180ms | ~1170ms | 101% |
| mandelbrot | ~2160ms | ~2000ms | 108% |

---

## Application Control Status

| Tool | Location | Status |
|------|----------|--------|
| `opt.exe` | C:/msys64/ucrt64/bin | BLOCKED |
| `opt.exe` | C:/Program Files/LLVM/bin | NOT AVAILABLE |
| `clang.exe` | All locations | BLOCKED |
| `llc.exe` | C:/msys64/ucrt64/bin | Works |
| `gcc.exe` | C:/msys64/ucrt64/bin | Works |

### WSL Availability

| Component | Version | Status |
|-----------|---------|--------|
| Ubuntu 24.04 | WSL2 | Available |
| LLVM/opt | 18.1.3 | Installed |
| LLVM 21 | - | Available in apt |

**Issue:** LLVM version mismatch (21.1.8 bitcode incompatible with 18.1.3)

---

## Recommended Actions

### Priority 1: Request IT Exception
- Request Application Control whitelist for `C:/msys64/ucrt64/bin/opt.exe`
- Expected performance improvement: 221% -> 121% on compute benchmarks

### Priority 2: Install LLVM 21 in WSL
```bash
wsl -d Ubuntu-24.04 -- sudo apt-get install -y llvm-21
```
Then modify compiler to use:
```bash
wsl -d Ubuntu-24.04 -- opt-21 -O3 -o <output.bc> <input.bc>
```

### Priority 3: Strengthen MIR Optimizations
Reduce LLVM dependency by implementing:
- Loop Invariant Code Motion (LICM)
- Global Value Numbering (GVN)
- Strength Reduction
- Phi Simplification

---

## Code Changes

### `bmb/src/codegen/llvm.rs`

#### v0.60.42: Added llc fallback
```rust
// v0.60.42: Try llc -O3 as fallback when opt is unavailable
if !opt_success {
    let llc_result = Command::new("llc")
        .args(["-O3", "-filetype=obj", "-o"])
        .arg(&obj_from_llc)
        .arg(&temp_bc)
        .output();
    // ...
}
```

#### v0.60.43: Use -O3 for Release mode
```rust
let llc_opt = match self.opt_level {
    OptLevel::Debug => "-O0",
    OptLevel::Release => "-O3",  // Was -O2, now -O3
    OptLevel::Size => "-Os",
    OptLevel::Aggressive => "-O3",
};
```

### `bmb/src/build/mod.rs`

#### v0.60.42: Fixed runtime path resolution
```rust
if let Ok(path) = std::env::var("BMB_RUNTIME_PATH") {
    let p = PathBuf::from(&path);
    // v0.60.42: If path is a directory, look for the library file inside it
    if p.is_dir() {
        let lib_path = p.join("libbmb_runtime.a");
        if lib_path.exists() {
            return Ok(lib_path);
        }
    }
}
```

---

## Verification

Build and run with llc fallback:
```powershell
$env:BMB_RUNTIME_PATH = "d:/data/lang-bmb/bmb/runtime"
.\target\x86_64-pc-windows-gnu\release\bmb.exe build main.bmb -o test.exe --release
# Output shows: "Note: llc -O3 optimization successful"
```

---

**Version:** v0.60.43
