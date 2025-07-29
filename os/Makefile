CROSS_PREFIX = i386-elf-
CC      = $(CROSS_PREFIX)gcc
LD      = $(CROSS_PREFIX)ld
AS      = $(CROSS_PREFIX)as
OBJCOPY = $(CROSS_PREFIX)objcopy

BUILD_DIR = build

# Fichiers sources
SRC_C    := $(shell find kernel -name "*.c" | sort | uniq)
SRC_ASM  := $(shell find kernel -name "*.asm" | sort | uniq)
SRC_S    := $(shell find kernel -name "*.S" | sort | uniq)

# Objets générés
OBJ_C    := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_C))
OBJ_ASM  := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(SRC_ASM))
OBJ_S    := $(patsubst %.S, $(BUILD_DIR)/%.o, $(SRC_S))

DEPS := $(OBJ_C:.o=.d) $(OBJ_S:.o=.d)

# Include headers
INCLUDE_DIRS := $(shell find kernel -type f -name "*.h" -exec dirname {} \; | sort -u)
INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_DIRS))

CFLAGS  = -m32 -ffreestanding -nostdlib -fno-pie -Wall -Wextra -MD $(INCLUDE_FLAGS)
LDFLAGS = -T linker.ld -nostdlib

all: os.img

# Compilation .c
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation .S
$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation .asm
$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

# Bootloader
boot.bin: boot.asm
	nasm -f bin $< -o $@

# Lien du kernel
kernel.bin: $(OBJ_ASM) $(OBJ_S) $(OBJ_C) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJ_ASM) $(OBJ_S) $(OBJ_C)
	$(OBJCOPY) -O binary $@ $@

# Générer image disque
os.img: boot.bin kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=boot.bin of=$@ conv=notrunc bs=512 seek=0
	dd if=kernel.bin of=$@ conv=notrunc bs=512 seek=1

run: os.img
	qemu-system-i386 -fda os.img -vga std

print-src:
	@echo "Fichiers sources C :"
	@echo $(SRC_C) | tr ' ' '\n'
	@echo "\nFichiers sources ASM :"
	@echo $(SRC_ASM) | tr ' ' '\n'
	@echo "\nFichiers sources .S :"
	@echo $(SRC_S) | tr ' ' '\n'

print-objs:
	@echo "Fichiers objets C :"
	@echo $(OBJ_C) | tr ' ' '\n'
	@echo "\nFichiers objets ASM :"
	@echo $(OBJ_ASM) | tr ' ' '\n'
	@echo "\nFichiers objets .S :"
	@echo $(OBJ_S) | tr ' ' '\n'


clean:
	rm -rf $(BUILD_DIR) *.bin *.img kernel.bin

-include $(DEPS)
