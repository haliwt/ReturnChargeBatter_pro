#include "lb_key.h"
#include "lb_ir.h"
#include "..\lib\LB_Run.h"
#include "..\lib\LB_Led.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_AD.h"
xdata struct _CleanMode cleanWorks;
/****************************************************
	*
	*Function Name: INT8U AutoDC_ReChargeStatus(void)
	*Function :
	*Inpute Ref: NO
	*Return Ref: battery is full electric quantiy value
	*            1 --full quantiy  0- no full
	*
*****************************************************/
INT8U AutoDC_ReChargeStatus(void)
{
    static INT8U full=0;
	if(Auto_DCCharge ==1 || DC_Recharge  ==1 ){//�س�͵�Դ������DC�����⣬û������??
	     
             if(chargeflag ==0){
					chargeflag ++ ;
					SetStop();
					SetFan(0);
					SetEdge(0);	
					Delay_ms(1000);
					Delay_ms(1000);
					SetBuzzerTime(25);
					Delay_ms(500);
					BuzzerOff();
					SetBuzzerTime(25);
					Delay_ms(500);
					BuzzerOff();
					SetBuzzerTime(25);
					Delay_ms(500);
					BuzzerOff();
					
					
			}
            if(BatteryRechargStatus ==1){
			   LedRedOff();
			   LedGreenON();
	           Delay_ms(1000);
               full ++ ;
			   if(full > 250)full =11;
               if(full > 10){
			   	    InitMotorRetreat_TOPIR();
				    Delay_ms(500);
					SetStop();
					RunMode = 0;
					RunStep = 0;
					SetBuzzerTime(4);
					Delay_ms(10);
					BuzzerOff();
		            SetFan(0);  //WT.EDIT 
					SetEdge(0);	 //WT.EDIT 	
					ADCtl=0;
					SysFlag = IDEL;
					return 1;
               }
			   return 1;
	        
		   }
	
				SetStop();
			    SetFan(0);
				SetEdge(0);	
				RunMode = 0; //the second input auto recharge 
				RunStep = 0;
				  if(twinkle < 1 ){
					 LedRedOff();
					 LedGreenOff();
					 full=0;
				}
				else{
						 if(twinkle > 2)twinkle =0;
						 LedGreenOff();
						 LedRedON();
						 full=0;
				}
			return 1;
	}
	else 
		return 0;
}

/****************************************************
	*
	*Function Name: INT8U AutoDC_ReChargeStatus(void)
	*Function :
	*Inpute Ref: NO
	*Return Ref: battery is full electric quantiy value
	*            1 --full quantiy  0- no full
	*
*****************************************************/
void ItselfChecking(void)
{
   
      	switch(RunStep)
		{
		case 0:
		{
              RunStep =1;
			  RunMs =0 ;
		}
		break;
		case 1:
		{
			if(RunMs<20){

				InitMotorForward();
				RunMs=0;
				RunStep=6;
			}
		}
		break;

		case 2:
			if(RunMs>500)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=3;
			}

		break;

		case 3:
			if(RunMs>500)
			{
				InitMotorRight();
				RunMs=0;
				RunStep=3;
			}

		break;

		default:

		break;

 }
}
void TOP_IR(void)
{

   
	switch(RunStep){
	case 0:
		   
				
		  if(RunMs <  20){
               InitMotorForwardSlow();//InitMotorLeft();
		   }
		   else {
		      RunMs =0;
			  RunStep =1;
		   
		   }
	break;

	case 1:
			 
				
		   
		   if(RunMs< 30){
			   SetStop();

		   }
		   else{
		   
		    RunStep = 2;
				 RunMs =0;
		   
		   }
	break;

	 /***************TOP IR PROC**********************/
	case 2: //旋转  //Fast turn run  InitMotorLeft(void);
			
				
			  

			
			if(RunMs < 100){
				InitMotorLeft();//InitMotorForwardSlow();
				

			}
			else{
			
			  RunStep=3;//
				RunMs = 0;
			}

		break;
		case 3:
			
	            
				
		   
		  if(RunMs< 30){

             SetStop();
			 

			}
		   else{
		     RunStep = 4;
			RunMs =0;
		   
		   }
		break;
		case 4: //直线 
            

                
                
		    
			if(RunMs< 30){
				
				 InitMotorForwardSlow();
			}
			else{
			 RunStep = 5 ;
			     RunMs = 0;
			
			}

		break;
		case 5:
			
				
				
			 
			 if(RunMs<20){
					 SetStop();
				
			 }
			 else{
			 
			  RunStep = 0;
				 RunMs =0; //转圈--look for
			 }
			
		break;

		

	}


}


