section .data
message: db  'hello, world', 0

section .text
global _start

exit:
    mov  rax, 60
    xor  rdi, rdi          
    syscall




string_length:
   mov  rax, rdi
     .counter:
         cmp  byte [rdi], 0
	     je   .end
	         inc  rdi
		     jmp  .counter
		       .end:
		           sub  rdi, rax
			       mov  rax, rdi
			           ret



print_string:
    push rdi
    call string_length
    pop rdi
    mov  rdx, rax
    mov  rsi, rdi
    mov  rax, 1
    mov  rdi, 1
    syscall








parse_uint:
	xor rax, rax
   	xor rax, rax
	xor rcx, rcx
        xor rdx, rdx

	.loop:
	  mov dl, byte[rdi + rcx]
	  sub dl, 48
	  cmp dl, 0
	  js .end
	  cmp dl, 10
	  jns .end
	  imul rax, 10
	  add rax, rdx
	  inc rcx
	  jmp .loop

	.end:
	  mov rdx, rcx
	  ret

