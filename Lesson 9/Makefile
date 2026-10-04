CC = avr-gcc
CFLAGS = -DF_CPU=16000000UL -Og -Wall -Wextra -Wpedantic -g -mmcu=atmega328p -std=gnu17

.PHONY: all clean

all: main.elf

main.elf: main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -MM -MF main.d $<
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f main.d main.o main.elf

-include main.d
