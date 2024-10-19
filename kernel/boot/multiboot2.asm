section .multiboot2_header
multiboot2_start:
dd 0xE85250D6 ; magic number
dd 0 ; architecture (i386)
dd multiboot2_end - multiboot2_start ; header length
dd -(0xE85250D6 + multiboot2_end - multiboot2_start) ; checksum
dw 0 ; type
dw 0 ; flags
dd 8 ; size
multiboot2_end: