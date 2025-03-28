[bits 16]
[org 0x3000]

GDT_Start:
    null_descriptor:
        dd 0
        dd 0
    code_descriptor:
        dw 0xffff      ; Limit (low)
        dw 0          ; Base (low)
        db 0          ; Base (middle)
        db 10011010   ; Access byte (Code: executable, readable)
        db 11001111   ; Limit (high) + flags
        db 0          ; Base (high)
    data_descriptor:
        dw 0xffff      ; Limit (low)
        dw 0          ; Base (low)
        db 0          ; Base (middle)
        db 10010010   ; Access byte (Data: writable)
        db 11001111   ; Limit (high) + flags
        db 0          ; Base (high)

GDT_End:

CODE_SEG equ (code_descriptor - GDT_Start)
DATA_SEG equ (data_descriptor - GDT_Start)

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1
    dd GDT_Start

cli

lgdt [GDT_Descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:protected_mode_start

[bits 32]
protected_mode_start:
    ; Do something useful in protected mode
    jmp $
