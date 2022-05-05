#include <Arduino.h>
#include "../include/uart.h"
#include "../include/sensors.h"

/*** MODE ***/
#define TEST

/*** UART params ***/
constexpr long BAUD = 9600;
constexpr int TIMEOUT = 10;

/*** PINOUT ***/
#define VOLT_SENSOR A0

void setup()
{
  uart_begin(BAUD, TIMEOUT);
}

void loop()
{
  int voltage = get_voltage(VOLT_SENSOR);

#ifdef TEST
  uart_transmit(voltage);
#endif
}