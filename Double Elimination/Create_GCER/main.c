#include "generic.h"
#include "createDrive.h"
//#include "newmenu.h"

#define SERV_ARM 2
#define SERV_FLIP 1
//self explanatory
void arm_up()
{
	set_servo_position(SERV_ARM,222);
	msleep(1500);
}
//self explanatory
void arm_down()
{
	set_servo_position(SERV_ARM,1735);
}
//self explanatory
void flip_open()
{
	set_servo_position(SERV_FLIP,300);
	msleep(1000);
}
void flip_close()
{
	set_servo_position(SERV_FLIP,2047);
	msleep(1000);
}
//Picks up cubes by lifting arm slightly and flipping the cover. Should only be used in the beginning
void serv_pick()
{
	set_servo_position(SERV_ARM,1300);
	msleep(2000);
	flip_open();
}
int main()
{
	//init
	create_connect();
	arm_down();
	set_servo_position(SERV_FLIP,2047);
	enable_servos();
	
	//begin
	//serv_pick();
	//arm_down();
	//msleep(500);
	//flip_close();
	
	//drive
	create_left(88,0,200);
	create_block();
	
	create_backward(650,300);
	create_block();
	
	create_right(88,0,200);
	create_block();
	
	arm_up();
	
	create_backward(735,300);
	create_block();
	
	flip_open();
}
