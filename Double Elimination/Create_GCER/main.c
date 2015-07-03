#include "generic.h"
#include "createDrive.h"
//#include "newmenu.h"

#define LIGHT_PORT 0

#define SERV_ARM 2
#define SERV_FLIP 1
//self explanatory
void arm_up()
{
	set_servo_position(SERV_ARM,150);
	msleep(2000);
}
void arm_final()
{
	set_servo_position(SERV_ARM,300);
	msleep(500);
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
	msleep(500);
}
void flip_close()
{
	set_servo_position(SERV_FLIP,2047);
	msleep(1000);
}
//Picks up cubes by lifting arm slightly and flipping the cover. Should only be used in the beginning
void serv_pick()
{
	set_servo_position(SERV_ARM,900);
	msleep(2000);
	flip_open();
	msleep(900);
	set_servo_position(SERV_ARM,1050);
	msleep(900);
	set_servo_position(SERV_ARM,1500);
	msleep(1000);
}
int main()
{
	//init
	//sleep(10);
	create_connect();
	arm_down();
	set_servo_position(SERV_FLIP,2047);
	enable_servos();
	
	//begin
	serv_pick();
	msleep(2000);
	arm_down();
	msleep(500);
	flip_close();
	
	//drive
	create_left(86,0,200);
	create_block();
	
	create_backward(640,400);
	create_block();
	
	create_right(106,0,200);
	create_block();
	
	arm_up();
	
	create_left(22,0,200);
	create_block();
	
	flip_open();
	msleep(500);
	
	create_backward(400,400);
	create_block();
	
	set_servo_position(SERV_FLIP,500);
	msleep(300);
	
	create_backward(150,100);
	create_block();
		
	create_left(5,0,100);
	create_block();
		
	flip_open();
	//flip_open();
}
