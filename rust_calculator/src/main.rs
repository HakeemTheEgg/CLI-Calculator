use std::io;

enum Operator{
    Add,
    Sub,
    Mul,
    Div,
}

fn calculate(left:f64, op:Operator, right:f64) -> Result<f64, String>{
    match op {
        Operator::Add => Ok(left + right),
        Operator::Sub => Ok(left - right),
        Operator::Mul => Ok(left * right),
        Operator::Div => {
            if right == 0.0{
                Err("division by zero".to_string())
            }
            else {
                Ok(left/right)
            }

        }
    }
}
fn parse_input(input: &str) -> Result<(f64, Operator, f64), String>{
    let tokens: Vec<&str> = input.split_whitespace().collect();
    if tokens.len() != 3{
        return Err("please enter in the format: number operator number".to_string());
    }

    let left: f64 = tokens[0]
        .parse()
        .map_err(|_| format!("invalid number: {}", tokens[0]))?;

    let op = match tokens[1]{
        "+" => Operator::Add,
        "-" => Operator::Sub,
        "*" => Operator::Mul,
        "/" => Operator::Div,
        _ => return Err(format!("invalid operator: {}", tokens[1])),
    };
    
    let right: f64 = tokens[2]
        .parse()
        .map_err(|_| format!("invalid number: {}", tokens[2]))?;

    Ok((left, op, right))
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
        
        
        }


    }