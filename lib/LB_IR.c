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

    #if 1
	P1M6 = 0x62;//0x68;			        	//P1_6����Ϊ��SMT(ʩ���ع���)��������

 	  PITS3 |= 0x30;						//INT14,�ⲿ�жϵ�ƽѡ��,�������ͷ���������ж�
	 //PITS3 |=(2<<4);   //01 �½��س���
	//PITS3 &=~(1<<5); //set 0 
	
	PINTE1 |= 0x40;						//ʹ��INT14

	IE2 |= 0x01;						//��INT8-17�ж�
	EA=1;
	Remote1_ReadIR.ReadIRFlag=0;
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
     
  if(Remote1_ReadIR.ReadIRFlag==1)
	{
		Remote1_ReadIR.Nowcount++;
		if(Remote1_ReadIR.Nowcount>600)//if(Remote1_ReadIR.Nowcount>200)//WT.EDIT 
		{
			Remote1_ReadIR.ReadIRFlag=2;
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
	    (Remote1_ReadIR.NowVoltage==1)&&(Remote1_ReadIR.ReadIRFlag==1)
	)
	{
	   SBUF=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit++;
		if(Remote1_ReadIR.ReadIRBit>32)//if(Remote1_ReadIR.ReadIRBit>80) //WT.EDIT
			Remote1_ReadIR.ReadIRFlag=2;

	}
	else if(
	    (Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1)
	)
	{
	   //SBUF=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit++;
		if(Remote1_ReadIR.ReadIRBit>32)//WT.EDIT //if(Remote1_ReadIR.ReadIRBit>80)
			Remote1_ReadIR.ReadIRFlag=2;
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
#if  IR2
void CheckXReadIR_IR2(ReadIRByte *P)
{
	
	INT8U k;

	{
		if(P->ReadIRFlag==2)
		{
			{

				P->ReadIR[0]=0;

				k=0;
				P->ReadIRByte=0;
				for(P->AABit=0; P->AABit<16;)
				{
					if(
					    (P->ReadIRData[P->AABit]>10)&&(P->ReadIRData[P->AABit]<40)
					)
					{
						P->ReadIRByte<<=1;
						P->ReadIRByte|=1;
						P->AABit+=2;

						k++;
						if(k>7)
						{

							P->ReadIR[0]=P->ReadIRByte;
							k=0;

							P->ReadIRByte=0;

						}
					}
					else
					{
						P->AABit+=2;
						P->ReadIRByte<<=1;
						k++;
						if(k>7)
						{

							P->ReadIR[0]=P->ReadIRByte;
							k=0;

							P->ReadIRByte=0;
							//P->AABit++;
						}
					}

				}
				for(P->AABit=0; P->AABit<20; P->AABit++)
					P->ReadIRData[P->AABit]=0;
			}

			P->ReadIRFlag=3;
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
	INT8U KK=0,i =0;
	INT8U N=0;
	INT8U M=0;
	
	CheckXReadIR_IR2(&Remote1_ReadIR);
	#if 1
				Usart1Send[0]=5;
				Usart1Send[1]=Remote1_ReadIR.ReadIR[0];
				Usart1Send[2]=Remote1_ReadIR.ReadIR[1];
				Usart1Send[3]=Remote1_ReadIR.ReadIR[2];
				Usart1Send[4]=Remote1_ReadIR.ReadIR[3];
				Usart1Send[5]=0x88;
				SendCount=1;
				SBUF=Usart1Send[SendCount];
			#endif 

  if(Remote1_ReadIR.ReadIRFlag==3)
   {
   
	//  KeyclearTime=0;
     Remote1_ReadIR.ReadIRFlag=0;
	
	 Remote1_ReadIR.BitHigh=0;
	 Remote1_ReadIR.BitLow =0 ;
	 Remote1_ReadIR.ReadIRBit=0; 
	  Remote1_ReadIR.recordTime =0;//WT.EDIT
	  Remote1_ReadIR.Inttime=0;

	  
	 
	 
   }
   
  return(0XFF);
}
/******************************************************************************
 * *
 * Function Name: void CheckRechargeIR()
 * Function :Sample machine be used to Mide IR be charged 
 * 
 * 
 * 
******************************************************************************/
void CheckRechargeIR()
{
  // CheckXReadIR(&Left_ReadIR);
  // CheckXReadIR(&Right_ReadIR);
//   CheckXReadIR(&Remote1_ReadIR);
#if 0
	if(Remote1_ReadIR.ReadIRFlag==3)
	{
			//SBUF=Remote1_ReadIR.ReadIR[0];
			if((Remote1_ReadIR.ReadIR[0]&0XF4)==0XF4)
				MidIR.Right++;
			else if((Remote1_ReadIR.ReadIR[0]&0XF2)==0XF2)
				MidIR.Mid++;			
			else if((Remote1_ReadIR.ReadIR[0]&0XF8)==0XF8)
				MidIR.Left++;
			else if((Remote1_ReadIR.ReadIR[0]&0XF1)==0XF1)
				MidIR.Top++;

			else if(Remote1_ReadIR.ReadIR[0]!=0)
				MidIR.Err++;
#endif 
			Remote1_ReadIR.ReadIR[0]=0;
			Remote1_ReadIR.ReadIRFlag=0;
			#if 1
				Usart1Send[0]=5;
				Usart1Send[1]=Remote1_ReadIR.ReadIR[0];
				Usart1Send[2]=Remote1_ReadIR.ReadIR[1];
				Usart1Send[3]=Remote1_ReadIR.ReadIR[2];
				Usart1Send[4]=Remote1_ReadIR.ReadIR[3];
				Usart1Send[5]=0x88;
				SendCount=1;
				SBUF=Usart1Send[SendCount];
			#endif 

	}
/*******************************************************
  * 
  * Function Name:void Delay_ms(INT16U fui_i)
  * Function :
  *           Fcpu = 16MHz delay 1ms
  * 
**************************************************************/
void Delay_ms(INT16U fui_i)
{
	INT16U fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --)
	{
		;
	}
}

/***************************************************************************
	*
	*Function Name :
	*
	*
	*
	*
	*
***************************************************************************/

INT8U max2(INT8U a , INT8U b)
{
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
    
}

INT8U max4(INT8U a ,INT8U b ,INT8U c ,INT8U d)
{
    INT8U res;
    res = max2(a,b);        //��max2���ظ�ֵ��res 
    res = max2(res,c);      //��res��c��ֵ�ֱ��뵽max2�е�a,c�����Ƚ� a b�����ֵ�����Ƚ�res��c�е����ֵ�� 
    res = max2(res,d);
    return res;             //����res��ֵ��max4���� 
    
}


