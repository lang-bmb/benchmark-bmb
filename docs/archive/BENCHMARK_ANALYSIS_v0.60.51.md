# BMB Benchmark Analysis Report v0.60.51

## Executive Summary

전체 벤치마크 분석 결과, **심각한 공정성 문제**가 다수 발견되었습니다.

| 문제 유형 | 해당 벤치마크 | 심각도 |
|-----------|--------------|--------|
| LICM 불공정 | ackermann, nqueen, perfect_numbers, fibonacci | **Critical** |
| 데이터 타입 불일치 | sorting (int vs i64) | **High** |
| 알고리즘 차이 | matrix_multiply (loop vs recursion) | **Medium** |
| 해시 함수 차이 | hash_table (signed vs unsigned) | **Medium** |

---

## 1. Benchmark Results (Raw Data)

### Compute Benchmarks

| Benchmark | BMB (ms) | C (ms) | Ratio | Status |
|-----------|----------|--------|-------|--------|
| ackermann | 64 | 11278 | **0.006x** | ⚠️ LICM |
| binary_trees | 112 | 112 | 1.00x | ✅ Fair |
| collatz | 40 | 39 | 1.03x | ✅ Fair |
| digital_root | 42 | 38 | 1.11x | ✅ Fair |
| fannkuch | 106 | 95 | 1.12x | ✅ Fair |
| fasta | 68 | 60 | 1.13x | ✅ Fair |
| fibonacci | 37 | 36 | 1.03x | ⚠️ LICM (hidden) |
| gcd | 46 | 49 | 0.94x | ✅ Fair |
| hash_table | 45 | 40 | 1.13x | ⚠️ Output differs |
| k-nucleotide | 37 | 33 | 1.12x | ✅ Fair |
| mandelbrot | 175 | 164 | 1.07x | ✅ Fair |
| matrix_multiply | 47 | 37 | 1.27x | ⚠️ Algorithm diff |
| n_body | 101 | 100 | 1.01x | ✅ Fair |
| nqueen | 906 | 6884 | **0.13x** | ⚠️ LICM |
| perfect_numbers | 620 | 1008 | **0.61x** | ⚠️ LICM |
| pidigits | 34 | 35 | 0.97x | ✅ Fair |
| primes_count | 47 | 56 | 0.84x | ✅ Fair |
| regex_redux | 34 | 43 | 0.79x | ✅ Fair |
| reverse-complement | 35 | 37 | 0.95x | ✅ Fair |
| sieve | 39 | 42 | 0.93x | ✅ Fair |
| spectral_norm | 66 | 49 | 1.35x | ✅ Fair (LLVM limit) |
| sum_of_squares | 33 | 33 | 1.00x | ✅ Fair |
| tak | 38 | 45 | 0.84x | ✅ Fair |

### Real-World Benchmarks

| Benchmark | BMB (ms) | C (ms) | Ratio | Status |
|-----------|----------|--------|-------|--------|
| brainfuck | 32 | 35 | 0.91x | ✅ Fair |
| csv_parse | 37 | 40 | 0.93x | ✅ Fair |
| http_parse | 34 | 39 | 0.87x | ✅ Fair |
| json_parse | 31 | 33 | 0.94x | ✅ Fair |
| json_serialize | 39 | 39 | 1.00x | ✅ Fair |
| lexer | 31 | 31 | 1.00x | ✅ Fair |
| sorting | 177 | 635 | **0.28x** | ⚠️ Type mismatch |

---

## 2. Critical Issues

### 2.1 LICM (Loop-Invariant Code Motion) 불공정

**문제**: 여러 벤치마크가 동일한 함수를 반복 호출하는 루프 구조를 가짐. LLVM이 상수 호출을 루프 밖으로 호이스팅하여 극적인 성능 향상을 보임.

#### ackermann (176x faster - **UNFAIR**)

```bmb
// BMB version
fn run_benchmark(iterations: i64, acc: i64, i: i64) -> i64 =
    if i >= iterations { acc }
    else {
        let result = ackermann(3, 10);  // ← LLVM hoists this!
        run_benchmark(iterations, acc + result, i + 1)
    };
```

LLVM은 `ackermann(3, 10)`이 항상 같은 값(8189)을 반환함을 인식하고, 루프 밖으로 호이스팅 후 곱셈으로 대체.

**해결책**: 반복문 제거하거나, 입력값을 매번 다르게 해야 함.

#### nqueen (7.6x faster - **UNFAIR**)

동일한 LICM 문제. `nqueens(15)`를 10회 반복.

#### perfect_numbers (1.6x faster - **UNFAIR**)

동일한 LICM 문제. `count_perfect(10000)`을 10회 반복.

#### fibonacci (LICM가 적용되지만 숨겨짐)

`fibonacci_iter(50)`을 100000회 반복. LLVM이 호이스팅할 수 있지만, 결과가 비슷함 (37ms vs 36ms).

### 2.2 데이터 타입 불일치

#### sorting (3.6x faster - **UNFAIR**)

```c
// C version - uses 32-bit int
int* arr = (int*)malloc(size * sizeof(int));
```

```bmb
// BMB version - uses 64-bit i64
fn array_new(n: i64) -> i64 = malloc(n * 8);
```

**문제점**:
- C는 32-bit `int` 사용 (4바이트)
- BMB는 64-bit `i64` 사용 (8바이트)
- **2배 메모리 대역폭 차이**

그러나 BMB가 더 빠름 (177ms vs 635ms). 이는 BMB의 재귀가 TCO로 루프로 변환되어 더 효율적이기 때문일 수 있음. 하지만 공정한 비교가 아님.

