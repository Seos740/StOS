[bits 16]
[org 0x3000]

GDT_Start:
    null_descriptor:
        dd 0
        dd 0
    code_descriptor:
        dw 0xFFFF      ; Limit (low)
        dw 0x0000      ; Base (low)
        db 0x00        ; Base (middle)
        db 0x9A        ; Access byte (Code: executable, readable)
        db 0xCF        ; Limit (high) + flags
        db 0x00        ; Base (high)
    data_descriptor:
        dw 0xFFFF      ; Limit (low)
        dw 0x0000      ; Base (low)
        db 0x00        ; Base (middle)
        db 0x92        ; Access byte (Data: writable)
        db 0xCF        ; Limit (high) + flags
        db 0x00        ; Base (high)

GDT_End:

CODE_SEG equ (code_descriptor - GDT_Start)
DATA_SEG equ (data_descriptor - GDT_Start)

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1  ; Limit (16-bit) - Ensure it's within 0xFFFF
    dd GDT_Start                ; Base (32-bit)

lgdt [GDT_Descriptor]
cli  ; Disable interrupts AFTER loading GDT

mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:protected_mode_start

[bits 32]
protected_mode_start:
    ; Set up stack
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov esp, 0x90000  ; Stack at 576KB (below 1MB)

    ; Load address 0x100000 (1MB) into EDI
    mov edi, 0x100000
    jmp far [jump_to_1MB]  ; Far jump using a memory operand

align 4
jump_to_1MB:
    dw CODE_SEG  ; Segment selector
    dd 0x100000  ; Offset (1MB)
