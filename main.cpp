#include <Arduino.h>
#include "../include/uart.h"
#include "../include/sensors.h"

/*** SWITCHES
LOG - log voltage
WORK - send voltage to UART
*/
#define WORK

/*** UART params ***/
constexpr long BAUD = 115200;
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

#ifdef WORK
  uart_transmit(voltage);
#endif

#ifdef LOG
  /************************** Set header and params to log **********************************/
  const String header = "time,voltage";
  const long log_parametrs[] = {millis(), voltage};
  /********************************************************************************************/

  const int NumOfParams = sizeof(log_parametrs) / sizeof(log_parametrs[0]);
  log_uart(header, log_parametrs, NumOfParams);
#endif
}