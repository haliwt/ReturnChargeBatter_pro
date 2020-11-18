/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Run_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#include "LB_AD.h"
#include "LB_Led.h"
#include "LB_IR.h"
#endif
 
void  CheckRun()
{

		switch(RunStep)
		{
		case 0:
		{

		}
		break;

		case 0x0D:
		{

			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				ImpSecond=0;
				RunStep=0x0;
				AllStop();
			}
			else 

			if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=0;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=0;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=0;
			}
		}
		break;
		case 0x0c:
		{
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				ImpSecond=0;
				RunStep=0x1;
				AllStop();
			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=3;
				Enter3=8;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=3;
				Enter3=9;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=3;
				Enter3=10;
			}
		}
		break;

		case 1:
		{
			ImpSecond=0;
			SetXMotor(1,10,15,1,1,10,15,1);
			SetMotorcm(1,1000);
			RunStep=2;
			RunMs=0;
		}
		break;
		case 2:
		///*
		     if(ImpSecond>5)
			 Imp2Time=0;

			if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(2,10,25,1,2,10,25,1);
				SetMotorcm(2,5);
				RunMs=20;
				Imp2Time++;
				Enter3=1;
			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Imp2Time++;
				Enter3=2;
			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Imp2Time++;
				Enter3=3;
			}
			else   
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				NoImpSecond=0;
				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=4;		
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;

				NoImpSecond=0;

				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=5;

			}
            else if(ImpStatus==1)
			{
				Imp2Time++;

				NoImpSecond=0;

				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=6;

			}
			//*/
			break;
		case 3:
//			if(RunMs>10)
//			{
//			    if(Gong_Step==1)
//			    {
//				  SetXMotor(2,10,20,1,2,10,20,1);
//				  SetMotorcm(2,5);
//				}
//				
//				RunMs=0;
//				RunStep=4;
//			}
//			break;
            if(RunMs>10)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=4;
			}
			break;

		case 4:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			    if((ImpStatus==1))
				{
				AllStop();
				RunMs=0;
				RunStep=3;
				IMPTime++;
				Enter3=11;
				}
				else 
				{
				AllStop();
				RunMs=0;
				RunStep=5;
				IMPTime=0;
				IMPTime=0;
				}
			}
