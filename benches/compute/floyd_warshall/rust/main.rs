// Floyd-Warshall all-pairs shortest path benchmark
// Measures: triple nested loop, 2D array access, min operations
// Workload: 500 nodes, ~30% edge density, 20 iterations

const INF: i64 = 999999999;

fn floyd_warshall(dist: &mut [i64], n: usize) -> i64 {
    for k in 0..n {
        for i in 0..n {
            let dik = dist[i * n + k];
            if dik >= INF { continue; }
            for j in 0..n {
                let dkj = dist[k * n + j];
                let via_k = dik + dkj;
                if via_k < dist[i * n + j] {
                    dist[i * n + j] = via_k;
                }
            }
        }
    }
    let mut sum: i64 = 0;
    for i in 0..n * n {
        if dist[i] < INF { sum += dist[i]; }
    }
    sum
}

fn main() {
    let n: usize = 500;
    let iters: i64 = 20;
    let mut dist = vec![0i64; n * n];

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        for i in 0..n {
            for j in 0..n {
                dist[i * n + j] = if i == j { 0 } else { INF };
            }
        }
        let mut seed: i64 = 77777 + iter;
        for i in 0..n {
            for j in 0..n {
                if i == j { continue; }
                seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
                if seed % 100 < 30 {
                    seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
                    dist[i * n + j] = (seed % 100) + 1;
                }
            }
        }
        checksum += floyd_warshall(&mut dist, n);
    }
    println!("{}", checksum);
}
