section .data
newline: db 10
codes:
    db   '0123456789ABCDEF', 10

section .text
global _start

print_locals:
push 0xaa
push 0xbb
push 0xff
push rax
mov rdi, [rsp+8]
call print_hex
mov rdi, [rsp+16]
call print_hex
mov rdi,  [rsp+24]
call print_hex
pop rax
pop rax
pop rax
pop rax
ret


_start:
   call  print_locals
   mov rax, 60
   xor rdi, rdi
   syscall


print_new_line:
	mov rax, 1
	mov rdi, 1
	mov rsi, newline
	mov rdx, 1
	syscall
	ret


print_hex:
 ; number 1122... in hexadecimal format
    mov  rax, rdi

    mov  rdi, 1
    mov  rdx, 1
    mov  rcx, 64
    ; Each 4 bits should be output as one hexadecimal digit
    ; Use shift and bitwise AND to isolate them
    ; the result is the offset in 'codes' array
.loop:
    push rax
    sub  rcx, 4
    ; cl is a register, smallest part of rcx
    ; rax -- eax -- ax -- ah + al
    ; rcx -- ecx -- cx -- ch + cl
    sar  rax, cl
    and  rax, 0xf

    lea  rsi, [codes + rax]
    mov  rax, 1

    ; syscall leaves rcx and r11 changed
    push  rcx
    syscall
    pop  rcx

    pop  rax
    ; test can be used for the fastest 'is it a zero?' check
    ; see docs for 'test' command
    test rcx, rcx
    jnz .loop
    call print_new_line
    ret


