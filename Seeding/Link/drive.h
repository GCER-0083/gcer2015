//define things for drive.c here

#define WHEEL_DIAMETER 5.7
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 0
#define LEFT_FULL_POWER 100
#define RIGHT_FULL_POWER 100
#define SERVO_OPEN_CLOSE 1
#define SERVO_UP_DOWN 3
#define CLAW_OPEN 890
#define CLAW_DOWN 900
#define CLAW_OPEN_READY CLAW_CLOSED+600
#define CLAW_UP_READY 400
#define LS_LEFT 1
#define LS_RIGHT 0
#define TAPE_VALUE 880
#define PI 3.141592653589793236482
#define BLOCK_GRAB CLAW_CLOSED+200

//tuning constants
#define DrFLC 100
#define DrFRC 98
#define DrBRC 98
#define DrBLC 100
#define Rt 1							
#define Lt 0.99
#define CLAW_CLOSED 110
#define CLAW_UP 77

//tune this value to make driving as accurate as possible
#define CMTOBEMF (866/(PI*WHEEL_DIAMETER))

//claw actions
void enableAllServos();
void raiseClaw();
void raiseClawReady();
void lowerClaw();
void openClaw();
void closeClaw();
void clawCloseBack(float distance, float speed);
//drive actions
void driveForward(float distance, float speed);
void driveBackward(float distance, float speed);
void driveUntilTape(float speed);
void driveUntilLine(float speed);
void turnRight(float degrees/*, float radius*/);
void turnLeft(float degrees/*, float radius*/);
void squareUp(float speed,float time);
void driveUntilET(float speed);
void driveUntilET2(float speed);
void driveUntilTH(float speed);
void driveUntilETFollow(float speed);

//main

void LINK_main();
