#include "template.h"

//main file gets run by robot calls methods in all other files

//create waits at 1:40
//LINK arrives at 1 at 0:43

void playTunes() {
	enableDevices();
	playPowerup();
	playCoin();
}

void pingPongHigh() {
	//raiseLowerArm(ARM_HIGH - 200, 0.5);		//drives with raised arm
	//createDrive(100, 26);	
	//set_servo_position(0,760);
	//sleep(1);
	armMove(ARM_HIGH, 1000, 26, 325);
	//playCoin();
	set_servo_position(ARM_SERVO, 0); 				//gets ping pong ball
	msleep(500);
	//createDriveBack(100, 8);
	//msleep(500);
}

void pingPongMedium() {
	//raiseLowerArm(ARM_MEDIUM - 200, 1);
	//msleep(500);
	createDriveBack(200, 2);
	armMove(ARM_MEDIUM + 500, 1000, 17, -100);		//gets into position
	createTurnLeft(19);
	createDrive(300, 16);
	raiseLowerArm(ARM_HIGH, 500);
	playCoin();
	//gets ping pong
	msleep(500);
	//createDriveBack(100, 12);
	//msleep(500);
}
	
void pingPongLow() {
	//raiseLowerArm(ARM_LOW - 100, 1);
	createDriveBack(175, 3);
	armMove(ARM_LOW + 475, 1000, 9, -150);		//gets into position
	msleep(500);
	createTurnLeft(16);
	createDrive(300, 25);
	raiseLowerArm(ARM_MEDIUM, 500);
	playCoin();
	//gets ping pong	
	createDriveBack(200, 7);
	raiseLowerArm(ARM_DRIVE_HEIGHT-50, 500);
}

void pingPong() {
	pingPongHigh();
	pingPongMedium();
	pingPongLow();
}



void pingPongLow2() {
	
	armMove(ARM_LOW+500, 1000, 10, 100);
	createDrive(350, 11);
	raiseLowerArm(ARM_MEDIUM, 1000);
	playCoin();
	createDriveBack(100, 2);
	armMove(ARM_HIGH, 1000, 15, -100);		//gets into position

}

void basketDump() {
	/*createTurnRight(7);
	createSquareUp(300, 2);
	createDriveBack(100, 5);
	raiseLowerArm(ARM_DOWN, 1000);
	msleep(10*60*1000);
	/*msleep(5000);
	armMove(ARM_MEDIUM + 300, 1000, 35, -200);*/
	set_servo_position(ARM_SERVO, ARM_DRIVE_HEIGHT);
	createDriveBack(200, 5);
	raiseLowerArm(ARM_HIGH+1, 2000);
	//createTurnRight(78);
	createTurnRight(92);
	driveTouch(-200);		
	set_servo_position(ARM_SERVO, ARM_VERY_HIGH);
	createSquareUp(350, 3);
	createDriveBack(100, 4);
	raiseLowerArm(ARM_DOWN+400, 1000);
	msleep(6500);
	set_servo_position(ARM_SERVO, ARM_VERY_HIGH);
	createDriveBack(200, 35);
	set_servo_position(ARM_SERVO, ARM_MEDIUM + 300);
	driveTouch(-200);
	createTurnLeft(80);
	createSquareUp(300, 1);
	set_servo_position(ARM_SERVO, ARM_DRIVE_HEIGHT);
	createDriveBack(200, 5);
	createTurnRight(81);
	//createTurnRight(92);
	driveTouch(-100);
	//armMove(ARM_MEDIUM + 300, 1000, 35, -200);
}

void pingPongMedium2() {
	//createTurnRight(20);
	raiseLowerArm(ARM_LOW+200, 1000);
	createTurnRight(22);
	createDrive(300, 14);
	raiseLowerArm(ARM_HIGH, 1000);		//gets ping pong
	playCoin();
	msleep(500);
}

void pingPongHigh2() {
	createDriveBack(100, 2);
	armMove(ARM_HIGH + 850, 1000, 8, -200);		//gets into position
	msleep(500);
	createTurnRight(19);
	armMove(ARM_HIGH, 1000, 21, 350);		//gets ping pong	
	raiseLowerArm(ARM_HIGH, 500);
	set_servo_position(ARM_SERVO, 0);	//gets ping pong
	playCoin();
	createDriveBack(100, 15);
}

void pingPong2() {
	basketDump();
	pingPongLow2();
	pingPongMedium2();
	pingPongHigh2();
}

void scrape() {
	//raiseLowerArm(ARM_HIGH+1, 3000);
	//msleep(2000);
	createTurnLeft(-35);
	createTurnRight(-35);
	driveTouch(-200);
	createTurnLeft(.1);
	createDrive(100, 3);
	createScrapeBasket();
	sleep(1);
	createTurnRight(.05);
	createDrive(100,3);
	//createTurnRight(.1);
	//createDrive(100, 3);
	createSquareUp(100, 5);
}

void squareAndSound() {
	create_drive_straight(-500);
	playStar();
	msleep(500);
	create_stop();
	create_drive_straight(-200);
	msleep(3000);
}

void preparePingPong() {
	createTurnLeft(54);
	//createSquareUp(500, 3.9);
	//createSquareUp(300, 1.2);
	squareAndSound();
}

void dump() {
	raiseLowerArm(ARM_DRIVE_HEIGHT, 1000);
	createTurnRight(49);
	driveTouch(-400);
	createDrive(300, 125);
	raiseLowerArm(ARM_VERY_HIGH, 1000);
	createTurnLeft(83);
	createSquareUp(200, 3);
	createDriveBack(100,2);
	//createTurnLeft(.5);
	createBasketDump();
	createSquareUp(500, 0.5);
	createDriveBack(150,4);
	
}

void dump2() {
	raiseLowerArm(ARM_DOWN+300, 2000);
	msleep(5000); 
	raiseLowerArm(ARM_VERY_HIGH, 1000);
	createBasketDump();
	/*createDriveBack(100, 45);
	createTurnRight(3);
	raiseLowerArm(ARM_DOWN, 1000);
	msleep(14000);
	raiseLowerArm(ARM_VERY_HIGH, 1000);
	createTurnLeft(1);
	createSquareUp(300, 3);
	createDriveBack(100,2);
	createBasketDump();
	createSquareUp(100, 0.5);*/
}

void createMain() { //This is being programmed for the actual competion now
	
	pingPong();
	preparePingPong();
	pingPong2();
	dump();
	dump2();
	scrape();
}


int main() {
	enableDevices();
	//createDrive(100, 10);
	//raiseLowerArm(ARM_HIGH, 1000);
	//wait_for_light(0);
	shut_down_in(120);
	prepareDevices();
	createMain();
//	playTunes();
	playWin();
	return 0;
}
