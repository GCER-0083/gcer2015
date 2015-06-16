#include "template.h"

int main() {
	//wait_for_light(0);
	enableAllServos();
	LINK_main();
	/*enableAllServos();
	openClaw();
	clawCloseBack(30,1);*/
}

void LINK_main() {
	
	//start up
	
	//msleep(300);
	
	//blocks to basket
	//raiseClawReady();
	raiseClaw();
	driveForward(40, 1);
	msleep(200);
	turnLeft(90);
	driveForward(9,1);
	msleep(200);
	turnLeft(85);
	msleep(500);
	//driveForward(2, 1);
	msleep(500);
	raiseClawReady();
	openClaw();
	msleep(400);
	closeClaw();
	
	
	
	//get into position to alley
	raiseClaw();
	driveBackward(3, 1);
	turnLeft(-95);
	squareUp(1,3);
	msleep(200);
	
	raiseClaw();
	turnRight(88);
	closeClaw();
	driveUntilET(1);
	turnRight(98); //bump turn
	driveUntilET2(1);
	driveUntilET(1);
	turnRight(95); //bumpy turn
	lowerClaw();

	
	//drive down first alley for tribbles
	openClaw();
	driveUntilTH(1);
	clawCloseBack(2,1);
	//closeClaw();
	raiseClaw();
	driveBackward(5,1);
	msleep(500);
	
	//turn around down other alley
	raiseClaw();
	turnRight(100);
	squareUp(1, 2);
	turnLeft(-30);
	squareUp(1, 2);
	turnLeft(-20);
	msleep(500);
	driveForward(1, 1);
	turnRight(98);
	msleep(500);
	lowerClaw();
	openClaw();
	
	veerForward(40,1);
	closeClaw();
	raiseClaw();
	driveForward(10,1);
	lowerClaw();
	openClaw();
	driveUntilTH(1);
	clawCloseBack(2,1);
	raiseClaw();
	msleep(1000);
	driveBackward(5,1);
	
	turnRight(100);
	squareUp(1, 2);
	turnLeft(-30);
	squareUp(1, 2);
	turnLeft(-30);
	msleep(500);
	turnRight(100);
	driveUntilET(1);
	turnRight(85);
	driveForward(25,1);
	turnLeft(80);
	raiseClawReady();
	dumpClaw();
	driveBackward(50,1);
}
