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
*	2�����루SMT��ģʽ��VDD=5Vʱ���͵�ƽ������͵�ѹ��VIL1����ΧΪ0~1V���ߵ�ƽ������ߵ�
*	   ѹ��VIH1����ΧΪ4~5V��
*	3��P0xDBCT [5:0]���õ�����ʱ����һ����Χ����Ƶϵ��*Tosc*P0xDBCT[5:0]-Tosc<����ʱ��<
*	   ��Ƶϵ��*Tosc*(P0xDBCT[5:0]+1)-Tosc��
	4��HC89F003�ϵ縴λ�Լ�������λ���ܵĸ�λ�����е�IO��ؼĴ�������ָ�ΪĬ��ֵ��
*	************************************************************************************
*									 Ӧ��ע������
*	1����ʹ�÷�����ʱ����JTAG���õ�IO�ڻ��ж�ȡ��д�������쳣����˽���ʹ�÷�����ʱ��Ҫ
*	   �����⼸��IO�ڡ��Ͽ�������ʹ�õ�Դ���缴��������������
*	2�����䵽P0.0/P0.1/P0.2�������ܽ��ϵĹ��ܽš��ⲿ�ж����롢���ϼ�����Ŷ����������ơ�
*   3��HC89F003��B�漰���Ժ�汾��IO��P23��P24��P25��P27������������������ͬʱʹ�ܵĹ��ܣ�
       ���ǲ�����ʹ�ô����������Լ����������룬���ǿ���ʹ�ô�ʩ�������������Լ���ʩ����
       �������룬�������DateSheet��������оƬ�汾�������ѯ�ʴ������Լ�ԭ��ҵ��
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
#include "..\lib\LB_Mode.h"
#include "..\lib\LB_Key.h"

unsigned int gui_T5Value;               //T5 �����ȡֵ
unsigned int gui_newT5Value = 0;		//T5 �����ȡ��ֵ
unsigned int gui_oldT5Value = 0; 		//T5 �����ȡ��ֵ

void InitSysclk(INT8U SYS)
{

	/************************************ϵͳ��ʼ��****************************************/
	WDTCCR = 0x00;						//�رտ��Ź�

	while((CLKCON&0x20)!=0x20);			//�ȴ��ڲ���Ƶ��������
	CLKSWR = 0x51;						//ѡ���ڲ���Ƶʱ��Ϊ��ʱ�ӣ��ڲ���ƵRC2��Ƶ��Fosc=16MHz
	while((CLKSWR&0xC0)!=0x40);			//�ȴ��ڲ���Ƶ�л����
	CLKDIV = SYS;						//Fosc1��Ƶ�õ�Fcpu��Fcpu=16MHz
}



