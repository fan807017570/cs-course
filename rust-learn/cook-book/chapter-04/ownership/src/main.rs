fn main() {
    copy_string();
    deep_copy_string();
    let s = String::from("hello");

    take_ownship(s);

    let x = 5;

    make_copy(x);

    let gs1 = gieves_ownership();

    let gs2 = String::from("hello");
    println!("gs2 = {gs2}");

    let gs3 = takes_and_gives_back(gs2);
    println!("gs1={gs1},gs3={gs3}");
    //println!("s={s}");
    let as1 = String::from("lenght");

    let (as2, len) = calculate_length(as1);

    println!("The length of {} is {}", as2, len);

    let rs1 = String::from("Reference");

    let rlen = caculate_length_reference(&rs1);

    println!("{}'s length is {}", rs1, rlen);

    let mut cs1 = String::from("hello ");
    change_function(&mut cs1);
    println!("input string is :{}", cs1);
}
fn copy_string() {
    let s1 = String::from("hello");
    let mut s2 = s1; // s1 is invalid
    s2.push_str("world"); // s2 is valid
    println!("string s2's content is :{s2}"); // if it goes out of the scope ,s2's memory will be freed by drop()
}
fn deep_copy_string() {
    let s1 = String::from("hello");

    let mut s2 = s1.clone(); // this statment is expensive

    s2.push_str(" world");

    println!("s1={s1}, s2= {s2}")
}
fn take_ownship(some_string: String) {
    println!("{}", some_string);
}

fn make_copy(some_integer: i32) {
    println!("{}", some_integer);
}

fn gieves_ownership() -> String {
    let some_string = String::from("yours");
    some_string
}

fn takes_and_gives_back(a_string: String) -> String {
    a_string
}
fn calculate_length(a_string: String) -> (String, usize) {
    let len = a_string.len();
    (a_string, len)
}

fn caculate_length_reference(some_string: &String) -> usize {
    some_string.len()
}

fn change_function(some_string: &mut String) {
    some_string.push_str(",world");
}
