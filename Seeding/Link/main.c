#include "template.h"

void blocks () {
	//start up

	//msleep(300);
	
	//blocks to basket
	//raiseClawReady();
	raiseClaw();
	driveForward(39, 1);
	msleep(200);
	turnLeft(100);
	driveForward(9,1);
	msleep(200);
	turnLeft(80);
	msleep(500);
	//driveForward(2, 1);
	msleep(500);
	raiseClawReady();
	openClaw();
	msleep(400);
	closeClaw();
	
	//get into position to alley
	raiseClaw();
	driveBackward(1, 1);
	turnLeft(-95);
	squareUp(1,3);
	msleep(200);
}

void prepare() {

	raiseClaw();
	turnRight(75);
	closeClaw();
	//driveUntilET(1);
	driveUntilET(1);
	turnRight(90); //bump turn
	driveUntilET2(1);
	driveUntilET(1);
	driveForward(3, 1);
	turnRight(95); //bumpy turn
}

void lane1() {
	//drive down first alley for tribbles
	lowerClaw();
	openClaw();
	driveUntilTH(1);
	clawCloseBack(1.5,1);
	//closeClaw();
	raiseClaw();
	driveBackward(15,1);
	msleep(500);
	turnLeft(-93);
	squareUp(1, 2);
	
}

void driveToLane () {
	driveForward(1, 1);
	turnRight(100);
	driveUntilET(1);
}

void throughLane () {
	driveForward(10, 1);
	lowerClaw();
	openClaw();
	driveUntilTH(1);
	clawCloseBack(1,1);
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
	laneOutDump();
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
}

