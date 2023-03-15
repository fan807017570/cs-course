fn main() {
    another_function(56);
    print_labeld_measurement(51,'y');
    let x = statement_function();
    println!("return value is :{x}");
    println!("plus one result is :{}",plus_one(8));
    condition_function();
    multi_branch_function();
    real_condition_function();
    loop_function();
    multi_loop_function();
    while_loop_function();
    for_loop_function();
    reverse_loop_function();
}
fn another_function(x: i32){
    println!("The value of x is :{x}");
}  
fn print_labeld_measurement(value :i32,unit_label:char){
    println!("The measurement is :{value}{unit_label}");
}
fn statement_function()-> i32 {
    5
}
fn plus_one(value: i32) -> i32 {
     value +1
}
fn condition_function(){
    let number = 3;
    if number < 5 {
        println!("Condition was true");
    }else{
        println!("Condition was false");
    }
}
fn multi_branch_function(){
    let number =6;
    if number % 4 == 0{
        println!("Number is divisible by 4");
    } else if number % 3 == 0 {
        println!("Number is divisible by 3");
    } else if number % 2 == 0{
        println!("Number is divisible by 2");
    }else{
        println!("Number is not divisible by 4,3,or 2");
    }
}
fn real_condition_function(){
    let condition = true;
    let number = if condition { 5 } else { 6 };

    println!("The value of number is: {number}");
}
fn loop_function(){
    let mut  counter = 0;
    let result = loop{
        counter +=1;
        if counter == 10{
            break counter*2;
        }
    };
    println!("The result is :{result}");
}
fn multi_loop_function(){
    let mut count = 0;
    'counting_up: loop{
        println!("count ={count}");
        let mut  remaining = 10;
        loop {
            println!("reminning = {remaining}");
            if remaining ==9 {
                break;
            }
            if count == 2 {
                break 'counting_up;
            }
            remaining -=1;
        }
        count += 1;
    }
    println!("End count = {count}");
}
fn while_loop_function(){
    let a = [10,20,30,40,50];

    let mut index = 0;
    while index < 5 {
        println!("The value si :{}",a[index]);
        index +=1;
    }
}

fn for_loop_function(){
    let a = [10,20,30,40,50];
    for elemetn in a {
        println!("The value is :{elemetn}");
    }
} 
fn reverse_loop_function(){
    for number in (1..4).rev(){
        println!("{number}");
    }
    println!("LIETOFF!!!");
}
