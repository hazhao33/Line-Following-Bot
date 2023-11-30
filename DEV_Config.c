/**************************************************************
* Class: CSC-615-01 Spring 2023
* Names: Xiao Deng, Axel Biehler, Hann Zhao, Mael Teyssedre
* Student IDs: 920966849, 922975011, 917565433
* GitHub ID: xdeng0
* Project: Term project - Self-Driving Car
* 
* File: DEV_Config.c
* 
* Description: Functions that handle communication with motor
*              driver hats using I2C. Modified based on
*              Waveshare team's sample code.
***************************************************************/

#include "DEV_Config.h"
#include <pigpio.h>
#include <unistd.h>

#define I2C_BUS 1

/**
 * @brief suspend execution for millisecond intervals
 * 
 * @param msec the number of milliseconds to sleep
 */
void DEV_Delay_ms(UDOUBLE msec)
{
  UDOUBLE i;
  for (i = 0; i < msec; i++)
  {
    usleep(1000);
  }
}

/**
 * @brief write a byte to the specified register
 *        of the device associated with handle
 * 
 * @param handle I2C handle associated with device
 * @param reg register to write
 * @param value data to be written
 */
void I2C_Write_Byte(int handle, uint8_t reg, uint8_t value)
{
  i2cWriteByteData(handle, reg, value);
}

/**
 * @brief read a byte from the specified register
 *        of the device associated with handle
 *
 * @param handle I2C handle associated with device
 * @param reg register to read
 * @return int byte read
 */
int I2C_Read_Byte(int handle, uint8_t reg)
{
  return i2cReadByteData(handle, reg);
}

/**
 * @brief open I2C interface at specified address
 * 
 * @param addr device I2C address
 * @return int I2C handle
 */
int DEV_I2C_Init(uint8_t addr)
{
  int handle;
  handle = i2cOpen(I2C_BUS, addr, 0);
  return handle;
}

/**
 * @brief close I2C device associated with handle
 * 
 * @param handle I2C handle associated with the device
 *               to be closed
 */
void DEV_ModuleExit(int handle)
{
  i2cClose(handle);
}