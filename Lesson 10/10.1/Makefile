CC = avr-gcc
CFLAGS = -DF_CPU=16000000UL -Og -Wall -Wextra -Wpedantic -g -mmcu=atmega328p -std=gnu17

.PHONY: all clean

all: digital.elf

digital.elf: main.o digital.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c digital.h
	$(CC) $(CFLAGS) -MM -MF main.d main.c
	$(CC) $(CFLAGS) -c main.c

digital.o: digital.c digital.h
	$(CC) $(CFLAGS) -MM -MF digital.d digital.c
	$(CC) $(CFLAGS) -c digital.c

clean:
	rm -f *.d *.o *.elf

-include $(wildcard *.d)
