# project name
ORPHAN_NAME := orphan_process
ZOMBIE_NAME := zombie_process


all: clean build

build:
	gcc -o ${ORPHAN_NAME} ${ORPHAN_NAME}.c 
	gcc -o ${ZOMBIE_NAME} ${ZOMBIE_NAME}.c 
	@echo "Compiled Successfully"

clean:
	rm -rf ${ORPHAN_NAME} ${ZOMBIE_NAME}
	clear
	@echo "Cleaned up"

