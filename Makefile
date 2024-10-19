CC = clang
CFLAGS = -Wall -Wextra -O3 -m32 -nostdlib -ffreestanding -Ikernel/boot -Ikernel/include

LD = ld
LDFLAGS = -Tlinker.ld -melf_i386

ASSEMBLER = nasm
GRUB_MKRESCUE = grub2-mkrescue

ISO_DIR = iso/

BIN_OUTPUT = $(ISO_DIR)boot/kernel.bin
ISO_OUTPUT = phantom.iso

QEMU_SYSTEM = qemu-system-i386

SRCFILES := kernel/boot/entry.asm \
	kernel/boot/multiboot2.asm \
	kernel/kernel.c \
	kernel/src/video/vga.c \

BUILD_DIR = build/
OBJFILES := $(patsubst %.c,$(BUILD_DIR)%.o,$(patsubst %.asm,$(BUILD_DIR)%.o,$(SRCFILES)))

.PHONY: kernel
default: kernel
kernel: $(OBJFILES)
	$(LD) $(LDFLAGS) -o $(BIN_OUTPUT) $^
	$(GRUB_MKRESCUE) -o $(ISO_OUTPUT) $(ISO_DIR) 

.PHONY: run
run: $(ISO_OUTPUT)
	$(QEMU_SYSTEM) -cdrom $(ISO_OUTPUT)
	
$(BUILD_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)%.o: %.asm
	@mkdir -p $(dir $@)
	$(ASSEMBLER) -felf32 $< -o $@

.PHONY: format
format: 
	@find . -path ./kernel/boot -prune -o -iname '*.c' -print -o -iname '*.h' -print | xargs clang-format -i

.PHONY: clean
clean: $(BUILD_DIR)
	@rm -rf $(BUILD_DIR)* $(BIN_OUTPUT) $(ISO_OUTPUT)