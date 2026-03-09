// Dijkstra shortest path benchmark — min-heap + graph traversal
// Measures: priority queue operations, random memory access, graph algorithms
// Workload: 20000 nodes, ~6 edges/node, weighted, 100 iterations

const INF: i64 = 0x3FFFFFFFFFFFFFFF;

fn dijk_swap(dist: &mut [i64], node: &mut [i64], a: usize, b: usize) {
    dist.swap(a, b);
    node.swap(a, b);
}

fn dijk_up(dist: &mut [i64], node: &mut [i64], mut i: usize) {
    while i > 0 {
        let p = (i - 1) / 2;
        if dist[i] < dist[p] { dijk_swap(dist, node, i, p); i = p; }
        else { break; }
    }
}

fn dijk_down(dist: &mut [i64], node: &mut [i64], size: usize, mut i: usize) {
    loop {
        let mut s = i;
        let l = 2 * i + 1;
        let r = 2 * i + 2;
        if l < size && dist[l] < dist[s] { s = l; }
        if r < size && dist[r] < dist[s] { s = r; }
        if s == i { break; }
        dijk_swap(dist, node, i, s);
        i = s;
    }
}

fn dijkstra(nodes: usize, adj_off: &[i64], adj_dst: &[i64], adj_wt: &[i64],
            src: usize, best: &mut [i64], heap_d: &mut [i64], heap_n: &mut [i64]) -> i64 {
    for i in 0..nodes { best[i] = INF; }
    best[src] = 0;
    let mut hsize: usize = 0;
    heap_d[0] = 0;
    heap_n[0] = src as i64;
    hsize = 1;

    while hsize > 0 {
        let d = heap_d[0];
        let u = heap_n[0] as usize;
        hsize -= 1;
        heap_d[0] = heap_d[hsize];
        heap_n[0] = heap_n[hsize];
        if hsize > 0 { dijk_down(heap_d, heap_n, hsize, 0); }
        if d > best[u] { continue; }
        let begin = adj_off[u] as usize;
        let end = adj_off[u + 1] as usize;
        for e in begin..end {
            let v = adj_dst[e] as usize;
            let nd = d + adj_wt[e];
            if nd < best[v] {
                best[v] = nd;
                heap_d[hsize] = nd;
                heap_n[hsize] = v as i64;
                dijk_up(heap_d, heap_n, hsize);
                hsize += 1;
            }
        }
    }
    let mut mx: i64 = 0;
    for i in 0..nodes {
        if best[i] != INF && best[i] > mx { mx = best[i]; }
    }
    mx
}

fn main() {
    let nodes: usize = 20000;
    let edges_per: usize = 6;
    let iters: usize = 100;
    let total_edges = nodes * edges_per;

    let mut adj_off = vec![0i64; nodes + 1];
    let mut adj_dst = vec![0i64; total_edges];
    let mut adj_wt = vec![0i64; total_edges];
    let mut best = vec![0i64; nodes];
    let mut heap_d = vec![0i64; nodes];
    let mut heap_n = vec![0i64; nodes];

    let mut seed: i64 = 12345;
    for i in 0..nodes {
        adj_off[i] = (i * edges_per) as i64;
        for e in 0..edges_per {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            adj_dst[i * edges_per + e] = seed % (nodes as i64);
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            adj_wt[i * edges_per + e] = (seed % 100) + 1;
        }
    }
    adj_off[nodes] = total_edges as i64;

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        checksum += dijkstra(nodes, &adj_off, &adj_dst, &adj_wt, iter % nodes, &mut best, &mut heap_d, &mut heap_n);
    }
    println!("{}", checksum);
}
