// Surpass Benchmark: Tree Balance Check (C baseline)
// Goal: BMB > C through invariant-based rebalancing skip
//
// C must check balance at runtime even when tree is always balanced
// BMB's invariants can prove balance at compile time

#include <stdio.h>
#include <stdint.h>

#define TREE_SIZE 31
#define ITERATIONS 5000

// Get tree height from node
static int tree_height(int64_t* tree, int idx) {
    if (idx >= TREE_SIZE) return 0;
    if (tree[idx] < 0) return 0;  // Empty node

    int left_h = tree_height(tree, idx * 2 + 1);
    int right_h = tree_height(tree, idx * 2 + 2);
    return 1 + (left_h > right_h ? left_h : right_h);
}

// Check if subtree is balanced
static int is_balanced(int64_t* tree, int idx) {
    if (idx >= TREE_SIZE) return 1;
    if (tree[idx] < 0) return 1;

    int left_h = tree_height(tree, idx * 2 + 1);
    int right_h = tree_height(tree, idx * 2 + 2);
    int diff = left_h > right_h ? left_h - right_h : right_h - left_h;

    if (diff > 1) return 0;
    return is_balanced(tree, idx * 2 + 1) && is_balanced(tree, idx * 2 + 2);
}

// Sum tree with balance assumption (C cannot enforce)
static int64_t sum_with_assumption(int64_t* tree, int idx) {
    if (idx >= TREE_SIZE) return 0;
    if (tree[idx] < 0) return 0;

    return tree[idx] +
           sum_with_assumption(tree, idx * 2 + 1) +
           sum_with_assumption(tree, idx * 2 + 2);
}

// Sum tree with runtime balance check
static int64_t sum_with_check(int64_t* tree, int idx) {
    if (idx >= TREE_SIZE) return 0;
    if (tree[idx] < 0) return 0;

    // Must verify balance at runtime
    if (!is_balanced(tree, idx)) return 0;

    return tree[idx] +
           sum_with_check(tree, idx * 2 + 1) +
           sum_with_check(tree, idx * 2 + 2);
}

int main() {
    // Balanced binary tree (heap array representation)
    int64_t tree[TREE_SIZE] = {
        15,          // Level 0
        7, 23,       // Level 1
        3, 11, 19, 27,   // Level 2
        1, 5, 9, 13, 17, 21, 25, 29,  // Level 3
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1  // Level 4
    };

    int64_t total_with = 0;
    int64_t total_without = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total_with += sum_with_assumption(tree, 0);
        total_without += sum_with_check(tree, 0);
    }

    printf("With assumption: %lld, With check: %lld\n",
           (long long)total_with, (long long)total_without);
    return 0;
}
