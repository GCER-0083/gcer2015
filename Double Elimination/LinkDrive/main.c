#include "drive.h"
#include "generic.h"
#include "newmenu.h"

//Sensors
#define LEFT_BUMP digital(14)
#define RIGHT_BUMP digital(15)
#define CAM_RES LOW_RES

/*
Camera colors:

RED: #0
Hue:
Saturation:
Value:
 
GREEN: #1
Hue:
Saturation:
Value:
*/

//Motors and servos
#define SERV_SORT 2
#define SERV_SWEEP 0
#define SERV_GRAB 3
#define MOT_PICK 3
#define SORT_SPEED 70

#define RETURNTEST 1

//Position functions
void sort_main(){set_servo_position(SERV_SORT,600);msleep(200);}
void sort_sec(){set_servo_position(SERV_SORT,1120);}
//void sort_mid(){set_servo_position(SERV_SORT,1090);msleep(200);}

void grab_poms_fast(){set_servo_position(SERV_GRAB,1271);}
void grab_poms(){set_servo_position(SERV_GRAB,1271);msleep(200);}
void release_poms_fast(){set_servo_position(SERV_GRAB,1782);}
void release_poms(){set_servo_position(SERV_GRAB,1782);msleep(200);}
void bump_poms(){set_servo_position(SERV_GRAB,1510);msleep(10);set_servo_position(SERV_GRAB,1410);}

void sweep_bump(){set_servo_position(SERV_SWEEP,1450);msleep(40);}
void sweep_out(){set_servo_position(SERV_SWEEP,0);msleep(200);}
void sweep_out2(){set_servo_position(SERV_SWEEP,1182);msleep(100);}
void sweep_default(){set_servo_position(SERV_SWEEP,1750);msleep(50);}

