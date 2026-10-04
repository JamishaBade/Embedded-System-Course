#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << DDB5);

    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);

    while (1) {
        if ((PIND & (1 << PIND2)) == 0) {
            PORTB |= (1 << PORTB5);
        } else {
            PORTB &= ~(1 << PORTB5);
        }

        _delay_ms(10);
    }
}
