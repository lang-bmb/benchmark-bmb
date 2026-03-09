// Trie insert and search benchmark — flat array trie with 26 children per node
// Measures: pointer chasing, random memory access, branching
// Workload: 50000 inserts + 50000 searches, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Trie node layout (flat array):
// Each node = 27 slots: children[0..25] + is_end
// Node i starts at offset i * 27
// children[c] = index of child node (0 = no child)
// is_end = 1 if word ends here

#define NODE_SIZE 27
#define MAX_NODES 600000

static void trie_init(int64_t* trie, int64_t* next_node) {
    // Clear root node
    for (int64_t i = 0; i < NODE_SIZE; i++) {
        trie[i] = 0;
    }
    *next_node = 1;
}

static void trie_insert(int64_t* trie, int64_t* next_node,
                         const int64_t* word, int64_t len) {
    int64_t node = 0;
    for (int64_t i = 0; i < len; i++) {
        int64_t c = word[i];
        int64_t child_idx = node * NODE_SIZE + c;
        if (trie[child_idx] == 0) {
            int64_t new_node = *next_node;
            *next_node = new_node + 1;
            // Clear new node
            for (int64_t j = 0; j < NODE_SIZE; j++) {
                trie[new_node * NODE_SIZE + j] = 0;
            }
            trie[child_idx] = new_node;
        }
        node = trie[child_idx];
    }
    trie[node * NODE_SIZE + 26] = 1;  // mark end
}

static int64_t trie_search(const int64_t* trie, const int64_t* word, int64_t len) {
    int64_t node = 0;
    for (int64_t i = 0; i < len; i++) {
        int64_t c = word[i];
        int64_t child = trie[node * NODE_SIZE + c];
        if (child == 0) return 0;
        node = child;
    }
    return trie[node * NODE_SIZE + 26];
}

int main() {
    int64_t NUM_WORDS = 50000;
    int64_t ITERS = 200;
    int64_t MAX_WORD_LEN = 10;

    int64_t* trie = (int64_t*)malloc((int64_t)MAX_NODES * NODE_SIZE * sizeof(int64_t));
    int64_t* words = (int64_t*)malloc(NUM_WORDS * MAX_WORD_LEN * sizeof(int64_t));
    int64_t* word_lens = (int64_t*)malloc(NUM_WORDS * sizeof(int64_t));

    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 77777 + iter;

        // Generate random words (length 5-10, chars 0-25)
        for (int64_t w = 0; w < NUM_WORDS; w++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t wlen = 5 + (seed % 6);  // 5 to 10
            word_lens[w] = wlen;
            for (int64_t c = 0; c < wlen; c++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                words[w * MAX_WORD_LEN + c] = seed % 26;
            }
        }

        // Initialize trie and insert all words
        int64_t next_node;
        trie_init(trie, &next_node);
        for (int64_t w = 0; w < NUM_WORDS; w++) {
            trie_insert(trie, &next_node, &words[w * MAX_WORD_LEN], word_lens[w]);
        }

        // Search for all words (all should be found)
        int64_t found = 0;
        for (int64_t w = 0; w < NUM_WORDS; w++) {
            found += trie_search(trie, &words[w * MAX_WORD_LEN], word_lens[w]);
        }
        checksum += found;
    }

    printf("%lld\n", (long long)checksum);
    free(trie);
    free(words);
    free(word_lens);
    return 0;
}
