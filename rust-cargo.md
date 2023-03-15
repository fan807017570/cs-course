##### cargo command line 

- cargo

  cargo build 

  cargo update 

  cargo run 

  cargo doc --open 

  cargo new  'project-name'

- Cargo.toml

  ```
  [package]                                                                                                         
    2 name = "guessing_game"
    3 version = "0.1.0"
    4 edition = "2021"
    5  
    6 # See more keys and their definitions at https://doc.rust-lang.org/cargo/reference/manifest.html
    7  
    8 [dependencies]
    9 rand="0.8.3"   # add dependencies crate append last line 
  
  ```

  

- Cargo.lock

- ##### language 

  - immutable and mutable 

  - match expression 

  - use std::io / use Range::range import the header

  - exptect() method 

    ```
    ```

    

  - constants 

    You are not allowed to use mut before constans 

    ```rust
    const  THREE_HOURS_IN_SECONDS :u32 = 60*60*30;
    ```

    

  - mut and shadowing 

    use 'let' to shadow the first variable
  
    ```rust
    let x = 10;
    let x = x+1; # x = 11 ,a new variable
    ```
  
    use  mut to make the variable be mutable
  
    ```rust
    let mut x = 10;
    x = 11;  # if remove the 'mut' this line will occur compiler error.
    ```
  
    
  
  - Data Types
  
    - Rust is a staticially typed language ,which means that it must know the types of all variables at compile time .
  
      ```rust
      let guess: u32 = "23".parse().expect("Not a number"); # if remove the u32 ,the compiler will throw error.
      
      ```
  
      
  
    - char
  
      ust’s `char` type is four bytes in size and represents a Unicode Scalar Value, which means it can represent a lot more than just ASCII. Accented letters; Chinese, Japanese, and Korean characters; emoji; and zero-width spaces are all valid `char` values in Rust. 
  
      ```
      fn main() {
          let c = 'z';
          let z: char = 'ℤ'; // with explicit type annotation
          let heart_eyed_cat = '😻';
      }
      ```
  
      
  
    - Compound Types 
  
      - The Tuple Type
  
         
  
      - The Array Type 
  
        - Arrays in rust have a fixed length 
  
        - Define an array's type using square brackets with the type of each element.
  
          ```rust
          let a: [i32;5]= [1,2,3,4,5] # means 5 i32 elements in the array.
          ```
  
        - Define the same value in array 
  
          ```rust
          let a: [3;4]=[3,3,3,3]
          ```
  
        - Accessing array elements 
  
          
  
        - 
  
    - Function 
  
      - how to define a function 
  
        We define a function in Rust by entring 'fn' followed by a function name and a set of parentheres . The curly brackets tell the compiler where the function body begins and ends.
  
        ```rust
        fn  application_start(){
         # function body 
        }
        ```
  
        
  
      - Return values from loops 
  
        
  
      - Loop labels to disambiguate between multiple loops 
  
        ```rust
        fn main() {
            let mut count = 0;
            'counting_up: loop { // 注意是单引号
                println!("count = {count}");
                let mut remaining = 10;
        
                loop {
                    println!("remaining = {remaining}");
                    if remaining == 9 {
                        break;
                    }
                    if count == 2 {
                        break 'counting_up;
                    }
                    remaining -= 1;
                }
        
                count += 1;
            }
            println!("End count = {count}");
        }
        ```
  
        
  
      - 
  
  - Understanding Ownership 
  
    - Ownership Rules
  
      - Each value in Rust has an owner .
      - There can only be one owner at a time
      - When the owner goes out of scope ,the value will be droped 
  
    - String type 
  
      
  
    - References and Borrowing 
  
      - Dangling Refrence
  
        A pointer that references a location in memory that may have been given to someone else -by freeing some memory while preserving a pointer to that memory . In rust ,the compiler guarantees that references will never be dangling references .
  
        Dangling pointer in C/C++ 
  
        ```c++
        #include<iostream>
        
        using namespace std;
        
        int *fun(){
            int x = 5;
            return &x;
        }
        int main(){
            int *p = fun();
            fflush(stdin);
        	/* p is a dangling pointer ,you can change the x  to static to fix this problem*/	    
            cout<< *p<<endl;
            return 0;
        }
        
        ```
  
        Same Code in Rust (Compiler prevent these  problem)
  
        ```rust
        fn main(){
         let reference_to_nothing= dangle();
        }
        fn dangle()->&String{
          let s = String::from("hello");
          &s 
        } //Here, s goes out of scope, and is dropped. Its memory goes away.
        ```
  
        
  
      - At any time ,you can have either one mutable reference or any number os immutable refeencese 
  
      - References must always be valid.
  
    - The Slice Type
  
    - 
  
    - 

