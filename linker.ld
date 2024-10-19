ENTRY(start)
SECTIONS {
    .boot : {*(.multiboot2_header)} 
    .text : {*(.text)}
}