#include "generic.h"
#include "createDrive.h"
//#include "newmenu.h"

#define MOT_ARM 1
#define MOT_CLAW 2

#define SERV_GRAB 2

/**
 * Windup function for the create robot. Tightens both claw and arm motors until they stop moving.
 * Includes a print statement for when the arm and claw are tightened.
 */
void windup()
{
	int tightened_claw = 0;
	int tightened_arm = 0;
	
	motor(MOT_ARM,30);
	motor(MOT_CLAW,30);
	
	int counter_arm = gmpc(MOT_ARM);
	int counter_claw = gmpc(MOT_CLAW);
	while(tightened_claw==0||tightened_arm==0)
	{
		msleep(1000);
		if(gmpc(MOT_ARM)<=counter_arm+50)
		{
			tightened_arm=1;
			motor(MOT_ARM,0);
			printf("arm done. previous:%d, current:%d\n",counter_arm,gmpc(MOT_ARM));
		}
		else
			counter_arm = gmpc(MOT_ARM);
		if(gmpc(MOT_CLAW)<=counter_claw+50)
		{
			tightened_claw=1;
			motor(MOT_CLAW,0);
			printf("claw done. previous:%d, current:%d\n",counter_claw,gmpc(MOT_CLAW));
		}
		else
			counter_claw = gmpc(MOT_CLAW);
	}
}
//self explanatory
void claw_open()
{
	set_servo_position(SERV_GRAB,896);
	msleep(200);
}
//self explanatory
void claw_close()
{
	set_servo_position(SERV_GRAB,300);
	msleep(200);
}
//time is the time the arm lifts in milliseconds. holds arm in place.
void arm_lift(int time)
{
	motor(MOT_ARM,100);
	msleep(time);
	motor(MOT_ARM,20);
}
int main()
{
	windup();
	enable_servos();
	claw_open();
	arm_lift(500);
	msleep(2000);
	ao();
	motor(MOT_ARM,-10);
	msleep(500);
	claw_close();
	ao();
	motor(MOT_CLAW,-30);
	msleep(1000);
	motor(MOT_CLAW,0);
	ao();
	arm_lift(5000);
	msleep(5000);
	//windup();
	/*create_left(56,0,500);
	create_block();
	create_backward(700,200);
	create_block();
	create_backward(125,100);
	create_block();*/
	
}
