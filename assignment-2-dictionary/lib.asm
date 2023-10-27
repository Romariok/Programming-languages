%DEFINE EXIT 60
%DEFINE SYS_READ 0
%DEFINE SYS_WRITE 1
%DEFINE STDIN 0
%DEFINE STDOUT 1
%DEFINE STDERR 2


section .text
 
global exit
global string_length
global print_string
global print_char
global print_int
global print_uint
global string_equals
global read_char
global read_word
global string_copy
global parse_int
global parse_uint
global print_error


; Принимает код возврата и завершает текущий процесс
exit: 
	 xor rdi, rdi
    mov rax, EXIT
    syscall

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
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

print_error:
    push rdi
    call string_length
    pop rdi
    mov  rdx, rax
    mov  rax, SYS_WRITE
    mov  rsi, rdi
    mov  rdi, STDERR
    syscall
    ret
; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    push rdi
    call string_length
    pop rdi
    mov  rdx, rax
    mov  rax, SYS_WRITE
    mov  rsi, rdi
    mov  rdi, STDOUT
    syscall
    ret
; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rdi, 0xA
; Принимает код символа и выводит его в stdout
print_char:
    push rdi
    mov  rdi, rsp
    call print_string
    pop rdi
    ret


; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    test rdi, rdi
    jge print_uint
    push rdi
    mov rdi, '-'
    call print_char
    pop rdi
    neg rdi    

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint: 
    mov rax, rdi
    push rbx
    xor rbx, rbx
    .lp: test rax, rax
        jz .end
        mov rdi, 10
        xor rdx ,rdx
        div rdi
        inc rbx
        push rdx
        jmp .lp
    .end: test rbx, rbx
    jz .zero
    .lp1:test rbx, rbx
	jz .endd
        pop rdi
        add rdi, '0'
        dec rbx
        call print_char
        jmp .lp1


    .zero: mov rdi, '0'
        call print_char
    .endd: pop rbx
        ret



; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    .lp:   mov al, byte[rsi]
           cmp byte[rdi], al
           jne .false
           test  byte [rdi], al
           jz  .true
           inc rdi
           inc rsi
           jmp .lp
    .false: xor rax, rax
           jmp .end
    .true:  mov rax, 1
    .end:   ret


; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:

    xor rax, rax
    push 0
    xor rax, rax
    xor rdi, rdi
    mov rdx, 1
    mov rsi, rsp
    syscall
    pop rax

    ret 
; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор

read_word:
	push rbx
	push r12
	push rbp
	mov r12, rdi
	mov rbp, rsi
	xor rbx, rbx

.loop:

	call read_char
	cmp al, 0xA
	je .loop
	cmp al, 0x20
	je .loop
	cmp al, 0x9
	je .loop
.nice_char:
	cmp al, 0x0
	je .exit
	cmp al, 0x20
	je .exit
	cmp al, 0xA
	je .exit
	cmp al, 0x9
	je .exit
	cmp rbx, rbp
	jg .badexit

	mov byte [r12+rbx], al
	inc rbx	
	call read_char
	jmp .nice_char

.exit:
	test rbp, rbp
	jz .badexit	
	mov byte [r12+rbx], 0x0
	mov rax, r12
	mov rdx, rbx
	pop rbp
	pop r12
	pop rbx
	
    ret

.badexit:
	xor rax, rax
	pop rbp
	pop r12
	pop rbx
	ret 





 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
	xor rax, rax
	xor rcx, rcx
	xor rdx, rdx

	.loop:
	  mov dl, byte[rdi+rcx]
	  sub dl, 48
	  test dl, dl
	  js .end
	  cmp dl, 10
	  ja .end
	  imul rax, 10
	  add rax, rdx
	  inc rcx
	  jmp .loop
	
	.end: mov rdx, rcx
	  ret



; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
	cmp byte[rdi], '+'
	je .plus
	cmp byte[rdi], '-'
	je .minus	
	call parse_uint
	ret
.minus:
	inc rdi
	call parse_uint
	neg rax
	inc rdx
	ret
.plus:
	inc rdi
	call parse_uint
	inc rdx
	ret

;Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Воmoзвращает длину строки если она умещается в буфер, иначе 0
string_copy:
	xor rax, rax
	xor r9, r9
	
.loop:
	xor rcx, rcx
	cmp rdx, 0
	je .exit
		dec rdx
	mov cl, [rdi+r9]
	mov byte [rsi+r9], cl
	inc r9

	cmp rcx, 0
	je .exit
	jmp .loop

.exit:
	ret
