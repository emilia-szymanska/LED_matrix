#include "shift_register.h"

#define SRCLK 4
#define SER 5
#define RCLK 6

#define SRCLK2 0
#define SER2 1
#define RCLK2 2

sh_reg reg;
sh_reg reg2;

void setup()
{
  reg.direction = &DDRD;
  reg.port = &PORTD;
  reg.rclk = RCLK;
  reg.ser = SER;
  reg.srclk = SRCLK;    
  shift_reg_init(&reg);

  reg2.direction = &DDRB;
  reg2.port = &PORTB;
  reg2.rclk = RCLK2;
  reg2.ser = SER2;
  reg2.srclk = SRCLK2;    
  shift_reg_init(&reg2);
}

int main()
{
    init();
    setup();
    uint8_t rows[8] = {0x00, 0x66, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00};   //heart pixels in hex
    while(1)
    {
      for(int i = 0; i < 8; i++)
      {
        shift_byte(&reg, 0x00);           //resetting columns to prevent them from being slightly lighted
        set_output(&reg);
        
        shift_byte(&reg2, ~rows[i]);      //setting rows
        shift_byte(&reg, (1<<i));         //setting columns
        
        set_output(&reg2);
        set_output(&reg);
      }

    }
}