//			else if(Gong_Step==0)
//			{				
//				AllStop();
//				RunMs=0;
//				RunStep=5;
//				IMPTime=0;
//				IMPTime=0;
//				Gong_Step=1;
//			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				NoImpSecond=0;
				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=7;
			}
			break;
		case 5:
			if(RunMs>10)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=6;
			}
			break;

		case 6:

			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=7;
				LCurrent=0;
				RCurrent=0;
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				Enter3=12;

			}
			else if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=20;
				Enter3=13;
			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Enter3=14;
			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Enter3=15;
			}


			break;
		case 7:
		{
			if(RunMs>10)
			{
				SetXMotor(1,10,20,1,1,10,20,1);
				SetMotorcm(1,20);
				RunMs=0;
				RunStep=8;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 8:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=9;

			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
			}
			else if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				CurrentMax++;
			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Imp2Time++;
			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Imp2Time++;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=9;
			}
			else if((ImpStatus==1))
			{

				Imp2Time++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=9;
			}
			break;
		case 9:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=10;
				IMPTime=0;
			   }
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				NoImpSecond=0;
				RunStep=10;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			break;
			break;

		case 10:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{

				{
					//InitMotorForward();
					AllStop();
					RunMs=0;
					RunStep=11;
					LCurrent=0;
					RCurrent=0;
				}
			}
			else if((ImpStatus==1))
			{

				Imp2Time++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=11;
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=11;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				CurrentMax++;
			}
			else if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=20;
				Enter3=16;
			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Enter3=17;
			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Enter3=18;
			}

			break;
		case 11:
			if(RunMs>10)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x12;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			break;
		case 0x12:
		{
		   	if(ImpSecond>5)
			 Imp2Time=0;
			 if(RunMs>200)
			   CurrentMax=0;
			if(GroundDp[1]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x13;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=20;

			}
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x13;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x13;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
 			else   
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				NoImpSecond=0;

				RunStep=0x13;
				AllStop();
				RunMs=0;		
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				EdgeTime=0;
				NoImpSecond=0;
				RunStep=0x13;
				AllStop();
				RunMs=0;
			}
			else if(ImpStatus==1)
			{

				Imp2Time++;
				EdgeTime=0;
				NoImpSecond=0;
				RunStep=0x13;
				AllStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
		break;
		case 0x13:
			if(RunMs>10)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x14;
			}
			break;

		case 0x14:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				AllStop();
				RunMs=0;
				RunStep=0x15;
				IMPTime=0;
				}
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				NoImpSecond=0;
				RunStep=0x15;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			break;
		case 0x15:
			if(RunMs>10)
			{
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x16;
			}
			break;

		case 0x16:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=0x17;
				LCurrent=0;
				RCurrent=0;
			}
 			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else 	  if(GroundDp[1]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}

			break;
		case 0x17:
		{
			if(RunMs>10)
			{
				SetXMotor(1,10,20,1,1,10,20,1);
				SetMotorcm(1,20);
				RunMs=0;
				RunStep=0x18;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 0x18:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=0x19;

			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else 	  if(GroundDp[1]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x19;
			}
			else if(ImpStatus==1)
			{
				Imp2Time++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x19;
			}
			break;
		case 0x19:
			if(RunMs>20)
			{
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x1a;
			}
			break;

		case 0x1a:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				//InitMotorForward();

				AllStop();
				RunMs=0;
				RunStep=0x1b;
				LCurrent=0;
				RCurrent=0;

			}
						else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else 	  if(GroundDp[1]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}

			break;
		case 0x1b:
			if(RunMs>20)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x2;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else 	  if(GroundDp[1]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}

			break;
			//沿墙
		case 0x20:
		{
			if(RunMs>20)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x21;
			}
		}
		break;
		case 0x21:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=0x22;
			}

		}
		break;
		case 0x22:
		{
			if(RunMs>5)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,60);
				RunMs=0;
				RunStep=0x23;
			}
		}
		break;
		case 0x23:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				AllStop();
				RunMs=0;
				RunStep=0x24;
				IMPTime=0;
				}
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x21;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else 	  if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x21;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
		}
		break;
		case 0x24:
		{
			if(RunMs>10)
			{
				SetXMotor(1,20,20,1,1,10,10,1);
				SetMotorcm(5,100);
				RunMs=0;
				RunStep=0x25;
			}

		}
		break;

		case 0x25:
		{
			if(RunMs>250)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x26;
			}
			else 	  if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x21;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x22;
				//InitMotorLeftMax();
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x22;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}
			else if(ImpStatus==1)
			{
				//CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}
		}
		break;

		case 0x26:
		{
			if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}
			else if(ImpStatus==1)
			{
				//CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}


		}
		break;
		case 0x2c:
		{
			if(RunMs>70)
			{
				ImpSecond=0;
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x21;
			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x22;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x22;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x22;
			}
		}
		break;
		//定点
		case 0x30:
		{
			SetXMotor(2,10,10,1,1,10,10,1);
			SetMotorcm(3,360);
			RunMs=0;
			RunStep=0x31;
			RunSecond=0;
			LCurrent=0;
			RCurrent=0;
		}
		break;
		case 0x31:
		{
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				RunSecond=0;
				RunStep=0x32;
				SetXMotor(1,4,4,1,1,15,15,1);
				SetMotorcm(5,1000);
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x32:
		{
			if(RunSecond>5)
			{
				RunSecond=0;
				RunStep=0x33;
				SetXMotor(1,6,6,1,1,20,20,1);
				SetMotorcm(5,1000);
			}
  			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x33:
		{
			if(RunSecond>10)
			{
				RunSecond=0;
				RunStep=0x34;
				SetXMotor(1,8,8,1,1,20,20,1);
				SetMotorcm(5,1000);
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x34:
		{
			if(RunSecond>15)
			{
				RunSecond=0;
				RunStep=0x35;
				SetXMotor(1,10,10,1,1,20,20,1);
				SetMotorcm(5,1000);
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x35:
		{
			if(RunSecond>30)
			{
				RunSecond=0;
				RunStep=0x31;
				SetXMotor(2,10,10,1,1,10,10,1);
				SetMotorcm(3,360);
			}
 			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x38:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				AllStop();
				RunMs=0;
				RunStep=0x39;
				IMPTime=0;
			  }
			}
		}
		break;
		case 0x39:
		{
			if(RunMs>5)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=0x3a;
			}
		}
		break;
		case 0x3a:
		{
			if(RunMs>90)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,100);
				RunMs=0;
				ImpSecond=0;
				RunStep=0x3b;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 0x3b:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				ImpSecond=0;
				RunStep=0x31;
				SetXMotor(2,10,10,1,1,10,10,1);
				SetMotorcm(3,360);
			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x3c:
		{
			if(RunMs>70)
			{
				ImpSecond=0;
				RunStep=0x31;
				SetXMotor(2,10,10,1,1,10,10,1);
				SetMotorcm(3,360);
			}
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[2]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		//打滑
		case 0x40:
		{
			AllStop();
			RunMs=0;
			RunStep=0x41;
		}
		break;
		case 0x41:
		{
			if(RunMs>5)
			{
				SetXMotor(2,15,15,1,2,15,15,1);
				SetMotorcm(2,20);
				RunMs=0;
				RunStep=0x42;
			}
		}
		break;
		case 0x42:
		{
			if(RunMs>40)
			{
				AllStop();
				RunMs=0;
				RunStep=0x43;
			}
		}
		break;
		case 0x43:
		{
			if(RunMs>40)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				RunStep=0x44;
			}
		}
		break;
		case 0x44:
		{
			if(RunMs>80)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x2;
			}
		}
		break;
		//	自由走
		case 0x50:
		{

			SetXMotor(1,10,15,1,1,10,15,1);
			SetMotorcm(1,1000);
			RunStep=0x51;
			LCurrent=0;
			RCurrent=0;
		}
		break;
		case 0x51:
			if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}

				}
				else
				{
					RunStep=0x52;
					SetXMotor(2,10,20,1,2,10,20,1);
					SetMotorcm(2,5);
				}
				RunMs=20;
			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}
				}
				else
				{
					RunStep=0x52;
					SetXMotor(2,10,20,1,1,10,20,1);
					SetMotorcm(3,45);
				}
			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
						SetXMotor(1,10,20,1,2,10,20,1);
						SetMotorcm(4,45);
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						SetXMotor(1,10,20,1,2,10,20,1);
						SetMotorcm(4,45);
					}

				}
				else
				{
					RunStep=0x52;
					SetXMotor(1,10,20,1,2,10,20,1);
					SetMotorcm(4,45);
				}
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				NoImpSecond=0;
				Imp2Time++;
				CurrentMax++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						AllStop();
					}
				}
				else
				{
					RunStep=0x52;
					AllStop();
				}
				RunMs=0;
			}
			else if(ImpStatus==1)
			{
				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						AllStop();
					}
				}
				else
				{
					RunStep=0x52;
					AllStop();
				}
				RunMs=0;			
			}
			break;
		case 0x52:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x53;
			}
			else if(RunMs>20)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x53;
			}
			break;

		case 0x53:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);				  
			   }
			   else
			   {
			   IMPTime=0;
				AllStop();
				RunMs=0;
				RunStep=0x54;
			   }
			}
			break;
		case 0x54:
			if(RunMs>5)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				RunStep=0x55;
			}
			break;

		case 0x55:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=0x56;
			}
 			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[1]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=20;

			}
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			break;
		case 0x56:
			if(RunMs>50)
			{
				RunMs=0;
				RunStep=0x50;
			}
			break;

			//边扫脱困
		case 0x70:
		{
			SetXMotor(2,10,20,1,2,10,20,1);
			SetMotorcm(2,5);
			RunMs=0;
			RunStep=0x71;
		}
		break;
		case 0x71:
		{
			if(RunMs>40)
			{
				AllStop();
				RunMs=0;
				RunStep=0x72;
			}
		}
		break;
		case 0x72:
		{
			if(RunMs>20)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=0x73;
			}
		}
		break;

		case 0x73:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x74;
			}
		}
		break;
		case 0x74:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=0x75;
			}
		}
		break;

		case 0x75:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x76;
			}
		}
		break;
		case 0x76:
		{
			if(RunMs>80)
			{
				//InitMotorForward();
				RunMs=0;
				RunStep=0x77;
				//SetEdge(11);
			}

		}
		break;
		case 0x77:
			break;

		}
}
void CheckMode(INT8U Key)
{

	 if(KeydelayTime>3)
     {
	   	   	   //定点
	   if(Key>0)
	   {
		 KeydelayTime=0;
//	     SBUF=Key;
	   }
   switch(Key)
   {
     

	   case 1:
	   case 4:
	   {
	    if(Mode!=2)
		{
	   	  Mode=2;
	   	  Step=0;
		  ModeBackup=0;
		}
	   }
	   break;
	   //启动/暂停
	   case 2:
	   case 7:
	   {
	     if(ModeBackup!=0)
		 {
		   Mode= ModeBackup;
		   Step=0;	
		   ModeBackup=0;
		 }
	   	  else if((Mode>0)&&(Mode<4))
		  {
	   	    Mode=0;
	   	    Step=0;		  
		  }
		  else if(Mode==0)
		  {
	   	    Mode=1;
	   	    Step=0;			  
		  }
	   }
	   break;
	   //弓形
	   case 3:
	   {
	   	  if(Mode!=1)
		  {
	   	    Mode=1;
	   	    Step=0;	
			ModeBackup=0;		  
		  }
	   }
	   break;
	   //模式切换
	   case 10:
	   {
	   
	   	  Mode++;
		  Step=0;
		  if(Mode>3)
		   Mode=1;
		  ModeBackup=0;
	   }
	   break;
	   //前
	   case 5:
	   {
		 //KeyRunTime=0;
	     if(Mode<4)
		 {
		 SetXMotor(1,10,10,1,1,10,10,1);
		 SetMotorcm(1,10);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }
	   /*
		  RunMs=0;
		 if((RunStep!=0x0D)||(RunStep!=0x0C)||(RunStep!=0x2C)||(RunStep!=0x3C))
		 {
		 KeyRunTime=0;
	     if(Mode<4)
		 {
		 SetXMotor(1,10,10,1,1,10,10,1);
		 SetMotorcm(1,1000);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }		 		 
		 }
		 else
		 {
		   KeyRunTime=0;
		 }
		*/

	   }
	   break;
	   //左
	   case 6:
	   {
	      RunMs=0;
	     if(Mode<4)
		 {
		 SetXMotor(2,10,10,1,1,10,10,1);
		 SetMotorcm(3,45);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }
	   }
	   break;
	   //右
	   case 8:
	   {
		 RunMs=0;
	     if(Mode<4)
		 {
		 SetXMotor(1,10,10,1,2,10,10,1);
		 SetMotorcm(4,45);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }
	   }
	   break;
	   //后
	   case 9:
	   {
	     RunMs=0;
	     if(Mode<4)
		 {
		 SetXMotor(2,10,10,1,2,10,10,1);
		 SetMotorcm(2,10);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }
	   }
	   break;
     }	   
   
   }
    switch(Mode)
	{
	  //暂停
	  case 0:
	  {
	   switch(Step)
	   {
	   	 case 0:
				SetFan(0);
				SetEdge(0);
				RunStep=0;
				Step=1;
				RunSecond=0;
				ADCtl=1;
				MotorSpeedIRON();
				AllStop();
		 break;
		 case 1:
		 if(RunSecond>30)
		 {
		   LedGreenOff();
		   Step=2;
		 }
		 break;
		 case 2:
		 if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		 break;
	   }
	  }
	  break;
	  //弓形
	  case 1:
	  {
	   switch(Step)
	   {
	   	 case 0:
		 {
		 	RunSecond=0;
			Step=1;
			ADCtl=1;
			LedGreenON();
			AllStop();
			SetIMPOutOn();
			MotorSpeedIRON();
			IMPTime=0;
		 }
		 break;
		 case 1:
		 {
		 	if(RunSecond>1)
			{
			  Step=2;
				SetFan(255);
				SetEdge(200);
			  RunStep=1;
			}
		 }
		 break;
		 case 2:
		 {
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//驱动轮
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//边扫电流
			else if(EdgeCurrentCount>3)
			{
			    EdgeCurrentCount2++;
				if(EdgeCurrentCount2<3)
				{
				   INT8U j=0;
				   LedGreenOff();
				   SetEdge(0);
				   for(EdgeErrordelayTime=0;EdgeErrordelayTime<7;)
                   {
	                   if(EdgeErrordelayTime==0 && j==0)
					   {
					   	 SetXMotor(2,10,10,1,2,10,10,1);
				         SetMotorcm(2,10);
						 LedRedON();
						 j++;
					   }
					   if(EdgeErrordelayTime==2 && j==1)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==3 && j==2)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==4 && j==3)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==5 && j==4)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==6 && j==5)
					   {
					   	 Mode=1;
	   	                 Step=0;
						 LedRedOff();
						 j++;
					   }
	               }
				   EdgeErrordelayTime=0;
				   EdgeCurrentCount=0;
				   j=0;	
				}
				else
				{
				   Mode=5;
				   Step=2;			
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);
				}							
			}
			//风机电流
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//卡壳
			else if(IMPTime>5)
			{
				Mode=5;
				Step=0;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			else if((RunSecond==300)||(Imp2Time>5))
			{
				AllStop();
				RunSecond=301;
				RunStep=0x50;
				CurrentMax=0;
				Imp2Time=0;
				Imp2Second=0;
			}

			else if(RunSecond>360)

			{
			    Imp2Time=0;
				AllStop();
				RunSecond=0;
				RunStep=1;
				RunMs=0;
			}


			else if(Voltage<620)
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
			}

			else if(GroundSecond>1)
			{
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				ModeBackup=Mode;
				LedRedON();
				RunSecond=0;
			}		 
		 if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}		 
		 }
		 break;
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }
			if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
				Step=3;
				RunSecond=0;
			 }

		   }
		   break;
	   }	  
	  }
	  break;
	  //定点
	  case 2:
	  {	 
	    switch(Step)
	     {
	   	 case 0:
		 {
		 	RunSecond=0;
			Step=1;
			LedGreenON();
			AllStop();
			ADCtl=1;
			SetIMPOutOn();
			IMPTime=0;
		 }
		 break;
		 case 1:
		 {
		 	if(RunSecond>1)
			{
			  Step=2;
			  RunStep=0x30;
				SetFan(255);
				SetEdge(200);
			}
		 }
		 break;	
		 case 2:
		 {
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//驱动轮
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//边扫电流
			else if(EdgeCurrentCount>3)
			{
			    EdgeCurrentCount2++;
				if(EdgeCurrentCount2<3)
				{
				   INT8U j=0;
				   LedGreenOff();
				   SetEdge(0);
				   for(EdgeErrordelayTime=0;EdgeErrordelayTime<7;)
                   {
	                   if(EdgeErrordelayTime==0 && j==0)
					   {
					   	 SetXMotor(2,10,10,1,2,10,10,1);
				         SetMotorcm(2,10);
						 LedRedON();
						 j++;
					   }
					   if(EdgeErrordelayTime==2 && j==1)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==3 && j==2)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==4 && j==3)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==5 && j==4)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==6 && j==5)
					   {
					   	 Mode=1;
	   	                 Step=0;
						 LedRedOff();
						 j++;
					   }
	               }
				   EdgeErrordelayTime=0;
				   EdgeCurrentCount=0;
				   j=0;	
				}
				else
				{
				   Mode=5;
				   Step=2;			
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);
				}
