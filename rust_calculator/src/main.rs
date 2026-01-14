use std::io;

fn main(){
    println!("rust calculator");
    println!("Enter an expression: ");
    println!("type exit to quit");

    
    loop{

        let mut input = String::new();
        println!("> ");
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");

        let input = input.trim();
        if input == "exit"{
            break;
        }
        }


    println!("you typed: {}", input);
    }