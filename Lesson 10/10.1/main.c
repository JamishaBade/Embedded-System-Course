#include "digital.h"

int main(void)
{
    bool button_high = false;

    digital_pin_mode(2, DIGITAL_INPUT_PULLUP);
    digital_pin_mode(13, DIGITAL_OUTPUT);

    while (1) {
        digital_read(2, &button_high);
        digital_write(13, !button_high);
    }
}
