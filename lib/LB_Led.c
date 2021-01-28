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
#include "..\lib\LB_Run.h"

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
  P3M3=0X84;
  P3_3=1;
   P2M3=0X84;
  P2_3=1;
}



void LedRedON()
{
//	P2_3=0;
  LED_R=0;
}


void LedRedOff()
{
 //P2_3=1;
   LED_R=1; //red 
}

void LedGreenON()
{
//  P3_3=0;
  LED_G=0;
}


void LedGreenOff()
{
//  P3_3=1;
  LED_G=1; //green
}
void InitKey(void)
{
  P3M4 = 0x58;                        //P00����Ϊʩ�������ִ���������
  P3M5 = 0x58;
  P3_4=0;                        //P00����Ϊʩ�������ִ���������
  P3_5=0;

}
/**********************************************************************
	*
	*Function Name : void InitIMP(void)
	*Function : initial impact GPIO
	*
	*
	*
**********************************************************************/
void InitIMP(void)
{
  P1M5 = 0X50;   //close switch Left   pull down 
  P3M2 = 0x50;   //close switch Right  pull down
  P1_5 =0;    //left
  P3_2 =0;    //right
  IMP=0;
}

void ReadIMP(void)
{
  if(P3_2)
	IMP|=1;  //right
  else
	IMP&=0xfe; 
  if(P1_5)
	IMP|=2;  //left
  else
	IMP&=0xfd;
}

/***********************************************************
 *  *
    *Function Name: INT8U ReadKey(void)
    *Function: ReCharge battery be detected
    *Input Ref: NO
    *Return Ref: 1 -battery recharge   0-no recharge
    * 
***********************************************************/
INT8U ReadKey(void)
{

  static INT16U  K1=0;
  static INT16U  K2=0;
  static INT16U  K3=0; //WT.EDIT 2021.01.16
  static INT8U cnt;
  INT8U	 value1 = 0;
  INT8U  value2 = 0;
  INT8U  value3 = 0;  //itselst check keyvalue.
	if(!T1msFlag)
		return value1;
	T1msFlag = 0;
	
  if(KEY1==1 && KEY2==0){ //KEY1 =POWER_KEY ,KEY2 = MODES
		cnt = 0;
		K1++;	 //power_key press 
  }
  else if(KEY2==1 && KEY1==0) {
		cnt = 0;
		K2++;   //modes_key press
  }
  else if(KEY1==1 && KEY2==1) { //combination key press
		cnt = 0;
		K1++;
		K2++;
		K3 ++; //itself checking key
  }
  else if(KEY1==0 && KEY2==0){ //oneself key 
		cnt++;
		if(cnt<30)
			return 0; 
		
		cnt = 0;
		if(K1>20 && K1 <500)
			value1 = 0x01;	//short time power press ---power on 
		else if(K1>500)
			value1 = 0x02;  //long time power press
		else 
			value1 = 0;
		
		if(K2>20 && K2 <500) //short time modes press 
			value2 = 0x10;
		else if(K2>500)   //long time modes press 
			value2 = 0x20;
		else 
			value2 = 0;		
		
		K1 = 0;
		K2 = 0;		
//		if((value1+value2)!=0)
//		SBUF = value1+value2;
		return (value1+value2);
	}
	
	if((K1==500) && (K2<50)) //combination key 
		value1 = 0x03;
	else 	if(K2==500 && K1<50)
		value2 = 0x30;
	else if(K1==100 && K2>100)
		value1 = 0x44;
	else if(K1>100 && K2==100)
		value1 = 0x44;
	else if(K3>1000){  //WT.EDIT 2021.01.16
		value3 =0x50;
		return value3 ;
	}
//	if((value1+value2)!=0)
//	SBUF = value1+value2;
  return (value1+value2);
}
/***********************************************************
 *  *
    *Function Name: INT8U ReadPowerAutoIn(void)
    *Function: ReCharge battery be detected
    *Input Ref: NO
    *Return Ref: 1 -battery recharge   0-no recharge
    * 
***********************************************************/
void InitPowerIn(void)
{
     P2M1 = 0X50 ; //ReCharge input SMT pull down
     P1M0 = 0x50;  //DC INPUT pull down 
     P2_1 =0; 
	 P1_0 =0;
	 P1M7 = 0x50 ; //Battery RechRGE status 
	 P1_7 =0;     
}

/***********************************************************
 *  *
    *Function Name: INT8U ReadPowerAutoIn(void)
    *Function: ReCharge battery be detected
    *Input Ref: NO
    *Return Ref: 1 -battery recharge   0-no recharge
    * 
***********************************************************/
INT8U ReadPowerAutoIn(void)
{
  return(P2_1);
}
/***********************************************************
 *  *
    *Function Name: ReadPowerDCIn(void)
    *Function: DC adapte input be dected 
    *Input Ref: NO
    *Return Ref: 1 -DC 5V    0-No DC 5V 
    * 
***********************************************************/
 INT8U ReadPowerDCIn(void)
{
  return(P1_0);
}
/***********************************************************
 *  *
    *Function Name: INT8U ReadPowerAutoIn(void)
    *Function: ReCharge battery be detected
    *Input Ref: NO
    *Return Ref: 1 -battery recharge   0-no recharge
    * 
***********************************************************/
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
 // BuzzerFlag=1;
  SetBuzzerTime(4);
//  PWM3C = 0x96; 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ
//  P2_2=0;
}


void BuzzerOff()
{
 // BuzzerFlag=0;
  PWM3C = 0x00; 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ
  P2_2=1;
}

void SetBuzzerTime(INT8U time)
{
	BuzzerTime=time;
	
	PWM3C = 0x96; 						//ʹ��PWM3���ر��жϣ����������ʱ��?2��Ƶ	
    
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


