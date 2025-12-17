CC = clang
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LD = ld
AS = as --64
RM = rm -f

BUILD = build

BOOT_SRC = arch/x86_64/boot.s
BOOT_OBJ = $(BUILD)/boot.o

KERNEL_SRC = kernel/kernel.c
KERNEL_OBJ = $(BUILD)/kernel.o

LINKER_SCRIPT = linker/linker.ld
OUTPUT_BIN = $(BUILD)/cli_os.bin

GRUB_BIN = iso/boot/cli_os.bin
ISO_OBJ = $(BUILD)/cli_os.iso

all: main

$(BUILD):
	mkdir -p $(BUILD)

$(BOOT_OBJ): $(BOOT_SRC) | $(BUILD)
	$(AS) $(BOOT_SRC) -o $(BOOT_OBJ)

$(KERNEL_OBJ): $(KERNEL_SRC) | $(BUILD)
	$(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(KERNEL_OBJ)

$(OUTPUT_BIN): $(BOOT_OBJ) $(KERNEL_OBJ)
	$(LD) -T $(LINKER_SCRIPT) -o $(OUTPUT_BIN) $(BOOT_OBJ) $(KERNEL_OBJ)

$(ISO_OBJ): $(OUTPUT_BIN) | $(BUILD)
	cp $(OUTPUT_BIN) $(GRUB_BIN)
	grub-mkrescue -o $(ISO_OBJ) iso/

main: $(ISO_OBJ)

run: $(ISO_OBJ)
	qemu-system-x86_64 -cdrom $(ISO_OBJ) -display gtk -serial stdio

clean:
	$(RM) $(BOOT_OBJ) $(KERNEL_OBJ) $(OUTPUT_BIN) $(GRUB_BIN)

fclean: clean
	$(RM) $(ISO_OBJ)

re: fclean main

.PHONY: all main clean fclean re boot kernel link
