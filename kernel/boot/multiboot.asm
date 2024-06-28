section .multiboot_header
multiboot_header_start:
dd 0xE85250D6 ; magic
dd 0 ; architecture
dd multiboot_header_end - multiboot_header_start ; header length
dd -(0xE85250D6 + 0 + multiboot_header_end - multiboot_header_start) ; checksum
dw 0 ; tag type
dw 0 ; tag flags
db 0 ; tag size
multiboot_header_end: