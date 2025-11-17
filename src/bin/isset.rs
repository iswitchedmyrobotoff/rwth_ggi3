use std::env;
use std::process;

fn main(){

    let args: Vec<String>= env::args().collect();
    let mut verbose = false;

    if args.len() < 2 {
        println!("No parameter was given!");
        process::exit(1);
    }

    if args.len() > 2 && args[1] == "-v" {
        verbose = true;
    }

    if args.len() > (2 + verbose as usize) {
        println!("Only one variable is checkable at a time!");
        process::exit(2);
    }


    // key is either args[1] (no verbose) or args[2] (with verbose)
    let key_index = 1 + verbose as usize;
    let key = &args[key_index];
    let value = env::var(key).ok();

    match(value, verbose){
        (Some(v), true) => {
            println!("{} is set with value = {}", key, v);
            process::exit(0);
        }
        (Some(_), false) => {
            println!("Given variable '{}' is set.", key);
            process::exit(0);
        }
        (None, _) => {
            println!("Given variable '{}' is not set.", key);
            process::exit(1);
        }
    }
}