# PROCESS

## 📌 Available Flags (Compile-Time Options)

- `USE_EXEC` — Used in BT3  
  → The child process will execute the `ls` command using `exec()`.

- `USE_SIGKILL` — Used in BT4  
  → The child process will be terminated using the `SIGKILL` signal (simulating abnormal termination).

> ✅ You can combine both flags when compiling if needed.

---

## ⚙️ How to Compile

### 🔹 Basic Compilation:
```bash
make
```

### 🔹 With Optional Flags:
```bash
make USE_EXEC=1
make USE_SIGKILL=1
make USE_EXEC=1 USE_SIGKILL=1
```

---

## 🚀 How to Run

Each folder `BT1`, `BT2`, ..., `BT5` contains specific examples. To run them:

```bash
./BTx/main
```
Where `x` is a number from `1` to `4`.

### 🔸 Special Case — BT5:

- To demonstrate **orphan process**:
  ```bash
  ./BT5/orphan
  ```

- To demonstrate **zombie process**:
  ```bash
  ./BT5/zombie
  ```

---
 