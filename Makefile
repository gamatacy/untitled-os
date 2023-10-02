NASM=nasm
NASM_FLAGS=-f elf64

LD=ld
LD_FLAGS=--nmagic --script=$(LINKER)

CC=gcc 
CFLAGS=-Wall -c -ffreestanding -mgeneral-regs-only

GRUB=grub-mkrescue
GRUB_FLAGS=-o

LINKER=x86_64/boot/linker.ld

ISO_DIR=isofiles/

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

build_kernel: $(object_files)
	$(LD) $(LD_FLAGS) --output=kernel.bin $?
	mv kernel.bin $(ISO_DIR)boot

build_iso: build_kernel
	$(GRUB) $(GRUB_FLAGS) kernel.iso $(ISO_DIR)
	mv kernel.iso $(ISO_DIR)boot

QEMU=qemu-system-x86_64
QEMU_FLAGS=-cdrom

# -s -S -kernel
# tap adapter 

qemu: build_iso
	$(QEMU)  \
	$(QEMU_FLAGS) \
	$(ISO_DIR)boot/kernel.iso

clean: 
	rm -rf $(BUILD_DIR)
	rm -f $(ISO_DIR)boot/kernel.*

install:
	apt install xorriso
	apt install mtools
	apt install qemu-system-x86 