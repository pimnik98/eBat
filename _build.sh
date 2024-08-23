gcc eBat.c eBatRuntime.c $(wildcard modules/*.c) -o eBat.elf -Wall -g -O2 -Wunused-variable
chmod 0777 eBat.elf
./eBat.elf