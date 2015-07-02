/**
	drive.c
	Purpose: Holds functions that move different parts of the robot.
	@author Jonas Schill, Andy Wang, Max Simpson
	@version 1.1 2/16/2015
*/

#include "drive.h"

//---------Claw actions---------//

void enableAllServos() {
	enable_servos();
	set_servo_position(SERVO_UP_DOWN, CLAW_DOWN);
	set_servo_position(SERVO_OPEN_CLOSE, BLOCK_GRAB);
	msleep(500);
}

void raiseClaw () {
	set_servo_position(SERVO_UP_DOWN,CLAW_UP);
	msleep(500);
}

void raiseClawReady () {
	set_servo_position(SERVO_UP_DOWN, CLAW_UP_READY);
	msleep(500);
}

void lowerClaw () {
	set_servo_position(SERVO_UP_DOWN,CLAW_DOWN);
	msleep(500);
}

void openClaw () {
	set_servo_position(SERVO_OPEN_CLOSE,CLAW_OPEN);
	msleep(500);
}

void closeClaw () {
	set_servo_position(SERVO_OPEN_CLOSE,CLAW_CLOSED);
	msleep(500);
}

void dumpClaw () {
	closeClaw();
	openClaw();
	closeClaw();
	openClaw();
	closeClaw();
	openClaw();
	closeClaw();
}

//---------Drive Actions---------//

	/**
		Drives the robot forward a specified distance at a specified speed.
		
		@param distance : The distance is measured in cm
		@param speed : The speed is a number between 0 and 1
*/

void clawCloseBack(float distance, float speed) {
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_LEFT,-speed*LEFT_FULL_POWER*DrBLC);
	motor(MOTOR_RIGHT,-speed*RIGHT_FULL_POWER*DrBRC);
	//set_servo_position(SERVO_OPEN_CLOSE,CLAW_CLOSED);
	while(get_motor_position_counter(MOTOR_LEFT)>-distance*CMTOBEMF && get_motor_position_counter(MOTOR_RIGHT)>-distance*CMTOBEMF){
		if (get_motor_position_counter(MOTOR_LEFT) < (-distance*CMTOBEMF)/2 + 10 && get_motor_position_counter(MOTOR_LEFT) > (-distance*CMTOBEMF)/2 - 10)
		{
			set_servo_position(SERVO_OPEN_CLOSE,CLAW_CLOSED);
		}
	}
	ao();
	msleep(400);
}

void driveForward(float distance, float speed) {
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_RIGHT, speed*DrFRC);
	motor(MOTOR_LEFT, speed*DrFLC);
	int i = 0;
	while(get_motor_position_counter(MOTOR_LEFT)< distance*CMTOBEMF  && get_motor_position_counter(MOTOR_RIGHT) < distance*CMTOBEMF) {
	}
	printf("%d\n", get_motor_position_counter(MOTOR_LEFT));
	ao();
}

	/**
		Drives the robot backward a specified distance at a specified speed.
		
		@param distance : The distance is measured in cm
		@param speed : The speed is a number between 0 and 1
*/

void driveBackward(float distance, float speed) {
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_LEFT,-speed*DrBLC);
	motor(MOTOR_RIGHT,-speed*DrBRC);
	while(get_motor_position_counter(MOTOR_LEFT)>-distance*CMTOBEMF && get_motor_position_counter(MOTOR_RIGHT)>-distance*CMTOBEMF){
	}
	ao();
}

	/**
		Drives the robot in a specified direction until it reaches a black line.
		
		@param direction : 0 is forward and 1 is backward
		@param distance : The distance is measured in cm
		@param speed : The speed is a number between 0 and 1
*/

void turnRight(float degrees/*, float radius*/) {
	int check = 0;
	double radius = 14.5;
	double dr = (degrees/360)*2*PI*radius*Rt;
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_LEFT,LEFT_FULL_POWER);
	while(get_motor_position_counter(MOTOR_LEFT)+175<dr*CMTOBEMF) 
	{	
		check = 1;
	} 
	if (check != 1)
	{
		motor(MOTOR_LEFT,-LEFT_FULL_POWER);
		while(get_motor_position_counter(MOTOR_LEFT)+175>dr*CMTOBEMF) {
		}
	}
	ao();
}

	/**
		Drives the robot forward a specified distance at a specified speed.
		
		@param degrees : The distance is measured in cm
		@param radius : The radius of the arc the robot will travel in (in cm)
		@param speed The speed is a number between 0 and 1
*/
void turnLeft(float degrees/*, float radius*/) {
	int check = 0;
	double radius = 14.5;
	double dr = (degrees/360)*2*PI*radius*Lt;
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_RIGHT,100);
	while(get_motor_position_counter(MOTOR_RIGHT)<dr*CMTOBEMF) 
	{	
		check = 1;
	} 
	if (check != 1)
	{
		motor(MOTOR_RIGHT,-RIGHT_FULL_POWER);
		while(get_motor_position_counter(MOTOR_RIGHT)>dr*CMTOBEMF) {
		}
	}
	ao();
}

void squareUp(float speed,float time) {
	motor(MOTOR_RIGHT,speed*-1*LEFT_FULL_POWER);
	motor(MOTOR_LEFT,speed*-1*RIGHT_FULL_POWER);
	msleep(time*1000);
	ao();
}

void driveUntilET(float speed) {
//	printf("Initial ET sensor: %d\n", analog_et(0));
	while (analog_et(0) > 350) {
//	while (1) {
		motor(MOTOR_LEFT, speed*DrFLC);
		motor(MOTOR_RIGHT, speed*DrFRC);
		printf("ET sensor: %d\n", analog_et(0));
	}
	ao();
}

void driveUntilETFollow(float speed) {
//	printf("Initial ET sensor: %d\n", analog_et(0));
	while (analog_et(0) > 270) {
	//while (1) {
		if ( analog_et(0) <= 610 && analog_et(0) >= 520) {
			motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC);
			motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*DrFRC);
		}
		else if (analog_et(0) > 610) {
			motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC-20);
			motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*DrFRC);
		}
		else {
			motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC);
			motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*DrFRC-40);
		}
	}
	ao();
}

void driveUntilTH(float speed) {
	while (analog10(7) > 350) {
		motor(MOTOR_LEFT, speed*DrFLC);
		motor(MOTOR_RIGHT, speed*DrFRC);
	}	
	ao();
}

void driveUntilET2(float speed) {
//	printf("Initial ET sensor: %d\n", analog_et(0));
	while (analog_et(0) < 340) {
//	while (1) {
		motor(MOTOR_LEFT, speed*DrFLC);
		motor(MOTOR_RIGHT, speed*DrFRC);
		printf("ET sensor: %d\n", analog_et(0));
	}
	ao();
}

