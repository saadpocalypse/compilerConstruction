# Lab 2

## Creat a program in C that fulfills the following requirements:

### 1. Your program should accept one text file name as a command line argument.

### 2. Your program should then read the first file line by line using *fgets()* function using the following algorithm:

* Check whether user has provided the desired argument. If not, quit the program with an appropriate message.

* Using the *malloc()* function, create a char buffer of size 100 to store the line read from file and using the *memset()* function, fill the buffer with the *'\0'* character.

* Now open the files one by one with appropriate file opening modes. If any file fails to open, terminate the program with an appropriate message to the user. Make sure to perform house keeping tasks appropriately.

* Now read the first file line by line and display it on the screen with line number placed in the start.

* Count the number of lines in the entire file.

* Count the number of printable characters (excluding spaces and new line characters) in each line.

* Search for the given character in the file and count its occurrences.

* You should also save the file with line numbering in the file user has provided as second command line argument.

### 3. Once all is done, your program should terminate by giving a message to the user about successful completion of the program.


