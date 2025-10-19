CC := gcc
CFLAGS := -Wall -Iinclude
TARGETS := task_dispatcher task_worker

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm -f $(TARGETS)
	clear