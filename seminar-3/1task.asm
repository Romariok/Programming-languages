%macro concat 4
    %4: db %1, ',', ' ', %2, ',', ' ', %3, 0

%endmacro
section .data
concat "hello", "another", "world", newSTR
section .text

global _start
_start:
   mov rdi, newSTR
   call print_string
   mov rax, 60
   mov rdi, 0
   syscall




; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax
   push rbx
   mov  rax, rdi
  .counter:
    mov bl, byte[rdi]
    test byte[rdi], bl
    jz   .end
    inc  rdi
    jmp  .counter
  .end:
    sub  rdi, rax
    mov  rax, rdi
    pop rbx
    ret


; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    xor rax, rax
    push rdi
    call string_length
    pop rdi
    mov  rdx, rax
    mov  rax, 1
    mov  rsi, rdi
    mov  rdi, 1
    syscall
    ret