/***************************************************************************************
  * @ʵ��Ч��	��P02�˿ڵ�������������Ϊ100K

����3004����ң��ɨ�ػ����ܶ���??????? 2020.09.09
?
����������
1.???? �����������书�� 
?
2.???? ����һ���е��ײ����
?
3.��ɨģʽ:
3.1. ��������ɨģʽ������Ĭ�����ģʽ����
3.2. �ӱ���ɨģʽ�����ڹ�������ɨģʽ�£� 30������ײǽ5���Զ������ӱ���ɨģʽ��
3.3 ������ɨģʽ�� 
3.4. �˹���ɨģʽ����ͨ��ң�����ٿط����������ҷ���
?
4.������ң��: ǰ�������ҿ��ƣ�������3��������ͷ�����ӿڣ�����ϸ�뿴˿ӡͼ��
?
5.��е��ײ��⣺���飬�м�һ����⿪�أ����������һ���ᴥ����
?
6.������������ֹͣ�������ܲ�����ԭ����ģʽ�����»ص�������ɨʱ���ٴΰ�������/��ͣ����,���ٴ��������ǰ��ģʽ���빤��״̬.
?
7.���أ�����������ܵ�Դ���أ������������ϵ�����Դ����ʱ������Ĭ�Ϲ�������ɨģʽ.
�����������أ����Ϊ������ɨ��ݰ������ұ�Ϊ��ͣ/���������뿴˿ӡͼ��
?
8.???? ��Դ����﮵��7.4V������3.7V����2000MAH��
?
8.1 USB5V��磬����Ϊ MICRO? USB
?
8.2 ������Ϊ0.65A,������緽ʽ����������������������̵ơ������庸һ�����5MM˫ɫ�ƣ�
?
8.3 ���ŵ�ѹΪ6V,�����͵�ѹ�����������������죬�����ֹ��ѹΪ8.4V��
?
9.???? ��������: �ο��ͺ�̼ˢ��� RC-365SH-1992-52K ������ѹ6.8V����������ر�����
?
��������Ҫ������·�壬������˾�ṩPCB���ϣ������������������������ϣ�
?
10.? ��ɨ����: �ο��ͺŵ�ˢ���320CH-11480 ��������ѹ6.8V, ��������ر�����
?
11.��������: �ο��ͺ�̼ˢ���YRK-370SH-24110 D/V6.8������ѹ6.8V, ��������ر�����
?
������ʾ��
?
1.???? ������ס���������ÿ��5����һ��������
2.???? �������գ��������ÿ��5��������������
3.???? ��ɨ�����ת���������ÿ��5��������������
4.???? ���������ת���������ÿ��5��������������1�����һ��������
5.???? ���ȶ�ת���ߵ����󣬺������ÿ��5��������������1���������������
6.???? �͵�ʱ�����������������������ʾ������������


***************************************************************************************/
void main(void)
{
	INT8U KK;

	InitSysclk(1);

	InitT1();
	InitADIO();
	Init_MotorSpeed();
    InitMotorIO();
	Init_Usart1();
	Iint_T5(); //WT.EDIT
	//InitMotorForward();
	InitFanEdgeIO();
	InitLed();
	
	InitPowerIn();
	Init_IR();
	InitBuzzer();
	SetBuzzerTime(2);
	InitIMP();
	KeyInit(); //WT.EDIT 
	ReChargeBatter_Init();//WT.EDIT 
	Init_MotorSpeedIR();
	ADCtl=1;
	//LedBlueON();
	EdgeCollectDelayTime=0;
	RunStep=0;
	RCurrentMax=300;
	LCurrentMax=300;
	LCurrent=0;
	RCurrent=0;
	FanPersent=0;
	EdgePersent=0;
	EdgeCurrent=0;
	FanCurrent=0;
	EdgeCurrentCount=0;
	EdgeCurrentCount2=0;
	Gong_Step=0;
	Enter3=0;
	Mode=1;
	Step=0;
	ModeBackup=0;
	while(1)
	{
      
	   KK=HDKey_Scan(0);

	  if(BatterCharge ==1|| P1_0 ==1){
	     AllStop();
		 LedGreenON();
		 Delay_ms(500);
		 LedGreenOff();
		 Delay_ms(500);
	  
	  }
	  else{
            
			 switch (KK)
			 {
			 case 1: //PowerOn status
				 Mode_OnePowerOnStatus();
 
				 break;
			 case 2: //Mode =1 ,bow

			 	break;

			 case 3: //Mode = 2 ,fixed point 

			 	break;

			 case 4: //Mode =3 ,edgeways

			 	break; 

			 case 5:  //Mode =4  ,random

			 	break;

			 case 6:  //Mode =5 , recharge to batter

			 	break;
			 
			 default:
				 break;
			 }
	         
	        // CheckMode(KK);
	       //  CheckGround();
	       //  CheckRun();
		  
		
	     
		 }

		
	  }
	
  }


