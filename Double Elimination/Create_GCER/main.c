#include "generic.h"
#include "createDrive.h"
//#include "newmenu.h"

#define LIGHT_PORT 0

#define SERV_ARM 2
#define SERV_FLIP 1
#define SERV_IGUS 0
//self explanatory
void igus_close()
{
	set_servo_position(SERV_IGUS,654);
}
//self explanatory
void igus_open()
{
	set_servo_position(SERV_IGUS,2047);
}
//self explanatory
void arm_up()
{
	set_servo_position(SERV_ARM,0);
	msleep(2000);
}
//self explanatory
void arm_middle()
{
	set_servo_position(SERV_ARM,1100);
	msleep(500);
}
//self explanatory
void arm_down()
{
	set_servo_position(SERV_ARM,2047);
}
//self explanatory
void flip_open()
{
	set_servo_position(SERV_FLIP,300);
	msleep(500);
}
//self explanatory
void flip_close()
{
	set_servo_position(SERV_FLIP,2047);
	msleep(1000);
}
//Picks up cubes by lifting arm slightly and flipping the cover. Should only be used in the beginning
void serv_pick()
{
	set_servo_position(SERV_ARM,500);
	msleep(2000);
	flip_open();
	msleep(900);
	arm_down();
	msleep(1000);
}
int main()
{
	
	//init
	create_connect();
	create_write_byte(132);
	arm_down();
	set_servo_position(SERV_FLIP,2047);
	igus_close();
	enable_servos();
	light_start(LIGHT_PORT);
	
	//begin
	sleep(3);
	serv_pick();
	msleep(2000);
	arm_down();
	msleep(500);
	flip_close();
	
	//drive
	printf("stop 1");
	create_left(84,0,200);
	printf("stop 2");
	create_block();
	
	arm_middle();
	create_backward_fast(640,400);
	create_block();
	
	create_right(100,0,200);
	create_block();
	
	arm_up();
	
	create_left(10,0,200);
	create_block();
	/*
	create_backward_fast(100,400);
	create_block()
	*/
	flip_open();
	msleep(500);
	
	create_left(3,0,200);
	create_block();
	
	create_backward_fast(300,400);
	create_block();
	
	set_servo_position(SERV_FLIP,800);
	msleep(300);
	
	create_backward(150,100);
	create_block();
		
	flip_open();/*
	igus_open();
	igus_close();
	igus_open();
	igus_close();
	igus_open();
	create_forward(50,100);
	create_block();
	create_backward(50,100);
	create_block();
	create_left(5,0,100);
	create_block();
	/*flip_open();
	flip_open();
	msleep(1000);
	create_left(15,0,200);
	create_block();*/
}
int main2()
{
	create_connect();
	create_backward_fast(700,400);
	create_block();
}
int main3()
{
	//init
	create_connect();
	create_write_byte(132);
	arm_down();
	set_servo_position(SERV_FLIP,2047);
	igus_close();
	enable_servos();
	light_start(LIGHT_PORT);
	
		
	//begin
	sleep(3);
	serv_pick();
	msleep(2000);
	arm_down();
	msleep(500);
	flip_close();
	
	//pre-squaring
	create_left(45,0,200);
	create_block();
	
	arm_middle();
	
	create_backward(640,400);
	create_block();
	
	//backwards at speed 100
	create_write_byte(145);
	create_write_int(-100);
	create_write_int(-100);
	create_wait_event(10);
	
}

