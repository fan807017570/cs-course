use std::io;
use std::cmp::Ordering;
use rand::Rng;
fn main() {
   println!("Guess the number~");
   let scret_number = rand::thread_rng().gen_range(1..=100);
   println!("The scret number is :{scret_number}");

   loop {
       println!("Please input your guess .");
       let mut guess = String::new();
       io::stdin()
           .read_line(&mut guess)
           .expect("Failed to read line from stdin");
    
        println!("You gussed :{guess}");
        let guess: u32 = match guess.trim().parse(){
        }

       match guess.cmp(&scret_number){

            Ordering::Less => println!("Too small"),

            Ordering::Greater => println!("Too big"),

            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
}
