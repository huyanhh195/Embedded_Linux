# Answer for EX2
What happens if you don’t call alarm(1) again inside the handler?

The alarm will only trigger once, so the handler runs a single time and the program keeps running without exiting 

---

# Usage
```bash
./main <flag>
```
Where flag can be --enable or -e to to call alarm() in signal handler
Note: If no flag is provided, the program only call alarm() once time