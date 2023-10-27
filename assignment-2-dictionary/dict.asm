%include "lib.inc"

%define NEXT_INDEX 8 ;dict element size



section .text

global find_word


; Она принимает два аргумента:
; Указатель на нуль-терминированную строку.
; Указатель на начало словаря.
; Пройдёт по всему словарю в поисках подходящего ключа. 
; Если подходящее вхождение найдено, вернёт адрес начала вхождения в   словарь (не значения), 
; иначе вернёт 0.
find_word:

   push r12
   push r9

   mov r9, rdi
   mov r12, rsi
   .loop:
      test r12, r12 ;Проверка на конец словаря
      jz .badexit
      mov rdi, r9
      add rsi , NEXT_INDEX
      call string_equals
      test rax, rax
      jnz .exit
      mov rsi, [r12]
      mov r12, rsi
      jmp .loop
   .exit:
      mov rax, r12
      jmp .pop_ret
   .badexit:
      xor rax, rax
   .pop_ret: pop r9
      pop r12
      ret
