CROSS_PREFIX = i386-elf-
CC      = $(CROSS_PREFIX)gcc
LD      = $(CROSS_PREFIX)ld
AS      = $(CROSS_PREFIX)as
OBJCOPY = $(CROSS_PREFIX)objcopy

BUILD_DIR = build

# Trouver tous les fichiers source
SRC_C    := $(shell find kernel -name "*.c")
SRC_ASM  := $(shell find kernel -name "*.asm")
SRC_S    := $(shell find kernel -name "*.S")

# Fichiers objets
OBJ_C    := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_C))
OBJ_ASM  := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(SRC_ASM))
OBJ_S    := $(patsubst %.S, $(BUILD_DIR)/%.o, $(SRC_S))

DEPS := $(OBJ_C:.o=.d) $(OBJ_S:.o=.d)

# Dossiers des headers
INCLUDE_DIRS := $(shell find kernel -type f -name "*.h" -exec dirname {} \; | sort -u)
INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_DIRS))

CFLAGS  = -m32 -ffreestanding -nostdlib -fno-pie -Wall -Wextra -MD $(INCLUDE_FLAGS)
LDFLAGS = -T linker.ld -nostdlib

all: os.img

# Bootloader
boot.bin: boot.asm
	nasm -f bin $< -o $@

# Compilation .c
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation .S (ASM avec cpp)
$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation .asm (NASM)
$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

# Link kernel
kernel.bin: $(OBJ_C) $(OBJ_S) $(OBJ_ASM) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJ_ASM) $(OBJ_S) $(OBJ_C)
	$(OBJCOPY) -O binary $@ $@

# Générer image disque
os.img: boot.bin kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=boot.bin of=$@ conv=notrunc bs=512 seek=0
	dd if=kernel.bin of=$@ conv=notrunc bs=512 seek=1

run: os.img
	qemu-system-i386 -fda os.img -vga std

clean:
	rm -rf $(BUILD_DIR) *.bin *.img kernel.bin

-include $(DEPS)
