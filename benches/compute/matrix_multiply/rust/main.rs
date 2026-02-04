// Matrix Multiplication Benchmark
// Measures: array access, nested loops, memory access patterns

const N: usize = 512;

fn main() {
    let mut a = vec![0i64; N * N];
    let mut b = vec![0i64; N * N];
    let mut c = vec![0i64; N * N];

    // Initialize matrices
    for i in 0..N {
        for j in 0..N {
            a[i * N + j] = (i + j) as i64;
            b[i * N + j] = (i * j) as i64;
        }
    }

    // Multiply
    for i in 0..N {
        for j in 0..N {
            let mut sum: i64 = 0;
            for k in 0..N {
                sum += a[i * N + k] * b[k * N + j];
            }
            c[i * N + j] = sum;
        }
    }

    // Checksum
    let mut checksum: i64 = 0;
    for i in 0..N {
        for j in 0..N {
            checksum += c[i * N + j];
        }
    }
    println!("{}", checksum);
}
