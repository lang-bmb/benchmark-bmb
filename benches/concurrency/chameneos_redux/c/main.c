// Chameneos-Redux - Symmetric thread rendezvous benchmark
// Reference: Computer Language Benchmarks Game
//
// This is a simplified single-threaded simulation
// Full benchmark uses pthreads for symmetric rendezvous

#include <stdio.h>
#include <stdlib.h>

typedef enum { BLUE = 0, RED = 1, YELLOW = 2 } Color;

const char* color_name(Color c) {
    switch (c) {
        case BLUE: return "blue";
        case RED: return "red";
        case YELLOW: return "yellow";
    }
    return "unknown";
}

Color complement(Color c1, Color c2) {
    if (c1 == c2) return c1;

    switch (c1) {
        case BLUE:
            return (c2 == RED) ? YELLOW : RED;
        case RED:
            return (c2 == BLUE) ? YELLOW : BLUE;
        case YELLOW:
            return (c2 == BLUE) ? RED : BLUE;
    }
    return BLUE;
}

typedef struct {
    Color color;
    int meetings;
    int self_meetings;
} Creature;

void run_meetings(Creature *creatures, int num_creatures, int num_meetings) {
    int meetings_left = num_meetings;
    int idx1 = 0, idx2 = 1;

    while (meetings_left > 0) {
        Color c1 = creatures[idx1].color;
        Color c2 = creatures[idx2].color;
        Color new_color = complement(c1, c2);

        creatures[idx1].color = new_color;
        creatures[idx2].color = new_color;
        creatures[idx1].meetings++;
        creatures[idx2].meetings++;

        if (idx1 == idx2) {
            creatures[idx1].self_meetings++;
        }

        idx1 = (idx1 + 1) % num_creatures;
        idx2 = (idx2 + 1) % num_creatures;
        if (idx1 == idx2) {
            idx2 = (idx2 + 1) % num_creatures;
        }

        meetings_left--;
    }
}

int run_first_set(int num_meetings) {
    Creature creatures[3] = {
        {BLUE, 0, 0},
        {RED, 0, 0},
        {YELLOW, 0, 0}
    };

    printf("%s %s %s\n", color_name(BLUE), color_name(RED), color_name(YELLOW));

    run_meetings(creatures, 3, num_meetings);

    int total = 0;
    for (int i = 0; i < 3; i++) {
        printf("%d %d\n", creatures[i].meetings, creatures[i].self_meetings);
        total += creatures[i].meetings;
    }
    printf("%d\n", total);

    return total;
}

int run_second_set(int num_meetings) {
    Color colors[10] = {BLUE, RED, YELLOW, RED, YELLOW, BLUE, RED, YELLOW, RED, BLUE};
    Creature creatures[10];

    for (int i = 0; i < 10; i++) {
        creatures[i].color = colors[i];
        creatures[i].meetings = 0;
        creatures[i].self_meetings = 0;
        printf("%s ", color_name(colors[i]));
    }
    printf("\n");

    run_meetings(creatures, 10, num_meetings);

    int total = 0;
    for (int i = 0; i < 10; i++) {
        printf("%d %d\n", creatures[i].meetings, creatures[i].self_meetings);
        total += creatures[i].meetings;
    }
    printf("%d\n", total);

    return total;
}

int main(int argc, char *argv[]) {
    int num_meetings = 600;
    if (argc > 1) {
        num_meetings = atoi(argv[1]);
    }

    // Print complement table
    printf("%s + %s -> %s\n", color_name(BLUE), color_name(BLUE), color_name(complement(BLUE, BLUE)));
    printf("%s + %s -> %s\n", color_name(BLUE), color_name(RED), color_name(complement(BLUE, RED)));
    printf("%s + %s -> %s\n", color_name(BLUE), color_name(YELLOW), color_name(complement(BLUE, YELLOW)));
    printf("\n");

    run_first_set(num_meetings);
    printf("\n");
    run_second_set(num_meetings);

    return 0;
}
