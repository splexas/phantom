# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

CC = gcc
LD = ld
ASSEMBLER = nasm

BUILD_DIR = build/
INCLUDE_DIR = ./kernel/include
GRUB_DIR = iso/
GRUB_MKRESCUE = grub2-mkrescue
QEMU = qemu-system-i386

OUTPUT_NAME = os

OBJFILES := $(BUILD_DIR)multiboot.o \
			$(BUILD_DIR)kernel.o \
			$(BUILD_DIR)vga.o \
			$(BUILD_DIR)gdt.o \
			$(BUILD_DIR)idt.o \
			$(BUILD_DIR)idt_stub.o

.PHONY: clean all

clean:
	rm -rf $(BUILD_DIR)
	mkdir $(BUILD_DIR)

all: $(OBJFILES)
	$(LD) -melf_i386 -Tlinker.ld $? --oformat elf32-i386 -o $(GRUB_DIR)boot/kernel.bin
	$(GRUB_MKRESCUE) $(GRUB_DIR) -o $(OUTPUT_NAME).iso
	$(QEMU) -cdrom $(OUTPUT_NAME).iso

$(BUILD_DIR)%.o: kernel/boot/%.asm
	$(ASSEMBLER) -felf32 -o $@ $<

$(BUILD_DIR)%.o: kernel/src/%.asm
	$(ASSEMBLER) -felf32 -o $@ $<

$(BUILD_DIR)%.o: kernel/%.c
	$(CC) -m32 -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)%.o: kernel/src/%.c
	$(CC) -m32 -I$(INCLUDE_DIR) -c $< -o $@