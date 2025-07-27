# Nom des fichiers
BOOT = boot.asm
KERNEL = kernel.asm

BOOT_BIN = boot.bin
KERNEL_BIN = kernel.bin
IMG = os.img

all: $(IMG)

$(BOOT_BIN): $(BOOT)
	nasm -f bin $(BOOT) -o $(BOOT_BIN)

$(KERNEL_BIN): $(KERNEL)
	nasm -f bin $(KERNEL) -o $(KERNEL_BIN)

$(IMG): $(BOOT_BIN) $(KERNEL_BIN)
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	dd if=$(BOOT_BIN) of=$(IMG) conv=notrunc bs=512 seek=0
	dd if=$(KERNEL_BIN) of=$(IMG) conv=notrunc bs=512 seek=1

run: $(IMG)
	qemu-system-i386 -fda $(IMG)

clean:
	rm -f $(BOOT_BIN) $(KERNEL_BIN) $(IMG)
