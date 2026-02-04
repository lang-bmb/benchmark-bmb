// Brainfuck Interpreter Benchmark
// Tests interpreter overhead, loop handling, array access

const TAPE_SIZE: usize = 30000;

fn interpret(program: &[u8]) {
    let mut tape = [0u8; TAPE_SIZE];
    let mut ptr: usize = 0;
    let mut pc: usize = 0;
    let len = program.len();

    while pc < len {
        match program[pc] {
            b'>' => {
                ptr += 1;
                if ptr >= TAPE_SIZE {
                    ptr = 0;
                }
            }
            b'<' => {
                if ptr == 0 {
                    ptr = TAPE_SIZE - 1;
                } else {
                    ptr -= 1;
                }
            }
            b'+' => {
                tape[ptr] = tape[ptr].wrapping_add(1);
            }
            b'-' => {
                tape[ptr] = tape[ptr].wrapping_sub(1);
            }
            b'.' => {
                print!("{}", tape[ptr] as char);
            }
            b',' => {
                // Skip input in benchmark
            }
            b'[' => {
                if tape[ptr] == 0 {
                    let mut depth = 1;
                    while depth > 0 {
                        pc += 1;
                        if program[pc] == b'[' {
                            depth += 1;
                        } else if program[pc] == b']' {
                            depth -= 1;
                        }
                    }
                }
            }
            b']' => {
                if tape[ptr] != 0 {
                    let mut depth = 1;
                    while depth > 0 {
                        pc -= 1;
                        if program[pc] == b']' {
                            depth += 1;
                        } else if program[pc] == b'[' {
                            depth -= 1;
                        }
                    }
                }
            }
            _ => {}
        }
        pc += 1;
    }
}

const HELLO_WORLD: &[u8] = b"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";

const NESTED_LOOPS: &[u8] = b"++++++++++[>++++++++++[>++++++++++[>+<-]<-]<-]>>>[-]++++++++[>+++++++++++<-]>.[-]++++++++++.";

const ADD_TEST: &[u8] = b"++++++++[>++++++++<-]>.";

fn run_benchmark_loop(n: i32) {
    for _ in 0..n {
        interpret(HELLO_WORLD);
        interpret(NESTED_LOOPS);
        interpret(ADD_TEST);
    }
}

fn main() {
    println!("Brainfuck Interpreter Benchmark");
    print!("Hello World: ");
    interpret(HELLO_WORLD);
    println!();
    print!("Nested loops (1000 iterations): ");
    interpret(NESTED_LOOPS);
    println!();
    print!("Add test (8*8=@): ");
    interpret(ADD_TEST);
    println!();
    run_benchmark_loop(9);
    println!("Done.");
}
