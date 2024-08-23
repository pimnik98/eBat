
SRC_MAIN = $(wildcard modules/*.c) $(wildcard *.c)
OUTPUT_NAME = eBat.elf

all:
	$(MAKE) build

build:
	gcc $(SRC_MAIN) -o $(OUTPUT_NAME) -Wall -g -Wunused-variable -O0

run:
	chmod 0777 $(OUTPUT_NAME)
	./$(OUTPUT_NAME)