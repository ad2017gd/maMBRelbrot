FLAGS = -masm=intel -Wno-error -c -Os -fno-asynchronous-unwind-tables -ffunction-sections -fdata-sections -nostdinc -nostdlib -nodefaultlibs -fno-builtin -Wl,--gc-sections -fno-stack-protector -ffreestanding -m32 -Wall -I.

boot: boot.c linker.ld
	@gcc ${FLAGS} -S -o boot.s boot.c
	@gcc ${FLAGS} -o boot.o boot.c
	@ld -melf_i386 -static -Tlinker.ld -nostdlib --nmagic -o boot.elf boot.o
	@objcopy -O binary boot.elf BOOT.TMP
	@rm boot.elf boot.o
	{ head -c 512 > BOOT.BIN; } < BOOT.TMP
	@rm BOOT.TMP
	@qemu-system-i386 -serial file:serial.log -accel tcg,thread=multi BOOT.BIN
	
clean:
	rm -rf boot.elf BOOT.BIN boot.o serial.log boot.o boot.s