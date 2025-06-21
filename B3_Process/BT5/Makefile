# project name
PN := main
ORPHAN_NAME := orphan
ZOMBIE_NAME := zombie


all: clean build

build:
	gcc -o ${ORPHAN_NAME} ${ORPHAN_NAME}.c 
	gcc -o ${ZOMBIE_NAME} ${ZOMBIE_NAME}.c 
	@echo "Compiled Successfully"

clean:
	rm -rf ${ORPHAN_NAME} ${ZOMBIE_NAME}
	clear
	@echo "Cleaned up"

