/**
*   ************************************************************************************
*								�Ϻ�оʥ���ӹɷ����޹�˾
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.0.0
*	@Demo Version		V1.0.1.0
*	@Date				2017.09.18
*	************************************************************************************
*									 ģ�����ܽ���
*	1�����루��SMT��ģʽ��VDD=5Vʱ���͵�ƽ������͵�ѹ��VIL1����ΧΪ0~1.5V���ߵ�ƽ������
*	   �ߵ�ѹ��VIH1����ΧΪ3.5~5V��
*	2�����루SMT��ģʽ��VDD=5Vʱ���͵�ƽ������͵�ѹ��VIL1����ΧΪ0~1V���ߵ�ƽ������ߵ�?
*	   ѹ��VIH1����ΧΪ4~5V��
*	3��P0xDBCT [5:0]���õ�����ʱ����һ����Χ����Ƶϵ��*Tosc*P0xDBCT[5:0]-Tosc<����ʱ��<
*	   ��Ƶϵ��*Tosc*(P0xDBCT[5:0]+1)-Tosc��
	4��HC89F003�ϵ縴λ�Լ�������λ���ܵĸ�λ�����е�IO��ؼĴ�������ָ�ΪĬ��ֵ��
*	************************************************************************************
*									 Ӧ��ע������
*	1����ʹ�÷�����ʱ����JTAG���õ�IO�ڻ��ж�ȡ��д�������쳣����˽���ʹ�÷�����ʱ���?
*	   �����⼸��IO�ڡ��Ͽ�������ʹ�õ�Դ���缴��������������
*	2�����䵽P0.0/P0.1/P0.2�������ܽ��ϵĹ��ܽš��ⲿ�ж����롢���ϼ�����Ŷ����������ơ�?
*   3��HC89F003��B�漰���Ժ�汾��IO��P23��P24��P25��P27������������������ͬʱʹ�ܵĹ��ܣ�
       ���ǲ�����ʹ�ô����������Լ����������룬���ǿ���ʹ�ô�ʩ�������������Լ���ʩ����
       �������룬�������DateSheet��������оƬ�汾�������ѯ�ʴ������Լ�ԭ��ҵ��?
*	************************************************************************************
*  								       �ͻ�����
*	��л��ʹ�����ǵĵ�Ƭ���������ִ����Ժ�����ʹ�ô������ʡ��������Ϻ�оʥ���ӹٷ�QQȺ
*	****************************����֧��Ⱥ��201030494***********************************
*   ************************************************************************************
**/
#define	ALLOCATE_EXTERN
#define	ver 5

#include "HC89F0541.h"

#include "..\lib\LB_Led.h"
#include "..\lib\LB_AD.h"
#include "..\lib\LB_Usart.h"
#include "..\lib\LB_eeprom.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_IR.h"
#include "..\lib\LB_Run.h"
#include "..\lib\LB_Key.h"

void InitSysclk(INT8U SYS)
{

	/************************************ϵͳ��ʼ��****************************************/
	WDTCCR = 0x00;						//�رտ��Ź�

	while((CLKCON&0x20)!=0x20);			//�ȴ��ڲ���Ƶ��������
	CLKSWR = 0x51;						//ѡ���ڲ���Ƶʱ��Ϊ��ʱ�ӣ��ڲ���ƵRC2��Ƶ��Fosc=16MHz
	while((CLKSWR&0xC0)!=0x40);			//�ȴ��ڲ���Ƶ�л����?
	CLKDIV = SYS;						//Fosc1��Ƶ�õ�Fcpu��Fcpu=16MHz
}



/***************************************************************************************
  * @ʵ��Ч��	��P02�˿ڵ�������������Ϊ100K
***************************************************************************************/
void main(void)
{
	
	INT8U kk,flag;
	
	InitSysclk(1);
	InitT1();
	InitADIO();
    InitMotorIO();
	Init_Usart1();
	InitFanEdgeIO();
	InitLed();
	InitKey();
	InitPowerIn();
	Init_IR();
	InitBuzzer();
	InitIMP();
	
	ADCtl=1;   //ǿ���ź� IR ������?0--�رգ� 1 --��
	Mode = 0 ;//Mode=2;
	Step= 0x0 ;  //0;
	RunMode=0;
	RunStep=0xFF;
	RCurrentMax=150;
	LCurrentMax=150;
	LCurrent=0;
	RCurrent=0;
	CheckTime = 0;
	battDetect1sFlag = 0;
	lastMode = 0;
	SysFlag = 0XFF;

	while(1)
	{
       
		//TOP_IR();

		#if 1
		flag = AutoDC_ReChargeStatus();
		if(flag==0){
		
			chargeflag =0;
			CheckWall();
			CheckRechargeIR();

			kk=ReadKey();
			sysMode(kk);
			CheckRun();
			battVoltDetect();
			
		}
	#endif
		
	}
}


