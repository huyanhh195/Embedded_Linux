CC := gcc
CFLAGS := -Wall -Iinclude
TARGETS := posix_shm_producer posix_shm_consumer

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm -f $(TARGETS)
	clear