#include "drive.h"
#include <math.h>

void drive_off(){
	off(MOT_RIGHT);
	off(MOT_LEFT);
}
void clear_all_drive(){ 
	clear_motor_position_counter(MOT_RIGHT);
	clear_motor_position_counter(MOT_LEFT);
}
void drive(float l_ticks, float r_ticks, float max_pwr)//actually moves the robot-->called from f/b/l/r
{//ticks each motor has to travel (+ or -), power of the fast motor (+)
	drive_off();//make sure both motors are off from the start--just to be safe
	if(max_pwr==0||(r_ticks==0&&l_ticks==0))//don't move or move at 0 speed
		return;//can't do anything-->just exit
	if(max_pwr<0)//negative power-->needs to be positive
	{
		max_pwr=-max_pwr;//make it positive
		l_ticks=-l_ticks;//switch the signs of the motor movements
		r_ticks=-r_ticks;//
	}
	float l_base_pwr;//power each motor moves at if everything is going as intended
	float r_base_pwr;//
	int timeout;//in ms, based off how far the fast motor has to travel-->if it reaches the timeout, it will stop
	if(my_abs(l_ticks)>my_abs(r_ticks))//left motor is moving faster
	{
		l_base_pwr=max_pwr*sign(l_ticks);//run left at max power in the right direction
		r_base_pwr=max_pwr*(r_ticks/my_abs(l_ticks));//run right at lower speed, proportional to distance to travel
		timeout=my_abs(l_ticks)*TIMEOUT;
	}
	else//< (can also be equal, but then the division term will end up being 1, so it works out)
	{
		r_base_pwr=max_pwr*sign(r_ticks);//see above
		l_base_pwr=max_pwr*(l_ticks/my_abs(r_ticks));//
		timeout=my_abs(r_ticks)*TIMEOUT;
	}
	cmpc(MOT_LEFT);
	cmpc(MOT_RIGHT);
	int start_time=curr_time();
	if(l_ticks==0)//means the right motor moves but the left doesn't
	{//I know they can't both be 0 because I sanitized my results at the beginning
		while(my_abs(gmpc(MOT_RIGHT))<my_abs(r_ticks)&&curr_time()-start_time<timeout)
		{
			float r_pwr=r_base_pwr;//actual power it will turn at
			float r_left=my_abs(r_ticks)-my_abs(gmpc(MOT_RIGHT));//ticks remaining
			if(r_left<END_THRESHOLD)//needs to start slowing down
				r_pwr*=END_SCALE+(r_left*(1-END_SCALE)/END_THRESHOLD);//scales from full power to END_SCALE
			motor(MOT_RIGHT, round(r_pwr));
			msleep(10);
		}
	}
	else if(r_ticks==0)//ditto for if the right doesn't move
	{
		while(my_abs(gmpc(MOT_LEFT))<my_abs(l_ticks)&&curr_time()-start_time<timeout)
		{
			float l_pwr=l_base_pwr;//see comments above
			float l_left=my_abs(l_ticks)-my_abs(gmpc(MOT_LEFT));
			if(l_left<END_THRESHOLD)
				l_pwr*=END_SCALE+(l_left*(1-END_SCALE)/END_THRESHOLD);
			motor(MOT_LEFT, round(l_pwr));
			msleep(10);
		}
	}
	else//both motors have to move
	{
		while((my_abs(gmpc(MOT_LEFT))<my_abs(l_ticks)||my_abs(gmpc(MOT_RIGHT))<my_abs(r_ticks))&&curr_time()-start_time<timeout)//one isn't finished
		{
			float l_pwr=l_base_pwr;//actual power
			float r_pwr=r_base_pwr;//
			float l_left=my_abs(l_ticks)-my_abs(gmpc(MOT_LEFT));//ticks remaining
			float r_left=my_abs(r_ticks)-my_abs(gmpc(MOT_RIGHT));//
			float l_perc_left=l_left/my_abs(l_ticks);//percent of distance remaining-->on [0,1]
			float r_perc_left=r_left/my_abs(r_ticks);//
			r_pwr+=(r_perc_left-l_perc_left)*r_ticks*PID_CONST;//increases in magnitude if motor is behind,
			l_pwr+=(l_perc_left-r_perc_left)*l_ticks*PID_CONST;//or slows down if it's ahead
			if(l_left<END_THRESHOLD)//needs to slow down
				l_pwr*=END_SCALE+(l_left*(1-END_SCALE)/END_THRESHOLD);
			if(r_left<END_THRESHOLD)//same for the right
				r_pwr*=END_SCALE+(r_left*(1-END_SCALE)/END_THRESHOLD);
			if(r_left<=0||sign(r_pwr)!=sign(r_base_pwr))//has reached end or so far off that it has to stop entirely
				r_pwr=0;
			if(l_left<=0||sign(l_pwr)!=sign(l_base_pwr))//ditto for the left
				l_pwr=0;
			motor(MOT_LEFT, round(l_pwr));
			motor(MOT_RIGHT, round(r_pwr));
			msleep(10);
		}
	}
	drive_off();//stop it at the end
}


/*void right(float degrees, float radius){//turn right a number of degrees with a certain radius
	int turnrspeed;
	long turnl=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
	long turnr=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
	if(turnl == 0l) return;
	turnrspeed = round((float)turnr/(float)turnl*SPD);
	mrp(MOT_LEFT, SPD,turnl);
	if(turnrspeed < 0) turnrspeed = -turnrspeed;
	if(turnrspeed < 50){
		turnrspeed = 0;
		turnr = 0l;
		off(MOT_RIGHT);
		}else{
		mrp(MOT_RIGHT,turnrspeed,turnr);
	}
	bmd(MOT_RIGHT);
	bmd(MOT_LEFT);
}*/

