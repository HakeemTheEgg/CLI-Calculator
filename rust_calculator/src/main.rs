use std::io;

enum Operator{
    Add,
    Sub,
    Mul,
    Div,
}

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
        
        let tokens: Vec<&str> = input.split_whitespace().collect();//creates a vector of string slices that are separated by whitespace
        
        if tokens.len() !=3{
            println!("invalid expression. please enter in the format: number operator number");
            continue;
        }
        //splits the vector into three tokens
        let left = tokens[0];
        let op = tokens[1];
        let right = tokens[2];

        let operator = match op{
            "+" => Operator::Add,
            "-" => Operator::Sub,
            "*" => Operator::Mul,
            "/" => Operator::Div,
            _ => {
                println!("invalid operator. please use one of +, -, *, /");
                continue;
            }
        };

        let left: f64 = match left.parse(){
            Ok(num) => num,
            Err(_) => {
                println!("invalid number: {}", left);
                continue;
            }
        };

        let right: f64 = match right.parse(){
            Ok(num) => num,
            Err(_) => {
                println!("invalid number: {}", right);
                continue;
            }
        };

        let result = match operator{
            Operator::Add => left + right,
            Operator::Sub => left - right,
            Operator::Mul => left * right,
            Operator::Div => {
                if right == 0.0{
                    println!("error: division by zero");
                    continue;
                }else{
                    left / right
                }
            }
        };


        println!("results: {} ", result);


        }
        }