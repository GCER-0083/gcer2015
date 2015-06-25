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
	motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC);
	motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*DrFRC);
	int i = 0;
	while(get_motor_position_counter(MOTOR_LEFT)< distance*CMTOBEMF  && get_motor_position_counter(MOTOR_RIGHT) < distance*CMTOBEMF) {
      if (++i > 1000) {
	    printf("ET sensor: %d\n", analog_et(0));
		i = 0;
	  }
	}
	printf("%d\n", get_motor_position_counter(MOTOR_LEFT));
	ao();
}
void veerForward(float distance, float speed) {
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC);
	motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*veerFRC);
	while(get_motor_position_counter(MOTOR_LEFT)< distance*CMTOBEMF  && get_motor_position_counter(MOTOR_RIGHT) < distance*CMTOBEMF) {}
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
	motor(MOTOR_LEFT,-speed*LEFT_FULL_POWER*DrBLC);
	motor(MOTOR_RIGHT,-speed*RIGHT_FULL_POWER*DrBRC);
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

void driveUntilLine(float speed) { //TO EDIT 
	motor(MOTOR_LEFT, speed*LEFT_FULL_POWER/2);
	motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER/2); //forward half power
	while (analog(LS_LEFT) < TAPE_VALUE && analog(LS_RIGHT) < TAPE_VALUE) {} //until one sees black
	ao();
	msleep(500);
	if (analog(LS_LEFT) > TAPE_VALUE) //checking which sensor saw black first
	{
		motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER/2); //turn to straighten on line
		//motor(MOTOR_LEFT, -15);
		while (analog(LS_RIGHT) < TAPE_VALUE) {}
		ao();
	}
	if (analog(LS_RIGHT) > TAPE_VALUE) 
	{
		motor(MOTOR_LEFT, speed*LEFT_FULL_POWER/2);
		//motor(MOTOR_RIGHT, -15);
		while (analog(LS_LEFT) < TAPE_VALUE) {}
		ao();
	}
}

void driveUntilTape(float speed) {
	motor(MOTOR_LEFT, speed*LEFT_FULL_POWER/1.5);
	motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER/1.5); //forward half power
	while (analog(LS_LEFT) < TAPE_VALUE && analog(LS_RIGHT) < TAPE_VALUE) {} //until one sees black
	ao();
	msleep(500);
	if (analog(LS_LEFT) > TAPE_VALUE) //checking which sensor saw black first
	{
		motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER/2); //turn to straighten on line
		motor(MOTOR_LEFT, -25);
		while (analog(LS_RIGHT) < TAPE_VALUE) {}
		ao();
	}
	if (analog(LS_RIGHT) > TAPE_VALUE) 
	{
		motor(MOTOR_LEFT, speed*LEFT_FULL_POWER/2);
		motor(MOTOR_RIGHT, -25);
		while (analog(LS_LEFT) < TAPE_VALUE) {}
		ao();
	}
}

	/**
		Makes the robot follow a line forward for a specified distance at a specified speed.
	
		@param distance : The distance the robot should go in cm
		@param speed : a number between 0 and 1
*/
void lineFollowForward(float distance, float speed) {
	
}

	/**
		Makes the robot follow a line forward for a specified distance at a specified speed.
	
		@param distance : The distance the robot should go in cm
		@param speed : a number between 0 and 1
*/
void lineFollowBackward(float distance, float speed) {
	
}

	/**
		Drives the robot a specified number of degrees around a circle of specified radius.
	
		@param degrees : How many degrees the robot should move around the arc
		@param radius : The radius of the arc the robot will travel in (in cm)
		@param speed : The speed is a number between 0 and 1
*/
void turnRight(float degrees/*, float radius*/) {
	int check = 0;
	double radius = 14.3;
	double dr = (degrees/360)*2*PI*radius*Rt;
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_LEFT,LEFT_FULL_POWER);
	while(get_motor_position_counter(MOTOR_LEFT)<dr*CMTOBEMF) 
	{	
		check = 1;
	} 
	if (check != 1)
	{
		motor(MOTOR_LEFT,-LEFT_FULL_POWER);
		while(get_motor_position_counter(MOTOR_LEFT)>dr*CMTOBEMF)
		{
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
	double radius = 14.3;
	double dr = (degrees/360)*2*PI*radius*Lt;
	clear_motor_position_counter(MOTOR_LEFT);
	clear_motor_position_counter(MOTOR_RIGHT);
	motor(MOTOR_RIGHT,RIGHT_FULL_POWER);
	while(get_motor_position_counter(MOTOR_RIGHT)<dr*CMTOBEMF) 
	{	
		check = 1;
	} 
	if (check != 1)
	{
		motor(MOTOR_RIGHT,-RIGHT_FULL_POWER);
		while(get_motor_position_counter(MOTOR_RIGHT)>dr*CMTOBEMF)
		{
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
	while (analog_et(0) > 320) {
//	while (1) {
		motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC);
		motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*DrFRC);
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
	while (analog10(7) > 420) {
		motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC);
		motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*DrFRC);
	}
	ao();
}

void driveUntilET2(float speed) {
//	printf("Initial ET sensor: %d\n", analog_et(0));
	while (analog_et(0) < 320) {
//	while (1) {
		motor(MOTOR_LEFT, speed*LEFT_FULL_POWER*DrFLC);
		motor(MOTOR_RIGHT, speed*RIGHT_FULL_POWER*DrFRC);
		printf("ET sensor: %d\n", analog_et(0));
	}
	ao();
}

void moveServo(int destination, int time, int port) {
	int increment;
	int initAngle = get_servo_position(port);
	int angle = initAngle;
	if(angle < destination) {
		increment = 1;
	} else {
		increment = -1;
	}	
	
	while(abs(angle - destination) > 5) {
		printf("%d\n", angle);
		angle += increment;
		set_servo_position(port, angle);
		msleep(time / abs(destination - initAngle));
	}
}
