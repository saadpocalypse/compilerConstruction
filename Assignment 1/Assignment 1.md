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
* Only float data type is supported.
* Float values may be stored in identifiers.
* Valid identifers start with a letter and can be followed by any combination of letters and/or numbers.
* New line is considered the end of the line, no restrictions are to be applied for a semi-colon.

## Programming Guidelines
Your program must read the input file character by character and use the characters to fill up an input buffer. Two pointers should be used to keep track of each lexeme generated. Your major function should be a DFASimulator, which eaither accepts or rejects the lexemes as valid tokens. DFAs can be easily implemented using transition tables. Each valid token must be enlisted in a symbol table. The generated output file should contain all the tokens from the input code.

