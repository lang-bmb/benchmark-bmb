// Binary Trees Benchmark
// Measures: memory allocation, tree traversal

struct Tree {
    left: Option<Box<Tree>>,
    right: Option<Box<Tree>>,
}

fn make(depth: i32) -> Box<Tree> {
    if depth <= 0 {
        Box::new(Tree { left: None, right: None })
    } else {
        Box::new(Tree {
            left: Some(make(depth - 1)),
            right: Some(make(depth - 1)),
        })
    }
}

fn check(tree: &Tree) -> i64 {
    match (&tree.left, &tree.right) {
        (Some(l), Some(r)) => 1 + check(l) + check(r),
        _ => 1,
    }
}

fn main() {
    let min_depth = 4;
    let max_depth = 17;
    let stretch_depth = max_depth + 1;

    let stretch_tree = make(stretch_depth);
    println!("stretch tree of depth {}\t check: {}", stretch_depth, check(&stretch_tree));
    drop(stretch_tree);

    let long_lived_tree = make(max_depth);

    let mut depth = min_depth;
    while depth <= max_depth {
        let iterations = 1 << (max_depth - depth + min_depth);
        let mut sum: i64 = 0;
        for _ in 0..iterations {
            let tree = make(depth);
            sum += check(&tree);
        }
        println!("{}\t trees of depth {}\t check: {}", iterations, depth, sum);
        depth += 2;
    }

    println!("long lived tree of depth {}\t check: {}", max_depth, check(&long_lived_tree));
}
