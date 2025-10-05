CC := gcc
CFLAGS := -Wall -Iinclude

CLIENT := client
SERVER := server

all: clean $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT).c
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT).c

$(SERVER): $(SERVER).c
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER).c

clean:
	rm -f $(CLIENT) $(SERVER)
	clear