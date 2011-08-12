CPU = atmega168
F_CPU = 8000000
OPT = s

CSTANDARD = -std=gnu99
CDEFS = -DF_CPU=$(F_CPU)
CWARN = -Wall -Wstrict-prototypes
CTUNING = -ffreestanding -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums  -fwhole-program -Wl,--relax
#-Wl,--relax
CFLAGS = -mmcu=$(CPU) $(CDEFS) -O$(OPT) $(CWARN) $(CSTANDARD) $(CEXTRA) $(CTUNING)

.phony: all clean program

all: hello.hex

program: hello.hex
	avrdude -p m168 -c avrisp2 -U flash:w:hello.hex

clean:
	rm *.o *.elf *.hex *.hex.eep

hello.hex: hello.c
	avr-gcc -c $(CFLAGS) hello.c -o hello.o
	avr-gcc $(CFLAGS) hello.o -o hello.elf
	avr-objcopy -R .eeprom -O ihex hello.elf hello.hex
	avr-size -A hello.elf
