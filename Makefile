CC = gcc
LD = ld
AS = as
RM = rm -rf

BUILD = build
ISO_DIR = iso

KERNEL_SRC = $(shell find kernel -name '*.c')
KERNEL_OBJ = $(patsubst kernel/%.c,$(BUILD)/kernel/%.o,$(KERNEL_SRC))
KERNEL_CFLAGS = -m64 -fno-pic -ffreestanding -nostdlib -mno-red-zone -Wall -Wextra -Werror -Iinclude
KERNEL_LDFLAGS = -m elf_x86_64 --oformat binary -T linker/linker64.ld
KERNEL_BIN = $(BUILD)/kernel.bin

ARCH_C_SRC = $(shell find arch -name '*.c')
ARCH_S_SRC = $(shell find arch -name '*.s')
ARCH_C_OBJ = $(patsubst arch/%.c,$(BUILD)/arch/%.o,$(ARCH_C_SRC))
ARCH_S_OBJ = $(patsubst arch/%.s,$(BUILD)/arch/%.o,$(ARCH_S_SRC))

ARCH_CFLAGS = -m32 -fno-pic -ffreestanding -nostdlib -Wall -Wextra
ARCH_ASFLAGS = --32
ARCH_LDFLAGS = -m elf_i386 -T linker/linker32.ld

FINAL_BIN = $(BUILD)/os_image.bin
ISO_IMAGE = $(BUILD)/os_image.iso

all: $(ISO_IMAGE)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/kernel/%.o: kernel/%.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(KERNEL_CFLAGS) -c $< -o $@

$(KERNEL_BIN): $(KERNEL_OBJ)
	$(LD) $(KERNEL_LDFLAGS) -o $@ $^

$(BUILD)/arch/%.o: arch/%.s $(KERNEL_BIN) | $(BUILD)
	mkdir -p $(dir $@)
	$(AS) $(ARCH_ASFLAGS) $< -o $@

$(BUILD)/arch/%.o: arch/%.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(ARCH_CFLAGS) -c $< -o $@

$(FINAL_BIN): $(ARCH_S_OBJ) $(ARCH_C_OBJ)
	$(LD) $(ARCH_LDFLAGS) -o $@ $(ARCH_S_OBJ) $(ARCH_C_OBJ)

$(ISO_IMAGE): $(FINAL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(FINAL_BIN) $(ISO_DIR)/boot/cli_os.bin
	grub-mkrescue -o $(ISO_IMAGE) $(ISO_DIR)

run: $(ISO_IMAGE)
	qemu-system-x86_64 -cdrom $(ISO_IMAGE) -display gtk -serial stdio

clean:
	$(RM) $(BUILD)

fclean: clean
	$(RM) $(ISO_IMAGE)

re: fclean all

.PHONY: all run clean fclean re
