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
#include "LB_Led.h"

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

void InitLed(void)
{
  P2M3=0X84;
  P3M3=0X84;
  P3_3=1;
  P2_3=1;
}



void LedGreenON()
{
  P3_3=0;
  P2_3=1;
}


void LedGreenOff()
{
  P3_3=1;
}

void LedRedON()
{
  P3_3=1;
  P2_3=0;
}


void LedRedOff()
{
  P2_3=1;
}
void AllLedOff()
{
  P3_3=1;
  P2_3=1;
}

void InitKey(void)
{
  P0M0 = 0x60;                        //P00����Ϊʩ�������ִ���������
  P3M2 = 0x60;                        //P32����Ϊʩ�������ִ���������
  P0_0=1;
  P3_2=1;

}

void InitIMP(void)
{
  P2M1 = 0x60;                        //P01����Ϊʩ�������ִ���������
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

void ReadIMP(void)
{
  if(P2_1)
  ImpStatus=1;
  else
  ImpStatus=0;
}
/****************************************************************
 * * *
 * Function Name:INT8U ReadKey(void)
 * Function: Touch key of define function 
 * 
 * 
 ***************************************************************/
INT8U ReadKey(void)
{

  static INT8U  K1temp,K2temp;
  INT8U t_Key;
  t_Key=0;
  if(P3_2==0)
  {
    if(K1temp<200)
   	 K1temp++;
	 BuzzerON();
  }
  else	
  {	  

   	K1temp=0;
	BuzzerOff();
  }

  if(P0_0==0)
  {
    if(K2temp<200)
   	 K2temp++;
	 BuzzerON();
  }
  else	
  {	  

   	K2temp=0;
	BuzzerOff();
  }


  if(K1temp==190)
  {
    K1temp=201;
   //return(1);
	t_Key|=1;
  }
  if(K2temp==190)
  {
    K2temp=201;
   //return(1);
	t_Key|=2;
  }
  return(t_Key);  
}
void InitPowerIn(void)
{
  P1M7 = 0x60; 
  P1M0 = 0x50;                        //P10����Ϊʩ�������ִ���������
  P1_0=1;                  //����������ӿ�----��⣬��12V����

}


 INT8U ReadPowerDCIn(void)
{
  return(P1_0);
}


void InitBuzzer(void)
{

    P2M2 = 0xC2;                        //P35����Ϊ�������
	PWM3_MAP = 0x22;					//PWM3ӳ��P35��
	//���ڼ��� 	= 0xFF / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0xFF /(16000000 / 4)			
	// 			= 255 /4000000
	//			= 63.75us		��15.69KHZ		

	PWM3P = 0xc4;						//PWM����Ϊ0xFF
	//��Ч��ƽʱ����㣨��ռ�ձȣ� 	
	//			= 0x55 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x55 /(16000000 / 4)			
	// 			= 85 /4000000
	//			= 21.25us		ռ�ձ�Ϊ 21.25 / 63.75 = 34%

	PWM3D = 0x30;						//PWMռ�ձ�����
	PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ	


//  P2M2 = 0x84;                        //P01����Ϊʩ�������ִ���������
//  P2_2=0;

}
void BuzzerON()
{
 // BuzzerFlag=1; //WT.EDIT
 //SetBuzzerTime(4); //WT.EDIT 
//  PWM3C = 0x96; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ
//  P2_2=0;
}


void BuzzerOff()
{
  BuzzerFlag=0;
//  PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ
//  P2_2=1;
}

void SetBuzzerTime(INT8U time)
{
	//BuzzerTime=time; //WT.EDIT
	
	//PWM3C = 0x96; //WT.EDIT 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ	
}

void CheckBuzzer()
{
   if(BuzzerTime<200)
   {
     
     BuzzerTime--;

	 if(BuzzerTime<1)
	 {
	   PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ	
	 }
   }
}