/* \fn void right(int degrees, int radius)
 * \brief turns right degrees degrees at int radius radius
 * \param degrees degrees forward to go
 * \param radius radius at which to turn around
 */
void right(float degrees, float radius){
		int turnrspeed;
		long turnl=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
		long turnr=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
    	if(turnl == 0l) return;
    	turnrspeed = round((float)turnr/(float)turnl*SPD);
    	msleep(30l);
    	if(turnl > 0l)
      		motor(MOT_LEFT, SPD);
    	else
      		motor(MOT_LEFT, -SPD);
    	if(turnrspeed < 0) turnrspeed = -turnrspeed;
		if(turnr > 0l)
			motor(MOT_RIGHT, turnrspeed);
		else
			motor(MOT_RIGHT, -turnrspeed);
    	turnl += gmpc(MOT_LEFT);
    	turnr += gmpc(MOT_RIGHT);
    	if(turnr - gmpc(MOT_RIGHT) > 0l){
        	if(turnl - gmpc(MOT_LEFT) > 0l){
            		while((turnr > gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl > gmpc(MOT_LEFT)){
                		if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
                		if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
            		}
        	}else{
            		while((turnr > gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl < gmpc(MOT_LEFT)){
                		if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
                		if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
            }
        }
    }else{
        if(turnl - gmpc(MOT_LEFT) > 0l){
            while((turnr < gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl > gmpc(MOT_LEFT)){
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
            }
        }else{
            while((turnr < gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl < gmpc(MOT_LEFT)){
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
            }
        }
    }
    drive_off();
    msleep(30l);
}
/* \fn void left(int degrees, int radius)
 * \brief turns left degrees degrees at int radius radius
 * \param degrees degrees forward to go
 * \param radius radius at which to turn around
 */
void left(float degrees, float radius){
int turnlspeed;
	long turnl=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
	long turnr=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
    if(turnr == 0l) return;
    turnlspeed = round((float)turnl/(float)turnr*SPD);
    msleep(30l);
    if(turnr > 0l)
      motor(MOT_RIGHT, SPD);
    else
      motor(MOT_RIGHT, -SPD);
    if(turnlspeed < 0) turnlspeed = -turnlspeed;
	if(turnl > 0l)
	  motor(MOT_LEFT, turnlspeed);
	else
	  motor(MOT_LEFT, -turnlspeed);
    turnr += gmpc(MOT_RIGHT);
    turnl += gmpc(MOT_LEFT);
    if(turnl - gmpc(MOT_LEFT) > 0l){
        if(turnr - gmpc(MOT_RIGHT) > 0l){
            while((turnl > gmpc(MOT_LEFT) && turnlspeed != 0) || turnr > gmpc(MOT_RIGHT)){
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
                if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
            }
        }else{
            while((turnl > gmpc(MOT_LEFT) && turnlspeed != 0) || turnr < gmpc(MOT_RIGHT)){
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
            }
        }
    }else{
        if(turnr - gmpc(MOT_RIGHT) > 0l){
            while((turnl < gmpc(MOT_LEFT) && turnlspeed != 0) || turnr > gmpc(MOT_RIGHT)){
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
                if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
            }
        }else{
            while((turnl < gmpc(MOT_LEFT) && turnlspeed != 0) || turnr < gmpc(MOT_RIGHT)){
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
            }
        }
    }
    drive_off();
    msleep(30l);
}

void multforward(float distance, float speedmult){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	long l = gmpc(MOT_LEFT)+newdist;
	long r = gmpc(MOT_RIGHT)+newdist;
	motor(MOT_LEFT,SPDl*speedmult);
	motor(MOT_RIGHT,SPDr*speedmult);
	while(gmpc(MOT_LEFT) < l && gmpc(MOT_RIGHT) < r){
		if (gmpc(MOT_LEFT) >= l)
			off(MOT_LEFT);
		if (gmpc(MOT_RIGHT) >= r)
			off(MOT_RIGHT);
	}
	drive_off();
}
void forward(float distance)//move forward a certain distance at a given power
{//distance in inches, power from 1-100
	int power = 100;
	if(distance==0||power==0)//not helpful-->don't move
		return;
	if(distance<0)//negative distance means go backwards
	{
		back(-distance, power);//- to make it positive
		return;
	}
	if(power<0)//same deal with negative power
	{
		back(distance, -power);
		return;
	}
	if(power>100)//can't go above 100
		power=100;//so go at max power
	float r_dist=distance*INtoCM*CMtoBEMF*R_DIST_CONST;//total backEMF counts it needs to go
	float l_dist=distance*INtoCM*CMtoBEMF*L_DIST_CONST;//
	drive(l_dist, r_dist, (float)(power));
}
void backward(float distance){//go backward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;
	long l = gmpc(MOT_LEFT)-newdist;
	long r = gmpc(MOT_RIGHT)-newdist;
	motor(MOT_LEFT,-SPDlb);
	motor(MOT_RIGHT,-SPDrb);
	while(gmpc(MOT_LEFT) > l && gmpc(MOT_RIGHT) > r){
		if (gmpc(MOT_LEFT) <= l)
			off(MOT_LEFT);
		if (gmpc(MOT_RIGHT) <= r)
			off(MOT_RIGHT);
	}
	drive_off();
}
