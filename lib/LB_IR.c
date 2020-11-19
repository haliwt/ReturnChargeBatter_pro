/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_IR_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_IR.h"
#include "..\lib\LB_Usart.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#include "LB_Led.h"

#endif
#define setbit(x,y)    	 		x|=(1<<y)          //��X�ĵ�Yλ��1
#define clrbit(x,y)   	 		x&=~(1<<y)        //��X�ĵ�Yλ��0
#define reversebit(x,y) 	 	x^=(1<<y)        //ȡ��
#define getbit(x,y)  			((x) >> (y)&1)    //��ȡλ




void Init_IR()
{

    
	P1M6 = 0x68;			        	//P1_6����Ϊ��SMT(ʩ���ع���)��������

 	//PITS3 |= 0x00;						//INT14,�ⲿ�жϵ�ƽѡ��,�������ͷ���������ж�
	//PITS3 |=(3<<4);
	PITS3 &=~(1<<5);
	
	PINTE1 |= 0x40;						//ʹ��INT14

	IE2 |= 0x01;						//��INT8-17�ж�
	EA=1;
	Remote1_ReadIR.ReadIRFlag=0;


}
/**************************************************************
	*
	*Function Name:void Remote1_Count(void)
	*Fucntion :�ڶ�ʱ��T1,0.1ms�жϺ�����ִ��,�жϸߵ�ƽʱ��ir3
    *          IR3
	*
	*
**************************************************************/
void Remote1_Count(void)
{

#if 0 //IR3
	if(Remote1_ReadIR.ReadIRFlag==1) //IR_gpio �ж����� 1
	{
		
		if(Remote1_ReadIR.Nowcount>=0x32)//WT.EDIT 57ms if(Remote1_ReadIR.Nowcount>200)
		{
			//Remote1_ReadIR.ReadIRFlag=2;
			//Remote1_ReadIR.AABit ++ ;
			 
			     Remote1_ReadIR.BitHigh ++;
			    // Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =1 ;
				Remote1_ReadIR.ReadIRData[Remote1_ReadIR.BitHigh] =1 ;
			
		}
		else if(Remote1_ReadIR.Nowcount<0x32 && Remote1_ReadIR.Nowcount > 10){
		       Remote1_ReadIR.BitHigh ++;
			   Remote1_ReadIR.ReadIRData[Remote1_ReadIR.BitHigh] =0; 
		       

      }
   }
#endif
}
/**************************************************************
	*
	*Function Name:void Remote11_Count(void)
	*Fucntion :�ڶ�ʱ��T1,0.1ms�жϺ�����ִ��,�жϸߵ�ƽʱ��ir1
    *          IR1
	*
	*
**************************************************************/
void Remote11_Count(void)
{

#if IR1
	if(Remote1_ReadIR.ReadIRFlag==1) //IR_gpio �ж����� 1
	{
		if(P1_6 ==1)
		    Remote1_ReadIR.Nowcount++ ;
		//else Remote1_ReadIR.Nowcount--;
		if(Remote1_ReadIR.Nowcount>=0x18)//WT.EDIT 57ms if(Remote1_ReadIR.Nowcount>200)
		{
			//Remote1_ReadIR.ReadIRFlag=2;
			//Remote1_ReadIR.AABit ++ ;
			 
			    // Remote1_ReadIR.BitHigh ++;
			    Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =1 ;
				//Remote1_ReadIR.ReadIRData[Remote1_ReadIR.BitHigh] =1 ;
			
		}
		else if(Remote1_ReadIR.Nowcount<0x18 ){
		       Remote1_ReadIR.BitHigh ++;
			   Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =0 ;
		       

      }
   }
#endif
}
/**************************************************************
	*
	*Function Name:void Remote11_Count(void)
	*Fucntion :�ڶ�ʱ��T1,0.1ms�жϺ�����ִ��,�жϸߵ�ƽʱ��ir2
    *          IR1
	*
	*
**************************************************************/
#if IR2

void Remote12_Count(void)
{


	if(Remote1_ReadIR.ReadIRFlag==1) //IR_gpio �ж����� 1
	{
		if(P1_6 ==1)
		    Remote1_ReadIR.Nowcount++ ;
		//else Remote1_ReadIR.Nowcount--;
		if(Remote1_ReadIR.Nowcount>=0x18)//WT.EDIT 57ms if(Remote1_ReadIR.Nowcount>200)
		{
			
			 
			   
			    Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =1 ;
				
			
		}
		else if(Remote1_ReadIR.Nowcount<0x18 ){
		       
			   Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =0 ;
		       

      }
   }

}
#endif


