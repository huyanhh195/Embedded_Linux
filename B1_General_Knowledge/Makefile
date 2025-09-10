# Project name 
PN := main
LOG_LIB_NAME := logging
STR_LIB_NAME := strutils

# Define the directories
BASE_DIR := .
BUILD_DIR := $(BASE_DIR)/build
LOG_DIR := $(BASE_DIR)/logs
INC_DIR := $(BASE_DIR)/include
SRC_DIR := $(BASE_DIR)/src
BIN_DIR := $(BASE_DIR)/bin
LIB_DIR := ${BASE_DIR}/libs
LIB_SHARED_DIR := ${LIB_DIR}/shared
LIB_STATIC_DIR := ${LIB_DIR}/static

all: clean create_folder static shared
	@echo "---------------------------------------------------------------------"	

	@echo "Build complete"

	@echo "---------------------------------------------------------------------"	
	clear

stage1: $(BASE_DIR)/main.c
	@echo "---------------------------------------------------------------------"
	@echo "Preprocessing"

	gcc -E $(BASE_DIR)/main.c -o $(BUILD_DIR)/main.i -I$(INC_DIR)/

	@echo "Preprocessing done"	
	@echo "---------------------------------------------------------------------"

stage2: stage1
	@echo "Compiling"

	gcc -S $(BUILD_DIR)/main.i -o $(BUILD_DIR)/main.s

	@echo "Compile done"
	@echo "---------------------------------------------------------------------"

stage3: stage1 stage2
	@echo "Assembling"

	gcc -c $(BUILD_DIR)/main.s -o $(BUILD_DIR)/main.o

	@echo "Assembly done"
	@echo "---------------------------------------------------------------------"

stage4: ${LIB_BUILD_TARGET} 
	@echo "Linking"

	gcc $(BUILD_DIR)/main.o ${LIB_OUTPUT} -l${LOG_LIB_NAME} -l${STR_LIB_NAME} -Wl,-rpath=$(LIB_SHARED_DIR) -o $(BIN_DIR)/$(PN)

	@echo "Linking done"
	@echo "---------------------------------------------------------------------"	

static_lib: 
	@echo "Creating static library"
	gcc -c ${SRC_DIR}/${LOG_LIB_NAME}.c -o ${BUILD_DIR}/${LOG_LIB_NAME}.o -I${INC_DIR}/
	gcc -c ${SRC_DIR}/${STR_LIB_NAME}.c -o ${BUILD_DIR}/${STR_LIB_NAME}.o -I${INC_DIR}/

	ar rcs ${LIB_STATIC_DIR}/lib${LOG_LIB_NAME}.a  ${BUILD_DIR}/${LOG_LIB_NAME}.o 
	ar rcs ${LIB_STATIC_DIR}/lib${STR_LIB_NAME}.a  ${BUILD_DIR}/${STR_LIB_NAME}.o 
	@echo "Created static library"
	@echo "---------------------------------------------------------------------"	
	
static: create_folder stage3 static_lib
	@echo "Linking static binary"

	gcc $(BUILD_DIR)/main.o -L$(LIB_STATIC_DIR) -l${LOG_LIB_NAME} -l${STR_LIB_NAME} -o $(BIN_DIR)/$(PN)_static
	
	cp -r ${BIN_DIR}/${PN}_static ${BASE_DIR}
	@echo "Static binary done"
	@echo "---------------------------------------------------------------------"

shared: create_folder stage3 shared_lib
	@echo "Linking shared binary"

	gcc $(BUILD_DIR)/main.o -L$(LIB_SHARED_DIR) -l${LOG_LIB_NAME} -l${STR_LIB_NAME} -Wl,-rpath=$(LIB_SHARED_DIR) -o $(BIN_DIR)/$(PN)_shared
	cp -r ${BIN_DIR}/${PN}_shared ${BASE_DIR}

	@echo "Shared binary done"
	@echo "---------------------------------------------------------------------"

shared_lib:  
	@echo "---------------------------------------------------------------------"
	@echo "Creating shared library"

	gcc -fPIC -c ${SRC_DIR}/${LOG_LIB_NAME}.c -o $(BUILD_DIR)/${LOG_LIB_NAME}.o -I$(INC_DIR)/
	gcc -fPIC -c ${SRC_DIR}/${STR_LIB_NAME}.c -o $(BUILD_DIR)/${STR_LIB_NAME}.o -I$(INC_DIR)/

	gcc -shared $(BUILD_DIR)/${LOG_LIB_NAME}.o -o $(LIB_SHARED_DIR)/lib${LOG_LIB_NAME}.so
	gcc -shared $(BUILD_DIR)/${STR_LIB_NAME}.o -o $(LIB_SHARED_DIR)/lib${STR_LIB_NAME}.so

	@echo "Created shared library"
	@echo "---------------------------------------------------------------------"	
	
create_folder:
	@echo "---------------------------------------------------------------------"	

	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(LOG_DIR)
	mkdir -p ${LIB_SHARED_DIR}
	mkdir -p ${LIB_STATIC_DIR}


clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(LOG_DIR)
	rm -rf ${LIB_DIR}
	rm -rf ${BASE_DIR}/${PN}_static
	rm -rf ${BASE_DIR}/${PN}_shared
	clear

