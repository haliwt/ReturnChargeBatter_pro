/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
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


void InitPowerIn(void)
{
  P1M7 = 0x60; //P17 input GPIO PULL  UP =charge_sata 
 // P1M0 = 0x50;     
   //P10 input GPIO PULL DOWN =DC detected ,outside charge batter connector
   //P1_0 =1;
}

/***************************************************************************
	*
	*Function Name: void  CheckRun()
	*Function :A star alogrithm
	*
	*
	*
***************************************************************************/

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
				  //����
		  if(Key>0)
		  {
			KeydelayTime=0;
   		//SBUF=Key;
		  }
	  }
	  	
		//Enter3=0;RunStep=0;
		//Mode=1;
		//Step=0;
	  switch(Key)
	  {
		
       
	
         //
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
		  //����/��ͣ
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
		  //����
		  case 3:
		  {
			 if(Mode!=1)
			 {
			   Mode=1; //ģʽ1 
			   Step=0; 
			   ModeBackup=0;		 
			 }
		  }
		  break;
		  //ģʽ�л�
		  case 10:
		  {
		  
			 Mode++;
			// Step=0;
			// if(Mode>3)
			  //Mode=1;
			 //Step = 0; //WT.EDIT 
			// ModeBackup=0;
		  }
		 // break;
		  //ǰ
		 // case 5: //WT.EDIT 
		  {
			RunSecond=0;
			//KeyRunTime=0;
			if(Mode<4)
			{
			SetXMotor(1,10,10,1,1,10,10,1);
			SetMotorcm(1,10);
			}
			if(Mode==0)  //ģʽ 0 
			{
			  RunStep=0x0D;
			}
			if(Mode==1) //ģʽ 1 
			{
			  RunStep=0x0C;
			}
			if(Mode==2) //ģʽ 2
			{
			  RunStep=0x3c;
			}
			if(Mode==3) //ģʽ 3 
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
		  //��
		  case 6:
		  {
			RunSecond=0;
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
		  //��
		  case 8:
		  {
			RunSecond=0;
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
		  //��
		  case 9:
		  {
			RunSecond=0;
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
/****************************************************/
	 //��ʼ��ֵ �� Mode=1; Step=0;ImpStatus=0;
      // RunStep=0; modeBackup =0 ; 
      
/****************************************************/
       switch(Mode)
	   {
		 //��ͣ
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
				 //  MotorSpeedIRON();
				   AllStop();
				   LedGreenON();
			break;
			case 1:
			if(RunSecond>10)
			{
			  LedGreenOff();
			//  After_Lowpowermode=1;
			  Step=2;
              #if 0
   
   //		  P0M0 = 0x02;			  //P25����Ϊģ������
			  P0M1 = 0x02;			  //P26����Ϊģ������
			  P0M2 = 0x02;			  //P27����Ϊģ������
			  P0M3 = 0x02;			  //P25����Ϊģ������
			  P0M4 = 0x02;			  //P26����Ϊģ������
			  P0M5 = 0x02;			  //P25����Ϊģ������
			  P0M6 = 0x02;			  //P26����Ϊģ������
			  P0M7 = 0x02;			  //P27����Ϊģ������
   
			  P1M0 = 0x02;			  //P25����Ϊģ������
			  P1M1 = 0x02;			  //P26����Ϊģ������
			  P1M2 = 0x02;			  //P27����Ϊģ������
			  P1M3 = 0x02;			  //P25����Ϊģ������
			  P1M4 = 0x02;			  //P26����Ϊģ������
			  P1M5 = 0x02;			  //P25����Ϊģ������
   //		  P1M6 = 0x02;			  //P26����Ϊģ������
   
			  P2M0 = 0x02;			  //P25����Ϊģ������
			  P2M1 = 0x02;			  //P26����Ϊģ������
			  P2M2 = 0x02;			  //P27����Ϊģ������
			  P2M3 = 0x02;			  //P25����Ϊģ������
			  P2M4 = 0x02;			  //P26����Ϊģ������
			  P2M5 = 0x02;			  //P25����Ϊģ������
			  P2M6 = 0x02;			  //P26����Ϊģ������
			  P2M7 = 0x02;			  //P27����Ϊģ������
   
			  P3M0 = 0x02;			  //P25����Ϊģ������
			  P3M1 = 0x02;			  //P26����Ϊģ������
			  P3M2 = 0x02;			  //P27����Ϊģ������
			  P3M3 = 0x02;			  //P25����Ϊģ������
			  P3M4 = 0x02;			  //P25����Ϊģ������
			  P3M5 = 0x02;
   
   
			  IE &= 0xef;  
			  TCON	= 0x00; 					   //ʹ��T1
			  EA=1;
			  PCON |= 0x02; 						   //�͹��ļĴ���
			  #endif 
   
			}
			else if(ReadPowerDCIn())
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
		 /****************Mode = 0 END*******************/
		 /**************************************************/
		  //��ʼ��ֵ �� Mode=1; Step=0;ImpStatus=0;
          // RunStep=0; modeBackup =0 ; 
          /**********Mode =1 start***********************/
		 /***********************************************/
		 //����
		 //Mode =1 start 
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
			   SetIMPOutOn();   //������ײ����
			  // MotorSpeedIRON();
			   IMPTime=0;
			}
			break;
			case 1:
			{
			   if(RunSecond>1) //1s
			   {
				    Step=2;
				   SetFan(255);
				   SetEdge(200);
				   RunStep=1;  //-------
			   }
			}
			break;
			case 2:
			{
			  //����ײ
			   if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[0]>GroundMin))
			   {
				   GroundSecond=0; //���ϰ���
			   }
			   if((RunSecond%30)==0)
			   {
				   CurrentMax=0;
				   RunSecond++;
			   }
			   //������
			   if(CurrentMax>4)
			   {
				   Mode=5;
				   Step=5;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);		   
			   }
			   //��ɨ����
			   else if(EdgeCurrentCount>5)
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
			   //�������
			   else if(FanCurrent>2300)
			   {
				   Mode=5;
				   Step=9;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);			   
			   
			   }
			   //����
			   else if(IMPTime>5) //
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
   
   
			   else if(Voltage<680)
			   {
				   P1_7=0;
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
			else LedGreenON();			
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
		 /******************Mode =1 END *****************/
		 /************************************************************/
		 /************************************************************/
		 //����
		 //Mode =2 start 
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
			   if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin))//if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[0]>GroundMin))
			   {
				   GroundSecond=0;
			   }
			   if((RunSecond%30)==0)
			   {
				   CurrentMax=0;
				   RunSecond++;
			   }
			   //������
			   if(CurrentMax>4)
			   {
				   Mode=5;
				   Step=5;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);		   
			   }
			   //��ɨ����
			   else if(EdgeCurrentCount>5)
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
   //			   Mode=5;
   //			   Step=2;		   
   //			   RunStep=0;
   //			   RunSecond=0;
   //			   SetFan(0);
   //			   SetEdge(0);			   
			   
			   }
			   //�������
			   else if(FanCurrent>2300)
			   {
				   Mode=5;
				   Step=9;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);			   
			   
			   }
			   //����
			   else if(IMPTime>5)
			   {
				   Mode=5;
				   Step=0;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);			   
			   
			   }
			   else if(Voltage<680)
			   {
				   P1_7=0;
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
		 /**********************Mode =3 END**************************/
		 /***********************************************************/
		 /**********************************************************/
		 //�ر�
		 //Mode =3 
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
			   if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[0]>GroundMin))
			   {
				   GroundSecond=0;
			   }
			   if((RunSecond%30)==0)
			   {
				   CurrentMax=0;
				   RunSecond++;
			   }
			   //������
			   if(CurrentMax>4)
			   {
				   Mode=5;
				   Step=5;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);		   
			   }
			   //��ɨ����
			   else if(EdgeCurrentCount>5)
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
   //			   Mode=5;
   //			   Step=2;		   
   //			   RunStep=0;
   //			   RunSecond=0;
   //			   SetFan(0);
   //			   SetEdge(0);			   
			   }
			   //�������
			   else if(FanCurrent>2300)
			   {
				   Mode=5;
				   Step=9;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);			   
			   
			   }
			   //����
			   else if(IMPTime>5)
			   {
				   Mode=5;
				   Step=0;		   
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);			   
			   
			   }
			   else if(Voltage<680)
			   {
				   P1_7=0;
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
		 /********************Mode =3 END***************************/
		 /**********************************************************/
		 /**********************************************************/
		 /*********************************************************/
		 break;
		 //���
		 //Mode =4 start 
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
   //		   if((Voltage>820)||(ReadPowerDCIn()==0))
			   if((ReadPowerRecharge()==1)||(ReadPowerDCIn()==0))
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
		 //����
		 case 5:
		 {
		   switch(Step)
		   {
			  //������ס,�������ÿ��5����һ��������
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
			  //��ɨ�����ת	�������ÿ��5��������������
   
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
			  //���������ת �������ÿ��5��������������1�����һ��������
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
			  /*
				if(Run100MSecond==3)
				{
				   Run100MSecond=4;
				   SetBuzzerTime(5);
				}
				*/
				if(Run100MSecond==3)//7
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
			  //���ȶ�ת���ߵ�����    �������ÿ��5��������������1���������������
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
   
   
   
   /***************�������µ�ģʽ������������е�ģ�?*************************/
   /**************************************************************************/
    switch(Mode) ///ģʽ Mode -> step
	{
	  //��ͣ
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
	  //����
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
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[0]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//������
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//��ɨ����
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
			//�������?
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//����
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
	  //����
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
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[0]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//������
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//��ɨ����
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
			//�������?
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//����
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
	  //�ر�
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
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[0]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//������
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//��ɨ����
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
			//�������?
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//����
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
	  //���?����س��
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
	  //����
	  case 5:
	  {
	    switch(Step)
		{
		   //������ס,�������ÿ��?����һ��������
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
		   //��ɨ������? �������ÿ��?��������������

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
		   //����������?�������ÿ��?��������������1�����һ��������?
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
		   //���ȶ�ת���ߵ�����	�������ÿ��?��������������1���������������?
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
/*************************************************************************
	*
	*
	*
	*

	*
	*
**************************************************************************/
void  CheckRun()
{

		switch(RunStep)
		{
		case 0:
		{

		}
		break;

		case 0x0D:  //forward Step =5 to RunStep = 0x0D 
		{

			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				ImpSecond=0;
				RunStep=0x0;
				AllStop();
			}
			else 

			if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=0;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				SetXMotor(2,10,20,1,2,10,20,1);  //Big radian run 
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=0;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1); //
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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

		//����ģʽ�л�������RunStep =1;

		case 1:
		{
			ImpSecond=0;
			SetXMotor(1,10,15,1,1,10,15,1); //ֱ�� ----
			SetMotorcm(1,1000);
			RunStep=2;
			RunMs=0;
		}
		break;
		case 2:
		///*
		     if(ImpSecond>5)
			 Imp2Time=0;

			if(GroundDp[1]>GroundMin) //right IR ������ײ
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(2,10,25,1,2,10,25,1); //��Ļ�����
				SetMotorcm(2,5);
				RunMs=20;
				Imp2Time++;
				Enter3=1;
			}
			else if(GroundDp[0]>GroundMin) //left IR ������ײ 
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Imp2Time++;
				Enter3=2;
			}
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Imp2Time++;
				Enter3=3;
			}
			#endif 
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
            if(RunMs>10)
			{
				SetXMotor(2,10,20,1,2,10,20,1); //�ߴ�Ļ��� CCW
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
				SetXMotor(2,10,20,1,1,10,20,1); //�ߴ�Ļ���CCW 
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
				SetXMotor(2,10,20,1,2,10,20,1);//�ߴ�Ļ���
				SetMotorcm(2,5);
				RunMs=0;
				Enter3=12;

			}
			else if(GroundDp[1] > GroundMin) //right IR 
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Enter3=15;
			}
  			#endif 

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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Imp2Time++;
			}
			#endif 
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Enter3=18;
			}
			#endif 

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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 
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
			else if(GroundDp[0]<GroundMin)
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
           #endif 
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 

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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 
			break;
			//��ǽ
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x22;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
		//����
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
				SetXMotor(1,10,20,1,1,10,20,1);
				SetMotorcm(1,50);
//				SetXMotor(2,10,10,1,1,10,10,1);
//				SetMotorcm(3,360);
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
			else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin))//else if((GroundDp[0]<GroundMin)||(GroundDp[1]<GroundMin)||(GroundDp[0]<GroundMin))
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
		//��
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
		//	������
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
			#if 0
			else if(GroundDp[0]<GroundMin)
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
			#endif 
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
			#if 0
			else if(GroundDp[0]<GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			#endif 
			break;
		case 0x56:
			if(RunMs>50)
			{
				RunMs=0;
				RunStep=0x50;
			}
			break;

			//��ɨ����
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
/***********************************************************
	*
	*Function Name :void RunRandom_Mode(void)
	*Function : 
	*Input Ref:NO
	*Retrun Ref:NO 
	*
***********************************************************/
void RunRandom_Mode(INT8U randomStep)
{
	
    switch(randomStep){
	case 0:
          AllStop();

	 break; 
	 case 1: //KEY press  RunStep =1 
		{
            SetXMotor(2,10,20,2,2,10,20,2);//SetXMotor(2,5,20,2,2,5,20,2);//WT.EDIT //SetXMotor(2,20,40,2,2,20,40,2);//new line SetXMotor(1,20,40,1,1,20,40,1);
			SetMotorcm(1,5000);
			randomStep=2;
			RunMs=0;
	     }
		break;
		case 2:
        {
		   // floor Robot to touch to wall 
          if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||CloseSwitch_L==1||CloseSwitch_R==1)
			{
				 AllStop();
				 //SetXMotor(1,20,1,1,1,20,1,1);
				  randomStep=3;
				 RunMs=0;			
			}
			if(InfraredHead_L ==0 || InfraredHead_R==0){
				AllStop();
				 //SetXMotor(1,20,1,1,1,20,1,1);
				  randomStep=3;
				 RunMs=0;	


			}
			if((RightMoveMotorData.Flag==1)||(LeftMoveMotorData.Flag==1))
			{
 				
					SetXMotor(2,10,20,2,2,10,20,2);//SetXMotor(2,5,20,2,2,5,20,2);//WT.EDIT //SetXMotor(2,20,40,2,2,20,40,2);//new line SetXMotor(1,20,40,1,1,20,40,1);  //???
					
					SetMotorcm(1,5000);
 				
			}
			
			if(RunMs>2000)//if(RunMs>3000)
			{
				 AllStop();
				 //SetXMotor(1,20,1,1,1,20,1,1);
				randomStep=3;
				RunMs=0;	
			}
			
		}
		break;
		case 3:
		   if(RunMs>20)  //Back run 
		   {
			SetXMotor(1,10,20,2,1,10,20,2);//SetXMotor(1,5,20,2,1,5,20,2);//WT.EDIT //SetXMotor(1,20,40,2,1,20,40,2);//new line //SetXMotor(2,20,40,1,2,20,40,1); //back 
			SetMotorcm(2,1000);
			randomStep=4;
			}
		break;
		case 4:
		{
			if(RunMs>120)
			{
				AllStop();
				RunMs=0;
				randomStep=5;
		
			}
			
		}
			break;
	    case 5:
		  {
			if(RunMs>20) //right run  --
			{
				
				SetXMotor(1,10,20,2,2,10,20,2);//SetXMotor(1,5,20,2,2,5,20,2);//SetXMotor(1,20,40,2,2,20,40,2);//new line SetXMotor(2,20,40,1,1,20,40,1); //right turn 
				SetMotorcm(3,5000);//SetMotorcm(3,9000);
				randomStep=6;
		
			}	
		}
		break;
		case 6:
			if(RunMs > 100)//if(RunMs>100)
			{
				AllStop();
				RunMs=0;
				randomStep=7;
			
			}
			
			break;
		case 7: //water pump
			
			if(RunMs>10) //20 * 10ms =200ms
			{
				SetXMotor(2,10,20,2,1,10,20,2);//SetXMotor(2,5,20,2,1,5,20,2);//WT.EDIT  //SetXMotor(2,20,40,2,1,20,40,2);//SetXMotor(1,20,40,1,2,20,40,1); //left turn run 转圈
						SetMotorcm(4,4000);//WT.EDIT 2020.11.17//SetMotorcm(4,9000); //??
						SetXMotor(1,10,20,2,2,10,20,2);//SetXMotor(1,5,20,2,2,5,20,2); //WT.EDIT //SetXMotor(1,20,40,2,2,20,40,2); //SetXMotor(2,20,40,1,1,20,40,1); //right turn 
				        SetMotorcm(3,9000);
						randomStep=8;
			}
		break;
		case 8: // water pump
		   if(RunMs > 100)//if(RunMs>100)
			{
				AllStop();
				RunMs=0;
				randomStep=9;
			
			}
			
			break;
			     
		 break;
		 case 9:
		 
		   if(RunMs > 240)
		   {
			
			
			    RunMs=0;
			    randomStep=0;
				SetXMotor(2,10,20,2,2,10,20,2);//SetXMotor(2,5,20,2,2,5,20,2);//WT.EDIT //SetXMotor(2,20,40,2,2,20,40,2);//new line //SetXMotor(1,20,40,1,1,20,40,1);//SetXMotor(1,20,25,1,1,20,40,1);//SetXMotor(1,20,25,1,1,20,40,1); //???
				SetMotorcm(1,5000);	
		   }
			
		 break;
		   
	   }
}
	
	




