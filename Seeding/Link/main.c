#include "template.h"

void blocks () {
	//start up

	//msleep(300);
	
	//blocks to basket
	//raiseClawReady();
	//msleep(2000);
	raiseClaw();
	squareUp(1, 1);
	driveForward(39, 1);
	msleep(200);
	turnLeft(100);
	driveForward(9,1);
	msleep(200);
	turnLeft(80);
	msleep(500);
	driveForward(2,1);
	raiseClawReady();
	openClaw();
	msleep(400);
	closeClaw();
	
	//get into position to alley
	raiseClaw();
	driveBackward(2, 1);
	turnLeft(-90);
	squareUp(1,3);
	msleep(200);
}

void prepare() {
	raiseClaw();
	turnRight(84);
	closeClaw();
	driveUntilET(1);
	//driveBackward(1, 1);
	turnRight(120); //bump turn
	driveUntilET2(1);
	driveUntilET(1);
	turnRight(90); //bumpy turn
}

void lane1() {
	//drive down first alley for tribbles
	lowerClaw();
	openClawPart ();
	driveForward(68, 1);
	driveUntilTH(1);
	driveBackward(1.6, 1);
	closeClaw();
	raiseClaw();
	driveBackward(15,1);
	msleep(500);
	turnLeft(-93);
	squareUp(1, 2);
}

void driveToLane () {
	raiseClaw();
	turnRight(95);
	driveUntilET(1);
}

void throughLane () {
	driveForward(20, 1);
	lowerClaw();
	openClawPart ();
	driveForward(60, 1);
	driveUntilTH(1);
	driveBackward(1.5, 1);
	closeClaw();
	raiseClaw();
	//driveBackward(37, 1);
	driveBackward(12, 1);
	turnLeft(-5);
	driveBackward(25, 1);
	set_servo_position(SERVO_UP_DOWN,CLAW_UP_READY-120);
	msleep(8000);
	driveForward(16, 1);
	openClaw();
	closeClaw();
	openClaw();
	closeClaw();
	openClaw();
	closeClaw();
	//clawCloseBack(2,1);
}

void laneSquareUp() {
	raiseClaw();
	msleep(100);
	driveBackward(15,1);
	
	turnLeft(-95);
	squareUp(1, 2);
}

void cube1 () {
	closeClaw();
	raiseClaw();
	turnRight(85);
	driveUntilET(1);
	driveForward(3,1);
	turnLeft(90);
	driveForward(19,1);
	turnRight(97);
	//lowerClaw();
	closeClaw();
	driveForward(28, 1);
	turnRight(-70);
	squareUp(2, 1); 
	
	//square up finish
	
	turnRight(90);
	driveBackward(3,1);
	lowerClaw();
	openBlockClaw();
	driveUntilTH(1);
	driveBackward(1.6,1);
	turnLeft(7);
	openClaw();
	driveForward(10,1);
	closeClaw();
	raiseClaw();
	driveBackward(15,1);
	turnRight(-90);
	squareUp(2, 1);
}

void cube1give() {
	raiseClawReady();
	openClaw();
	closeClaw();
	openClaw();
	closeClaw();
	openClaw();
	closeClaw();
	raiseClaw();
}
	
void cube2 () {
	driveForward(2,1);
	turnLeft(105);
	driveForward(55, 1);
	turnLeft(-80);
	squareUp(2, 1);
	turnLeft(80);
	lowerClaw();
	openClaw();
	driveUntilTH(1);
	driveBackward(1, 1);
	//driveForward(10,1);
	closeClaw();
	raiseClaw();
	driveBackward(40,1);
	turnLeft(-90);
	squareUp(2, 1);
}
	
void back () {
	raiseClaw();
	driveForward(1,1);
	turnRight(95);
	closeClaw();
	driveUntilET(1);
	//driveBackward(1, 1);
	//turnRight(100); //bump turn
	driveForward(5,1);
	driveUntilET2(1);
	//driveBackward(1,1);
	turnRight(94);
	msleep(6000);
	squareUpForward(2,1);
	raiseClawReady();
	openClaw();
	closeClaw();
	driveBackward(10,1);
}

void lane2Dump () {
	driveToLane();
	throughLane();
	laneSquareUp();
}

void LINK_main() {
	blocks ();
	prepare ();
	lane1 ();
	lane2Dump();
	cube1();
	cube2();
	back();
}
	
int main() {
	wait_for_light(1);
	shut_down_in(119);
	enableAllServos();
	LINK_main();
//	raiseClaw();
//	turnRight(90);
}

