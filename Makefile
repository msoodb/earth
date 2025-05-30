CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -Os -ffreestanding -nostdlib
LDFLAGS = -T linker.ld -nostdlib -Wl,--gc-sections,-no-warn-rwx-segments

all: blink.elf blink.bin

blink.elf: main.c
	$(CC) $(CFLAGS) main.c -o blink.elf $(LDFLAGS)

blink.bin: blink.elf
	$(OBJCOPY) -O binary blink.elf blink.bin

flash: blink.bin
	st-flash write blink.bin 0x8000000

clean:
	rm -f blink.elf blink.bin
