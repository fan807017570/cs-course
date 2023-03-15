fn main() {
    operator_function();
    another_function(); 
    char_function();
    tuple_function();
}

fn another_function(){
    println!("another_function");
}
fn operator_function(){
    let sum = 5+10;
    println!("5+ 10 ={sum}");
    let difference = 95.5 -4.3;
    println!("95.5 - 4.3 = {difference}");

    let product = 4 * 30;
    println!("4 * 30 = {product}");


    let quatient = 56.7/32.2;
    println!("56.7 / 32.2={quatient}");

    let floored = 1/3;
    println!("1/3={floored}");

    let remainder = 43 % 5 ;
    println!("43 % 5={remainder}");
}
fn char_function(){
    let c = 'z';
    let z:char = '在';
    let heart_eyed_cat = '🥫';
    println!("c={},z={},heart_eyed_cat={}",c,z,heart_eyed_cat);
}

fn tuple_function(){
    let tup = (500,6.4,1);
    let tup: (i32,f64,u8)= (500,6.4,1);
    let (x,y,z) = tup;
    println!("The value of y is :{y}");
}
fun tuple_destruct(){
    let x:(i32,f64,u8) = (500,7.7,1);
    let five_hundred =  x.0;

    let six_point_four = x.1;


    let one = x.2 ;
    
    println!("five_hundred = {five_hundred},six_point_four={six_point_four},one={one}");
}
