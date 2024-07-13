.set IRQ_BASE, 0x20
.section .text

.extern _ZN15InterruptManger15handleInterruptEhj

.macro HandleException num
.global _ZN15InterruptManger16handleException\num\()Ev   
    movb $\num, (interruptNumber)
    jmp int_bottom
.endm
.macro HandleInterruptRequest num
.global _ZN15InterruptManger26handleInterruptRequest\num\()Ev   
    movb $\num + IRQ_BASE, (interruptNumber)
    jmp int_bottom
.endm
HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    pushl %esp
    push(interruptNumber)
    call _ZN15InterruptManger15handleInterruptEhj
    movl %eax, %esp
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    iret
.data
    interruptNumber: .byte 0