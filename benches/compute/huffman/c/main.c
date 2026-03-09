// Huffman encoding benchmark — frequency counting + priority queue + tree build
// Measures: array access, sorting, tree construction, encoding
// Workload: 100K character messages, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ALPHA 26

// Simple min-heap for Huffman
static void heap_swap(int64_t* freq, int64_t* idx, int64_t a, int64_t b) {
    int64_t tf = freq[a]; freq[a] = freq[b]; freq[b] = tf;
    int64_t ti = idx[a]; idx[a] = idx[b]; idx[b] = ti;
}

static void heap_up(int64_t* freq, int64_t* idx, int64_t i) {
    while (i > 0) {
        int64_t p = (i - 1) / 2;
        if (freq[i] < freq[p]) { heap_swap(freq, idx, i, p); i = p; }
        else break;
    }
}

static void heap_down(int64_t* freq, int64_t* idx, int64_t size, int64_t i) {
    while (1) {
        int64_t smallest = i;
        int64_t l = 2 * i + 1, r = 2 * i + 2;
        if (l < size && freq[l] < freq[smallest]) smallest = l;
        if (r < size && freq[r] < freq[smallest]) smallest = r;
        if (smallest == i) break;
        heap_swap(freq, idx, i, smallest);
        i = smallest;
    }
}

static int64_t huffman_encode(const int64_t* msg, int64_t len) {
    // Count frequencies
    int64_t counts[ALPHA] = {0};
    for (int64_t i = 0; i < len; i++) counts[msg[i]]++;

    // Build heap
    int64_t heap_freq[ALPHA * 2];
    int64_t heap_idx[ALPHA * 2];
    int64_t heap_size = 0;

    for (int64_t i = 0; i < ALPHA; i++) {
        if (counts[i] > 0) {
            heap_freq[heap_size] = counts[i];
            heap_idx[heap_size] = i;
            heap_up(heap_freq, heap_idx, heap_size);
            heap_size++;
        }
    }

    // Build Huffman tree (combine two smallest)
    int64_t total_bits = 0;
    while (heap_size > 1) {
        // Extract two minimums
        int64_t f1 = heap_freq[0];
        heap_freq[0] = heap_freq[--heap_size];
        heap_idx[0] = heap_idx[heap_size];
        heap_down(heap_freq, heap_idx, heap_size, 0);

        int64_t f2 = heap_freq[0];
        heap_freq[0] = heap_freq[--heap_size];
        heap_idx[0] = heap_idx[heap_size];
        heap_down(heap_freq, heap_idx, heap_size, 0);

        // Combine
        int64_t combined = f1 + f2;
        total_bits += combined;
        heap_freq[heap_size] = combined;
        heap_idx[heap_size] = -1;
        heap_up(heap_freq, heap_idx, heap_size);
        heap_size++;
    }

    return total_bits;
}

int main() {
    int64_t LEN = 100000;
    int64_t ITERS = 200;
    int64_t* msg = (int64_t*)malloc(LEN * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 9999 + iter;
        for (int64_t i = 0; i < LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            // Non-uniform distribution (more realistic)
            int64_t r = seed % 100;
            if (r < 40) msg[i] = seed % 5;        // 40% in first 5 chars
            else if (r < 70) msg[i] = 5 + seed % 5; // 30% in next 5
            else msg[i] = 10 + seed % 16;            // 30% in remaining 16
        }
        checksum += huffman_encode(msg, LEN);
    }

    printf("%lld\n", (long long)checksum);
    free(msg);
    return 0;
}
