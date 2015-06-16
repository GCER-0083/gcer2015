#define MOT_ARM ???
#define MOT_CLAW ???

void windup()
{
	int tightened_claw = 0;
	int tightened_arm = 0;
	motor(MOT_ARM,50);
	motor(MOT_CLAW,50);
	int counter_arm = gmpc(MOT_ARM);
	int counter_claw = gmpc(MOT_CLAW);
	while(tightened_claw==0||tightened_arm==0)
	{
		if(gmpc(MOT_ARM)<=counter_arm+50)
		{
			tightened_arm=1;
			motor(MOT_ARM,0);
		}
		else
			counter_arm = gmpc(MOT_ARM);
		if(gmpc(MOT_CLAW)<=counter_claw+50)
		{
			tightened_claw=1;
			motor(MOT_CLAW,0);
		}
		else
			counter_claw = gmpc(MOT_CLAW);
		msleep(250);
	}
}
int main()
{
	windup();
}
