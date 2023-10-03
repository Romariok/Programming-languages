
# ЗАДАНИЕ 3
# lib.o: lib.asm
# 	nasm -felf64 -o lib.o lib.asm


# main.o : main.asm lib.o
# 	nasm -felf64 -o main.o main.asm

# TASK3:  lib.o main.o
# 	ld -o TASK3 main.o lib.o


NASM = nasm
NASMFLAGS = -felf64 -o
LD = ld -o
# ЗАДАНИЕ 3.5
all:
	make TASK3_5
clean:
	rm -f *.o
%.o: %.asm
	$(NASM) $(NASMFLAGS) $@ $<

main.o : main.asm lib.o
	$(NASM) $(NASMFLAGS) $@ $<

TASK3_5: lib.o main.o
	$(LD) $@ $^
	make clean

.PHONY: TASK3_5 clean all


