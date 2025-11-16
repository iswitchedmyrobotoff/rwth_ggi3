use std::env;

fn main(){
    let mut counter = 0;

    for(key, value) in env::vars(){
        println!("{}={}", key, value);
        counter += 1;
    }
    
    println!("Amount of variables set = {}", counter);
}