BASE_DIR = .
BT1_DIR = $(BASE_DIR)/BT1
BT2_DIR = $(BASE_DIR)/BT2
BT3_DIR = $(BASE_DIR)/BT3
BT4_DIR = $(BASE_DIR)/BT4
BT5_DIR = $(BASE_DIR)/BT5

all: clean build

build:
	gcc $(BT1_DIR)/main.c -o $(BT1_DIR)/main
	gcc $(BT2_DIR)/main.c -o $(BT2_DIR)/main
	gcc $(BT3_DIR)/main.c -o $(BT3_DIR)/main
	gcc $(BT4_DIR)/main.c -o $(BT4_DIR)/main
	gcc $(BT5_DIR)/main.c -o $(BT5_DIR)/main
	@echo "Compile done"
clean:
	rm -rf $(BT1_DIR)/main $(BT2_DIR)/main $(BT3_DIR)/main $(BT4_DIR)/main $(BT5_DIR)/main
	clear
	@echo "clean up done"