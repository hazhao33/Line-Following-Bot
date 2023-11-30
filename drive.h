/**************************************************************
* Class: CSC-615-01 Spring 2023
* Names: Xiao Deng, Axel Biehler, Hann Zhao, Mael Teyssedre
* Student IDs: 920966849, 922975011, 917565433
* GitHub ID: xdeng0
* Project: Term project - Self-Driving Car
* 
* File: drive.h
* 
* Description: Header file for drive functions
***************************************************************/

#ifndef DRIVE_H
#define DRIVE_H

#include "motorControl.h"

void car_start(void);
void car_pause(void);
void car_stop(void);
void goStraight(UWORD speed);
void sidewaysLeft(UWORD speed);
void sidewaysRight(UWORD speed);
void turnRight(UWORD speed);
void turnLeft(UWORD speed);

#endif