/*
shakes the robot left and right reps amount of times
reps: the amount of shakes we did.
*/
void shake(int reps)
{
	int i;
	for(i = 0;i<reps;i++)
	{
		left(5,0);
		right(5,0);
	}
}
/*
sorts the poms into their respective bins for time seconds

mainColor: the pom color that goes into the main bin. See above comment for camera color designations.
size: the average size of tribbles on the camera, based on a percentage value between 0 and 100.
discrepancy: the maximum discrepancy from the main size allowed, based on a percentage value between 0 and 100.
time: the duration for which this program runs, in seconds.
*/
void cam_sort(int mainColor, int size, int discrepancy, int time, int jamDist)
{
	release_poms();
	//initialization process
	if(size<0||size>100) 
	printf("Warning: Size is out of the specified range!\n");
	if(discrepancy<0||discrepancy>100)
	printf("Warning: Discrepancy is out of the specified range!\n");
	jamDist = jamDist*CMtoBEMF;
	float lastTest = curr_time();
	//determining resolution
	printf("Tracking in:");
	int res_val = 0;
	switch(CAM_RES)
	{
		case LOW_RES:
		res_val = (160*120)/100;
		printf("Low res\n");
		break;
		case MED_RES:
		res_val = (320*240)/100;
		printf("Medium res\n");
		break;
		case HIGH_RES:
		res_val = (640*480)/100;
		printf("High res\n");
		break;
		default:
		printf("Warning: Unknown res!\n");
		break;
	}
	size = res_val*size;
	discrepancy = res_val*discrepancy;
	//camera sorting initialization
	multicamupdate(5);
	float startTime = curr_time();
	int leftPos, rightPos;
	float newTime = curr_time();
	int area = 0;
	int last = get_motor_position_counter(MOT_PICK);
	int alt = 0;
	int turn = 0;
	int otherColor = 0;
	if(mainColor==0)
		otherColor=1;
	motor(MOT_PICK,SORT_SPEED);
	//Sorting process
	leftPos = gmpc(MOT_LEFT);
	rightPos = gmpc(MOT_RIGHT);
	motor(MOT_RIGHT,71);
	motor(MOT_LEFT,71);
	while(startTime+time>=curr_time())	//Timekeeper
	{
		if((double)(gmpc(MOT_LEFT)-leftPos)/CMtoBEMF>=1&&(double)(gmpc(MOT_RIGHT)-rightPos)/CMtoBEMF>=1)
		{
			printf("newTime:%d\n",newTime);
			printf("curr time:%d\n",curr_time());
			motor(MOT_RIGHT,0);
			motor(MOT_LEFT,0);
			if(newTime+2 <= curr_time())
			{
				if(turn==0||turn==6)
				{
					grab_poms_fast();
					motor(MOT_RIGHT,60);
					rightPos=gmpc(MOT_RIGHT);
					turn = 1;
				}
				else if(turn==2)
				{
					grab_poms_fast();
					motor(MOT_LEFT,60);
					leftPos=gmpc(MOT_LEFT);
					turn = 3;
				}
				else
				{
					release_poms_fast();
					motor(MOT_RIGHT,71);
					motor(MOT_LEFT,71);
					rightPos=gmpc(MOT_RIGHT);
					leftPos=gmpc(MOT_LEFT);
					turn++;
				}
				newTime = curr_time();
			}
		}
		else
		{
			if((double)(gmpc(MOT_LEFT)-leftPos)/CMtoBEMF>=1)
			{
				motor(MOT_LEFT,0);
			}
			else
			{
				newTime = curr_time();
			}
			if((double)(gmpc(MOT_RIGHT)-rightPos)/CMtoBEMF>=1)
			{
				motor(MOT_RIGHT,0);
			}
			else
			{
				newTime=curr_time();
			}
			printf("gmpc: Mot_left-leftPos = %d",(gmpc(MOT_LEFT)-leftPos)/CMtoBEMF);
			printf("gmpc: Mot_right-rightPos = %d",(gmpc(MOT_RIGHT)-rightPos)/CMtoBEMF);
			
		}
		//leftPos = get_motor_position(MOT_LEFT);
		//rightPos = get_motor_position(MOT_RIGHT);
		//failsafe
		if(lastTest+1<=curr_time())
		{
			if(alt == 1)
			{
				//bump_poms();
				//forward(2);
				alt = 0;
			}
			else
			{
				alt = 1;
				//motor(MOT_LEFT,0);
				//motor(MOT_RIGHT,0);
			}
			if(jamDist>(get_motor_position_counter(MOT_PICK)-last))
			{
				motor(MOT_PICK,-90);
				msleep(1000);
				motor(MOT_PICK,SORT_SPEED);
			}
			last = get_motor_position_counter(MOT_PICK);
			lastTest = curr_time();
			sweep_bump();
			msleep(20);
			sweep_default();
		}
		//actual sorting
		camera_update();
		area = get_object_area(mainColor,0);
		if(area>500)
		{
			printf("Seen Blob of Main color\n");
			if(area>=size-discrepancy&&area<=size+discrepancy)
			{
				motor(MOT_PICK,SORT_SPEED/2);
				sort_main();
				msleep(50);
				motor(MOT_PICK,SORT_SPEED);
				printf("sorted");
				area = get_object_area(otherColor,0);
				if(area>=size-discrepancy&&area<=size+discrepancy)
				{
					printf("2 Poms Found!! Reversing");
					motor(MOT_PICK,-90);
				}
				else
				{
					printf("poms reverted. Resuming pickup");
					motor(MOT_PICK,SORT_SPEED);
				}
				//motor(MOT_PICK,0);
				//msleep(100);
				//sweep_bump();
				//motor(MOT_PICK,SORT_SPEED);
				//sweep_default();
			}
			else
			{
				printf("Blob failed specifications\n");
				sort_sec();
			}
		}
		else
		{
			sort_sec();
		}
	}
	motor(MOT_PICK,0);
	motor(MOT_LEFT,0);
	motor(MOT_RIGHT,0);
	if(turn==1)
		right(5,0);
	else if(turn==3)
		left(5,0);
}
//same as above, drives around.
void static_sort(int mainColor, int size, int discrepancy, int time, int jamDist)
{
	release_poms();
	//initialization process
	if(size<0||size>100) 
	printf("Warning: Size is out of the specified range!\n");
	if(discrepancy<0||discrepancy>100)
	printf("Warning: Discrepancy is out of the specified range!\n");
	jamDist = jamDist*CMtoBEMF;
	float lastTest = curr_time();
	//determining resolution
	printf("Tracking in:");
	int res_val = 0;
	switch(CAM_RES)
	{
		case LOW_RES:
		res_val = (160*120)/100;
		printf("Low res\n");
		break;
		case MED_RES:
		res_val = (320*240)/100;
		printf("Medium res\n");
		break;
		case HIGH_RES:
		res_val = (640*480)/100;
		printf("High res\n");
		break;
		default:
		printf("Warning: Unknown res!\n");
		break;
	}
	size = res_val*size;
	discrepancy = res_val*discrepancy;
	//camera sorting initialization
	multicamupdate(5);
	float startTime = curr_time();
	int leftPos, rightPos;
	float newTime = curr_time();
	int area = 0;
	int last = get_motor_position_counter(MOT_PICK);
	int alt = 0;
	int turn = 0;
	int otherColor = 0;
	if(mainColor==0)
		otherColor=1;
	motor(MOT_PICK,SORT_SPEED);
	//Sorting process
	
	leftPos = gmpc(MOT_LEFT);
	rightPos = gmpc(MOT_RIGHT);
	while(startTime+time>=curr_time())	//Timekeeper
	{
		//failsafe
		if(lastTest+1<=curr_time())
		{
			if(alt == 1)
			{
				//bump_poms();
				//forward(2);
				alt = 0;
			}
			else
			{
				alt = 1;
				//motor(MOT_LEFT,0);
				//motor(MOT_RIGHT,0);
			}
			if(jamDist>(get_motor_position_counter(MOT_PICK)-last))
			{
				motor(MOT_PICK,-90);
				msleep(1000);
				motor(MOT_PICK,SORT_SPEED);
			}
			last = get_motor_position_counter(MOT_PICK);
			lastTest = curr_time();
			sweep_bump();
			msleep(20);
			sweep_default();
		}
		//actual sorting
		camera_update();
		area = get_object_area(mainColor,0);
		if(area>500)
		{
			printf("Seen Blob of Main color\n");
			if(area>=size-discrepancy&&area<=size+discrepancy)
			{
				motor(MOT_PICK,SORT_SPEED/2);
				sort_main();
				msleep(50);
				motor(MOT_PICK,SORT_SPEED);
				printf("sorted");
				area = get_object_area(otherColor,0);
				if(area>=size-discrepancy&&area<=size+discrepancy)
				{
					printf("2 Poms Found!! Reversing");
					motor(MOT_PICK,-90);
				}
				else
				{
					printf("poms reverted. Resuming pickup");
					motor(MOT_PICK,SORT_SPEED);
				}
				//motor(MOT_PICK,0);
				//msleep(100);
				//sweep_bump();
				//motor(MOT_PICK,SORT_SPEED);
				//sweep_default();
			}
			else
			{
				printf("Blob failed specifications\n");
				sort_sec();
			}
		}
		else
		{
			sort_sec();
		}
	}
	motor(MOT_PICK,0);
	motor(MOT_LEFT,0);
	motor(MOT_RIGHT,0);
	if(turn==1)
		right(5,0);
	else if(turn==3)
		left(5,0);
}

