[bits 16]
[org 0x3000]

GDT_Start:
    null_descriptor:
        dd 0
        dd 0
    code_descriptor:
        dw 0xffff
        dw 0
        db 0
        db 10011010
        db 11001111
        db 0
    data_descriptor:
        dw 0xffff
        dw 0
        db 0
        db 10011010
        db 11001111
        db 0
    GDT_Descriptor:
        dw GDT_End - GDT_Start - 1
        dd Gdt_Start

    CODE_SEG equ code_descriptor - GDT_Start
    DATA_SEG equ data_descriptor - GDT_Start

    cli

    lgdt [GDT_Descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODESEG:start_protected_mode

    [bits 32]
    start_protected_mode:

    jmp 0x100000
