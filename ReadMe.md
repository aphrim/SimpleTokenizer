## TOKENIZER

A simple, easy to understand, and easy to expand tokenizer.
Easy to add new keywords, tokens and more.
Stores a token in a token struct, which is just an enum + an ```std::vector<uint8_t>```. A token can store an infinite amount of data with it, for example a string or a number.
Supports basic string escaping and such.

Example input/output:
```
> (10 * 69420 + "Hello World"    
TOKEN_LEFT_PAREN
TOKEN_NUMER: 10
TOKEN_MULTIPLY
TOKEN_NUMER: 69420
TOKEN_PLUS
TOKEN_STRING: Hello World
TOKEN_EOF
```
```
>if(true) { print("Hello World") }
TOKEN_IF
TOKEN_LEFT_PAREN
TOKEN_TRUE
TOKEN_RIGHT_PAREN
TOKEN_LEFT_BRACKET
TOKEN_VARIABLE: print
TOKEN_LEFT_PAREN
TOKEN_STRING: Hello World
TOKEN_RIGHT_PAREN
TOKEN_RIGHT_BRACKET
TOKEN_EOF
```

```
>print(10,100,"The program says \"Hello World\"")
TOKEN_VARIABLE: print
TOKEN_LEFT_PAREN
TOKEN_NUMER: 10
TOKEN_COMMA
TOKEN_NUMER: 100
TOKEN_COMMA
TOKEN_STRING: The program says "Hello World"
TOKEN_RIGHT_PAREN
TOKEN_EOF
```

## Building and running

### Linux

Requires cmake installed.
```cmake .```
```make```
and then run ./tokenizer.exe.

### Windows

Requires cmake installed.
```cmake .```
Then use your build tool to build using the makefile.
Run the output.

## Modifing.

### Adding a token

Step 1: Add the token to token.hpp
Step 2: Modify the scanner to support the token.
Step 3: Add it to the debugger.

### Accessing token data

Token data is stored in the tokens data member as a vector of uint8_t.
Currently this supports storing of strings and numbers, but adding other datatypes should be quite trivial.
Example of how to access int stored in data, where data is the ```std::vector<uint8_t>```
```
int* loc = (int*)(&data[0]);
std::cout << *loc << std::endl;
```
Example of how to access string stored in data, where data is the ```std::vector<uint8_t>```
```
std::cout << "TOKEN_STRING: ";
for (uint8_t c : data) {
	std::cout << (char) c;
}
```


