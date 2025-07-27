# Nom du compilateur croisé
CROSS_PREFIX = i386-elf-
CC = $(CROSS_PREFIX)gcc
AS = $(CROSS_PREFIX)as
LD = $(CROSS_PREFIX)ld

# Options de compilation
CFLAGS = -m32 -ffreestanding -nostdlib -fno-pie
LDFLAGS = -T linker.ld -nostdlib

# Cible principale
all: os.img

# Compilation du bootloader
boot.bin: boot.asm
	nasm -f bin $< -o $@

# Compilation du point d'entrée ASM
kernel_entry.o: kernel_entry.asm
	nasm -f elf32 $< -o $@

# Compilation du noyau C
kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link du noyau en ELF, puis conversion en binaire brut
kernel.bin: kernel_entry.o kernel.o linker.ld
	$(LD) $(LDFLAGS) kernel_entry.o kernel.o -o $@
	objcopy -O binary $@ $@

# Création de l'image disque bootable
os.img: boot.bin kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=boot.bin of=$@ conv=notrunc bs=512 seek=0
	dd if=kernel.bin of=$@ conv=notrunc bs=512 seek=1

# Lancer l'OS dans QEMU
run: os.img
	qemu-system-i386 -fda os.img

# Nettoyage
clean:
	rm -f *.bin *.o *.img
