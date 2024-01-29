SANITIZER := address

CC 				:= gcc
CFLAGS 		:= -O3 -Wall -Wextra -fsanitize=$(SANITIZER) -pedantic -c -g -fPIC
DEPFLAGS 	:= -MMD -MP
CPPFLAGS	:= -Iinclude
LDFLAGS 	:= -lm -fsanitize=$(SANITIZER)

ASMC	 		:= nasm
ASMFLAGS 	:= -felf64 -g

SRC_DIR 	:= src
OBJ_DIR 	:= obj
BIN_DIR 	:= bin
ASM_DIR 	:= asm
IMG_DIR := img

SRC				:= $(wildcard $(SRC_DIR)/*.c)
ASM				:= $(wildcard $(ASM_DIR)/*.asm)
OBJ_C			:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.c.o)
OBJ_ASM		:= $(ASM:$(ASM_DIR)/%.asm=$(OBJ_DIR)/%.asm.o)

BIN_C 		:= $(BIN_DIR)/main
BIN_CMP 			:= $(BIN_DIR)/compare

IMG := $(IMG_DIR)/input
IMG_C := $(IMG:=_output.bmp)

FORMAT_STYLE := LLVM

.PHONY: clean format

all: $(BIN_C) $(BIN_CMP)



$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(OBJ_DIR)/%.asm.o: $(ASM_DIR)/%.asm | $(OBJ_DIR)
	$(ASMC) -MP -MD $@.d $(ASMFLAGS) $< -o $@

$(OBJ_DIR)/main_c.c.o: $(SRC_DIR)/main.c | $(OBJ_DIR)
	$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(BIN_C): $(filter-out $(OBJ_DIR)/main.c.o $(OBJ_DIR)/compare.c.o, $(OBJ_C)) $(OBJ_ASM) $(OBJ_DIR)/main_c.c.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN_CMP): $(filter-out $(OBJ_DIR)/main.c.o, $(OBJ_C)) $(OBJ_ASM) | $(BIN_DIR)
	$(CC) $(DEPFLAGS) $(LDFLAGS) -o $@ $^
	./$(BIN_CMP)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@


clean:
	rm -f img/*output*.bmp
	rm -rf $(OBJ_DIR) $(BIN_DIR)

img/%_output.bmp: img/%.bmp $(BIN_C)
	$(BIN_C) $< $@ asm

format:
	clang-format -style=$(FORMAT_STYLE) -i src/*.c include/*.h

tidy:
	clang-tidy src/*.c include/*.h


-include $(OBJ_ASM:.o=.d)
-include $(OBJ_C:.o=.d)