//				Mode=5;
//				Step=2;			
//				RunStep=0;
//				RunSecond=0;
//				SetFan(0);
//				SetEdge(0);				
			
			}
			//风机电流
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//卡壳
			else if(IMPTime>5)
			{
				Mode=5;
				Step=0;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			else if(Voltage<620)
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				AllStop();
				SetFan(0);
				SetEdge(0);


			}

			else if(GroundSecond>1)
			{
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				ModeBackup=Mode;
			}		 
		    if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}		 
		 }
		 break;
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }
			if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
				Step=3;
				RunSecond=0;
			 }

		   }
		   break;
		 }		   
	  }
	  break;
	  //沿边
	  case 3:
	  {
	    switch(Step)
	     {
	   	 case 0:
		 {
		 	RunSecond=0;
			Step=1;
			LedGreenON();
			AllStop();
			ADCtl=1;
			SetIMPOutOn();
			IMPTime=0;
		 }
		 break;
		 case 1:
		 {
		 	if(RunSecond>1)
			{
			  Step=2;
			  RunStep=0x20;
				SetFan(255);
				SetEdge(200);
			}
		 }
		 break;	
		 case 2:
		 {
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//驱动轮
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//边扫电流
			else if(EdgeCurrentCount>3)
			{
			    EdgeCurrentCount2++;
				if(EdgeCurrentCount2<3)
				{
				   INT8U j=0;
				   LedGreenOff();
				   SetEdge(0);
				   for(EdgeErrordelayTime=0;EdgeErrordelayTime<7;)
                   {
	                   if(EdgeErrordelayTime==0 && j==0)
					   {
					   	 SetXMotor(2,10,10,1,2,10,10,1);
				         SetMotorcm(2,10);
						 LedRedON();
						 j++;
					   }
					   if(EdgeErrordelayTime==2 && j==1)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==3 && j==2)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==4 && j==3)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==5 && j==4)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==6 && j==5)
					   {
					   	 Mode=1;
	   	                 Step=0;
						 LedRedOff();
						 j++;
					   }
	               }
				   EdgeErrordelayTime=0;
				   EdgeCurrentCount=0;
				   j=0;	
				}
				else
				{
				   Mode=5;
				   Step=2;			
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);
				}
