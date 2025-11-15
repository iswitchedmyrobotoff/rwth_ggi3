use std::env;

fn main(){
    let args: Vec<String> = env::args().collect();

    for args in &args[1..] {
        print!("{} ", args);
    }
    println!();
}

// starting with i = 1, otherwise would've started with the execution command: target/debug/myecho = argv[0]