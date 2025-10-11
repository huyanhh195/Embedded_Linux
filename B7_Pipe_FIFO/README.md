# FIFO

## Overview
Specifically, it simulates the shell command:

```bash
ls -l | wc -l
```
1. **ls -l**:  
   This command runs first. It lists all files and directories in the current folder in **long format**, showing one item per line.  
   The output is a text stream with multiple lines.

2. **| (Pipe)**:  
   The pipe operator takes the entire output of `ls -l` and **redirects it** as input to the next command.

3. **wc -l**:  
   This command runs after `ls -l`. It receives the piped data and **counts the number of lines** (`-l` stands for "lines").


## Usage:
```bash
make
./mypipe
Number of files: 4
```
The program will execute the equivalent of `ls -l | wc -l` and print the total number of files.