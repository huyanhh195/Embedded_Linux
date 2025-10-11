CC := gcc
CFLAGS := -Wall -Iinclude

MAIN := mypipe

all: clean $(MAIN) 

$(MAIN): $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).c


clean:
	rm -f $(MAIN) 
	clear