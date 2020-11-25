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
/***************************************************************************
	*
	*Function Name: void  CheckRun()
	*Function :A star alogrithm
	*
	*
	*
***************************************************************************/
void  CheckRun()
{
      
	  static INT8U maxValue,diffopen;
	  INT8U runkey=0,runkey1 =0;
	   switch(Step){
		case 0:
                 LedRedON();// 
				 RunMs=0;
				 KeyclearTime=0;
				 Step =1;
	             

		break;

		case 1:  //ֱ������
		
			  LedGreenON();
			if(Remote1_ReadIR.ReadCloseList[0]==1){//不在这个方向执行运行
                 RunMs=0;
			     KeyclearTime=0;
				 Step =3;           //
			}
			else{
               if(KeyclearTime < 1)
		       {	
			   SetXMotor(2,5,5,2,2,5,5,2);
		        SetMotorcm(1,50);
				SetXMotor(2,10,20,2,2,0,1,2);
		        SetMotorcm(1,50);
			    SetXMotor(2,10,20,2,2,1,1,2);
		        SetMotorcm(1,50);
				
				
					if(ReadPowerDCIn()){ //�Զ����
		              
			               AllStop();
						   LedGreenON();
						  
						
							if(Voltage>820)
							{
			                     Mode=0;
						         Step=0;
								LedGreenON();
							}
					} 	
                }
			   else{
			     Step =2;

				}
			}
	    break;


		case 2: //Adjust line run condition
           
				 AllStop();
				 Delay_ms(500);
				 Remote1_ReadIR.ReadASTAR[0][0]=Remote1_ReadIR.Interrupt_IR2;//����1 ��
				 Remote1_ReadIR.ReadASTAR[0][1]=Remote1_ReadIR.ReadIR[0];
				 if(Remote1_ReadIR.ReadASTAR[0][0] ==0){
					 Remote1_ReadIR.ReadCloseList[0]= 1;
					 RunMs=0;
			         KeyclearTime=0;
				     Step =3;
				 }
				 else {
					  Remote1_ReadIR.ReadCloseList[0]= 0;
					  Remote1_ReadIR.ReadOpenList[0] =1;
				 
						if(maxValue == 1){
							RunMs=0;
							KeyclearTime=0;
							Step=1;
			           }
					   else{
						   	RunMs=0;
							KeyclearTime=0;
							Step=1;

					   }
					
				 }
		case 3:
				 //CCW 90 RUN 
                if(Remote1_ReadIR.ReadCloseList[1]==1){//不在这个方向执行运行
                        RunMs=0;
						KeyclearTime=0;
						Step =4;
			    }
				else{
				 if(ReadPowerDCIn()){ //CCW 90 
		             AllStop();
				 }

		         else if(KeyclearTime<3)//To motor CCW   90 degree
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
				 Step=4;
		
				}
		break; 

		case 4:
                 AllStop();
				 Delay_ms(500);
				 Remote1_ReadIR.ReadASTAR[1][0]=Remote1_ReadIR.Interrupt_IR2;//����1 ��
				 Remote1_ReadIR.ReadASTAR[1][1]=Remote1_ReadIR.ReadIR[0];
                 if(Remote1_ReadIR.ReadASTAR[1][0]==0){
					 Remote1_ReadIR.ReadCloseList[1]=1;	
					  RunMs=0;
			          KeyclearTime=0;
				      Step =5;
				 }
				 else{
					 Remote1_ReadIR.ReadCloseList[1]=0;	
					 Remote1_ReadIR.ReadOpenList[1] =1;
				 
					if(maxValue == 2 ){
						RunMs=0;
						KeyclearTime=0;
						Step=13;
						maxValue =0;
						diffopen =2;
		            }
					else{
						RunMs=0;
						KeyclearTime=0;
						Step =13;
						diffopen =2;
					}
				 }

		break;

		case 5:   //CCW 180 degree  180 degree 
				if(Remote1_ReadIR.ReadCloseList[2]==1){//不在这个方向执行运行
                        RunMs=0;
						KeyclearTime=0;
						Step =6;
			    }
				 if(ReadPowerDCIn()){ //CCW 90 
		             AllStop();
				 }
                  else if(KeyclearTime<3)//To motor CCW   90 degree
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
				 else{
				
				 
			      Step =6;
				 }

		break;

		case 6:
			     AllStop();
				 Delay_ms(500);
				 Remote1_ReadIR.ReadASTAR[2][0]=Remote1_ReadIR.Interrupt_IR2;//����1 ��
				 Remote1_ReadIR.ReadASTAR[2][1]=Remote1_ReadIR.ReadIR[0];
				 if(Remote1_ReadIR.ReadASTAR[2][0]==0){
					 Remote1_ReadIR.ReadCloseList[2]=1;	
					  RunMs=0;
			          KeyclearTime=0;
				      Step =7;
				 }
				 else{
					 Remote1_ReadIR.ReadCloseList[2]=0;	
					 Remote1_ReadIR.ReadOpenList[2] =1;
				 
					if(maxValue == 3){
					RunMs=0;
					KeyclearTime=0;
					Step=13;
					maxValue =0;
					diffopen = 3;
		
					}
					else{
					diffopen =3;
					RunMs=0;
					KeyclearTime=0;
					Step =13;
					}
				 }
		break;


		case 7:  //CCW 270 degree
			 
			//������ ��90
			if(Remote1_ReadIR.ReadCloseList[3]==1){//不在这个方向执行运行
                        RunMs=0;
						KeyclearTime=0;
						Step =8;
			}
			else {
			if(ReadPowerDCIn()){ //�Զ����
		             AllStop();
			}
			else if(KeyclearTime<3)//To motor CCW   90 degree
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
			else {
		
			 
			 Step =8;

			}
			}
		break;
		case 8:
				 AllStop();
				 Delay_ms(500);
				   Remote1_ReadIR.ReadASTAR[3][0]=Remote1_ReadIR.Interrupt_IR2;//����1 ��
			       Remote1_ReadIR.ReadASTAR[3][1]=Remote1_ReadIR.ReadIR[0];
				   if(Remote1_ReadIR.ReadASTAR[3][0]==0){
					 Remote1_ReadIR.ReadCloseList[3]=1;	
					  RunMs=0;
			          KeyclearTime=0;
				      Step =11;
				 }
				 else{ 
					 Remote1_ReadIR.ReadCloseList[3]=0;
					 Remote1_ReadIR.ReadOpenList[3] =1;
				 }
				  if(maxValue == 4){
                  RunMs=0;
			      KeyclearTime=0;
				  Step=13;
				  maxValue =0;
				  diffopen =4;
    
				 }
				 else{
					 RunMs=0;
					 KeyclearTime=0;
					 Step =13;
					 diffopen =4;
				 }

		break;

		case 11: 
		         
				 if(ReadPowerDCIn()){ //�Զ����
		             AllStop();
				 }
				 else if(KeyclearTime<3)//To motor CCW   90 degree
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
				 RunMs=0;
			     KeyclearTime=0;
				 Step=12;
				 

		break;
		

		case 12:  //�Ƚ�4�������ֵ��С��
		         AllStop();
		         Delay_ms(500);
                #if 0
		        runkey=max4(Remote1_ReadIR.ReadASTAR[0][0],Remote1_ReadIR.ReadASTAR[1][0] ,Remote1_ReadIR.ReadASTAR[2][0],Remote1_ReadIR.ReadASTAR[3][0]);
		        if(runkey ==0){
					runkey1=max4(Remote1_ReadIR.ReadASTAR[0][1],Remote1_ReadIR.ReadASTAR[1][1] ,Remote1_ReadIR.ReadASTAR[2][1],Remote1_ReadIR.ReadASTAR[3][1]);
                 }
				if(runkey !=0){
				#endif 
				if(Remote1_ReadIR.ReadOpenList[0] ==1) 
				{
					RunMs=0;
					KeyclearTime=0;
					Step =2;
					maxValue = 1;
				}
				else if(runkey ==Remote1_ReadIR.ReadASTAR[0][1]){
						Step =3; //the first turn on 90 degree then run line.13
						RunMs=0;
					    KeyclearTime=0;
						maxValue =2;
				} 
				else if(runkey ==Remote1_ReadIR.ReadASTAR[0][2]) {
					Step =6; //������
					RunMs=0;
					KeyclearTime=0;
					maxValue =3;
				}
				else if(runkey ==Remote1_ReadIR.ReadASTAR[0][3]){
					Step =8; //������
					RunMs=0;
					KeyclearTime=0;
					maxValue = 4;
				} 
				
				else Step =0;
		break;
        
		case 13 :
		      
			  if(Remote1_ReadIR.ReadCloseList[4]==1){//不在这个方向执行运行
                        RunMs=0;
						KeyclearTime=0;
						Step =14;
			}
			else {
			if(ReadPowerDCIn()){ //�Զ����
		              
			               AllStop();
						   LedGreenON();
						  
						
							if(Voltage>820)
							{
			                     Mode=0;
						         Step=0;
								LedGreenON();
							}
			} 	
			  
			else if(KeyclearTime < 1)
		       {	
			   SetXMotor(2,5,5,2,2,5,5,2);
		        SetMotorcm(1,50);
				SetXMotor(2,10,20,2,2,0,1,2);
		        SetMotorcm(1,50);
			    SetXMotor(2,10,20,2,2,1,1,2);
		        SetMotorcm(1,50);
				
				
					
                }
			   else{
			     Step =14;

				}
			}
	   break; 
       
	   case 14:
	             AllStop();
				 Delay_ms(500);
				Remote1_ReadIR.ReadASTAR[4][0]=Remote1_ReadIR.Interrupt_IR2;//����1 ��
			    Remote1_ReadIR.ReadASTAR[4][1]=Remote1_ReadIR.ReadIR[0];
				   if(Remote1_ReadIR.ReadASTAR[4][0]==0){
					 Remote1_ReadIR.ReadCloseList[4]=1;	
					  RunMs=0;
			          KeyclearTime=0;
				      Step =0;
				 }
				 else{ 
					 Remote1_ReadIR.ReadCloseList[4]=0;
					 Remote1_ReadIR.ReadOpenList[4] =1;
				 }
				 if(diffopen == 2 || diffopen ==3 || diffopen ==4){
                  RunMs=0;
			      KeyclearTime=0;
				  Step=13;
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
	   	   	   //����
	   if(Key>0)
	   {
		 KeydelayTime=0;
//	     SBUF=Key;
	   }
   switch(Key)  //��������ֵ��ѡ��ģʽ�����в�����
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
	   //����/��ͣ
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
	   //����
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
	   //ģʽ�л�
	   case 10:
	   {
	   
	   	  Mode++;
		  Step=0;
		  if(Mode>3)
		   Mode=1;
		  ModeBackup=0;
	   }
	   break;
	   //���ֱ���ƶ� ----
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
	   //��
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
	   //��
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
	   //��
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
   /***************�������µ�ģʽ������������е�ģʽ *************************/
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
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
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
			//�������
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
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
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
			//�������
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
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
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
			//�������
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
	  //���,����س��
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
		   //��ɨ�����ת  �������ÿ��5��������������

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
		   //���ȶ�ת���ߵ�����	�������ÿ��5��������������1���������������
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
