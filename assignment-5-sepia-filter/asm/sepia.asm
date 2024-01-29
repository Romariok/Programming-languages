
global sepia_image
global sepia_pixel

;sizeof(uint64_t)
%define HW_OFFSET 8 
%define SIZEOF_PIXEL 3

%macro change_pixel 2
   movdqu xmm4, xmm3
   mulps xmm4, %1
   haddps xmm4, xmm4      
   haddps xmm4, xmm4   
   cvtps2dq xmm4, xmm4     
   extractps rdx, xmm4, 0
   cmp rdx, 0xff        
   jle %%skip
   mov rdx, r8
%%skip:
   mov byte[rdi + %2], dl
%endmacro

section .text
; void sepia_image(struct image *img)
;rax - pixels count
;rdi - iterator
sepia_image:
   mov rax, [rdi]
   imul rax, SIZEOF_PIXEL
   imul rax, [rdi + HW_OFFSET]
   mov rdi, [rdi + (HW_OFFSET * 2)]
   add rax , rdi
   mov r8, 0xff

   lddqu xmm0, [rel r]
   lddqu xmm1, [rel g]
   lddqu xmm2, [rel b]

   .loop:
      lddqu xmm3, [rdi]
      pmovzxbd xmm3, xmm3
      cvtdq2ps xmm3, xmm3

      change_pixel xmm2, 0
      change_pixel xmm1, 1
      change_pixel xmm0, 2

      add rdi, SIZEOF_PIXEL
      cmp rdi, rax
      jne .loop
      ret


section .rodata
r: dd 0.189, 0.769, 0.393, 0.0
g: dd 0.168, 0.686, 0.349, 0.0
b: dd 0.131, 0.534, 0.272, 0.0
