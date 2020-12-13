/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_Led_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "..\lib\LB_Led.h"

#endif

void InitT1(void)
{
	TCON1 = 0x00;						//T1��ʱ��ʱ��ΪFosc
	TMOD = 0x00;						//16λ��װ�ض�ʱ��/������

	//Tim1����ʱ�� 	= (65536 - 0xFACB) * (1 / (Fosc /Timer��Ƶϵ��))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//��ʱ0.1ms
	//���Ƴ�ֵ 	= 65536 - ((1/10000) / (1/(Fosc / Timer��Ƶϵ��)))
	//		   	= 65536 - ((1/10000) / (1/(16000000 / 12)))
	//			= 65536 - 133
	//			= 0xFf78
	TH1 = 0xFf;
	TL1 = 0x78;
	IE |= 0x08;							//��T1�ж�
	TCON |= 0x40;						//ʹ��T1
    
	EA = 1;	

}
/*********************************************************************/
void KeyInit(void)
{
   P0M0=0X51; //输入 SMT 
   P0M1=0X51;
   P0_0=0;
   P0_1=0;

}
/*************************************************************************/
void InitLed(void)
{
  P2M3=0X84; 
  P3M3=0X84;
  P3_3=1;
  P2_3=1;
}



void LedGreenON()
{
  P2_3=0; //Green
}

void LedGreenOff()
{
  P2_3=1; //Green
}

void LedRedON()
{
  P3_3=0; //
 }


void LedRedOff()
{
  P3_3=1;
}
void AllLedOff()
{
  P3_3=1;
  P2_3=1;
}



void InitIMP(void)
{
 // P2M1 = 0x60;                        //P01����Ϊʩ�������ִ���������
  P2M0 = 0xC2;                        //P21
  P2_0=0;
  //P2_1=0;

}
void SetIMPOutOn()
{
  P2_0=1;
}

 void SetIMPOutOff()
{
  P2_0=0;
}

/****************************************************************
	*
	*Function Name : ReChargeBatter()
	*Function :
	*
	*
	*
****************************************************************/
void ReChargeBatter_Init(void)
{
     P2M1 = 0X51 ; //input SMT pull down
     P2_1 =0; 

}
void ReadIMP(void)
{
 // if(P2_1)
 // ImpStatus=1;
 // else
 // ImpStatus=0;
}



 INT8U ReadPowerDCIn(void)
{
  return(P1_0);
}


void InitBuzzer(void)
{

    P2M2 = 0xC2;                        //P35����Ϊ�������?
	PWM3_MAP = 0x22;					//PWM3ӳ��P35��
	//���ڼ��� 	= 0xFF / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0xFF /(16000000 / 4)			
	// 			= 255 /4000000
	//			= 63.75us		��15.69KHZ		

	PWM3P = 0xc4;						//PWM����Ϊ0xFF
	//��Ч��ƽʱ����㣨��ռ�ձȣ�?	
	//			= 0x55 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x55 /(16000000 / 4)			
	// 			= 85 /4000000
	//			= 21.25us		ռ�ձ�Ϊ 21.25 / 63.75 = 34%

	PWM3D = 0x30;						//PWMռ�ձ�����
	PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ	


//  P2M2 = 0x84;                        //P01����Ϊʩ�������ִ���������
//  P2_2=0;

}
void BuzzerON()
{
 // BuzzerFlag=1; //WT.EDIT
 //SetBuzzerTime(4); //WT.EDIT 
//  PWM3C = 0x96; 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ
//  P2_2=0;
}


void BuzzerOff()
{
  BuzzerFlag=0;
//  PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ
//  P2_2=1;
}
 
void SetBuzzerTime(INT8U time)
{
	//BuzzerTime=time; //WT.EDIT
	
	//PWM3C = 0x96; //WT.EDIT 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ	
}
 
void CheckBuzzer()
{
   if(BuzzerTime<200)
   {
     
     BuzzerTime--;

	 if(BuzzerTime<1)
	 {
	   PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ	
	 }
   }
}
