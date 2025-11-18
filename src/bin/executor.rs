use std::env;
use std::ffi::{CString};
use std::io::{self, Write};
use libc::{fork, execl, waitpid, c_char, pid_t};

fn split_args(line: &str) -> Vec<String>{
    line.split_whitespace()
        .map(|s| s.to_string())
        .collect()
}


fn main(){
    //read path and prompt and set to default if NULL
    let mypath = env::var("MYPATH").unwrap_or("/bin".to_string());
    let myprompt = env::var("MYPROMPT").unwrap_or("> ".to_string());

    //print path
    print!("{}", myprompt);
    io::stdout().flush().unwrap();

    //read line
    let mut scanline = String::new();

    if io::stdin().read_line(&mut scanline).is_err() {
            println!("exit");
            return;
        }

    //ask againg if its only newline    
    if scanline.trim().is_empty() {
        continue;
    }

    let scanline = scanline.trim();

    //exit command
    if scanline == "exit" {
        return;
    }

    //split args
    let args = split_args(scanline);
    let cmd = &args[0];

    //path to run /bin/cmd
    let fullpath = format!("{}/{}", mypath, cmd);

    //convert to c strings
    let c_path = CString::new(fullpath.clone()).unwrap();

    //execl arguments
    let mut c_args: Vec<CString> = args.iter().map(|a| CString::new(a.as_str()).unwrap()).collect();
    c_args.push(CString::new("").unwrap()); // NULL terminator için

    //wrap them all arguments up to c pointer
    let mut ptrs: Vec<*const c_char> = c_args.iter().map(|s| s.as_ptr()).collect();
    ptrs.push(std::ptr::null());

    unsafe {
        // fork()
        let pid: pid_t = fork();

        if pid == 0 {
            // Child process
            println!("Hello from Childprocess, start: {}", fullpath);
            execl(
                c_path.as_ptr(),
                ptrs[0],
                ptrs[1],
                ptrs[2],
                ptrs[3],
                std::ptr::null::<c_char>(),
            );
            // fail case:
            std::process::exit(-1);
        } else {
            // Parent process
            println!("Hello from Mainprocess, the Childprocess is {}.", pid);
            waitpid(pid, std::ptr::null_mut(), 0);
        }
    }
}
