#include "createDrive.h"
int main()
{
	create_connect();
	printf("connected");
	/*
	create_backward(250,100);
	create_stop();
	printf("forward works");
	msleep(3000);
	
	create_write_byte(145);
	create_write_byte(255);
	create_write_byte(156);
	create_write_byte(255);
	create_write_byte(156);
	
	create_write_byte(156);
	create_write_byte(255);
	create_write_byte(6);
	create_stop();
	*/
	create_left(90,0,100);
	create_block();
	create_right(90,0,100);
	create_block();
	create_disconnect();
}
