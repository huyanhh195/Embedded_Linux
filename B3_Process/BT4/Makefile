# project name
PN := main

#define flags
ifeq ($(USE_SIGKILL),1)
	FLAG_BT4 += -DUSE_SIGKILL
endif

all: clean build

build:
	gcc -o ${PN} ${PN}.c ${FLAG_BT4} 

	@echo "Compiled Successfully"

clean:
	rm -rf ${PN}
	clear
	@echo "Cleaned up"

