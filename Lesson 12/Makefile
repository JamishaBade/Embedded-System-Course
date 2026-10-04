CC = avr-gcc
CFLAGS = -DF_CPU=16000000UL -Og -Wall -Wextra -Wpedantic -g -mmcu=atmega328p -std=gnu17

.PHONY: all clean

all: main.elf

main.elf: main.o twi.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c twi.h
	$(CC) $(CFLAGS) -MM -MF main.d main.c
	$(CC) $(CFLAGS) -c main.c

twi.o: twi.c twi.h
	$(CC) $(CFLAGS) -MM -MF twi.d twi.c
	$(CC) $(CFLAGS) -c twi.c

clean:
	rm -f *.d *.o *.elf

-include $(wildcard *.d)
