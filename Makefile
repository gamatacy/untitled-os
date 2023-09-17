NASM=nasm
NASM_FLAGS=-f elf64

LD=ld
LD_FLAGS=--nmagic --output=kernel.bin --script=$(LINKER)

GRUB=grub-mkrescue
GRUB_FLAGS=-o

LINKER=x86_64/boot/linker.ld

BOOT_SRC_DIR=x86_64/boot/
BUILD_DIR=build/

ISO_DIR=isofiles/

BOOT_ASM_SRC=$(wildcard $(BOOT_SRC_DIR)*.asm)
BOOT_OBJ_FILES=$(patsubst $(SRC_DIR)%.asm, $(BUILD_DIR)%.o, $(BOOT_ASM_SRC))

all: $(BOOT_OBJ_FILES)

$(BUILD_DIR)%.o: $(SRC_DIR)%.asm
	@mkdir -p $(BUILD_DIR)$(BOOT_SRC_DIR)
	$(NASM) $(NASM_FLAGS) $< -o $@

build_kernel: $(BOOT_OBJ_FILES)
	$(LD) $(LD_FLAGS) $?
	mv kernel.bin $(ISO_DIR)boot

build_iso: build_kernel
	$(GRUB) $(GRUB_FLAGS) kernel.iso $(ISO_DIR)
	mv kernel.iso $(ISO_DIR)boot

QEMU=qemu-system-x86_64
QEMU_FLAGS=-cdrom

qemu: build_iso
	$(QEMU) $(QEMU_FLAGS) $(ISO_DIR)boot/kernel.iso

clean: 
	rm -rf $(BUILD_DIR)

install:
	sudo apt update
	sudo apt install xorriso
	sudo apt install mtools
	sudo apt install qemu-system-x86 