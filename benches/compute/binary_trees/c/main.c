// Binary trees benchmark
// Measures: memory allocation, recursion

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
} Node;

Node* make_tree(int depth) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (depth > 0) {
        node->left = make_tree(depth - 1);
        node->right = make_tree(depth - 1);
    } else {
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

long check_tree(Node* node) {
    if (node->left == NULL) return 1;
    return 1 + check_tree(node->left) + check_tree(node->right);
}

void free_tree(Node* node) {
    if (node->left != NULL) {
        free_tree(node->left);
        free_tree(node->right);
    }
    free(node);
}

int main() {
    int min_depth = 4;
    int max_depth = 14;  // Aligned with BMB version for fair comparison
    int stretch_depth = max_depth + 1;

    Node* stretch = make_tree(stretch_depth);
    printf("%ld\n", check_tree(stretch));
    free_tree(stretch);

    Node* long_lived = make_tree(max_depth);

    long total = 0;
    for (int depth = min_depth; depth <= max_depth; depth += 2) {
        int iterations = 1 << (max_depth - depth + min_depth);
        long check = 0;
        for (int i = 0; i < iterations; i++) {
            Node* tree = make_tree(depth);
            check += check_tree(tree);
            free_tree(tree);
        }
        printf("%ld\n", check);
        total += check;
    }

    long long_check = check_tree(long_lived);
    printf("%ld\n", long_check);
    free_tree(long_lived);

    printf("%ld\n", total + long_check);

    return 0;
}
