// brainfuck - Esoteric language interpreter benchmark
// Tests interpreter overhead, loop handling, array access
// Self-contained with embedded test program

use std::io::{self, Read, Write};

const TAPE_SIZE: usize = 30000;

/// Brainfuck interpreter
/// Instructions: > < + - . , [ ]
fn interpret(program: &[u8]) {
    let mut tape = vec![0u8; TAPE_SIZE];
    let mut ptr: usize = 0;
    let mut pc: usize = 0;

    while pc < program.len() {
        match program[pc] {
            b'>' => {
                ptr = (ptr + 1) % TAPE_SIZE;
            }
            b'<' => {
                ptr = if ptr == 0 { TAPE_SIZE - 1 } else { ptr - 1 };
            }
            b'+' => {
                tape[ptr] = tape[ptr].wrapping_add(1);
            }
            b'-' => {
                tape[ptr] = tape[ptr].wrapping_sub(1);
            }
            b'.' => {
                print!("{}", tape[ptr] as char);
                let _ = io::stdout().flush();
            }
            b',' => {
                let mut buf = [0u8; 1];
                if io::stdin().read(&mut buf).is_ok() {
                    tape[ptr] = buf[0];
                }
            }
            b'[' => {
                if tape[ptr] == 0 {
                    // Jump forward to matching ]
                    let mut depth = 1;
                    while depth > 0 {
                        pc += 1;
                        match program[pc] {
                            b'[' => depth += 1,
                            b']' => depth -= 1,
                            _ => {}
                        }
                    }
                }
            }
            b']' => {
                if tape[ptr] != 0 {
                    // Jump back to matching [
                    let mut depth = 1;
                    while depth > 0 {
                        pc -= 1;
                        match program[pc] {
                            b']' => depth += 1,
                            b'[' => depth -= 1,
                            _ => {}
                        }
                    }
                }
            }
            _ => {}
        }
        pc += 1;
    }
}

// Test programs
const HELLO_WORLD: &[u8] = b"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";

// Nested loops (1000 iterations to match BMB)
const NESTED_LOOPS: &[u8] = b"++++++++++[>++++++++++[>++++++++++[>+<-]<-]<-]>>>[-]++++++++[>+++++++++++<-]>.[-]++++++++++.";

// Simple add test
const ADD_TEST: &[u8] = b"++++++++[>++++++++<-]>."; // 8 * 8 = 64 = '@'

fn main() {
    println!("Brainfuck Interpreter Benchmark");

    // Run Hello World
    print!("Hello World: ");
    interpret(HELLO_WORLD);
    println!();

    // Run nested loops benchmark
    print!("Nested loops (1000 iterations): ");
    interpret(NESTED_LOOPS);
    println!();

    // Run add test
    print!("Add test (8*8=@): ");
    interpret(ADD_TEST);
    println!();

    println!("Done.");
}
