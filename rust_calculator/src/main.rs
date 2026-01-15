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
        
        let tokens: Vec<&str> = input.split_whitespace().collect();
        
        if tokens.len() !=3{
            println!("invalid expression. please enter in the format: number operator number");
            continue;
        }

        let left = tokens[0];
        let operator = tokens[1];
        let right = tokens[2];

        println!("you entered: {} {} {}", left, operator, right);


        }
        }