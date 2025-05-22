
Following the instruction below:
- make stage1 : Pre-Compiling           g++ -E main.c -o main.i
- make stage2 : Compilation             g++ -S main.i -o main.s
- make stage3 : Assembly                as main.s -o main.o
- make stage4 : Linking                 g++ -v -o main main.o
- make all    : Build excutable file
- make clean  : Clean everything
