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

INT16U   Rtime;
/**
  * @?μ?÷  	?óê±oˉêy
  * @2?êy  	fui_i : ?óê±ê±??
  * @·μ???μ ?T
  * @×￠ 	Fcpu = 16MHz￡?fui_i = 1ê±￡??óê±ê±?????a1Ms
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


void Iint_T5(void)
{
 /**********************************TIM5????3?��??��**************************************/
    P1M6 = 0x68;//P3M3 = 0x62;                        //P33����???a��?��-��?��?    
	T5_MAP = 0x16;						//T52????����3��?P33???��
	T5CON = 0x3F;						//256��Ƶ��16λ�½��ز���
	T5CON1 = 0x00;						//T5����ѡ�� T5�ŵı仯
	TH5 = 0x00;
	TL5 = 0x00;
	IE1 |= 0x10;						//�䨰?aT5?D??
	EA = 1;



}


void Init_IR()
{

   
	P1M6 = 0x62;//0x68;			        	//P1_6����Ϊ��SMT(ʩ���ع���)��������

 	  PITS3 |= 0x30;						//INT14,�ⲿ�жϵ�ƽѡ��,�������ͷ���������ж�
	 //PITS3 |=(2<<4);   //01 �½��س���
	//PITS3 &=~(1<<5); //set 0 
	
	PINTE1 |= 0x40;						//ʹ��INT14

	IE2 |= 0x01;						//��INT8-17�ж�
	EA=1;
	Remote1_ReadIR.ReadIRFlag=0;
   

}

void Remote1_Count(void)
{
	if(Remote1_ReadIR.ReadIRFlag==1)
	{
		Remote1_ReadIR.Nowcount++;
		if(Remote1_ReadIR.Nowcount>200)
		{
			Remote1_ReadIR.ReadIRFlag=2;
		}
	}
}


/****************************************************************
	*
	*Function Name:void Read_Remote1IR(void)
	*Function :the function run in interrupt program
	*
	*
	*
*************************************************************/
void Read_Remote1IR(void)
{
   						
	Remote1_ReadIR.NowVoltage=P1_6;

	if(
	    (Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==0)
	)
	{
		Remote1_ReadIR.ReadIRFlag=1;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit=0;
	}
    else if(
	    (Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1)
	)
	{
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Runcontrol=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;
        Remote1_ReadIR.ReadIRBit++;
		if(Remote1_ReadIR.ReadIRBit>80)
			Remote1_ReadIR.ReadIRFlag=2;
	}
}
/*************************************************************
	*
	*Function Name :void Read_RightIR(void)
	*Function : 
	*Iinput Ref:NO
	*Return Ref:NO
	*
*************************************************************/
void  CheckXReadIR(ReadIRByte *P)
{
	INT8U k,ReadIR_cnt,FristCodeflag;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;

	if(P->ReadIRFlag==2)
	{		
		P->ReadIRByte=0;
		k=0;
		if(P->ReadIRData[P->AABit]>120)
		{
			for(P->AABit=1; P->AABit<P->ReadIRBit;P->AABit++)
			{				     
					 if((P->ReadIRData[P->AABit]>0)&&(P->ReadIRData[P->AABit]<=14))
					 {
					 	P->ReadIRByte<<=1;
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
						    k=0;
						    P->ReadIRByte=0;
//							P->ReadIRFlag=3;

					    }
					 }
					 if((P->ReadIRData[P->AABit]>14)&&(P->ReadIRData[P->AABit]<28))
					 {
					 	P->ReadIRByte<<=1;
						P->ReadIRByte|=1;
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
						    k=0;
						    P->ReadIRByte=0;
							P->ReadIRFlag=3;
					    }
					 }
					 if(ReadIR_cnt==4)
					 {
			    	    #if 1
						 Usart1Send[0]=4;
	                    Usart1Send[1]=P->ReadIR[0];
						Usart1Send[2]=P->ReadIR[1];
						Usart1Send[3]=P->ReadIR[2];
						Usart1Send[4]=P->ReadIR[3];
	                    SendCount=1;
	                    SBUF=Usart1Send[SendCount];
						#endif 
						ReadIR_cnt=0;
						FristCodeflag=0;
						P->ReadIRFlag=3;
						
			}
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			    P->ReadIRData[P->AABit]=0;
			}
		}
	    }
		else if((P->ReadIRData[P->AABit]>105)&&(P->ReadIRData[P->AABit]<115))
		{
			P->ReadIRFlag=3;
		}
		else
		{
			Remote1_ReadIR.ReadIRFlag=0;
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			     P->ReadIRData[P->AABit]=0;
			}
		}		
	}
}
	




INT8U CheckHandsetIR()
{
	INT8U KK=0,irr;
    

    CheckXReadIR(&Remote1_ReadIR);

   if(irr ==5){
        

  	   return(5); //left
   }
   else if(irr==4){
     
     return(4); //right 
   }
   else 
      return(KK);
}




