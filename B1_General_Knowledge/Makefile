

BASE_DIR := .
BUILD_DIR := $(BASE_DIR)/build
BIN_DIR := $(BASE_DIR)/bin
INC_DIR := $(BASE_DIR)/include
SRC_DIR := $(BASE_DIR)/src
LOG_DIR := $(BASE_DIR)/logs
PROJECT_NAME := logging

stage1: $(SRC_DIR)/*.cpp 
	@echo "---------------------------------------------------------------------"
	@echo "Preprocessing"

	g++ -E $(SRC_DIR)/my_logging.cpp -I $(INC_DIR)/ -o  $(BUILD_DIR)/my_logging.i
	g++ -E $(SRC_DIR)/main.cpp -I $(INC_DIR)/ -o  $(BUILD_DIR)/main.i

	@echo "Preprocessing done"
	@echo "---------------------------------------------------------------------"

stage2: stage1
	@echo "---------------------------------------------------------------------"
	@echo "Compiling"

	g++ -S $(BUILD_DIR)/my_logging.i -o $(BUILD_DIR)/my_logging.s
	g++ -S $(BUILD_DIR)/main.i -o $(BUILD_DIR)/main.s

	@echo "Compile done"
	@echo "---------------------------------------------------------------------"

stage3: stage1 stage2
	@echo "---------------------------------------------------------------------"
	@echo "Assembling"

	g++ -c $(BUILD_DIR)/my_logging.s -o $(BUILD_DIR)/my_logging.o
	g++ -c $(BUILD_DIR)/main.s -o $(BUILD_DIR)/main.o

	@echo "Assembly done"
	@echo "---------------------------------------------------------------------"

stage4: clean stage1 stage2 stage3 
	@echo "---------------------------------------------------------------------"
	@echo "Linking"

	g++ $(BUILD_DIR)/*.o -o $(BIN_DIR)/$(PROJECT_NAME)

	@echo "Linking done"
	@echo "---------------------------------------------------------------------"	
all: stage4
	@echo "---------------------------------------------------------------------"	
	@echo "Build complete"
	@echo "---------------------------------------------------------------------"	
	
clean:
	@echo "---------------------------------------------------------------------"	
	rm -rf $(BUILD_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(LOG_DIR)/*
	@echo "Cleaned up"
	@echo "---------------------------------------------------------------------"	

