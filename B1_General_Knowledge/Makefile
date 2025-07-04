# Project name 
PN := logging
LOG_LIB_NAME := my_logging

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

ifeq ($(BUILD_SHARED),1)
	LIB_BUILD_TARGET := shared_lib
	LIB_OUTPUT := -L${LIB_SHARED_DIR}
else
	LIB_BUILD_TARGET := static_lib
	LIB_OUTPUT := -L${LIB_STATIC_DIR}
endif

#
# Build excutable file
#
all: clean create_folder stage3 stage4
	@echo "---------------------------------------------------------------------"	
	cp -r ${BIN_DIR}/${PN} ${BASE_DIR}

	@echo "Build complete"
	@echo "---------------------------------------------------------------------"	

#
# Step Pre-Compiling
#
stage1: $(BASE_DIR)/main.cpp 
	@echo "---------------------------------------------------------------------"
	@echo "Preprocessing"

	g++ -E $(BASE_DIR)/main.cpp -o $(BUILD_DIR)/main.i -I$(INC_DIR)/

	@echo "Preprocessing done"	
	@echo "---------------------------------------------------------------------"
#
# Step Compilation
#
stage2: stage1
	@echo "---------------------------------------------------------------------"
	@echo "Compiling"

	g++ -S $(BUILD_DIR)/main.i -o $(BUILD_DIR)/main.s

	@echo "Compile done"
	@echo "---------------------------------------------------------------------"

#
# Step Assembly
#
stage3: stage1 stage2
	@echo "---------------------------------------------------------------------"
	@echo "Assembling"

	g++ -c $(BUILD_DIR)/main.s -o $(BUILD_DIR)/main.o

	@echo "Assembly done"
	@echo "---------------------------------------------------------------------"


#
# Step Linking
#
stage4: ${LIB_BUILD_TARGET} 
	@echo "---------------------------------------------------------------------"
	@echo "Linking"

	# g++ $(BUILD_DIR)/main.o ${LIB_OUTPUT} -l${LOG_LIB_NAME} -o $(BIN_DIR)/$(PN)
	g++ $(BUILD_DIR)/main.o ${LIB_OUTPUT} -l${LOG_LIB_NAME}  -Wl,-rpath=$(LIB_SHARED_DIR) -o $(BIN_DIR)/$(PN)

	@echo "Linking done"
	@echo "---------------------------------------------------------------------"	

#
# Create static library
#
static_lib: 
	@echo "---------------------------------------------------------------------"
	@echo "Creating static library"
	
	g++ -c ${SRC_DIR}/${LOG_LIB_NAME}.cpp -o ${BUILD_DIR}/${LOG_LIB_NAME}.o -I${INC_DIR}/
	ar rcs ${LIB_STATIC_DIR}/lib${LOG_LIB_NAME}.a  ${BUILD_DIR}/${LOG_LIB_NAME}.o 

	@echo "Created static library"
	@echo "---------------------------------------------------------------------"	
	
#
# Create shared library
#
shared_lib:  
	@echo "---------------------------------------------------------------------"
	@echo "Creating shared library"

	g++ -fPIC -c ${SRC_DIR}/${LOG_LIB_NAME}.cpp -o $(BUILD_DIR)/${LOG_LIB_NAME}.o -I$(INC_DIR)/
	g++ -shared $(BUILD_DIR)/${LOG_LIB_NAME}.o -o $(LIB_SHARED_DIR)/lib${LOG_LIB_NAME}.so

	@echo "Created shared library"
	@echo "---------------------------------------------------------------------"	

create_folder:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(LOG_DIR)
	mkdir -p ${LIB_SHARED_DIR}
	mkdir -p ${LIB_STATIC_DIR}

#
# Clean the project
#
clean:
	@echo "---------------------------------------------------------------------"	

	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(LOG_DIR)
	rm -rf ${LIB_DIR}
	rm -rf ${BASE_DIR}/${PN}
	clear
	
	@echo "Cleaned up"
	@echo "---------------------------------------------------------------------"	

