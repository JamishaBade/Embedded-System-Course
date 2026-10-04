# Embedded Systems Course Labs

Arduino and embedded C/C++ lab work from the Cooper Union Summer STEM 2025 Embedded Systems course.

This repository collects the sketches and AVR C programs I used while learning low-level hardware control on an Arduino Uno: digital I/O, button inputs, PWM, analog sensing, serial communication, bitwise operations, state machines, direct register programming, interrupts, and I2C/TWI communication.

## Hardware and Tools

- Arduino Uno
- Arduino IDE or Arduino CLI
- `avr-gcc` and `make` for bare-metal AVR C lessons
- LEDs, RGB LED, push buttons, potentiometers, and resistors
- Optional 7-segment display, 74HC595 shift register, rotary encoder, and I2C sensor such as an MPU-6050
- Serial Monitor for interactive input and debugging
- C/C++ with Arduino APIs such as `pinMode`, `digitalWrite`, `analogRead`, `analogWrite`, `Serial`, `delay`, and `delayMicroseconds`

## Lab Work

| Lab | File | Focus |
| --- | --- | --- |
| Morse SOS blinker | `Lesson 1/1.1.1/1.1.1.ino` | LED output timing, helper functions, dot/dash signaling |
| Variable blink timing | `Lesson 1/1.1.2/1.1.2.ino` | Loop control, changing delay intervals, visual timing ramps |
| 4-bit binary counter | `Lesson 1/1.1.3/1.1.3.ino` | Button input, pull-up resistors, bit shifting, overflow state |
| Button-controlled PWM dimmer | `Lesson 1/1.2/1.2.ino` | Debounced button reads and software PWM brightness levels |
| Potentiometer LED meter | `Lesson 2/2.1/2.1.ino` | ADC reads, thresholds, hysteresis, multi-LED output |
| RGB color mixer | `Lesson 2/2.2/2.2.ino` | Mapping analog inputs to PWM channels, dim toggle |
| Serial RGB controller | `Lesson 2/2.3/2.3.ino` | UART/Serial input parsing, hexadecimal color values, PWM output |
| Traffic light controller | `Lesson 3/3.1/3.1.ino` | Timed state machine and debounced pedestrian request |
| Non-blocking blink | `Lesson 6/6.1/6.1.ino` | Independent timers using `millis()` instead of `delay()` |
| Vending machine FSM | `Lesson 6/6.2/6.2.ino` | Product selection, credit tracking, stock handling, state transitions |
| Quadrature encoder | `Lesson 7/7.1/` | Interrupt-driven rotary encoder module with reusable `.h/.cpp` files |
| Bare-metal blink | `Lesson 8/8.1/main.c` | Direct AVR DDR/PORT register control |
| Bare-metal button input | `Lesson 8/8.2/main.c` | Pull-up input and direct PIN register reads |
| Shift register display | `Lesson 9/main.c` | 74HC595 serial output and 7-segment bit masks |
| GPIO abstraction | `Lesson 10/10.1/` | Arduino pin to AVR register mapping library |
| Bare-metal state machine | `Lesson 10/main.c` | Vending machine logic using the custom GPIO abstraction |
| Timer interrupt clock | `Lesson 11/main.c` | Timer0 overflow ISR and custom millisecond timing |
| TWI/I2C driver | `Lesson 12/` | Interrupt-driven I2C master transfers and sensor register read |
| AVR starter | `AVR/main.c` | Minimal bare-metal AVR blink program |
| 7-segment marquee | `7 Segment Project/work/work.ino` | Multiplexed four-digit display and scrolling message |

## Concepts Practiced

- Configuring GPIO pins for input and output
- Using internal pull-up resistors for active-low buttons
- Debouncing mechanical button input
- Building visible timing behavior with delays and microsecond delays
- Representing counter values with bitwise shifts and masks
- Reading analog sensors with the Arduino ADC
- Smoothing threshold transitions with hysteresis
- Controlling LED brightness and RGB channels with PWM
- Parsing serial input into numeric values for hardware control
- Designing finite state machines for interactive hardware behavior
- Writing AVR C against DDR, PORT, PIN, timer, interrupt, and TWI registers
- Splitting embedded code into reusable source/header modules
- Driving displays with bit masks, shift registers, and multiplexing

## Run a Sketch

1. Open the `.ino` file in the Arduino IDE.
2. Select the Arduino Uno board and the correct serial port.
3. Wire the circuit using the pin constants at the top of the sketch.
4. Upload the sketch.
5. For `Lesson 2/2.3`, open Serial Monitor at `9600` baud and enter a six-character RGB hex value such as `FF00FF`.

## Build Bare-Metal AVR Lessons

The AVR C lessons include Makefiles. From a lesson folder, run:

```sh
make
```

To remove generated build files:

```sh
make clean
```

## Resume Summary

**Embedded Systems Course Labs - Arduino Uno, C/C++**

- Completed hands-on embedded systems labs using Arduino Uno and C/C++, implementing digital I/O, PWM LED control, ADC-based sensor input, serial communication, button debouncing, and bitwise logic.
- Built interactive circuits including an SOS blinker, 4-bit binary counter with overflow indication, potentiometer-driven LED meter with hysteresis, RGB color mixer, serial-controlled RGB LED parser, rotary encoder reader, vending-machine state machine, and multiplexed 7-segment display.
- Wrote bare-metal AVR C using direct register access, custom GPIO abstractions, Timer0 overflow interrupts, shift-register display output, and interrupt-driven TWI/I2C sensor communication.
- Practiced hardware-oriented debugging with the Arduino IDE, Serial Monitor, Makefiles, `avr-gcc`, GPIO pin mapping, active-low inputs, timing loops, and embedded state handling.

## Skills

`C/C++` `Arduino` `Embedded C` `AVR` `GPIO` `PWM` `ADC` `UART/Serial` `I2C/TWI` `Interrupts` `Timers` `Bitwise Operations` `Button Debouncing` `Sensor Input` `7-Segment Displays` `Hardware Debugging`