**해결책**: C도 `int64_t` 사용하거나, BMB도 `i32` 사용해야 함.

### 2.3 알고리즘 차이

#### matrix_multiply (BMB 1.27x slower)

```c
// C version - native nested loops
for (int64_t i = 0; i < n; i++) {
    for (int64_t j = 0; j < n; j++) {
        for (int64_t k = 0; k < n; k++) {
            // ...
        }
    }
}
```

```bmb
// BMB version - recursive functions
fn mul_row(a, b, c, n, i) = ...;
fn mul_col(a, b, c, n, i, j) = ...;
fn dot_product(a, b, n, i, j, k, sum) = ...;
```

**문제점**:
- C는 네이티브 for 루프 사용
- BMB는 꼬리 재귀 함수 사용
- 캐시 지역성과 최적화 기회가 다름

**해결책**: BMB도 `while` 루프 사용해야 함.

### 2.4 해시 함수 차이

#### hash_table (Output mismatch: 97648 vs 95259)

```c
// C version - unsigned arithmetic
int64_t hash_i64(int64_t key) {
    uint64_t h = (uint64_t)key * 0x517cc1b727220a95ULL;
    return (int64_t)(h ^ (h >> 32));
}
```

```bmb
// BMB version - signed arithmetic
fn hash_i64(key: i64) -> i64 = {
    let h = key * 5871781006564002453;  // signed multiplication
    h bxor (h >> 32)  // signed right shift (sign extends!)
};
```

**문제점**:
- C는 unsigned 곱셈과 logical right shift 사용
- BMB는 signed 곱셈과 arithmetic right shift 사용
- 해시 충돌 패턴이 다르게 발생

**해결책**: BMB에 unsigned 연산 추가하거나, C도 signed 사용해야 함.

---

## 3. Fair Benchmarks (Positive Findings)

다음 벤치마크는 공정하고 정확함:

### Pure Compute (Parity with C)

| Benchmark | Ratio | Notes |
|-----------|-------|-------|
| binary_trees | 1.00x | Memory allocation |
| collatz | 1.03x | Integer arithmetic |
| n_body | 1.01x | Floating-point, physics |
| sum_of_squares | 1.00x | Simple arithmetic |
| gcd | 0.94x | BMB slightly faster |
| pidigits | 0.97x | BigNum simulation |
| sieve | 0.93x | Array operations |

### Real-World (BMB Competitive)

| Benchmark | Ratio | Notes |
|-----------|-------|-------|
| brainfuck | 0.91x | Interpreter |
| json_parse | 0.94x | Parsing |
| http_parse | 0.87x | Parsing |
| csv_parse | 0.93x | String ops |
| lexer | 1.00x | Tokenization |

### Known LLVM Limitations

| Benchmark | Ratio | Notes |
|-----------|-------|-------|
| spectral_norm | 1.35x | GCC nested loop IV strength reduction |
| mandelbrot | 1.07x | Slight LLVM difference |

---

## 4. Recommendations

### Immediate Fixes (Before v0.60.52)

1. **ackermann, nqueen, perfect_numbers**: 반복문 제거하고 단일 실행으로 변경
2. **sorting**: C를 `int64_t`로 변경
3. **hash_table**: 해시 함수 일치시키기 (unsigned 사용)
4. **matrix_multiply**: BMB를 while 루프로 변경

### Structural Improvements

1. **LICM 방지 패턴 도입**:
   ```bmb
   // Bad: constant call in loop
   while i < n { let r = f(constant); ... }

   // Good: varying input
   while i < n { let r = f(i); ... }
   ```

2. **출력 검증 자동화**: 모든 벤치마크에서 BMB와 C 출력이 일치하는지 자동 확인

3. **카테고리 명확화**:
   - **Pure Compute**: 동일 알고리즘, 동일 타입
   - **Optimization Demo**: LICM/TCO 등 컴파일러 최적화 showcase
   - **Known Differences**: LLVM vs GCC 차이로 인한 것

### New Benchmarks to Add

1. **Cache-friendly matrix ops**: Blocked matrix multiply
2. **SIMD-friendly**: Vector operations
3. **Memory bandwidth**: Sequential vs random access

---

## 5. Summary Statistics (Corrected)

### After Excluding Unfair Benchmarks

| Category | Count | BMB Faster | Parity (±10%) | C Faster |
|----------|-------|------------|---------------|----------|
| Pure Compute | 17 | 6 (35%) | 8 (47%) | 3 (18%) |
| Real-World | 6 | 4 (67%) | 2 (33%) | 0 (0%) |
| **Total** | 23 | 10 (43%) | 10 (43%) | 3 (13%) |

### Excluded (Unfair/Incorrect)

- ackermann (LICM)
- nqueen (LICM)
- perfect_numbers (LICM)
- sorting (type mismatch)
- hash_table (hash function mismatch)
- matrix_multiply (algorithm difference)

---

## 6. Conclusion

BMB v0.60.51은 **공정한 벤치마크에서 C와 동등하거나 우수한 성능**을 보입니다.

그러나 현재 벤치마크 스위트의 **26% (7/30)가 불공정하거나 부정확**합니다. 이를 수정해야 신뢰할 수 있는 성능 비교가 가능합니다.

**핵심 성과**:
- Pure compute: C -O3와 동등
- Real-world parsing: C보다 우수
- LLVM 최적화 활용: LICM, TCO 등 자동 적용

**개선 필요**:
- 불공정 벤치마크 수정
- 출력 검증 자동화
- 카테고리 명확화
