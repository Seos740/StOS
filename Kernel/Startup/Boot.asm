[org 0x7c00]
[bits 16]

    mov bp, 0x5000
    mov sp, bp
    mov bh, 0
    push bx

    jmp 0x3000

    jmp $
    times 510 - ($ - $$) db 0
    db 0x55, 0xaa