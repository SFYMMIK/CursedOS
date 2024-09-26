# Directories and files
ISO_DIR = iso
BOOT_DIR = $(ISO_DIR)/boot
RC_DIR = $(ISO_DIR)/rc
KERNEL_BIN = $(BOOT_DIR)/kernel.bin
BOOTLOADER_BIN = $(BOOT_DIR)/bootloader.bin
STARTUP_RC = $(RC_DIR)/startup.rc

# Output ISO file
ISO = CursedOS.iso

# Toolchain
CC = gcc
LD = ld
NASM = nasm

# Kernel and bootloader source files
KERNEL_SRC = kernel/kernel.c kernel/terminal.c kernel/shell.c kernel/fs.c kernel/startup.c
BOOTLOADER_SRC = bootloader/bootloader.asm

# Compiler and linker flags
CFLAGS = -ffreestanding -O2 -Wall -Wextra -Ikernel/include
LDFLAGS = -T linker.ld

# Create the bootable ISO
all: $(ISO)

# Compile the kernel
$(KERNEL_BIN): $(KERNEL_SRC)
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o
	$(CC) $(CFLAGS) -c kernel/terminal.c -o terminal.o
	$(CC) $(CFLAGS) -c kernel/shell.c -o shell.o
	$(CC) $(CFLAGS) -c kernel/fs.c -o fs.o
	$(CC) $(CFLAGS) -c kernel/startup.c -o startup.o
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) kernel.o terminal.o shell.o fs.o startup.o

# Assemble the bootloader
$(BOOTLOADER_BIN): $(BOOTLOADER_SRC)
	$(NASM) -f bin $(BOOTLOADER_SRC) -o $(BOOTLOADER_BIN)

# Create the ISO file system structure
$(ISO_DIR): $(KERNEL_BIN) $(BOOTLOADER_BIN)
	@echo "Creating ISO directory structure..."
	mkdir -p $(BOOT_DIR)
	mkdir -p $(RC_DIR)
	cp $(KERNEL_BIN) $(BOOT_DIR)
	cp $(BOOTLOADER_BIN) $(BOOT_DIR)
	cp rc/startup.rc $(RC_DIR)

# Generate the bootable ISO using grub-mkrescue
$(ISO): $(ISO_DIR)
	@echo "Generating ISO image..."
	grub-mkrescue -o $(ISO) $(ISO_DIR) -- -iso-level 3 -boot-info-table

# Clean up generated files
clean:
	rm -rf *.o $(KERNEL_BIN) $(BOOTLOADER_BIN) $(ISO_DIR) $(ISO)
