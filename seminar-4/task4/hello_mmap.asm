; hello_mmap.asm
%define O_RDONLY 0 
%define PROT_READ 0x1
%define MAP_PRIVATE 0x2
%define SYS_WRITE 1
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define SYS_FSTAT 5
%define SYS_MMAP 9
%define SYS_MUNMAP 11
%define SYS_EXIT 60
%define FD_STDOUT 1
%define SIZE_OFFT 8
%define SIZEOF_STAT 144
%define OFFSET_ST_SIZE 48

section .data
    ; This is the file name. You are free to change it.
    fname: db 'hello.txt', 0

section .text
global print_file

; use exit system call to shut down correctly
exit:
    mov  rax, SYS_EXIT
    xor  rdi, rdi
    syscall

; These functions are used to print a null terminated string
; rdi holds a string pointer
print_string:
    push rdi
    call string_length
    pop  rsi
    mov  rdx, rax 
    mov  rax, SYS_WRITE
    mov  rdi, FD_STDOUT
    syscall
    ret

string_length:
    xor  rax, rax
.loop:
    cmp  byte [rdi+rax], 0
    je   .end 
    inc  rax
    jmp .loop 
.end:
    ret

; This function is used to print a substring with given length
; rdi holds a string pointer
; rsi holds a substring length
print_substring:
    mov  rdx, rsi 
    mov  rsi, rdi
    mov  rax, SYS_WRITE
    mov  rdi, FD_STDOUT
    syscall
    ret

; rdi - file name
print_file:
    ; Вызовите open и откройте fname в режиме read only.
    mov  rax, SYS_OPEN
    mov  rsi, O_RDONLY    ; Open file read only
    xor rdx, rdx   

    syscall

; save file descriptor
    mov rbx, rax
    
;Calling fstat to get file information
    mov rdi, rax
    sub rsp, SIZEOF_STAT
    mov rsi, rsp
    mov rax, SYS_FSTAT 
    syscall


;Mapping file
    mov rdi, 0
    mov rsi, [rsp+OFFSET_ST_SIZE]
    mov rdx, PROT_READ
    mov r10, MAP_PRIVATE
    mov r8, rbx
    mov r9, 0
    mov rax, SYS_MMAP
    syscall

;Print mapped file with file size
    mov rdi, rax
    mov rsi, [rsp+OFFSET_ST_SIZE]
    call print_substring

; delete mapping
    mov rax, SYS_MUNMAP
    mov rdi, 0
    mov rsi, [rsp+OFFSET_ST_SIZE]
    add rsp, SIZEOF_STAT
    syscall

; close file
    mov rax, SYS_CLOSE
    mov rdi, rbx

    syscall

    call exit



