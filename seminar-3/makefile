
# ЗАДАНИЕ 3
# lib.o: lib.asm
# 	nasm -felf64 -o lib.o lib.asm

# lib1.o: lib.inc lib.o
# 	nasm -felf64 -o lib1.o lib.inc

# main.o : main.asm lib1.o
# 	nasm -felf64 -o main.o main.asm

# TASK3:  lib.o lib1.o main.o
# 	ld -o TASK3 main.o lib.o lib1.o




# ЗАДАНИЕ 3.5
.PHONY: TASK3_5

%.o: %.asm
	$(NASMFLAGS) $@ $<

lib1.o: lib.inc lib.o 
	$(NASMFLAGS) $@ $<

main.o : main.asm lib1.o
	$(NASMFLAGS) $@ $<

TASK3_5: lib.o lib1.o main.o
	$(LD) $@ $^



