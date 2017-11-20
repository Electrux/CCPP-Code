 section .data
        num:        dq      102     ;my default number to print on the screen
        nl:         db      0x0a    ;newline character hexcode
        nlsize:     equ     $-nl    ;size of newline character
 
    section .bss
        rem:        resq        1   ;reserve a quad word for remainder
        rev:        resq        1   ;reserve a quad word for reverse
 
    section .text
        global _start
        mov qword [rev], 0      ;initialize rev with zero
 
    _start:
 
        cmp qword [num], 0      ;compare value of variable num with zero
            jng _rev            ;jump to _exit if num is not greater than 0 (jump not greater)
        mov rcx, 10             ;move 10 to rcx to be the divisor (does not need to be a qword)
        mov rax, [rev]          ;move reverse variable to rax
        mul rcx                 ;multiply reverse variable with 10 to modify places (ones,tens,hundreds,...)
        mov [rev], rax          ;put reverse back in rax
        mov rax, [num]          ;move the number to rax
        mov rdx, 0              ;rdx needs to be zero before division can occur
        div rcx                 ;divide number in rax by 10
        mov [num], rax          ;get the quotient to get the remaining number for quotient
        add [rev], rdx          ;get the remainder from rdx.
        jmp _start              ;get back to _start (loop)
   
    _rev:
   
        cmp qword [rev], 0      ;compare value of variable rev with zero
            jng _exit           ;jump to _exit if rev is not greater than 0
        mov rax, [rev]          ;move the number to rax
        mov rcx, 10             ;move 10 to rcx to be the divisor (does not need to be a qword
        mov rdx, 0              ;rdx needs to be zero before division can occur
        div rcx                 ;divide number in rax by 10
        mov [rev], rax          ;get the quotient to get the remaining number for quotient
        mov [rem], rdx          ;move the remainder to the rem variable
        call _disprem           ;call _disprem to display the remainder... call returns the flow back to the caller right? YES
        jmp _start              ;get to the loop again
 
    _exit:
        call _newl              ;display newline before exiting
        mov rax, 60             ;move 60 to rax which is the id for sys_exit
        mov rdi, 0              ;exit code is zero
        syscall                 ;call the kernel
 
    _newl:
        mov rax, 1              ;sys_code is 1 which is sys_write
        mov rdi, 1              ;write to output stream write
        mov rsi, nl             ;put the newline character cant do directly 0x0a because char* requires address
        mov rdx, nlsize         ;size of newline character
        syscall                 ;call the kernel
        ret                     ;return to the caller
 
    _disprem:
        mov rax, 1              ;sys_code is 1 which is sys_write
        mov rdi, 1              ;write to output stream write
        add qword [rem], 0x30   ;hex dont need to be qword
        mov rsi, rem            ;for getting ascii value (48 is ascii 0 in decimal) to convert the rem to character
        mov rdx, 1              ;see how this needs just 1 byte? Or is it taking 1 qword because of the declaration
        syscall                 ;yuhoo kernel! complete my task
        sub qword [rem], 0x30   ;get me my original number back plz thanks
        ret                     ;return to the caller
