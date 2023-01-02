#include <avr/io.h>
#define LED PD1

//Program to toggle LED after every 50ms. Clock frequency = 16Mhz
// Consider scalar = 1024. New clock frequency = 16/1024 = 15.625KHz
// 1 clk cycle = 1/15.625K = 64 microseconds.
// Timer 0 overflows after 255 ticks. This takes 64 * 255 = 16ms
// Number of overflows = 50/16 = 3 overflows.

void main()
{
  uint8_t timeCount = 0;
  DDRD |= 0x01;
  TCNT0 = 0x00;
  TCCR0 |= (1 << CS00)|(1 << CS02);
  while(1)
  {
    while((TIFR & 0x01) == 0); //Wait till overflow occurs
    TCNT0 = 0x00;
    TIFR = 0x00;
    timeCount++;
    if(timeCount >= 3)
    {
      PORTD ^= (1 << LED);
      timeCount = 0;
    }
  }
}