void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
	static INT8U t_1ms;  //vic
  static INT8U t_10ms;
  static INT8U t_100ms;
  static INT8U t_1s;
  //IRTime++;
	
  t_10ms++;  //0.1ms 
	
  ReadAD5ms();
 // BatteryLowVoltage_Detection();//WT.EDIT 1s detection
  MidIR_Count();
  CheckVoltage();
	
	if(t_1ms++>10){
		t_1ms = 0;
		T1msFlag = 1;
	}
	
  if(t_10ms>99) //10ms
	{
		t_10ms=0;
		t_100ms++;
		t_1s++;
		RunMs++;
		CheckBuzzer();
		SetMotorForwardPWMUP();
		if(t_100ms>9) //100ms
		{
			t_100ms=0;
			Run100MSecond++;
			RunSecond++;
			ImpSecond++;
			Imp2Second++;
			NoImpSecond++;
			WallSecond++;
			
			
			
			ReadIMP();
			CheckLCurrent();
			CheckRCurrent();
			CheckEdgeCurrent();
			CheckFanCurrent();			
			LedTip(SysFlag);
		}
		
		
		if(t_1s>99) //1s
		{
			t_1s=0;
			twinkle++;
			ModeStopTime ++ ;
			MidWallOffSecond++;
			CheckTime++;
			battDetect1sFlag = 1;
			#if 0			
			Usart1Send[0]=3;
			Usart1Send[1]=Voltage/100;
			Usart1Send[2]=Voltage%100;
			Usart1Send[3] =0xAB;
			SendCount=1;
			SBUF=Usart1Send[SendCount];
			Battery_HigVoltage = Voltage/100;
			Battery_LowVoltage = Voltage%100;
  	       #endif

           #if 1			
			if(SendCount>=5)//if(SendCount>=12)
			{
				Usart1Send[0]=5;
				Usart1Send[1]=Mid_ReadIR.ReadIR[0];
				Usart1Send[2]=Mid_ReadIR.ReadIR[1];
				Usart1Send[3]=Mid_ReadIR.ReadIR[2];				
				//	Usart1Send[1]=Voltage/100;
				//	Usart1Send[2]=Voltage%100;
				//	Usart1Send[3]=WallDp[0];
//				Usart1Send[4]=WallDp[1];
//				Usart1Send[5]=WallDp[2];
//				Usart1Send[6]=WallDp[3];
//				Usart1Send[7]=LCurrent;
//				Usart1Send[8]=RCurrent;
//				Usart1Send[9]=EdgeCurrent;
//				Usart1Send[10]=FanCurrent;
				Usart1Send[4]=IMP;
				Usart1Send[5]=RunStep;
				SendCount=1;
				SBUF=Usart1Send[SendCount];	
            				
//			Usart1Send[0]=12;
//			Usart1Send[1]=IRLocation.NearMid;
//			Usart1Send[2]=IRLocation.NearPreRight;
//			Usart1Send[3]=IRLocation.NearPreLeft;
//			Usart1Send[4]=IRLocation.NearRight;
//			Usart1Send[5]=IRLocation.NearLeft;
//			Usart1Send[6]=IRLocation.FarMid;
//			Usart1Send[7]=IRLocation.FarPreRight;
//			Usart1Send[8]=IRLocation.FarPreLeft;
//			Usart1Send[9]=IRLocation.FarRight;
//			Usart1Send[10]=IRLocation.FarLeft;
//			Usart1Send[11]=IMP;
//			Usart1Send[12]=RunStep;
//			SendCount=1;
//			SBUF=Usart1Send[SendCount];
			}
		 #endif 
			/*
			Usart1Send[0]=13;
			Usart1Send[1]=LeftIR.Left;
			Usart1Send[2]=LeftIR.Right;
			Usart1Send[3]=LeftIR.Mid;
			Usart1Send[4]=LeftIR.Top;

			Usart1Send[5]=MidIR.Left;
			Usart1Send[6]=MidIR.Right;
			Usart1Send[7]=MidIR.Mid;
			Usart1Send[8]=MidIR.Top;

			Usart1Send[9]=RightIR.Left;
			Usart1Send[10]=RightIR.Right;
			Usart1Send[11]=RightIR.Mid;
			Usart1Send[12]=RightIR.Top;

			Usart1Send[13]=RunStep;
			SendCount=1;
			SBUF=Usart1Send[SendCount];
				*/
			//SBUF=Usart1Send[SendCount];	
		}
  }
}
void WDT_Rpt() interrupt WDT_VECTOR
{
	WDTC &=~ 0x20;						//���WDT�жϱ�־λ
}
