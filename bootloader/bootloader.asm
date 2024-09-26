[BITS 16]
[ORG 0x7C00]

start:
    cli
    mov ax, 0x07C0
    mov ss, ax
    mov sp, 0x7BFF

    ; Load the kernel from disk
    call load_kernel

    ; Jump to kernel entry point
    jmp 0x1000

load_kernel:
    ; Code to load the kernel binary here (read from disk)
    ret

TIMES 510 - ($ - $$) db 0
DW 0xAA55  ; Boot signature
