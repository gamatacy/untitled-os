NASM=nasm
NASM_FLAGS=-f elf64

LD=ld
LD_FLAGS=--nmagic --script=$(LINKER)

CC=gcc 
CFLAGS=-Wall -c -g -ffreestanding -mgeneral-regs-only

GRUB=grub-mkrescue
GRUB_FLAGS=-o

LINKER=x86_64/boot/linker.ld

ISO_DIR=isofiles
ISO_BOOT_DIR := $(ISO_DIR)/boot

BUILD_DIR=build

x86_64_asm_source_files := $(shell find x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

kernel_source_files := $(shell find kernel -name *.c)
kernel_object_files := $(patsubst kernel/%.c, build/kernel/%.o, $(kernel_source_files))

kernel_asm_source_files := $(shell find kernel -name *.asm)
kernel_asm_object_files := $(patsubst kernel/%.asm, build/kernel/%.o, $(kernel_asm_source_files))

object_files := $(x86_64_asm_object_files) $(kernel_object_files) $(kernel_asm_object_files)

build/%.o: %.asm
	mkdir -p $(dir $@) && \
	$(NASM) $(NASM_FLAGS) $< -o $@

build/%.o: %.c
	mkdir -p $(dir $@) && \
	$(CC) $(CFLAGS) $< -o $@

$(ISO_BOOT_DIR)/kernel.bin: $(object_files)
	$(LD) $(LD_FLAGS) --output=$@ $^

$(ISO_DIR)/kernel.iso: $(ISO_BOOT_DIR)/kernel.bin
	$(GRUB) $(GRUB_FLAGS) $@ $(ISO_DIR)

build_kernel: $(ISO_BOOT_DIR)/kernel.bin
build_iso: $(ISO_DIR)/kernel.iso

QEMU=qemu-system-x86_64
QEMU_FLAGS=-cdrom

# -s -S -kernel
# tap adapter 

qemu: $(ISO_DIR)/kernel.iso
	$(QEMU)  \
	$(QEMU_FLAGS) \
	$(ISO_DIR)/kernel.iso

clean: 
	rm -rf $(BUILD_DIR)
	rm -f $(ISO_DIR)/kernel.*
	rm -f $(ISO_DIR)/**/kernel.*

install:
	apt install xorriso
	apt install mtools
	apt install qemu-system-x86 