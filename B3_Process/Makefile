# project name
PN := main
ORPHAN_NAME := orphan
ZOMBIE_NAME := zombie

#define the directories
BASE_DIR := .

BT1_DIR := $(BASE_DIR)/BT1
BT1_SRC_DIR := $(BT1_DIR)/src

BT2_DIR := $(BASE_DIR)/BT2
BT2_SRC_DIR := $(BT2_DIR)/src

BT3_DIR := $(BASE_DIR)/BT3
BT3_SRC_DIR := $(BT3_DIR)/src

BT4_DIR := $(BASE_DIR)/BT4
BT4_SRC_DIR := $(BT4_DIR)/src

BT5_DIR := $(BASE_DIR)/BT5
BT5_SRC_DIR := $(BT5_DIR)/src

#define flags
#flag for BT3
ifeq ($(USE_EXEC),1)
	FLAG_BT3 := -DUSE_EXEC
endif

#flag for BT4
ifeq ($(USE_SIGKILL),1)
	FLAG_BT4 += -DUSE_SIGKILL
endif

all: clean build

build:
	gcc -o ${BT1_DIR}/${PN} ${BT1_SRC_DIR}/${PN}.c
	gcc -o ${BT2_DIR}/${PN} ${BT2_SRC_DIR}/${PN}.c
	gcc -o ${BT3_DIR}/${PN} ${BT3_SRC_DIR}/${PN}.c ${FLAG_BT3}
	gcc -o ${BT4_DIR}/${PN} ${BT4_SRC_DIR}/${PN}.c ${FLAG_BT4} 
	gcc -o ${BT5_DIR}/${ORPHAN_NAME} ${BT5_SRC_DIR}/${ORPHAN_NAME}.c 
	gcc -o ${BT5_DIR}/${ZOMBIE_NAME} ${BT5_SRC_DIR}/${ZOMBIE_NAME}.c 
	@echo "Compiled Successfully"

clean:
	rm -rf ${BT1_DIR}/${PN} ${BT2_DIR}/${PN} ${BT3_DIR}/${PN} ${BT4_DIR}/${PN} ${BT5_DIR}/${ORPHAN_NAME} ${BT5_DIR}/${ZOMBIE_NAME}
	clear
	@echo "Cleaned up"

