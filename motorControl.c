/**************************************************************
* Class: CSC-615-01 Spring 2023
* Names: Xiao Deng, Axel Biehler, Hann Zhao, Mael Teyssedre
* Student IDs: 920966849, 922975011, 917565433
* GitHub ID: xdeng0
* Project: Term project - Self-Driving Car
* 
* File: motorControl.c
* 
* Description: Individual motor control functions
***************************************************************/

#include "motorControl.h"

/**
 * i2c handle for top motor driver HAT;
 * controls front motors
 */
int frontMotorHandle;

/**
 * i2c handle for bottom motor driver HAT;
 * controls rear motors
 */
int rearMotorHandle;

/**
 * @brief initialize top and bottom motor driver HATs
 */
void motor_init(void)
{
  frontMotorHandle = PCA9685_Init(TOP_HAT_ADDR);
  PCA9685_SetPWMFreq(frontMotorHandle, 100);
  rearMotorHandle = PCA9685_Init(BOTTOM_HAT_ADDR);
  PCA9685_SetPWMFreq(rearMotorHandle, 100);
}

/**
 * @brief run front right motor at specified
 * direction and speed
 * 
 * @param direction motor rotation direction
 * @param speed motor rotation speed
 */
void motor_run_frontRight(DIR direction, UWORD speed)
{
  PCA9685_SetPwmDutyCycle(frontMotorHandle, PWMR, speed);
  if (direction == FORWARD)
  {
    PCA9685_SetLevel(frontMotorHandle, R1, 1);
    PCA9685_SetLevel(frontMotorHandle, R2, 0);
  }
  else
  {
    PCA9685_SetLevel(frontMotorHandle, R1, 0);
    PCA9685_SetLevel(frontMotorHandle, R2, 1);
  }
}

/**
 * @brief run front left motor at specified
 * direction and speed
 * 
 * @param direction motor rotation direction
 * @param speed motor rotation speed
 */
 void motor_run_frontLeft(DIR direction, UWORD speed)
{
  PCA9685_SetPwmDutyCycle(frontMotorHandle, PWML, speed);
  if (direction == FORWARD)
  {
    PCA9685_SetLevel(frontMotorHandle, L1, 0);
    PCA9685_SetLevel(frontMotorHandle, L2, 1);
  }
  else
  {
    PCA9685_SetLevel(frontMotorHandle, L1, 1);
    PCA9685_SetLevel(frontMotorHandle, L2, 0);
  }
}

/**
 * @brief run rear right motor at specified
 * direction and speed
 * 
 * @param direction motor rotation direction
 * @param speed motor rotation speed
 */
void motor_run_rearRight(DIR direction, UWORD speed)
{
  PCA9685_SetPwmDutyCycle(rearMotorHandle, PWMR, speed);
  if (direction == FORWARD)
  {
    PCA9685_SetLevel(rearMotorHandle, R1, 1);
    PCA9685_SetLevel(rearMotorHandle, R2, 0);
  }
  else
  {
    PCA9685_SetLevel(rearMotorHandle, R1, 0);
    PCA9685_SetLevel(rearMotorHandle, R2, 1);
  }
}

/**
 * @brief run rear left motor at specified
 * direction and speed
 * 
 * @param direction motor rotation direction
 * @param speed motor rotation speed
 */
void motor_run_rearLeft(DIR direction, UWORD speed)
{
  PCA9685_SetPwmDutyCycle(rearMotorHandle, PWML, speed);
  if (direction == FORWARD)
  {
    PCA9685_SetLevel(rearMotorHandle, L1, 0);
    PCA9685_SetLevel(rearMotorHandle, L2, 1);
  }
  else
  {
    PCA9685_SetLevel(rearMotorHandle, L1, 1);
    PCA9685_SetLevel(rearMotorHandle, L2, 0);
  }
}

/**
 * @brief stop all motors
 */
void motor_stop()
{
  // stop front motors
  PCA9685_SetPwmDutyCycle(frontMotorHandle, PWML, 0);
  PCA9685_SetPwmDutyCycle(frontMotorHandle, PWMR, 0);

  // stop rear motors
  PCA9685_SetPwmDutyCycle(rearMotorHandle, PWML, 0);
  PCA9685_SetPwmDutyCycle(rearMotorHandle, PWMR, 0);
}

/**
 * @brief close I2C interface for motor driver HATs
 */
void motor_exit()
{
  DEV_ModuleExit(frontMotorHandle);
  DEV_ModuleExit(rearMotorHandle);
}