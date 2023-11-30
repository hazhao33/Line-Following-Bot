/**************************************************************
* Class: CSC-615-01 Spring 2023
* Names: Xiao Deng, Axel Biehler, Hann Zhao, Mael Teyssedre
* Student IDs: 920966849, 922975011, 917565433
* GitHub ID: xdeng0
* Project: Term project - Self-Driving Car
* 
* File: DEV_Config.h
* 
* Description: Header file for functions interacting with
*              the motor driver hats using I2C interface.
*              Modified based on Waveshare team's sample code.
***************************************************************/

#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <stdint.h>

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

void DEV_ModuleExit(int handle);
int DEV_I2C_Init(uint8_t addr);
void I2C_Write_Byte(int handle, uint8_t reg, uint8_t value);
int I2C_Read_Byte(int handle, uint8_t reg);
void DEV_Delay_ms(UDOUBLE msec);

#endif