/**************************************************************
	*
	*Function Name:void Read_Remote1IR(void)
	*Fucntion :GPIO ,�жϺ�����ִ��,IR3
	*Input Ref:NO
	*Return Ref: NO
	*
**************************************************************/
#if IR3

void Read_Remote1IR(void)
{

	Remote1_ReadIR.NowVoltage=P1_6; //remotoe receive GPIO
	
    if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==0))//input interrupt program
	{
		Remote1_ReadIR.ReadIRFlag=1;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit=0;
		Remote1_ReadIR.BitHigh=0;
	}
    else if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1))
	{
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Runcontrol=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;
		

//	  Usart1Send[0]=1;
//	  Usart1Send[1]=Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
//	  SendCount=1;
//	  SBUF=Usart1Send[SendCount];
		 Remote1_ReadIR.ReadIRBit++; //bit numbers add 
		
		if(Remote1_ReadIR.ReadIRBit >7){//WT.EDIT   ir_Middle //if(Remote1_ReadIR.ReadIRBit>80)
			Remote1_ReadIR.ReadIRFlag=2; 
		    Remote1_ReadIR.BitHigh=0;
		}
		
		
	}

}
#endif 

/**************************************************************
	*
	*Function Name:void Read_Remote11IR(void)
	*Fucntion :GPIO ,�жϺ�����ִ��,IR1,�ж�11��
	*Input Ref:NO
	*Return Ref: NO
	*
**************************************************************/
#if IR1

void Read_Remote11IR(void)
{

	Remote1_ReadIR.NowVoltage=P1_6; //remotoe receive GPIO
	
    if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==0))//input interrupt program
	{
		Remote1_ReadIR.ReadIRFlag=1;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit=0;
		Remote1_ReadIR.BitHigh=0;
	}
    else if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1))
	{
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Runcontrol=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;
		

//	  Usart1Send[0]=1;
//	  Usart1Send[1]=Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
//	  SendCount=1;
//	  SBUF=Usart1Send[SendCount];
		 Remote1_ReadIR.ReadIRBit++; //bit numbers add 
		
		if(Remote1_ReadIR.ReadIRBit ==10){//WT.EDIT   ir_Middle //if(Remote1_ReadIR.ReadIRBit>80)
			Remote1_ReadIR.ReadIRFlag=2; 
		   
		    Remote1_ReadIR.Interrupt_IR1 = 11;
		    
		}
		
		
	}

}
#endif 


/**************************************************************
	*
	*Function Name:void Read_Remote11IR(void)
	*Fucntion :GPIO ,�жϺ�����ִ��,IR2
	*Input Ref:NO
	*Return Ref: NO
	*
**************************************************************/
#if IR2

void Read_Remote12IR(void)
{

	Remote1_ReadIR.NowVoltage=P1_6; //remotoe receive GPIO
	
    if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==0))//input interrupt program
	{
		Remote1_ReadIR.ReadIRFlag=1;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit=0;
		Remote1_ReadIR.BitHigh=0;
	}
    else if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1))
	{
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Runcontrol=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;
		if(InterruptTime <6){
				Remote1_ReadIR.Interrupt_IR2 ++ ;

		        }
		   if(InterruptTime >6){
					  Usart1Send[0]=2;
					  Usart1Send[1]=Remote1_ReadIR.Interrupt_IR2;//Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
					  Usart1Send[2]=0xAB;
					  SendCount=1;
					  SBUF=Usart1Send[SendCount];
					 // Remote1_ReadIR.Interrupt_IR2=0;
		    }
      
		 Remote1_ReadIR.ReadIRBit++; //bit numbers add 
		
		if(Remote1_ReadIR.ReadIRBit ==16){//WT.EDIT   ir_Middle //if(Remote1_ReadIR.ReadIRBit>80)
			Remote1_ReadIR.ReadIRFlag=2; 
		   
		    
		    
		}
		
		
	}
 
}
#endif

