#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H
#include <stdint.h>
#include <Arduino.h>

//74HC595 shift register model

#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)

#define shift_delay 0.20

typedef struct shift_register
{
    volatile uint8_t *direction;
    volatile uint8_t *port;
    uint8_t ser;        //data
    uint8_t srclk;      //shifting
    uint8_t rclk;       //seeing output
} sh_reg;

void shift_reg_init(sh_reg *reg);
void shift_bit(sh_reg *reg, uint8_t bit);
void shift_byte(sh_reg *reg, uint8_t byte);
void set_output(sh_reg *reg);


#endif