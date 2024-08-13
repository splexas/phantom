ENTRY(start)
SECTIONS
{
    .multiboot_header_start : { *(.multiboot_header_start) }
    .text : { *(.text) }
}