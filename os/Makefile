CROSS_PREFIX = i386-elf-
CC      = $(CROSS_PREFIX)gcc
LD      = $(CROSS_PREFIX)ld
AS      = $(CROSS_PREFIX)as
OBJCOPY = $(CROSS_PREFIX)objcopy

BUILD_DIR = build

# Trouver tous les .c et .asm dans kernel/
SRC_C   := $(shell find kernel -name "*.c")
SRC_ASM := $(shell find kernel -name "*.asm")

# Créer les chemins .o dans build/
OBJ_C   := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_C))
OBJ_ASM := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(SRC_ASM))

DEPS := $(OBJ_C:.o=.d)

# Trouver tous les dossiers contenant des headers
INCLUDE_DIRS := $(shell find kernel -type f -name "*.h" -exec dirname {} \; | sort -u)
INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_DIRS))

CFLAGS  = -m32 -ffreestanding -nostdlib -fno-pie -Wall -Wextra -MD $(INCLUDE_FLAGS)
LDFLAGS = -T linker.ld -nostdlib

all: os.img

# Compilation du bootloader
boot.bin: boot.asm
	nasm -f bin $< -o $@

# Créer les .o dans build/ avec dossiers intermédiaires
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

# Link du noyau
kernel.bin: $(OBJ_C) $(OBJ_ASM) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJ_ASM) $(OBJ_C)
	$(OBJCOPY) -O binary $@ $@

# Image disque bootable
os.img: boot.bin kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=boot.bin of=$@ conv=notrunc bs=512 seek=0
	dd if=kernel.bin of=$@ conv=notrunc bs=512 seek=1

# Exécuter dans QEMU
run: os.img
	qemu-system-i386 -fda os.img -vga std

clean:
	rm -rf $(BUILD_DIR) *.bin *.img kernel.bin

# Inclusion auto des dépendances générées par -MD
-include $(DEPS)
