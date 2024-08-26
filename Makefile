
SRC_MAIN = $(wildcard modules/*.c) $(wildcard *.c)
OUTPUT_NAME = eBat.elf

all:
	$(MAKE) build

debug:
	gcc $(SRC_MAIN) -o $(OUTPUT_NAME) -Wall -g -O0 -DDEBUG

build:
	gcc $(SRC_MAIN) -o $(OUTPUT_NAME) -Wall -g -Wunused-variable -O0

run:
	chmod 0777 $(OUTPUT_NAME)
	./$(OUTPUT_NAME)

log:
	chmod 0777 $(OUTPUT_NAME)
	./$(OUTPUT_NAME) > ebat.log
