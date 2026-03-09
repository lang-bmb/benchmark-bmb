// BFS benchmark — breadth-first search on random graph
// Measures: queue operations, random memory access, graph traversal
// Workload: 50000 nodes, ~4 edges/node, 100 iterations

fn bfs(nodes: usize, adj_off: &[i64], adj_data: &[i64],
       start: usize, dist: &mut [i64], queue: &mut [usize]) -> i64 {
    for i in 0..nodes {
        dist[i] = -1;
    }
    dist[start] = 0;
    let mut head: usize = 0;
    let mut tail: usize = 0;
    queue[tail] = start;
    tail += 1;

    let mut max_dist: i64 = 0;
    while head < tail {
        let u = queue[head];
        head += 1;
        let d = dist[u];
        let begin = adj_off[u] as usize;
        let end = adj_off[u + 1] as usize;
        for e in begin..end {
            let v = adj_data[e] as usize;
            if dist[v] == -1 {
                dist[v] = d + 1;
                queue[tail] = v;
                tail += 1;
                if d + 1 > max_dist {
                    max_dist = d + 1;
                }
            }
        }
    }
    max_dist
}

fn main() {
    let nodes: usize = 50000;
    let edges_per: usize = 4;
    let iters: usize = 100;

    let total_edges = nodes * edges_per;
    let mut adj_off = vec![0i64; nodes + 1];
    let mut adj_data = vec![0i64; total_edges];
    let mut dist = vec![0i64; nodes];
    let mut queue = vec![0usize; nodes];

    let mut seed: i64 = 42;
    for i in 0..nodes {
        adj_off[i] = (i * edges_per) as i64;
        for e in 0..edges_per {
            seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
            adj_data[i * edges_per + e] = seed % (nodes as i64);
        }
    }
    adj_off[nodes] = total_edges as i64;

    let mut checksum: i64 = 0;
    for iter in 0..iters {
        let start = iter % nodes;
        checksum += bfs(nodes, &adj_off, &adj_data, start, &mut dist, &mut queue);
    }

    println!("{}", checksum);
}
