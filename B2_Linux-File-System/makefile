PN1 := bai1
PN2 := bai2
PN3 := bai3

BASE_DIR := .
BAI1_DIR := ${BASE_DIR}/bai1
BAI2_DIR := ${BASE_DIR}/bai2
BAI3_DIR := ${BASE_DIR}/bai3

all:
	gcc -o ${BAI1_DIR}/${PN1} ${BAI1_DIR}/main.c
	gcc -o ${BAI2_DIR}/${PN2} ${BAI2_DIR}/main.c
	gcc -o ${BAI3_DIR}/${PN3} ${BAI3_DIR}/main.c
	@echo "Compiled Successfully"

clean: 
	rm -f ${BAI1_DIR}/${PN1} ${BAI2_DIR}/${PN2} ${BAI2_DIR}/*.txt ${BAI3_DIR}/${PN3}
	clear