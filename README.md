# earth

**earth** is a minimal bare-metal C project for the STM32F101C6T8 microcontroller, designed to help you deeply understand **low-level embedded programming**.

It avoids all vendor libraries (no HAL, no CMSIS) and works purely with **memory-mapped registers**, teaching you how to:
- control GPIO,
- understand the MCU memory map (FLASH, RAM, peripherals),
- configure clocks,
- build + link a minimal embedded binary.

---

## What You’ll Learn

- Register-level programming on STM32F1 series (RCC, GPIO)
- ARM Cortex-M3 memory map + addressing
- Writing embedded C without standard libraries or startup files
- Creating and using a custom linker script
- Building and flashing bare-metal applications with `arm-none-eabi-gcc`

---

## Project Files

| File         | Description                                      |
|-------------|---------------------------------------------------|
| `main.c`    | Blink LED on PC13 using raw register access       |
| `linker.ld` | Custom linker script for FLASH, RAM, and sections |
| `Makefile`  | Build system for arm-none-eabi toolchain          |

---

## Build Instructions

```bash
make
```

To flash the binary (using ST-Link):
```bash
st-flash write blink.elf 0x8000000
```

Or with OpenOCD:
```bash
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program blink.elf verify reset exit"
```
