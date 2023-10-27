%include "dict.inc"
%include "lib.inc"
%include "words.inc"

%define NEXT_INDEX 8
%define NEW_LINE 0xA
%define BUF_SIZE 255


global _start 
section .rodata
not_found: db "Not found", 0
read_fail: db "Failed to read word", 0

section .bss
buffer: resb BUF_SIZE


section .text

_start:
   mov rdi, buffer
   mov rsi, BUF_SIZE
   call read_word
   test rax, rax
   jz .read_word_fail
   push rdx
   mov rdi, buffer
   mov rsi, top
   call find_word
   pop rdx
   test rax, rax
   jz .not_found
   mov rdi, rax
   add rdi, NEXT_INDEX
   add rdi, rdx
   inc rdi
   call print_string
   jmp exit


   .not_found:
      mov rdi, not_found
      jmp .error_out
   .read_word_fail:
      mov rdi, read_fail
   .error_out:
      call print_error
      jmp exit