// Fannkuch-Redux Benchmark
// Measures: array manipulation, permutations

fn fannkuch(n: i32) -> i32 {
    let n = n as usize;
    let mut perm = vec![0i32; n];
    let mut perm1 = vec![0i32; n];
    let mut count = vec![0i32; n];

    for i in 0..n {
        perm1[i] = i as i32;
    }

    let mut max_flips = 0;
    let mut r = n;

    loop {
        while r != 1 {
            count[r - 1] = r as i32;
            r -= 1;
        }

        for i in 0..n {
            perm[i] = perm1[i];
        }

        let mut flips = 0;
        let mut k = perm[0] as usize;
        while k != 0 {
            let mut i = 0;
            let mut j = k;
            while i < j {
                perm.swap(i, j);
                i += 1;
                j -= 1;
            }
            flips += 1;
            k = perm[0] as usize;
        }

        if flips > max_flips {
            max_flips = flips;
        }

        loop {
            if r == n {
                return max_flips;
            }
            let perm0 = perm1[0];
            for i in 0..r {
                perm1[i] = perm1[i + 1];
            }
            perm1[r] = perm0;
            count[r] -= 1;
            if count[r] > 0 {
                break;
            }
            r += 1;
        }
    }
}

fn main() {
    let result = fannkuch(11);
    println!("{}", result);
}
