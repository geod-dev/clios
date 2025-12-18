CC = gcc
CFLAGS = -fno-pic -m32 -ffreestanding -nostdlib -nostdinc -O2 -Wall -Wextra -Werror -mno-red-zone
LD = ld -m elf_i386
AS = as --32
RM = rm -f

BUILD = build

ASM_SRC = $(shell find arch -name '*.s')
ASM_OBJ = $(patsubst arch/%.s,$(BUILD)/arch/%.o,$(filter arch/%,$(ASM_SRC)))

C_SRC := $(shell find kernel -name '*.c') $(shell find arch -name '*.c')
C_OBJ := $(patsubst kernel/%.c,$(BUILD)/kernel/%.o,$(filter kernel/%,$(C_SRC))) \
			  $(patsubst arch/%.c,$(BUILD)/arch/%.o,$(filter arch/%,$(C_SRC)))
KERNEL_INC = -Iinclude

LINKER_SCRIPT = linker/linker.ld
OUTPUT_BIN = $(BUILD)/cli_os.bin

GRUB_BIN = iso/boot/cli_os.bin
ISO_OBJ = $(BUILD)/cli_os.iso

all: main

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(KERNEL_INC) -c $< -o $@

$(BUILD)/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $< -o $@

$(OUTPUT_BIN): $(ASM_OBJ) $(C_OBJ)
	$(LD) -T $(LINKER_SCRIPT) -o $(OUTPUT_BIN) $(ASM_OBJ) $(C_OBJ)

$(ISO_OBJ): $(OUTPUT_BIN) | $(BUILD)
	cp $(OUTPUT_BIN) $(GRUB_BIN)
	grub-mkrescue -o $(ISO_OBJ) iso/

main: $(ISO_OBJ)

run: $(ISO_OBJ)
	qemu-system-x86_64 -cdrom $(ISO_OBJ) -display gtk -serial stdio

clean:
	$(RM) $(ASM_OBJ) $(C_OBJ) $(OUTPUT_BIN) $(GRUB_BIN)

fclean: clean
	$(RM) $(ISO_OBJ)

re: fclean main

.PHONY: all main clean fclean re boot kernel link
