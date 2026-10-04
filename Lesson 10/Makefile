CC = avr-gcc
CFLAGS = -DF_CPU=16000000UL -Og -Wall -Wextra -Wpedantic -g -mmcu=atmega328p -std=gnu17 -I10.1

.PHONY: all clean

all: main.elf

main.elf: main.o digital.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c 10.1/digital.h
	$(CC) $(CFLAGS) -MM -MF main.d main.c
	$(CC) $(CFLAGS) -c main.c

digital.o: 10.1/digital.c 10.1/digital.h
	$(CC) $(CFLAGS) -MM -MF digital.d 10.1/digital.c
	$(CC) $(CFLAGS) -c 10.1/digital.c -o digital.o

clean:
	rm -f *.d *.o *.elf

-include $(wildcard *.d)
