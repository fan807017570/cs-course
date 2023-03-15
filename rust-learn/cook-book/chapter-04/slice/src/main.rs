fn main() {
    let text = String::from("hello fananran do you konw me ");
    let slice = first_word(&text);
    let first = &text[0..slice];
    println!("The first word is :{}", first);
}
fn first_word(s: &String) -> usize {
    let bytes = s.as_bytes();
    for (i, &element) in bytes.iter().enumerate() {
        if element == b' ' {
            return i;
        }
    }
    return s.len();
}