/********************************************************************
	*
	*Function Name:void CheckXReadIR(ReadIRByte *P)
	*Function :
	*Input Ref: pointer *p
	*Return Ref: NO 
	*
********************************************************************/
#if IR3
void CheckXReadIR(ReadIRByte *P)
{

	INT8U k,ReadIR_cnt,FristCodeflag;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;
	
               

	if(P->ReadIRFlag==2) // ir receive of Byte(8 bit)
	{		
		P->ReadIRByte=0; //��һ���ֽ� 0
		k=0;
		//if(P->ReadIRData[1]==1)//if(P->ReadIRData[P->AABit]>120) //
		{
			for(P->AABit=1; P->AABit<= P->ReadIRBit; P->AABit++)
			{				     
					P->ReadIRByte=P->ReadIRData[P->AABit]<<1;//P->ReadIRByte=P->ReadIRData[P->AABit]<<=1;
					 {
					 	//P->ReadIRByte<<=1;
					    k++;
						#if 1
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
						    k=0;
						    P->ReadIRByte=0;
							P->ReadIRFlag=3;
							Remote1_ReadIR.ReadIRFlag=0;
							Remote1_ReadIR.ReadIRBit=0;
							 Remote1_ReadIR.BitHigh=0;

					    }
						#endif 
					 }
					
					 if(ReadIR_cnt ==1)//4
					 {
						
						Usart1Send[0]=1;
						//Remote1_ReadIR.ReadIR[0]=P->ReadIR[0];
	                    Usart1Send[1]=P->ReadIR[1];
						//Usart1Send[2]=P->ReadIR[2];
						//Usart1Send[3]=P->ReadIR[2];
						//Usart1Send[4]=P->ReadIR[3];
						if(ReadIR_cnt==1)ReadIR_cnt=0;
	                    SendCount=1;
	                    SBUF=Usart1Send[SendCount];
						ReadIR_cnt=0;
						FristCodeflag=0;
						P->ReadIRFlag=3;


					 }
			}
			//for(P->AABit=0; P->AABit<600; P->AABit++)
			//{
			  //  P->ReadIRData[P->AABit]=0;
			//}
		}
		#if 0
		//else if((P->ReadIRData[P->AABit]>105)&&(P->ReadIRData[P->AABit]<115))
		//{
			//P->ReadIRFlag=3;
		//}
		else
		{
			Remote1_ReadIR.ReadIRFlag=0;
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			     P->ReadIRData[P->AABit]=0;
			}
		}	
		#endif 
	}

}
#endif 

