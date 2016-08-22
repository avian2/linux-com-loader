NASM=/usr/bin/nasm

all: run

hello.o: hello.asm
	$(NASM) -f elf64 -o $@ $<

hello.elf: hello.o com.ld
	ld -T com.ld -o $@ $<

hello.com: hello.elf
	objcopy -S --output-target=binary $< $@

loader: loader.c
	gcc -Wall -g -o $@ $<

run: hello.com loader
	./loader $<

clean:
	rm -f *.o *.elf *.com loader

.PHONY: all run clean
