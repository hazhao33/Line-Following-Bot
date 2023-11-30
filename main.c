/**************************************************************
* Class: CSC-615-01 Spring 2023
* Names: Xiao Deng, Axel Biehler, Hann Zhao, Mael Teyssedre
* Student IDs: 920966849, 922975011, 917565433
* GitHub ID: xdeng0
* Project: Term project - Self-Driving Car
* 
* File: main.c
* 
* Description: main program for the car. Uses threads to
               continuously get the readings of line sensors
               and lidar and maneuver car movement based on
               these readings.
***************************************************************/

#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "drive.h"

#define BUF_SIZE 50
#define TRUE 1
#define FALSE 0

#define LEFT_LINE 23
#define RIGHT_LINE 26

/**
 * @brief used as the condition for while loops in this program
 * 0: Ctrl C not pressed, the while loop continues;
 * 1: Ctrl C pressed, while loop exits
 */
static volatile int ctrlc_pressed;

/* stores the value used to determine if an object is in front of the car */
static volatile int objInFront;

/* line sensors' readouts */
static volatile int onLeftLine;
static volatile int onRightLine;

/**
 * @brief I/O stream of the demo app "ultra_simple"
 * compiled from rplidar library, used for getting
 * scanned data from lidar
 */
FILE* pipe_fp;

/* buffer for storing stdout from ultra_simple */
char readBuf[BUF_SIZE];

/**
 * @brief called by the signal function to handle Ctrl+C signal;
 * changes the condition of the while loops to false
 */
void handler()
{
  ctrlc_pressed = TRUE;
}

/**
 * @brief start routine for leftLineThread that
 * reads and stores left line sensor's data output
 * later used by the followLine function
 */
void* readLeftLine(void* ptr)
{
  while (!ctrlc_pressed)
  {
    onLeftLine = gpioRead(LEFT_LINE);
    usleep(1000);
  }
  return NULL;
}

/**
 * @brief start routine for rightLineThread that
 * reads and stores right line sensor's data output
 * later used by the followLine function
 */
void* readRightLine(void* ptr)
{
  while (!ctrlc_pressed)
  {
    onRightLine = gpioRead(RIGHT_LINE);
    usleep(1000);
  }
  return NULL;
}

/**
 * @brief start routine for lidarThread that
 * reads lidar data from the subprocess' stdout
 * and parses string to determine if an object
 * is detected in the front
 */
void* readLidar(void* ptr)
{
  char* token;
  char* saveptr;
  volatile float angle, distance;

  while (!ctrlc_pressed && fgets(readBuf, BUF_SIZE, pipe_fp))
  {
    token = strtok_r(readBuf, ",", &saveptr);
    angle = atof(token);
    token = strtok_r(NULL, ",", &saveptr);
    distance = atof(token);

    if (angle > 5 && angle < 20)
    {
      if (distance < 300)
      {
        objInFront = TRUE;
      }
      else
      {
        objInFront = FALSE;
      }
    }
  }
  return NULL;
}

/**
 * @brief changes car movement to track line
 * based on line sensor readings
 */
void followLine(void)
{
  if (!onLeftLine && !onRightLine) /* no line detected, go straight */
  {
    goStraight(30);
  }
  else if (onLeftLine && !onRightLine) /* left sensor detects black line, turn left */
  {
    turnLeft(30);
  }
  else if (!onLeftLine && onRightLine) /* right sensor detects black line, turn right */
  {
    turnRight(30);
  }
  else /* both sensors detect black line, in the middle of a turn, keep doing previous movement */
  {
    usleep(100);
  }
}

void avoidObject(void)
{
  /* move sideways to the left until object is no longer in front of the car */
  sidewaysLeft(25);
  while (!ctrlc_pressed && objInFront);

  /* drive past the object*/
  goStraight(30);
  sleep(3);

  /* move sideways to the right until the car gets back to the line */
  sidewaysRight(25);
  while (!ctrlc_pressed && !onLeftLine);
}

int main(void)
{
  /**
   * initialize pigpio library;
   * terminates program if initialization failed
   */
  if (gpioInitialise() < 0)
  {
    fprintf(stderr, "pigpio initialisation failed\n");
    return 1;
  }

  /**
   * set up signal handeling;
   * specifies the handler function to be called
   * when Ctrl+C is pressed
   */
  signal(SIGINT, handler);
  ctrlc_pressed = FALSE;

  /* set RPi GPIO pin 23 and 26 to be input from line sensors */
  gpioSetMode(LEFT_LINE, PI_INPUT);
  gpioSetMode(RIGHT_LINE, PI_INPUT);

  /* creates a pipe to read standard output of ultra_simple to get lidar data */
  pipe_fp = popen("./rplidar_sdk-master/ultra_simple --channel --serial /dev/ttyUSB0 115200", "r");
  if (pipe_fp == NULL)
  {
    perror("popen");
    exit(1);
  }

  car_start();

  /**
   * create one thread for each sensor;
   * each thread will execute their own start routine
   * to monitor the state of its corresponding sensor
   */
  pthread_t lidarThread, leftLineThread, rightLineThread;
  pthread_create(&lidarThread, NULL, readLidar, NULL);
  pthread_create(&leftLineThread, NULL, readLeftLine, NULL);
  pthread_create(&rightLineThread, NULL, readRightLine, NULL);

  while (!ctrlc_pressed)
  {
    /* if obstacle in front, pause the car and wait for the obstacle to clear itself */
    if (objInFront)
    {
      car_pause();
      sleep(2);
      /* if obstacle stays, start going aroud it */
      if (objInFront)
      {
        avoidObject();
      }
    }
    followLine();
  }

  /* wait for all threads to finish before continues execution */
  pthread_join(lidarThread, NULL);
  pthread_join(leftLineThread, NULL);
  pthread_join(rightLineThread, NULL);
  
  car_stop();
  pclose(pipe_fp);
  gpioTerminate();
  return 0;
}