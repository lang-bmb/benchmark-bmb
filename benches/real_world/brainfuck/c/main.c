// brainfuck - Esoteric language interpreter benchmark
// Tests interpreter overhead, loop handling, array access
// Self-contained with embedded test program

#include <stdio.h>
#include <string.h>

#define TAPE_SIZE 30000
#define MAX_PROG 10000

// Brainfuck interpreter
// Instructions: > < + - . , [ ]
void interpret(const char *program) {
    unsigned char tape[TAPE_SIZE] = {0};
    int ptr = 0;
    int pc = 0;
    int len = strlen(program);

    while (pc < len) {
        char c = program[pc];

        switch (c) {
            case '>':
                ptr++;
                if (ptr >= TAPE_SIZE) ptr = 0;  // Wrap around
                break;
            case '<':
                ptr--;
                if (ptr < 0) ptr = TAPE_SIZE - 1;  // Wrap around
                break;
            case '+':
                tape[ptr]++;
                break;
            case '-':
                tape[ptr]--;
                break;
            case '.':
                putchar(tape[ptr]);
                break;
            case ',':
                tape[ptr] = getchar();
                break;
            case '[':
                if (tape[ptr] == 0) {
                    // Jump forward to matching ]
                    int depth = 1;
                    while (depth > 0) {
                        pc++;
                        if (program[pc] == '[') depth++;
                        else if (program[pc] == ']') depth--;
                    }
                }
                break;
            case ']':
                if (tape[ptr] != 0) {
                    // Jump back to matching [
                    int depth = 1;
                    while (depth > 0) {
                        pc--;
                        if (program[pc] == ']') depth++;
                        else if (program[pc] == '[') depth--;
                    }
                }
                break;
        }
        pc++;
    }
}

// Test programs
// Hello World
const char *hello_world =
    "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]"
    ">>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";

// Nested loop benchmark (1000 iterations to match BMB)
const char *nested_loops =
    "++++++++++["              // 10 iterations
    ">++++++++++["            // 10 iterations (100 total)
    ">++++++++++["            // 10 iterations (1000 total)
    ">+<-"
    "]<-"
    "]<-"
    "]"
    ">>>[-]"                   // Clear result cell
    "++++++++[>+++++++++++<-]>." // Print 'X' (88)
    "[-]++++++++++.";             // Newline

// Simple add test
const char *add_test = "++++++++[>++++++++<-]>."; // 8 * 8 = 64 = '@'

// Run benchmark loop (no output) - v0.55: 10x for ~50ms execution
void run_benchmark_loop(int n) {
    for (int i = 0; i < n; i++) {
        interpret(hello_world);
        interpret(nested_loops);
        interpret(add_test);
    }
}

int main(void) {
    printf("Brainfuck Interpreter Benchmark\n");

    // Run Hello World (with output)
    printf("Hello World: ");
    interpret(hello_world);
    printf("\n");

    // Run nested loops benchmark (with output)
    printf("Nested loops (1000 iterations): ");
    interpret(nested_loops);
    printf("\n");

    // Run add test (with output)
    printf("Add test (8*8=@): ");
    interpret(add_test);
    printf("\n");

    // Run benchmark 10x for measurable timing (~50ms)
    run_benchmark_loop(9);

    printf("Done.\n");
    return 0;
}
