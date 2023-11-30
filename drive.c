/**************************************************************
* Class: CSC-615-01 Spring 2023
* Names: Xiao Deng, Axel Biehler, Hann Zhao, Mael Teyssedre
* Student IDs: 920966849, 922975011, 917565433
* GitHub ID: xdeng0
* Project: Term project - Self-Driving Car
* 
* File: drive.c
* 
* Description: Functions handling car movement
***************************************************************/

#include "drive.h"

/**
 * @brief start the car
 */
void car_start(void)
{
  motor_init();
}

/**
 * @brief stop the car
 */
void car_stop(void)
{
  motor_stop();
  motor_exit();
}

/**
 * @brief pause car movement
 */
void car_pause(void)
{
  motor_stop();
}

/**
 * @brief drive straight at specified speed
 * 
 * @param speed 0 ~ 100
 */
void goStraight(UWORD speed)
{
  motor_run_frontLeft(FORWARD, speed);
  motor_run_frontRight(FORWARD, speed);
  motor_run_rearLeft(FORWARD, speed);
  motor_run_rearRight(FORWARD, speed);
}

/**
 * @brief drive sideways to the left
 * at specified speed
 */
void sidewaysLeft(UWORD speed)
{
  motor_run_frontRight(FORWARD, speed);
  motor_run_rearRight(BACKWARD, speed);

  motor_run_frontLeft(BACKWARD, speed);
  motor_run_rearLeft(FORWARD, speed);
}

/**
 * @brief drive sideways to the left
 * at specified speed
 */
void sidewaysRight(UWORD speed)
{
  motor_run_frontLeft(FORWARD, speed);
  motor_run_rearLeft(BACKWARD, speed);

  motor_run_frontRight(BACKWARD, speed);
  motor_run_rearRight(FORWARD, speed);
}

/**
 * @brief make a right turn
 */
void turnRight(UWORD speed)
{
  UWORD slowerSpeed = (UWORD) (speed * 0.7);

  /* outside wheels go forward and faster */
  motor_run_frontLeft(FORWARD, speed);
  motor_run_rearLeft(FORWARD, speed);

  /* inside wheels go backwards and slower */
  motor_run_frontRight(BACKWARD, slowerSpeed);
  motor_run_rearRight(BACKWARD, slowerSpeed);
}

/**
 * @brief make a left turn
 */
void turnLeft(UWORD speed)
{
  UWORD slowerSpeed = (UWORD) (speed * 0.7);

  motor_run_frontRight(FORWARD, speed);
  motor_run_rearRight(FORWARD, speed);

  motor_run_frontLeft(BACKWARD, slowerSpeed);
  motor_run_rearLeft(BACKWARD, slowerSpeed);
}