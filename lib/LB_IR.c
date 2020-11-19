/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
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
#define setbit(x,y)    	 		x|=(1<<y)          //将X的第Y位置1
#define clrbit(x,y)   	 		x&=~(1<<y)        //将X的第Y位清0
#define reversebit(x,y) 	 	x^=(1<<y)        //取反
#define getbit(x,y)  			((x) >> (y)&1)    //读取位




void Init_IR()
{

    
	P1M6 = 0x68;			        	//P1_6设置为带SMT(施密特功能)上拉输入

 	//PITS3 |= 0x00;						//INT14,外部中断电平选择,红外接收头，上升沿中断
	//PITS3 |=(3<<4);
	PITS3 &=~(1<<5);
	
	PINTE1 |= 0x40;						//使能INT14

	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;
	Remote1_ReadIR.ReadIRFlag=0;


}
/**************************************************************
	*
	*Function Name:void Remote1_Count(void)
	*Fucntion :在定时器T1,0.1ms中断函数中执行,判断高电平时间
    *
	*
	*
**************************************************************/
void Remote1_Count(void)
{
	if(Remote1_ReadIR.ReadIRFlag==1) //IR_gpio 中断中置 1
	{
			#if 1
				 Remote1_ReadIR.Nowcount++;
		         Usart1Send[0]=1;
				//Remote1_ReadIR.ReadIR[0]=P->ReadIR[0];
                Usart1Send[1]=Remote1_ReadIR.Nowcount++;
				//Usart1Send[2]=0xAB;
                SendCount=1;
                SBUF=Usart1Send[SendCount];
			#endif 
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
}
/**************************************************************
	*
	*Function Name:void Read_Remote1IR(void)
	*Fucntion :GPIO ,中断函数中执行
	*Input Ref:NO
	*Return Ref: NO
	*
**************************************************************/
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
/********************************************************************
	*
	*Function Name:void CheckXReadIR(ReadIRByte *P)
	*Function :
	*Input Ref: pointer *p
	*Return Ref: NO 
	*
********************************************************************/
void CheckXReadIR(ReadIRByte *P)
{
	INT8U k,ReadIR_cnt,FristCodeflag;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;
	
	               

	if(P->ReadIRFlag==2) // ir receive of Byte(8 bit)
	{		
		P->ReadIRByte=0; //第一个字节 0
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
	

   CheckXReadIR(&Remote1_ReadIR);
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
	  if(Remote1_ReadIR.ReadIR[0]==0X7A)//if(Remote1_ReadIR.ReadIR[0]==0X44)
	  {
	     LedGreenON();
		 LedGreenOff();
		 LedGreenON();
		  LedGreenOff();
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
  * @?|ì???  	?¨?¨o?ào?￥¨oy
  * @2?¨oy  	fui_i : ?¨?¨o?à¨o?à??
  * @?¤|ì???|ì ?T
  * @?á?é 	Fcpu = 16MHz?ê?fui_i = 1¨o?à?ê??¨?¨o?à¨o?à?????a1Ms
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

