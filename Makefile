CC = gcc
LD = ld
LINKER_PATH = linker.ld
ASSEMBLER = nasm
GRUB_MKRESCUE = grub2-mkrescue
QEMU = qemu-system-i386

BUILD_DIR = build/
ISO_DIR = iso/
OUTPUT_FILE = phantom.iso

OBJFILES := $(BUILD_DIR)multiboot.o \
			$(BUILD_DIR)entry.o \
			$(BUILD_DIR)kernel.o \
			$(BUILD_DIR)vga.o \

.PHONY: kernel

kernel: $(OBJFILES)
	$(LD) -T$(LINKER_PATH) -melf_i386 $^ -o $(ISO_DIR)boot/kernel.elf
	$(GRUB_MKRESCUE) -o $(OUTPUT_FILE) $(ISO_DIR)
	$(QEMU) -m 2G -cdrom $(OUTPUT_FILE)

$(BUILD_DIR)%.o: kernel/boot/%.asm
	$(ASSEMBLER) -felf32 -o $@ $<

$(BUILD_DIR)%.o: kernel/%.c
	$(CC) -nostdlib -m32 -o $@ -c $<

$(BUILD_DIR)%.o: kernel/src/%.c
	$(CC) -nostdlib -m32 -o $@ -c $<