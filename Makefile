NASM=nasm
NASM_FLAGS=-f elf64

LD=ld
LD_FLAGS=--nmagic --output=kernel.bin --script=$(LINKER)

CC=gcc 
CFLAGS=-Wall -c -ffreestanding

GRUB=grub-mkrescue
GRUB_FLAGS=-o

LINKER=x86_64/boot/linker.ld

ISO_DIR=isofiles/

x86_64_asm_source_files := $(shell find x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

kernel_source_files := $(shell find kernel -name *.c)
kernel_object_files := $(patsubst kernel/%.c, build/kernel/%.o, $(kernel_source_files))

object_files := $(x86_64_asm_object_files) $(kernel_object_files)

$(x86_64_asm_object_files): build/x86_64/%.o : x86_64/%.asm
	mkdir -p $(dir $@) && \
	$(NASM) $(NASM_FLAGS) $(patsubst build/x86_64/%.o, x86_64/%.asm, $@) -o $@

$(kernel_object_files): build/kernel/%.o : kernel/%.c
	mkdir -p $(dir $@) && \
	$(CC) $(CFLAGS) $(patsubst build/kernel/%.o, kernel/%.c, $@) -o $@

build_kernel: $(object_files)
	$(LD) $(LD_FLAGS) $?
	mv kernel.bin $(ISO_DIR)boot

build_iso: build_kernel
	$(GRUB) $(GRUB_FLAGS) kernel.iso $(ISO_DIR)
	mv kernel.iso $(ISO_DIR)boot

QEMU=qemu-system-x86_64
QEMU_FLAGS=-cdrom

# -s -S -kernel
# tap adapter 

qemu: build_iso	
	$(QEMU) $(QEMU_FLAGS) $(ISO_DIR)boot/kernel.iso

clean: 
	rm -rf $(BUILD_DIR)
	rm -f $(ISO_DIR)boot/kernel.iso

install:
	sudo apt install xorriso
	sudo apt install mtools
	sudo apt install qemu-system-x86 