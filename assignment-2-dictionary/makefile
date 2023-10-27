NASM = nasm
NASMFLAGS = -felf64 -o
LD = ld -o

main: lib.o dict.o main.o
	$(LD) $@ $^

%.o: %.asm
	$(NASM) $(NASMFLAGS) $@ $<
	

dict.o: dict.asm lib.o


main.o: main.asm lib.o dict.o




.PHONY: test clean

clean:
	rm -f *.o
	rm main

test: main
	python3 ./test.py