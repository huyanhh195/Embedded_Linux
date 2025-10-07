PN := main
CC := gcc
CFLAGS := -Wall -Iinclude
SRC := ${PN}.c $(wildcard src/*.c) 
LOG_DIR := ./logging

all: clean $(LOG_DIR)
	${CC} ${CFLAGS} -o $(PN) $(SRC)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)

clean: 
	rm -rf ${PN} *.txt ${LOG_DIR}
	clear