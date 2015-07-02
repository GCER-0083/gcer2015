#include "template.h"

void blocks () {
	//start up

	//msleep(300);
	
	//blocks to basket
	//raiseClawReady();
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
	openClaw();
	driveForward(57, 1);
	driveUntilTH(1);
	driveBackward(3, 1);
	closeClaw();
	raiseClaw();
	driveBackward(15,1);
	msleep(500);
	turnLeft(-93);
	squareUp(1, 2);
}

void driveToLane () {
	raiseClaw();
	turnRight(93);
	driveUntilET(1);
}

void throughLane () {
	driveForward(20, 1);
	lowerClaw();
	openClaw();
	driveForward(60, 1);
	driveUntilTH(1);
	driveBackward(3, 1);
	closeClaw();
	
	driveBackward(30, 1);
	raiseClawReady();
	driveForward(5, 1);
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

void laneOutDump () {
	turnRight(85);
	driveUntilET(1);
	turnRight(85);
	driveForward(25,1);
	turnLeft(80);
	raiseClawReady();
	dumpClaw();
	driveBackward(50,1);
}

void lane2Dump () {
	driveToLane();
	throughLane();
	laneSquareUp();
	//laneOutDump();
}


void LINK_main() {
	blocks ();
	prepare ();
	lane1 ();
	lane2Dump();
}
	
int main() {
	//wait_for_light(0);
	enableAllServos();
	LINK_main();
//	raiseClaw();
//	turnRight(90);
}