/************************************************************
	*
	*Function Name:void INT8_17_Rpt() interrupt INT8_17_VECTOR 
	*Function :GPIO �жϺ���,�жϺ� INT15,INT14
	*
	*
************************************************************/
void INT8_17_Rpt() interrupt INT8_17_VECTOR 
{
	if(PINTF2&0x01)						//�ж�INT15�жϱ�־λ
	{
	  PINTF2 &=~ 0x01;				//���INT15�жϱ�־λ		
	  ReadLeftPulsed();
	}
	if(PINTF2&0x02)						//�ж�INT15�жϱ�־λ
	{
	  PINTF2 &=~ 0x02;				//���INT15�жϱ�־λ		
	  ReadRightPulsed();
	}
	 
	if(PINTF1&0x80)						//�ж�INT15�жϱ�־λ
	{
		PINTF1 &=~ 0x80;				//���INT15�жϱ�־λ

	}

	#if 1
	if(PINTF1&0x40)						//�ж�INT14�жϱ�־λ--IR
	{
		PINTF1 &=~ 0x40;	//���INT14�жϱ�־λ	
		#if IR3
		    Read_Remote1IR();  //ir3
		#endif 
		#if IR1
		   Read_Remote11IR(); //ir1
		#endif 
		#if IR2
		   Read_Remote12IR(); //ir2
		   
		  #endif 
	}
   #endif
	
}
/****************************************************************
	*
	*Function Name :void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
	*Function:��ʱ��T1 ,�жϺ��� 0.1ms�����ж�

	*
	*
****************************************************************/
void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
  
  static INT8U t_10ms;
  static INT8U t_100ms;
  static INT8U t_1s;
  t_10ms++;
  ReadAD5ms();
 // Remote1_Count(); //ir3
 // Remote11_Count();//ir1
   Remote12_Count(); //ir2
  if(t_10ms>99) //10ms
  {
  	t_10ms=0;
	t_100ms++;
	t_1s++;
	 ReadTimeOver++;
	InterruptTime ++ ; //10ms
	  RunMs++;
 	  CheckLeftMotorSpeed();
	  CheckRightMotorSpeed();
	  AdjustSpeed();
	CheckBuzzer();
	CheckVoltage();
	if(t_100ms>9) //100ms
	{
	 
	  t_100ms=0;
	   Run100MSecond++;
	   KeydelayTime++;
	   KeyRunTime++;
	  CheckLCurrent();
	  CheckRCurrent();
	  CheckFanCurrent();
	  CheckEdgeCurrent();
	  ReadIMP();  //IR impact 

	  #if 0
	  Usart1Send[0]=19;
	  Usart1Send[1]=Voltage/100;
	  Usart1Send[2]=Voltage%100;
	  Usart1Send[3]=Mode;
	  Usart1Send[4]=Step;

	  Usart1Send[5]=RunStep;
	  Usart1Send[6]=ImpStatus;
	  Usart1Send[7]=EdgeCurrent>>8;
	  Usart1Send[8]=EdgeCurrent;
	  Usart1Send[9]=GroundDp[0];
	  Usart1Send[10]=GroundDp[1];
	  Usart1Send[11]=GroundDp[2];
	  Usart1Send[12]=LeftMoveMotorData.AvgSpeed;
	  Usart1Send[13]=RightMoveMotorData.AvgSpeed;
	  
	  Usart1Send[14]=LeftMoveMotorData.NowPulsed/100;
	  Usart1Send[15]=LeftMoveMotorData.NowPulsed%100;
	  Usart1Send[16]=RightMoveMotorData.NowPulsed/100;
	  Usart1Send[17]=RightMoveMotorData.NowPulsed%100;
	  Usart1Send[18]=FanCurrent>>8;
	  Usart1Send[19]=FanCurrent;
	  
//	  Usart1Send[20]=EdgeCurrent>>8;
//	  Usart1Send[21]=EdgeCurrent;

	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
      #endif 

	  
	}
	
	if(t_1s>99)//100ms * 100 =1s
	{
	  t_1s=0;
	  KeyclearTime++;
	  EdgeErrordelayTime++;
	  EdgeCollectDelayTime++;
	  RunSecond++;	 
	  GroundSecond++; //1s
	  ImpSecond++;
	  
      #if 1
	  Usart1Send[0]=3;
	 // Usart1Send[1]=Voltage/100;
	 // Usart1Send[2]=Voltage%100;
	 // Usart1Send[1]=GroundDp[0];  //left 
	 // Usart1Send[2]=GroundDp[1];  //right 
	  //Usart1Send[3]=GroundDp[2];
	   Usart1Send[1]=Mode;
	  Usart1Send[2]=Step;
	  Usart1Send[3]=RunStep;
	 // Usart1Send[8]=RunStep;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
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
/***************************************************************************************
  * @˵��  	T5�жϷ�����
  *	@����	��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
void TIMER5_Rpt(void) interrupt T5_VECTOR
{     
 
	if(T5CON&0x40)                      //�Ƿ�Ϊ�ⲿ�¼�
    {
		
		gui_T5Value =RCAP5;			//��ȡ��ȡ������

		Remote1_ReadIR.Interrupt_IR2 ++ ;
		
      //  Remote1_ReadIR.Interrupt_IR2=RCAP5;
		
    }
	#if 1
	if(gui_newT5Value!=gui_T5Value)
	{	
		if(gui_newT5Value>gui_oldT5Value)
		{
			gui_T5Value = gui_newT5Value-gui_oldT5Value;
		}else if(gui_newT5Value<gui_oldT5Value){
			gui_T5Value = gui_oldT5Value-gui_newT5Value;

		}
		else{
			 gui_newT5Value = gui_T5Value;
			 if(gui_oldT5Value ==0) gui_oldT5Value  = gui_T5Value ;
		}
		
	}
	#endif 
    if(InterruptTime >10){  //>6
					 // Usart1Send[0]=2;
					 // Usart1Send[1]=gui_T5Value ;//Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
                     // Usart1Send[2]=Remote1_ReadIR.Interrupt_IR2  ;//0xff;
					 // SendCount=1;
					 // SBUF=Usart1Send[SendCount];
					  InterruptTime =0;
                      // Remote1_ReadIR.ReadA_Time++;
					  // Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time]=Remote1_ReadIR.Interrupt_IR2;
					  
					   Remote1_ReadIR.Interrupt_IR2=0;
					  
					  gui_T5Value=0;
					//  if(Remote1_ReadIR.ReadA_Time>3)Remote1_ReadIR.ReadA_Time=0;
					
		    }
		   //else Remote1_ReadIR.Interrupt_IR2 ++ ;

	
    T5CON &=~ 0x40;						//��������ⲿ�����¼�������־λ        
	T5CON &=~ 0x80;						//���T5�жϱ�־λ      
}

void WDT_Rpt() interrupt WDT_VECTOR
{
	WDTC &=~ 0x20;						//���WDT�жϱ�־λ
}
