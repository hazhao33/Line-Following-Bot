/**************************************************************
* Class: CSC-615-01 Spring 2023
* Names: Xiao Deng, Axel Biehler, Hann Zhao, Mael Teyssedre
* Student IDs: 920966849, 922975011, 917565433
* GitHub ID: xdeng0
* Project: Term project - Self-Driving Car
* 
* File: motorControl.h
* 
* Description: Header file for functions controlling motors
***************************************************************/

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "PCA9685.h"

#define TOP_HAT_ADDR 0x50    // I2C address of top motor driver hat
#define BOTTOM_HAT_ADDR 0x40 // I2C address of bottom motor driver hat

/**
 * channels for left motors
 */
#define L1   PCA_CHANNEL_3
#define L2   PCA_CHANNEL_4

/**
 * channels for right motors
 */
#define R1   PCA_CHANNEL_1
#define R2   PCA_CHANNEL_2

#define PWMR PCA_CHANNEL_0 // PWM channel for right motors
#define PWML PCA_CHANNEL_5 // PWM channel for left motors

/**
 * @brief motor rotation directions
 */
typedef enum {
  FORWARD,
  BACKWARD
} DIR;

void motor_init(void);
void motor_stop(void);
void motor_exit(void);
void motor_run_frontRight(DIR direction, UWORD speed);
void motor_run_frontLeft(DIR direction, UWORD speed);
void motor_run_rearRight(DIR direction, UWORD speed);
void motor_run_rearLeft(DIR direction, UWORD speed);

#endif