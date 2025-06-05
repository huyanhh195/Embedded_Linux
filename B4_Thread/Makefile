PN := main

BASE_DIR := .
BT1_DIR := ${BASE_DIR}/BT1
BT2_DIR := ${BASE_DIR}/BT2
BT3_DIR := ${BASE_DIR}/BT3
BT4_DIR := ${BASE_DIR}/BT4

all: clean
	gcc -o ${BT1_DIR}/${PN} ${BT1_DIR}/${PN}.c -lpthread
	gcc -o ${BT2_DIR}/${PN} ${BT2_DIR}/${PN}.c -lpthread
	gcc -o ${BT3_DIR}/${PN} ${BT3_DIR}/${PN}.c -lpthread
	gcc -o ${BT4_DIR}/${PN} ${BT4_DIR}/${PN}.c -lpthread

clean:
	rm -rf ${BT1_DIR}/${PN} ${BT2_DIR}/${PN} ${BT3_DIR}/${PN} ${BT4_DIR}/${PN}
	clear