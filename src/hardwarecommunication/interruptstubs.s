
.set IRQ_BASE, 0x20

.section .text
.extern _ZN6kiteos21hardwarecommunication16InterruptManager15handleInterruptEhj
.global _ZN6kiteos21hardwarecommunication16InterruptManager22IgnoreInterruptRequestEv


.macro HandleInterruptException num
.global _ZN6kiteos21hardwarecommunication16InterruptManager26HandleInterruptException\num\()Ev
_ZN6kiteos21hardwarecommunication16InterruptManager26HandleInterruptException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN6kiteos21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN6kiteos21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm

HandleInterruptException 0x00
HandleInterruptException 0x01
HandleInterruptException 0x02
HandleInterruptException 0x03
HandleInterruptException 0x04
HandleInterruptException 0x05
HandleInterruptException 0x06
HandleInterruptException 0x07
HandleInterruptException 0x08
HandleInterruptException 0x09
HandleInterruptException 0x0A
HandleInterruptException 0x0B
HandleInterruptException 0x0C
HandleInterruptException 0x0D
HandleInterruptException 0x0E
HandleInterruptException 0x0F
HandleInterruptException 0x10
HandleInterruptException 0x11
HandleInterruptException 0x12
HandleInterruptException 0x13

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31

int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs


    pushl %esp
    push (interruptnumber)
    call _ZN6kiteos21hardwarecommunication16InterruptManager15handleInterruptEhj
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

.global _ZN6kiteos21hardwarecommunication16InterruptManager22IgnoreInterruptRequestEv
_ZN6kiteos21hardwarecommunication16InterruptManager22IgnoreInterruptRequestEv:
    
    iret

.data
    interruptnumber: .byte 0