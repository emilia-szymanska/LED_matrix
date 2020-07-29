#include "shift_register.h"

void shift_reg_init(sh_reg *reg)
{
    sbi(*(reg->direction), reg->ser);
    sbi(*(reg->direction), reg->srclk);
    sbi(*(reg->direction), reg->rclk);

    cbi(*(reg->port), reg->ser);
    cbi(*(reg->port), reg->srclk);
    cbi(*(reg->port), reg->rclk);
}

void shift_bit(sh_reg *reg, uint8_t bit)
{
    if(bit == 0) cbi(*(reg->port), reg->ser);
    else sbi(*(reg->port), reg->ser);
    sbi(*(reg->port), reg->srclk);
    _delay_us(shift_delay);
    cbi(*(reg->port), reg->srclk);
    _delay_us(shift_delay);
}

void shift_byte(sh_reg *reg, uint8_t byte)
{
    for(int i = 0; i < 8; i++) shift_bit(reg, byte & (1<<i));
}

void set_output(sh_reg *reg)
{
    sbi(*(reg->port), reg->rclk);
    _delay_us(shift_delay);
    cbi(*(reg->port), reg->rclk);
    _delay_us(shift_delay);
}
