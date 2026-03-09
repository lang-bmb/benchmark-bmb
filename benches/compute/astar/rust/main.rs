// A* pathfinding benchmark — heuristic search on a grid
// Measures: priority queue, heuristic computation, grid traversal
// Workload: 200x200 grid, 500 path queries, random obstacles

const GRID_SIZE: usize = 200;
const TOTAL: usize = GRID_SIZE * GRID_SIZE;
const QUERIES: i64 = 500;
const INF: i64 = 999999999;

fn heap_swap(f: &mut [i64], n: &mut [i64], a: usize, b: usize) {
    f.swap(a, b); n.swap(a, b);
}
fn heap_up(f: &mut [i64], n: &mut [i64], mut i: usize) {
    while i > 0 {
        let p = (i - 1) / 2;
        if f[i] < f[p] { heap_swap(f, n, i, p); i = p; } else { break; }
    }
}
fn heap_down(f: &mut [i64], n: &mut [i64], sz: usize, mut i: usize) {
    loop {
        let mut s = i;
        let l = 2 * i + 1;
        let r = 2 * i + 2;
        if l < sz && f[l] < f[s] { s = l; }
        if r < sz && f[r] < f[s] { s = r; }
        if s == i { break; }
        heap_swap(f, n, i, s);
        i = s;
    }
}

fn manhattan(a: i64, b: i64, w: i64) -> i64 {
    let ar = a / w; let ac = a % w;
    let br = b / w; let bc = b % w;
    (ar - br).abs() + (ac - bc).abs()
}

fn astar(grid: &[i64], w: i64, h: i64, src: i64, dst: i64,
         g: &mut [i64], heap_f: &mut [i64], heap_n: &mut [i64]) -> i64 {
    let total = (w * h) as usize;
    for i in 0..total { g[i] = INF; }
    g[src as usize] = 0;

    let mut hsz: usize = 0;
    heap_f[0] = manhattan(src, dst, w);
    heap_n[0] = src;
    hsz = 1;

    let dx: [i64; 4] = [-1, 1, 0, 0];
    let dy: [i64; 4] = [0, 0, -1, 1];

    while hsz > 0 {
        let u = heap_n[0];
        hsz -= 1;
        heap_f[0] = heap_f[hsz];
        heap_n[0] = heap_n[hsz];
        if hsz > 0 { heap_down(heap_f, heap_n, hsz, 0); }

        if u == dst { return g[dst as usize]; }

        let ur = u / w;
        let uc = u % w;
        let gu = g[u as usize];

        for d in 0..4 {
            let nr = ur + dx[d];
            let nc = uc + dy[d];
            if nr < 0 || nr >= h || nc < 0 || nc >= w { continue; }
            let v = (nr * w + nc) as usize;
            if grid[v] == 1 { continue; }
            let ng = gu + 1;
            if ng < g[v] {
                g[v] = ng;
                let f = ng + manhattan(v as i64, dst, w);
                heap_f[hsz] = f;
                heap_n[hsz] = v as i64;
                heap_up(heap_f, heap_n, hsz);
                hsz += 1;
            }
        }
    }
    -1
}

fn main() {
    let w: i64 = GRID_SIZE as i64;
    let h: i64 = GRID_SIZE as i64;
    let total = TOTAL;
    let mut grid = vec![0i64; total];
    let mut g = vec![0i64; total];
    let mut heap_f = vec![0i64; total];
    let mut heap_n = vec![0i64; total];

    let mut seed: i64 = 99999;
    for i in 0..total {
        seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
        grid[i] = if seed % 100 < 20 { 1 } else { 0 };
    }
    grid[0] = 0;
    grid[total - 1] = 0;

    let mut checksum: i64 = 0;
    for _q in 0..QUERIES {
        seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
        let src = seed % (total as i64);
        seed = (seed.wrapping_mul(1103515245) + 12345) & 0x7FFFFFFF;
        let dst = seed % (total as i64);
        grid[src as usize] = 0;
        grid[dst as usize] = 0;
        let dist = astar(&grid, w, h, src, dst, &mut g, &mut heap_f, &mut heap_n);
        checksum += dist;
    }
    println!("{}", checksum);
}