/********************************************************************
	*
	*Function Name:void CheckXReadIR_IR1(ReadIRByte *P)
	*Function :
	*Input Ref: pointer *p
	*Return Ref: NO 
	*
********************************************************************/
#if IR1
void CheckXReadIR_IR1(ReadIRByte *P)
{
	INT8U k,ReadIR_cnt,FristCodeflag,j;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;
	
	if(P->Interrupt_IR1 == 10){         

	if(P->ReadIRFlag==2) // ir receive of Byte(8 bit)
	{		
		P->ReadIRByte=0; //��һ���ֽ� 0
		k=0;
		//if(P->ReadIRData[1]==1)//if(P->ReadIRData[P->AABit]>120) //
		{
			for(P->AABit=1; P->AABit< 9; P->AABit++)
			{				     
					P->ReadIRByte=P->ReadIRData[P->AABit]<<1;//P->ReadIRByte=P->ReadIRData[P->AABit]<<=1;
					 {
					 	//P->ReadIRByte<<=1;
					    k++;
						
						#if 1
						if(k==8)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
							k=0;
						    

					    }
						
						#endif 
					 }
			}	
			for(P->AABit=9; P->AABit< 11; P->AABit++)
			{				     
					P->ReadIRByte=P->ReadIRData[P->AABit]<<1;//P->ReadIRByte=P->ReadIRData[P->AABit]<<=1;
					 {
					 	//P->ReadIRByte<<=1;
					    j++;
						
						#if 1
						if(j==3)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
							j=0;
						    P->ReadIRByte=0;
							P->ReadIRFlag=3;
							Remote1_ReadIR.ReadIRFlag=0;
							Remote1_ReadIR.ReadIRBit=0;
							Remote1_ReadIR.BitHigh=0;
						    P->Interrupt_IR1 =0;

					    }
						
						#endif 
					 }
			    }			
					 if(ReadIR_cnt ==2)//4
					 {
						
						Usart1Send[0]=1;
						//Remote1_ReadIR.ReadIR[0]=P->ReadIR[0];
	                    Usart1Send[1]=P->ReadIR[1];
						Usart1Send[2]=P->ReadIR[2];
						//Usart1Send[3]=P->ReadIR[2];
						//Usart1Send[4]=P->ReadIR[3];
						if(ReadIR_cnt==2)ReadIR_cnt=0;
	                    SendCount=1;
	                    SBUF=Usart1Send[SendCount];
						ReadIR_cnt=0;
						FristCodeflag=0;
						P->ReadIRFlag=3;


					 }
			}
		
      }
	}

}
#endif 
/********************************************************************
	*
	*Function Name:void CheckXReadIR_IR2(ReadIRByte *P)
	*Function :
	*Input Ref: pointer *p
	*Return Ref: NO 
	*
********************************************************************/
#if IR2
void CheckXReadIR_IR2(ReadIRByte *P)
{
	INT8U k,ReadIR_cnt,FristCodeflag,j;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;
	
	if(P->Interrupt_IR2 ==9){ 
		
      
	if(P->ReadIRFlag==2) // ir receive of Byte(8 bit)
	{		
		P->ReadIRByte=0; //��һ���ֽ� 0
		k=0;
		j=0;
		//if(P->ReadIRData[1]==1)//if(P->ReadIRData[P->AABit]>120) //
		{
			for(P->AABit=1; P->AABit<9 ; P->AABit++)
			{				     
					P->ReadIRByte=P->ReadIRData[P->AABit]<<1;//P->ReadIRByte=P->ReadIRData[P->AABit]<<=1;
					 {
					 	//P->ReadIRByte<<=1;
					    k++;
						
						#if 1
						if(k==8)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
							//k=0;
							
						 }
						
						#endif 
					 }
			}	
			for(P->AABit=9; P->AABit< 17; P->AABit++)
			{				     
					P->ReadIRByte=P->ReadIRData[P->AABit]<<1;//P->ReadIRByte=P->ReadIRData[P->AABit]<<=1;
					 {
					 	//P->ReadIRByte<<=1;
					    j++;
						
						#if 1
						if(j==8)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
							j=0;
							k=0;
						    P->ReadIRByte=0;
							P->ReadIRFlag=3;
							Remote1_ReadIR.ReadIRFlag=0;
							Remote1_ReadIR.ReadIRBit=0;
						
							P->Interrupt_IR2 =0;
						    

					    }
						
						#endif 
					 }
			    }			
					 if(ReadIR_cnt ==2)//4
					 {
						
						Usart1Send[0]=1;
						//Remote1_ReadIR.ReadIR[0]=P->ReadIR[0];
	                    Usart1Send[1]=P->ReadIR[1];
						//Delay_ms(200);
						Usart1Send[2]=P->ReadIR[2];
						//Usart1Send[3]=P->ReadIR[2];
						//Usart1Send[4]=P->ReadIR[3];
						if(ReadIR_cnt==2)ReadIR_cnt=0;
	                    SendCount=1;
	                    SBUF=Usart1Send[SendCount];
						}
			}
		}
		
}

}
#endif 
/********************************************************************
	*
	*Function Name:INT8U CheckHandsetIR()
	*Function : To cheded ir of value
	*Input Ref: NO
	*Return Ref: NO 
	*
********************************************************************/
INT8U CheckHandsetIR()
{
	INT8U KK=0;
	INT8U N=0;
	INT8U M=0;
	//ReadIRByte irStruct;
   // irStruct.ReadIR[0]=0;
	

  // CheckXReadIR(&Remote1_ReadIR);
   // CheckXReadIR_IR1(&Remote1_ReadIR);
	CheckXReadIR_IR2(&Remote1_ReadIR);
#if 0
    Usart1Send[0]=2;
	//Usart1Send[1]=irStruct.ReadIR[0];
    Usart1Send[1]=Remote1_ReadIR.ReadIR[0];
     Delay_ms(500);
	Usart1Send[2]=0xA1;//P->ReadIR[1];
	//Usart1Send[3]=P->ReadIR[2];
	//Usart1Send[4]=P->ReadIR[3];
	 Delay_ms(500);
    SendCount=1;
    SBUF=Usart1Send[SendCount];
#endif 
   

   if(Remote1_ReadIR.ReadIRFlag==3)
   {
      KeyclearTime=0;
      Remote1_ReadIR.ReadIRFlag=0;
	  if(Remote1_ReadIR.ReadIR[1]==0X7A)//if(Remote1_ReadIR.ReadIR[0]==0X44)
	  {
	     LedGreenON();
		 LedGreenOff();
		 Delay_ms(500);
		 LedGreenON();
		  LedGreenOff();
		   Delay_ms(500);
   	       //SBUF=KK;

	  }
   }

   else	if(Remote1_ReadIR.ReadIRFlag!=3)
   {
   	 if(KeyclearTime>4)
     {
	    KeyclearTime=0;

		for(N=0; N<5; N++)
		{
		  Remote1_ReadIR.ReadIR[N]=0;
		}
	 }
   }
  return(KK);
}

/**
  * @?|��???  	?��?��o?��o?����oy
  * @2?��oy  	fui_i : ?��?��o?����o?��??
  * @?��|��???|�� ?T
  * @?��?�� 	Fcpu = 16MHz?��?fui_i = 1��o?��?��??��?��o?����o?��?????a1Ms
  */
void Delay_ms(unsigned int fui_i)
{
	unsigned int fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --)
	{
		;
	}
}

