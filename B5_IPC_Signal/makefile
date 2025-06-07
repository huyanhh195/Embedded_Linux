BASE_DIR = .
BT1_DIR = $(BASE_DIR)/BT1
BT2_DIR = $(BASE_DIR)/BT2

all: clean build

build:
	gcc $(BT1_DIR)/main.c -o $(BT1_DIR)/main
	gcc $(BT2_DIR)/main.c -o $(BT2_DIR)/main
	@echo "Compile done"
clean:
	rm -rf $(BT1_DIR)/main $(BT2_DIR)/main
	clear
	@echo "clean up done"