// Sorting Benchmark
// Measures: comparison operations, data movement

fn bubble_sort(arr: &mut [i64]) -> i64 {
    let n = arr.len();
    let mut comparisons: i64 = 0;
    for i in 0..n - 1 {
        for j in 0..n - i - 1 {
            comparisons += 1;
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
            }
        }
    }
    comparisons
}

fn insertion_sort(arr: &mut [i64]) -> i64 {
    let n = arr.len();
    let mut cost: i64 = 0;
    for i in 1..n {
        let key = arr[i];
        let mut j = i as i64 - 1;
        while j >= 0 && arr[j as usize] > key {
            arr[(j + 1) as usize] = arr[j as usize];
            j -= 1;
            cost += 1;
        }
        arr[(j + 1) as usize] = key;
        cost += 1;
    }
    cost
}

fn merge(arr: &mut [i64], l: usize, m: usize, r: usize, cost: &mut i64) {
    let n1 = m - l + 1;
    let n2 = r - m;
    let left: Vec<i64> = arr[l..=m].to_vec();
    let right: Vec<i64> = arr[m + 1..=r].to_vec();

    let mut i = 0;
    let mut j = 0;
    let mut k = l;

    while i < n1 && j < n2 {
        *cost += 1;
        if left[i] <= right[j] {
            arr[k] = left[i];
            i += 1;
        } else {
            arr[k] = right[j];
            j += 1;
        }
        k += 1;
    }

    while i < n1 {
        arr[k] = left[i];
        i += 1;
        k += 1;
    }

    while j < n2 {
        arr[k] = right[j];
        j += 1;
        k += 1;
    }
}

fn merge_sort_helper(arr: &mut [i64], l: usize, r: usize, cost: &mut i64) {
    if l < r {
        let m = l + (r - l) / 2;
        merge_sort_helper(arr, l, m, cost);
        merge_sort_helper(arr, m + 1, r, cost);
        merge(arr, l, m, r, cost);
    }
}

fn merge_sort(arr: &mut [i64]) -> i64 {
    let mut cost: i64 = 0;
    if !arr.is_empty() {
        merge_sort_helper(arr, 0, arr.len() - 1, &mut cost);
    }
    cost
}

fn partition(arr: &mut [i64], low: usize, high: usize, cost: &mut i64) -> usize {
    let pivot = arr[high];
    let mut i = low as i64 - 1;
    for j in low..high {
        *cost += 1;
        if arr[j] <= pivot {
            i += 1;
            arr.swap(i as usize, j);
        }
    }
    arr.swap((i + 1) as usize, high);
    (i + 1) as usize
}

fn quick_sort_helper(arr: &mut [i64], low: usize, high: usize, cost: &mut i64) {
    if low < high {
        let pi = partition(arr, low, high, cost);
        if pi > 0 {
            quick_sort_helper(arr, low, pi - 1, cost);
        }
        quick_sort_helper(arr, pi + 1, high, cost);
    }
}

fn quick_sort(arr: &mut [i64]) -> i64 {
    let mut cost: i64 = 0;
    if arr.len() > 1 {
        quick_sort_helper(arr, 0, arr.len() - 1, &mut cost);
    }
    cost
}

fn main() {
    let mut total: i64 = 0;

    for sizes in (1..=200).rev() {
        let size = sizes * 10;
        let mut arr: Vec<i64> = (0..size).map(|i| (size - i) as i64).collect();

        total += bubble_sort(&mut arr);

        for i in 0..size {
            arr[i] = (size - i) as i64;
        }
        total += insertion_sort(&mut arr);

        for i in 0..size {
            arr[i] = (size - i) as i64;
        }
        total += merge_sort(&mut arr);

        for i in 0..size {
            arr[i] = (size - i) as i64;
        }
        total += quick_sort(&mut arr);
    }

    println!("{}", total);
}