//side programs
#define s_RAWSORT 102
#define s_SWEEP 103
#define s_FORWARD 104

//main programs
#define s_START 1
#define s_CROSSFIELD 2
#define s_PILE2 4
#define s_RETURNFIELD 5
#define s_DUMPPOMS 6
#define s_PILEALT 7
#define s_CROSSBACK 8
#define s_SHORT 9
#define s_REALIGN 10
#define s_RETURN 11
#define s_RETURNSTART 12

#define s_END 0

struct menuitem menu[]=
{
	{s_START,"start"},
	{s_SHORT,"short"},
	{s_SWEEP,"sweep"},
	{s_FORWARD,"forward"},
	{s_DUMPPOMS,"dump"},
	{s_RAWSORT,"sorting"},
	{s_RETURN,"return"},
	{s_END,"END"}
	
};
void cam_display()
{
	graphics_open(80,60);
	int col, row;
	const unsigned char* ptr;
	while(!side_button())
	{
		camera_update();
		//printf("%3d,%3d,%3d\n",*ptr,*(ptr+1),*(ptr+2));//bgr
		int x,y;
		for(y=0;y<120;y+=2){
			const unsigned char* row = get_camera_frame_row(y);
			for(x=0;x<160;x+=2){
				ptr = row+(3*x);
				int r = *(ptr+2);
				int g = *(ptr+1);
				int b = *(ptr);
				//if (r > g*3/2+20 && r > b*3/2+20 && abs(b-g) < 20 && (r < 120))
				//graphics_pixel(x,y,255,0,0);
				//else
				graphics_pixel(x/2,y/2,r,g,b);
			}
		}
		graphics_update();
		msleep(200);
	}
	
	graphics_close();
}
int main()
{
	int alt= 0;
	set_servo_position(SERV_GRAB,950);
	sort_sec();
	sweep_default();
	enable_servos();
	camera_open(CAM_RES);
	multicamupdate(5);
	Get_Mode();
	while(currstate!=s_END)
	{
		state(s_SHORT)
		{
			alt = 1;
			next(s_START);
		}
		state(s_FORWARD)
		{
			release_poms();
			forward(100);
			backward(100);
		}
		state(s_SWEEP)
		{
			sweep_default();
			msleep(50);
			sweep_out();
			msleep(150);
		}
		state(s_RAWSORT)
		{
			release_poms();
			sort_main();
			sort_sec();
			cam_sort(0,60,40,30,3);
			sweep_out();
			next(s_END);
		}
		
		state(s_START) // start, cross field, then pilealt and pile2, returnfield, dumpPoms and end
		{
			//init
			light_start(0);
			shut_down_in(119);
			release_poms();
			
			forward(25);
			left(12,0);
			forward(25);
			grab_poms();
			right(11,0);
			if(alt==0)
				next(s_CROSSFIELD);	
			else
				next(s_CROSSBACK);
		}
		state(s_CROSSFIELD)
		{
			//put claw higher to prevent it from hitting the black tape
			forward(10);
			release_poms();
			forward(30);
			grab_poms();
			forward(50);
			release_poms();
			forward(30);
			grab_poms();
			next(s_PILEALT);
		}
		state(s_PILEALT)
		{
			left(120,ks/2);
			forward(15);
			right(-57,ks/2);
			motor(MOT_PICK,-70);
			backward(45);
			cam_sort(0,50,25,12,2);
			grab_poms();
			backward(23);
			cam_sort(0,50,25,10,2);
			//grab_poms();
			backward(23);
			next(s_PILE2);
		}
		state(s_CROSSBACK)
		{
			backward(70);
			forward(18);
			left(80,0);
			backward(40);
			cam_sort(0,50,25,20,2);
			grab_poms();
			backward(35);
			release_poms();
			cam_sort(0,50,25,20,2);
			grab_poms();
			next(s_REALIGN);
		}
		state(s_REALIGN) //re-aligns the link with the initial starting position
		{
			backward(50);
			forward(40);
			right(180,0);
			backward(30);
			next(s_RETURN);
		}
		state(s_RETURN)
		{	
			forward(30);
			left(90,0);
			backward(40);
			release_poms();
			msleep(100);
			forward(120); //return to other side of field
			grab_poms();
			forward(60);
			right(90,0);
			
			sweep_out(); //red poms go to other side
			msleep(150);
			sweep_default();
			msleep(100);
			sweep_out();
			msleep(100);
			sweep_default();
			msleep(100);
			sweep_out();
			msleep(100);
			sweep_default();
			msleep(100);
			
			cam_sort(1,50,25,20,2);
			backward(40);
			cam_sort(1,50,25,20,2);
			backward(40);
			#ifndef RETURNTEST
			next(s_END);
			#endif
			
			#ifdef RETURNTEST
			next(s_RETURNSTART);
			#endif
		}
		#ifdef RETURNTEST
		state(s_RETURNSTART) //return to starting field, dump poms
		{
			forward(50);
			right(90,0);
			backward(30);
			forward(160);
			next(s_DUMPPOMS);
		}
		#endif
		state(s_PILE2)
		{
			release_poms();
			forward(3);
			left(86,ks/2);
			grab_poms();
			backward(90);
			forward(26);
			//motor(MOT_PICK,-40);
			left(-86,ks/2);
			backward(25);
			release_poms();
			forward(46);
			grab_poms();
			backward(74);
			release_poms();
			forward(20);
			grab_poms();
			right(-88,ks/2);
			backward(35);
			cam_sort(0,50,25,30,2);
			msleep(750);
			sort_main();
			right(45,0);
			left(45,0);
			next(s_RETURNFIELD);
		}
		state(s_RETURNFIELD)
		{
			left(-88,ks/2);
			backward(20);
			forward(10);
			release_poms();
			forward(100);
			right(5,0);
			//right(15,0);
			forward(60);
			forward(30);
			next(s_DUMPPOMS);
		}
		state(s_DUMPPOMS)
		{
			sweep_out2();
			msleep(200);
			sweep_default();
			msleep(100);
			sweep_out();
			msleep(150);
			sweep_default();
			msleep(100);
			sweep_out();
			msleep(100);
			sweep_default();
			msleep(100);
			sweep_out();
			msleep(1000);
			sort_main();
			//left(-178,ks/2);
			//forward(10);
			static_sort(1,50,25,10,2);
			now();
			next(s_END);
		}
		return 0;
	}
}
