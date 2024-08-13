multiboot_header_start:
dd 0xE85250D6
dd 0
dd multiboot_header_end - multiboot_header_start
dd -(0xE85250D6 + 0 + multiboot_header_end - multiboot_header_start)
dw 0 ; type
dw 0 ; flags
dd 8 ; size
multiboot_header_end: