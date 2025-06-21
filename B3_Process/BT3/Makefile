# project name
PN := main


#define the directories
BASE_DIR := .

#define flags
ifeq ($(USE_EXEC),1)
	FLAG_BT3 := -DUSE_EXEC
endif

all: clean build

build:
	gcc -o ${PN} ${PN}.c ${FLAG_BT3}

	@echo "Compiled Successfully"

clean:
	rm -rf ${PN}
	clear 
    
	@echo "Cleaned up"

