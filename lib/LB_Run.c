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
/***************************************************************************
	*
	*Function Name: void  CheckRun()
	*Function :A star arithmetic 
	*
	*
	*
***************************************************************************/
void  CheckRun()
{
      
	  INT8U runkey=0;
	   switch(Step){
		case 0:
                 LedGreenON();
	             AllStop();
				 RunMs=0;
				 KeyclearTime=0;
		         runkey= CheckHandsetIR();
				 if(runkey ==3)Step = 1;    //left IR ,To motor move right dir
				 Step =1;
	             

		break;

		case 1:  //直线行走
		
			LedRedON();
			if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]>=0x0D){
			
               if(KeyclearTime < 1)
		       {	
			   SetXMotor(2,5,5,2,2,5,5,2);
		        SetMotorcm(1,50);
				SetXMotor(2,10,20,2,2,0,1,2);
		        SetMotorcm(1,50);
			    SetXMotor(2,10,20,2,2,1,1,2);
		        SetMotorcm(1,50);
				
					if(ReadPowerDCIn()){
						
                         AllStop();
					}
			   }
			}
			if(KeyclearTime>1)
		      AllStop(); 

			 if(ReadPowerDCIn()){ //自动充电
		              
			               RunSecond=0;
						   LedRedOff();
						   RunStep =1;
						   LedGreenON();
						   RunMs=0;
						   
						
						if(Voltage>820)
						{
		                     Mode=0;
					         Step=0;
							LedGreenON();
						}
					
		     }
		 } 	
		 else 
		     Step =2;
		
	    break;


		case 2:
                 AllStop();
				 Delay_ms(500);
		         if((Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >= Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1])  && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]  >= 0x0D)
				 {
				 	  Step=1;
		         }
				 else {	//旋转90度
					 RunMs=0;
			         KeyclearTime=0;
			         Step =3;
				   }

		break;


		case 3:  //To move right dir CCW (agree 90 )

		            if(KeyclearTime<3)//To motor CCW 
					{	
								
						if(KeyclearTime<2){
						  SetXMotor(1,5,5,1,2,5,5,1);
						  SetMotorcm(4,45);//SetMotorcm(4,45);
						  RunMs =0;
						}
						if(RunMs<40){
							SetXMotor(1,5,5,1,2,5,5,1);
						    SetMotorcm(4,45);//SetMotorcm(4,45);
						}
								 
					}
				 else 
				  Step=4;
				 AllStop();
				

		break;

		case 4:  //在判断方向
			
               AllStop();
				Delay_ms(500);
				if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]	>  Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]	 && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ]> 0x0D){
					Step=1;
				}
				if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]		  && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] < 0x0D)
				   {
					 Step=5;
				   }
				else{ //旋转180度 13

					RunMs=0;
					KeyclearTime=0;

                    Step =13;
				}


		break;

		case 5:   //走直线
           
				LedRedON();
			
			
		     if(KeyclearTime < 1)
			 {	
				if(KeyclearTime < 1)
		       {	
			   SetXMotor(2,5,5,2,2,5,5,2);
		        SetMotorcm(1,50);
				SetXMotor(2,10,20,2,2,0,1,2);
		        SetMotorcm(1,50);
			    SetXMotor(2,10,20,2,2,1,1,2);
		        SetMotorcm(1,50);
				
					if(ReadPowerDCIn()){
						
                         AllStop();
					}
			   }
		     }	
			 if(KeyclearTime>1)
		       AllStop(); 

			 if(ReadPowerDCIn()){ //自动充电
		              
			               RunSecond=0;
						   LedRedOff();
						   RunStep =1;
						   LedGreenON();
						   RunMs=0;
						   
						
						if(Voltage>820)
						{
		                     Mode=0;
					         Step=0;
							LedGreenON();
						}					 
		     }
			  
		 else 
		     Step =6;


		break;

		case 6:
                 AllStop();
				 Delay_ms(500);
		         if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]  >  Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]    && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] > 0x0D){
					 Step=1;
                 }
				 if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]        && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] < 0x0D)
				 	{
				 	  Step=5;
		         	}
				 else{ //旋转90度
					 RunMs=0;
			         KeyclearTime=0;

					 Step =7;
				 }

		break;
		

		case 7:  //To move right dir CCW (agree 90 )

					if(KeyclearTime<3)//To motor CCW 
					{	
								
						if(KeyclearTime<2){
						  SetXMotor(1,5,5,1,2,5,5,1);
						  SetMotorcm(4,45);//SetMotorcm(4,45);
						  RunMs =0;
						}
						if(RunMs<40){
							SetXMotor(1,5,5,1,2,5,5,1);
						    SetMotorcm(4,45);//SetMotorcm(4,45);
						}
								 
					}
					else 
				  Step=8;
				AllStop();
				

		break;
				
	    case 8:
			     AllStop();
				  Delay_ms(500);
		          if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]  >  Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]    && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] > 0x0D){
					 Step=1;
                 }
				 if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]        && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] < 0x0D)
				 	{
				 	  Step=9;
		         }
				 else { //否则就旋转180度方向
					   RunMs=0;
			          KeyclearTime=0;
					  Step=13; //旋转180度
				 }

		break;

		case 9:

                
					
			  if(KeyclearTime < 1)
		       {	
			   SetXMotor(2,5,5,2,2,5,5,2);
		        SetMotorcm(1,50);
				SetXMotor(2,10,20,2,2,0,1,2);
		        SetMotorcm(1,50);
			    SetXMotor(2,10,20,2,2,1,1,2);
		        SetMotorcm(1,50);
				
					if(ReadPowerDCIn()){
						
                         AllStop();
					}
			   }
		   	
			 if(KeyclearTime>1)
		       AllStop(); 

			 if(ReadPowerDCIn()){ //自动充电
		              
			               RunSecond=0;
						   LedRedOff();
						   RunStep =1;
						   LedGreenON();
						   RunMs=0;
						   
						
						if(Voltage>820)
						{
		                     Mode=0;
					         Step=0;
							LedGreenON();
						}					 
		     }
			 else 
		     Step =10;
			 AllStop();

		break;

		case 10:
                  AllStop();
				  Delay_ms(500);
		          if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]  >  Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]    && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] > 0x0D){
					 Step=1;
                 }
				 if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]        && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] < 0x0D)
				 	{
				 	  Step=9;
		         }
				 else {
						 RunMs=0;
						KeyclearTime=0;
						Step =11;
				 }


		break;

	
		case 11: //CW motor 90 degree ---顺时针旋转 90 度
		
			  if(KeyclearTime<3)//To motor move to right dir 
				 {	
							 LedRedON();
							if(KeyclearTime<2){
							   SetXMotor(2,5,5,1,1,5,5,1);
						       SetMotorcm(3,45);
								RunMs =0;
							}
							if(RunMs<40){
								SetXMotor(2,5,5,1,1,5,5,1);
							   SetMotorcm(3,45);
								
							}
							 
				}
                 else Step=12;

				 AllStop();
				
		break;

		case 12:
                 AllStop();
				  Delay_ms(500);
		           if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]  >  Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]    && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] > 0x0D){
					 Step=1;
                 }
				 if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]        && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] < 0x0D)
				 {
				 	  Step=9;
		         }
				  else{ //旋转180度
						 RunMs=0;
						KeyclearTime=0;
				         Step =13;
				  }
				  
		break;

		case 13 : // 旋转180度

		          if(KeyclearTime<6)//To motor move to right dir 
				 {	
						LedRedON();
							if(KeyclearTime<2){
							   SetXMotor(2,5,5,1,1,5,5,1);
						       SetMotorcm(3,45);
								RunMs =0;
							}
							if(RunMs<40){
								SetXMotor(2,5,5,1,1,5,5,1);
							   SetMotorcm(3,45);
								
							}
							 
				}
                 else{
					Step=14;
                 }
				 AllStop();

		break ;

		case 14 :
				  AllStop();
				  Delay_ms(500);
		          if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]  >  Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]    && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] > 0x0D){
					 Step=1;
                 }
				 if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time -1]        && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time ] < 0x0D)
				 	{
				 	  Step=9;
		         }
				  else{
						RunMs=0;
						KeyclearTime=0;
				        Step =11;
				  }
		break;
		
		
		
		}
}
/******************************************************************
	*
	*Function Name:void CheckMode(INT8U Key)
	*Function : power on be selected motor run mode 
	*Input Ref:intput button key value
	*Return Ref:NO
	*
******************************************************************/
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
   switch(Key)  //按键输入值，选择模式和运行步伐。
   {
     

	   case 1:
	   	         Mode =14 ; //WT.EDIT 
				 
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
	     if(ModeBackup!=0)		 {
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
	   //电机直线移动 ----
	   case 5:
	   {
		 //KeyRunTime=0;
	     if(Mode<4) //power on Mode =1 ,step =0;
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
   /***************按键按下的模式：电机具体运行的模式 *************************/
   /**************************************************************************/
    switch(Mode) ///模式 Mode -> step
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
	  //充电,给电池充电
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

		   case 14: 
               RunStep =1;
		      
		   	break;
		}
	  }
	  break;
	}
}
