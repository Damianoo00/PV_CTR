/**
 * @file main.cpp
 * @author Damian Płaskowicki (damian.plaskowicki.stud@pw.edu.pl)
 * @brief Solar panel simulator with remote control DC supply
 * @version 0.1
 * @date 2022-05-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>
#include "../include/uart.h"
#include "../include/sensors.h"

/**
 * @brief define or remove correct line to switch any mode {#define [param]}
 * @param LOG define to enable logging
 * @param WORK define to enable sending voltage to UART
 *
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
  int voltage = GetVoltage(VOLT_SENSOR);

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