//				Mode=5;
//				Step=2;			
//				RunStep=0;
//				RunSecond=0;
//				SetFan(0);
//				SetEdge(0);				
			}
			//风机电流
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//卡壳
			else if(IMPTime>5)
			{
				Mode=5;
				Step=0;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			else if(Voltage<620)
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				AllStop();
				SetFan(0);
				SetEdge(0);

			}

			else if(GroundSecond>1)
			{
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				ModeBackup=Mode;
			}		 
		   if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}		 
		 }
		 break;	
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }
			if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
				Step=3;
				RunSecond=0;
			 }

		   }
		   break;


		 }	   
	  }
	  break;
	  //充电
	  case 4:
	  {
	    switch(Step)
	     {
	   	 case 0:
		 {
			if(ReadPowerDCIn())
			{
			  Step=2;
			}
			if(RunSecond>1)
			{
			   RunSecond=0;
			   Step=1;
			   LedRedON();
			   ADCtl=0;
			   SetBuzzerTime(10);
			}
		 }
		 break;
		 case 1:
		 {
			if(ReadPowerDCIn())
			{
			  Step=2;
			}
			if(RunSecond>1)
			{
			   RunSecond=0;
			   Step=0;
			   LedRedOff();
			}
		 }
		 break;	
		 case 2:
		 {
			if(RunSecond>1)
			{
			   RunSecond=0;
			   Step=3;
			   LedRedON();
			}
		 
		 }
		 break;
		 case 3:
		 {
			if(RunSecond>1)
			{
			   RunSecond=0;
			   Step=2;
			   LedRedOff();
			}
			if(Voltage>820)
			{
			   Step=4;
			   LedGreenON();
			}					 
		 }
		 break;
		 case 4:
		 {
		 	if(ReadPowerDCIn()==0)
			{
			   Mode=0;
			   Step=0;
			}
		 }
		 break;
		 }	  
	  }
	  break;
	  //故障
	  case 5:
	  {
	    switch(Step)
		{
		   //机器卡住,红灯亮，每隔5秒响一声哔声；
		   case 0:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=1;
				RunSecond=0;
		   }
		   break;
		   case 1:
		   {
		   	  if(RunSecond>4)
			  {
			  	 RunSecond=0;
				 SetBuzzerTime(5);
			  }
		   }
		   break;
		   //边扫马达堵转  红灯亮，每隔5秒响三声哔声；

		   case 2:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				RunSecond=0;
		   }
		   break;
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }

		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
			 }
		   	 if(Run100MSecond==7)
			 {
			    Run100MSecond=0;
				RunSecond=0;
				Step=3;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		   //后轮马达堵转 红灯亮，每隔5秒响两声哔声，1秒后响一声哔声；
		   case 5:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=6;
				RunSecond=0;
		   }
		   break;
		   case 6:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=7;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }

		   }
		   break;
		   case 7:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
			 }
		   	 if(Run100MSecond==7)
			 {
				RunSecond=0;
				Step=8;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		   case 8:
		   {
		   	  if(RunSecond>1)
			  {
				 Step=6;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
				 RunSecond=0;
			  }		   
		   
		   }
		   break;
		   //风扇堵转或者电流大	红灯亮，每隔5秒响三声哔声，1秒后响两声哔声；
		   case 9:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=10;
				RunSecond=0;
		   }
		   break;
		   case 10:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=11;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }

		   }
		   break;
		   case 11:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
			 }
		   	 if(Run100MSecond==7)
			 {
			    Run100MSecond=2;
				RunSecond=0;
				Step=12;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		   case 12:
		   {
		   	  if(RunSecond>1)
			  {
				 Step=13;
				 SetBuzzerTime(3);
				 Run100MSecond=0;
				 RunSecond=0;
			  }		   
		   
		   }
		   break;
 		   case 13:
		   {

		   	 if(Run100MSecond==3)
			 {
				RunSecond=0;
				Step=9;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		}
	  }
	  break;
	}
}
