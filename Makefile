CC = gcc
LD = ld

CCFLAGS = -Ikernel/include/ -Ikernel/ -Wall -Wextra -nostdlib -m32

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
			$(BUILD_DIR)mb2.o \
			$(BUILD_DIR)vga.o \
			$(BUILD_DIR)gdt.o \
			$(BUILD_DIR)s_gdt.o \
			
.PHONY: kernel
default: kernel

kernel: $(OBJFILES)
	$(LD) -T$(LINKER_PATH) -melf_i386 $^ -o $(ISO_DIR)boot/kernel.elf
	$(GRUB_MKRESCUE) -o $(OUTPUT_FILE) $(ISO_DIR)

.PHONY: kernel
run: $(OUTPUT_FILE)
	$(QEMU) -m 2G -d int  -cdrom $(OUTPUT_FILE)

.PHONY: clean
clean: $(BUILD_DIR)
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o: kernel/boot/%.asm
	$(ASSEMBLER) -felf32 -o $@ $<

$(BUILD_DIR)%.o: kernel/stub/%.asm
	$(ASSEMBLER) -felf32 -o $@ $<

$(BUILD_DIR)%.o: kernel/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

$(BUILD_DIR)%.o: kernel/src/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

$(BUILD_DIR)%.o: kernel/src/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

$(BUILD_DIR)%.o: kernel/src/core/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

$(BUILD_DIR)%.o: kernel/src/grub/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<
