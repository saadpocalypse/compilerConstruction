# Assignment 1 (Lexical Analyzer)

## Assignment Statement
Create a lexical analyzer without using any existing code or tool. Your code should be in C and it should support the constructs listed below.

| Keyword/Operation      | Description |
| ----------- | ----------- |
| +, -, *, /     | Adding, subtracting and multiplying floats      |
| >, >=, <, <=, !=, \|\|, &&, =, ==  | To compare two float values      |
| if     | Conditional branching      |
| while  | Conditional loop       |
| break    | Exit from a conditional loop     |
| print | Prints a float value    |
| (, )     | Start or end of an 'if' condition or a while loop       |
| {, }  | Start and end of a comparison statement      |


## Rules
1. Only float data type is supported.
2. Float values may be stored in identifiers.
3. Valid identifers start with a letter and can be followed by any combination of letters and/or numbers.
4. New line is considered the end of the line, no restrictions are to be applied for a semi-colon.

## Programming Guidelines
Your program must read the input file character by character and use the characters to fill up an input buffer. Two pointers should be used to keep track of each lexeme generated. Your major function should be a DFASimulator, which eaither accepts or rejects the lexemes as valid tokens. DFAs can be easily implemented using transition tables. Each valid token must be enlisted in a symbol table. The generated output file should contain all the tokens from the input code.

## Input
Your input should be a .txt file which has code in it.
```
endAt = 7 // Note that an identifier is used without definition.
         // Also note that there is no semicolon.
         
startFrom = 0
fibLast = 1
fibSecondLast = 1
while (start From < endAt){
fibNext = fibLast + fibSecondLast
fibSecondLast = fibLast
fibLast = fibNext
startFrom = startFrom + 1
}

print(fib last) //prints the value of seventh digit
               // of the Fibonacci series.

```

