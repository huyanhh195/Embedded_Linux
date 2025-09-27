# Answer for EX1
If the program does not register a handler for SIGINT, the program will terminate immediately (default action) when press Ctrl + C

---

# Usage
```bash
./main <flag>
```
Where flag can be --register_signal or -r to register the signal handler 
Note: If no flag is provided, the program will run normally without registering any signal handler.
