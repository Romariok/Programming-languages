CFLAGS     = -g -O2 -Wall -Werror -std=c17 -Wdiscarded-qualifiers -Wincompatible-pointer-types -Wint-conversion
CC         = gcc
LD         = gcc
ASM        = nasm
ASMFLAGS   =-felf64 -g

# Если есть код на C, то компоновку тоже нужно производить
# с помощью gcc, а не ld
hello: hello.o hello_mmap.o
	$(LD) -o $@ $^

target : hello 
	./hello haski.txt


hello.o: hello.c 
	$(CC) -c $(CFLAGS) -o $@ $<

hello_mmap.o: hello_mmap.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

clean: 
	$(RM) hello hello.o hello_mmap.o

.PHONY: clean

