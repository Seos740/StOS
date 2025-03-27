[bits 16]
[org 0x7c00]

    mov ah, 2
    mov al, 1
    mov ch, 0
    mov cl, 0
    mov dh, 0
    mov dl, 0
    mov es, 0
    mov bx, 0x7e00
    int 0x13

    times 510 - ($ - $$) db 0
    db 0x55, 0xaa