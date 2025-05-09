# Raw GPIO Kernel Driver for Raspberry Pi Zero 2W

## Description
This is a simple Linux kernel module that controls a GPIO pin by directly accessing hardware registers using `ioremap()`.

## Files
- `gpio_raw_driver.c`: kernel driver
- `gpio-raw-overlay.dts`: Device Tree overlay
- `Makefile`: build script

## Usage
```bash
make
sudo insmod gpio_raw_driver.ko
