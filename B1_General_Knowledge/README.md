
# Build and Link Static / Shared Libraries using GCC

## Following the instruction below:

### 🛠 `make stage1` : Pre-Compiling
```bash
g++ -E main.c -o main.i
```

### ⚙️ `make stage2` : Compilation
```bash
g++ -S main.i -o main.s
```

### 🧱 `make stage3` : Assembly
```bash
g++ -c main.s -o main.o
```

### 🔗 `make stage4` : Linking
```bash
g++ -o main main.o
```

### ✅ `make all` : Build executable file
Build everything into the final binary.

### 🧹 `make clean` : Clean everything
Remove all build artifacts: `.o`, `.i`, `.s`, `.a`, `.so`, binary files, etc.

---

## Create the object files

Object files are created from `.c` source files and used in either static or shared libraries.

### ➤ Main object file (for executable)
```bash
gcc -c src/main.c -o bin/main.o
```

### ➤ Static Library Object Files (no `-fPIC`)
```bash
gcc -c src/tq84/add.c    -o bin/static/add.o
gcc -c src/tq84/answer.c -o bin/static/answer.o
```

### ➤ Shared Library Object Files (compiled with `-fPIC`)
```bash
gcc -c -fPIC src/tq84/add.c    -o bin/shared/add.o
gcc -c -fPIC src/tq84/answer.c -o bin/shared/answer.o
```

> `-fPIC` stands for **Position Independent Code**. It's required when building shared libraries so they can be loaded at any memory address.

---

## Create the Static Library

A static library is a collection of object files bundled into a single `.a` archive file using `ar`.

```bash
ar rcs bin/static/libtq84.a bin/static/add.o bin/static/answer.o
```

---

## Create the Shared Library

Use `gcc -shared` to link object files into a shared library (`.so`):

```bash
gcc -shared bin/shared/add.o bin/shared/answer.o -o bin/shared/libtq84.so
```

> ⚠️ Make sure to compile object files with `-fPIC` when building shared libraries.  
> Otherwise, you’ll get an error like:

```
/usr/bin/ld: bin/add.o: relocation R_X86_64_PC32 against symbol `gSummand' can not be used when making a shared object; recompile with -fPIC
```

---

## References

- [GCC: Creating Static and Shared Libraries](https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index)