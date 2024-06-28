ENTRY(start)
SECTIONS {
    .multiboot_header : {*(.multiboot_header)}
    .text : {*(.text)}
}