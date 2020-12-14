/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_Motor_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"

#endif

void Init_MotorSpeed()
{

	P3M4 = 0x68;			        	//P15����Ϊ��SMT��������
	P3M5 = 0x68;			        	//P16����Ϊ��SMT��������

							//INT16	17
 	PITS4 |= 0x0F;						

    PINTE2 |= 0x03;						//ʹ��INT17 16
	IE2 |= 0x01;						//��INT8-17�ж�
	EA=1;

}
void Init_MotorSpeedIR()
{
	//P1M5 = 0x84;			        	//P15����Ϊ
}
void MotorSpeedIRON()
{
  //P1_5=0;
}

void MotorSpeedIROff()
{
  P1_5=1;
}
void InitMotorIO(void)
{

    P1M1 = 0xC2;                        //P11����Ϊ�������
    P1M2 = 0xC2;                        //P12����Ϊ�������
    P1M3 = 0xC2;                        //P13����Ϊ�������
    P1M4 = 0xC2;                        //P14����Ϊ�������

  P1_1=0;
  P1_2=0;
  P1_3=0;
  P1_4=0;

}

void InitFanEdgeIO(void)
{
    P3M0 = 0xC2;                        //P34����Ϊ�������
    P3M1 = 0xC2;                        //P35����Ϊ�������
    P3_0=1;
    P3_1=1;

	PWM1_MAP = 0x30;					//PWM1ͨ��ӳ��P34��
	PWM11_MAP = 0x31;					//PWM11ͨ��ӳ��P35��
    PWM1C = 0x01;						//PWM1����Ч��PWM11����Ч��ʱ��8��Ƶ 
    PWMM |= 0x20;						//PWM1������						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM1PH = 0x00;						//���ڸ�4λ����Ϊ0x03
	PWM1PL = 0xff;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM1DH = 0x00;						//PWM1��4λռ�ձ�0x01
	PWM1DL = 0x00;						//PWM1��8λռ�ձ�0x55
	PWM1DTH = 0x00;						//PWM11��4λռ�ձ�0x01
	PWM1DTL = 0x00;						//PWM11��8λռ�ձ�0x55
	PWMEN |= 0x22;						//ʹ��PWM1�Լ�PWM11

}

void SetFan(INT8U status)
{
   PWM1DTL = status;
}
void SetEdge(INT8U status)
{
   PWM1DL = status;
}

 void InitMotorLeftRetreat(void)
{

    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
    PWM0C = 0x00;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x60;						//PWM0��8λռ�ձ�0x55
	PWMEN |= 0x01;						//ʹ��PWM0�Լ�PWM01

}

 void InitMotorRightRetreat(void)
{
    P1_1=0;
    P1_2=0;

	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x00;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%


	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x10;						//ʹ��PWM0�Լ�PWM01

}

 void InitMotorLeftForward(void)
{

    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P14��
    PWM0C = 0x00;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x60;						//PWM0��8λռ�ձ�0x55
	PWMEN |= 0x01;						//ʹ��PWM0�Լ�PWM01

}

 void InitMotorRightForward(void)
{
    P1_1=0;
    P1_2=0;

	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x00;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%


	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x10;						//ʹ��PWM0�Լ�PWM01

}



void LeftStop()
{

   PWMEN &= 0xfe;

    P1_3=0;
    P1_4=0;
	LeftMoveMotorData.MotorMode=0;

}

void RightStop()
{

   PWMEN &= 0xef;
    P1_1=0;
    P1_2=0;

	RightMoveMotorData.MotorMode=0;
}

void AllStop()
{
    PWMEN &= 0xee;
	
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	P1_1=0;
	
  
	
	LeftMoveMotorData.MotorMode=0;
	RightMoveMotorData.MotorMode=0;
}



 void ReadLeftPulsed(void)
{

	if((LeftMoveMotorData.MotorMode&0x03)==1)
	{
		LeftMoveMotorData.NowPulsed++;
		if(LeftMoveMotorData.NowPulsed>=(LeftMoveMotorData.MovePulsed+80))
		{
			LeftMoveMotorData.MovePulsed+=80;
			LeftMoveMotorData.RunCm++;
			if(LeftMoveMotorData.SetCm<=LeftMoveMotorData.RunCm)
			{
				LeftMoveMotorData.Flag=1;
				LeftStop();
			}
		}
	}
	else if((LeftMoveMotorData.MotorMode&0x03)==2)
	{
		LeftMoveMotorData.NowPulsed--;
		if(LeftMoveMotorData.NowPulsed<=(LeftMoveMotorData.MovePulsed-80))
		{
			LeftMoveMotorData.MovePulsed-=80;
			LeftMoveMotorData.RunCm--;
			if(LeftMoveMotorData.SetCm>=LeftMoveMotorData.RunCm)
			{
				LeftMoveMotorData.Flag=1;
				LeftStop();
			}	
				
		}
	}
}
void ReadRightPulsed(void)
{
	if((RightMoveMotorData.MotorMode&0x03)==1)
	{
		RightMoveMotorData.NowPulsed++;
		if(RightMoveMotorData.NowPulsed>=(RightMoveMotorData.MovePulsed+80))
		{

			RightMoveMotorData.RunCm++;
			RightMoveMotorData.MovePulsed+=80;
			if(RightMoveMotorData.SetCm<=RightMoveMotorData.RunCm)
			{
				RightMoveMotorData.Flag=1;
				RightStop();
			}
		}

	}
	else 
	{
		RightMoveMotorData.NowPulsed--;
		if(RightMoveMotorData.NowPulsed<=(RightMoveMotorData.MovePulsed-80))
		{

			RightMoveMotorData.RunCm--;
			RightMoveMotorData.MovePulsed-=80;

			if(RightMoveMotorData.SetCm>=RightMoveMotorData.RunCm)
			{
				RightMoveMotorData.Flag=1;
				RightStop();
			}
		}
	}
}
void CheckLeftMotorSpeed(void)
{

	static INT8U i;

	if(LeftMoveMotorData.MotorMode==1)
	{
		if(LeftMoveMotorData.NowPulsed>=LeftMoveMotorData.LastPulsed)
			LeftMoveMotorData.NowSpeed[i]=LeftMoveMotorData.NowPulsed-LeftMoveMotorData.LastPulsed;
	}
	else if(LeftMoveMotorData.MotorMode==2)
	{
		if(LeftMoveMotorData.LastPulsed>=LeftMoveMotorData.NowPulsed)
			LeftMoveMotorData.NowSpeed[i]=LeftMoveMotorData.LastPulsed-LeftMoveMotorData.NowPulsed;
	}
	else 
	{
	  LeftMoveMotorData.NowSpeed[i]=0;
	}
	i++;
	if(i>1)
	i=0;
	LeftMoveMotorData.LastPulsed=LeftMoveMotorData.NowPulsed;
	//if(i>1)
	{
		//i=0;
		LeftMoveMotorData.AvgSpeedLast=LeftMoveMotorData.AvgSpeed;
		LeftMoveMotorData.AvgSpeed=(LeftMoveMotorData.NowSpeed[0]+LeftMoveMotorData.NowSpeed[1])/2;

		//SBUF=LeftMoveMotorData.AvgSpeed;
   	  	
		if(LeftMoveMotorData.MotorMode<0x80)
		{
			if(0==LeftMoveMotorData.RunSpeed)
			{
				LeftMoveMotorData.OutPWM=0;
				LeftMoveMotorData.MotorMode|=0x80;
			}
 
			else if(LeftMoveMotorData.AvgSpeed>LeftMoveMotorData.RunSpeed)
			{

				 //if(LeftMoveMotorData.AvgSpeedLast<=LeftMoveMotorData.AvgSpeed)
				   if((LeftMoveMotorData.AvgSpeed-3)>LeftMoveMotorData.RunSpeed) 
					  LeftMoveMotorData.OutPWM-=4;
				   else if((LeftMoveMotorData.AvgSpeed-2)>LeftMoveMotorData.RunSpeed)
					  LeftMoveMotorData.OutPWM-=3;
				   else if((LeftMoveMotorData.AvgSpeed-1)>LeftMoveMotorData.RunSpeed)
					  LeftMoveMotorData.OutPWM-=2;
				   else 
					  LeftMoveMotorData.OutPWM--;
					 if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;	
			   /*
				{

          if((LeftMoveMotorData.AvgSpeed-LeftMoveMotorData.RunSpeed)>3)
					{
             LeftMoveMotorData.OutPWM-=4;
					if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;
					}					
					else 
					if((LeftMoveMotorData.AvgSpeed-LeftMoveMotorData.RunSpeed)>2)
					{
             LeftMoveMotorData.OutPWM-=3;
					if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;						
					}					
					else if((LeftMoveMotorData.AvgSpeed-LeftMoveMotorData.RunSpeed)>1)
					{

						LeftMoveMotorData.OutPWM-=2;
					if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;						
					}
					else
					{

						{

								LeftMoveMotorData.OutPWM--;
					if(LeftMoveMotorData.OutPWM<0X20)
						LeftMoveMotorData.OutPWM=0X20;								
					
						}

					}
         
				}
			  */
			}
			else if(LeftMoveMotorData.AvgSpeed<LeftMoveMotorData.RunSpeed)
			{
				 //if(LeftMoveMotorData.AvgSpeedLast>=LeftMoveMotorData.AvgSpeed)
				   if((LeftMoveMotorData.RunSpeed-3)>LeftMoveMotorData.AvgSpeed)
					 LeftMoveMotorData.OutPWM+=4;
				   else if((LeftMoveMotorData.RunSpeed-2)>LeftMoveMotorData.AvgSpeed)
					LeftMoveMotorData.OutPWM+=3;		
				   else if((LeftMoveMotorData.RunSpeed-1)>LeftMoveMotorData.AvgSpeed)
					LeftMoveMotorData.OutPWM+=2;	
				   else 
					LeftMoveMotorData.OutPWM++;
			  /*
				if((LeftMoveMotorData.RunSpeed-LeftMoveMotorData.AvgSpeed)>3)
				{
         
			
					if(LeftMoveMotorData.OutPWM>0xf0)
						LeftMoveMotorData.OutPWM=0xf0;
					else 
                    LeftMoveMotorData.OutPWM+=4;	 					
				}
				else
				if((LeftMoveMotorData.RunSpeed-LeftMoveMotorData.AvgSpeed)>2)
				{

				
					if(LeftMoveMotorData.OutPWM>0xf0)
						LeftMoveMotorData.OutPWM=0xf0;
					else 
            LeftMoveMotorData.OutPWM+=3;							
				}
				else
				if((LeftMoveMotorData.RunSpeed-LeftMoveMotorData.AvgSpeed)>1)
				{

					if(LeftMoveMotorData.OutPWM>0xf0)
						LeftMoveMotorData.OutPWM=0xf0;
					else 
            LeftMoveMotorData.OutPWM+=2;						
				}
				else
				{
					   LeftMoveMotorData.OutPWM++;
					if(LeftMoveMotorData.OutPWM>0xf0)
						LeftMoveMotorData.OutPWM=0xf0;	
					

				}
		   */
    


			}

		}
		else
			LeftMoveMotorData.OutPWM=0;
    
	   if(LeftMoveMotorData.MotorMode>0)
		 PWM0DL=LeftMoveMotorData.OutPWM;
	   else
		 LeftStop();
	 	 
	}

}




void CheckRightMotorSpeed(void)
{

	static INT8U i;

	if(RightMoveMotorData.MotorMode==1)
	{
		if(RightMoveMotorData.NowPulsed>=RightMoveMotorData.LastPulsed)
			RightMoveMotorData.NowSpeed[i]=RightMoveMotorData.NowPulsed-RightMoveMotorData.LastPulsed;
	}
	else if(RightMoveMotorData.MotorMode==2)
	{
		if(RightMoveMotorData.LastPulsed>=RightMoveMotorData.NowPulsed)
			RightMoveMotorData.NowSpeed[i]=RightMoveMotorData.LastPulsed-RightMoveMotorData.NowPulsed;
	}
	else
	{
	   RightMoveMotorData.NowSpeed[i]=0;
	}
	i++;
    if(i>1)
	i=0;
	RightMoveMotorData.LastPulsed=RightMoveMotorData.NowPulsed;
	//if(i>1)
	{
		//i=0;
		RightMoveMotorData.AvgSpeedLast=RightMoveMotorData.AvgSpeed;
		RightMoveMotorData.AvgSpeed=(RightMoveMotorData.NowSpeed[0]+RightMoveMotorData.NowSpeed[1])/2;


    
		if(RightMoveMotorData.MotorMode<0x80)
		{
			if(0==RightMoveMotorData.RunSpeed)
			{
				RightMoveMotorData.OutPWM=0;
				RightMoveMotorData.MotorMode|=0x80;
			}

			else if(RightMoveMotorData.AvgSpeed>RightMoveMotorData.RunSpeed)
			{
				 //if(RightMoveMotorData.AvgSpeedLast<=RightMoveMotorData.AvgSpeed)

				   if((RightMoveMotorData.AvgSpeed-3)>RightMoveMotorData.RunSpeed) 
					  RightMoveMotorData.OutPWM-=4;
				   else if((RightMoveMotorData.AvgSpeed-2)>RightMoveMotorData.RunSpeed)
					  RightMoveMotorData.OutPWM-=3;
				   else if((RightMoveMotorData.AvgSpeed-1)>RightMoveMotorData.RunSpeed)
					  RightMoveMotorData.OutPWM-=2;
				   else 
					  RightMoveMotorData.OutPWM--;
					 if(RightMoveMotorData.OutPWM<0X20)
						RightMoveMotorData.OutPWM=0X20;	

			}
			else if(RightMoveMotorData.AvgSpeed<RightMoveMotorData.RunSpeed)
			{
				 //if(RightMoveMotorData.AvgSpeedLast>=RightMoveMotorData.AvgSpeed)
				   if((RightMoveMotorData.RunSpeed-3)>RightMoveMotorData.AvgSpeed)
					 RightMoveMotorData.OutPWM+=4;
				   else if((RightMoveMotorData.RunSpeed-2)>RightMoveMotorData.AvgSpeed)
					RightMoveMotorData.OutPWM+=3;		
				   else if((RightMoveMotorData.RunSpeed-1)>RightMoveMotorData.AvgSpeed)
					RightMoveMotorData.OutPWM+=2;	
				   else 
					RightMoveMotorData.OutPWM++;														
                    if(RightMoveMotorData.OutPWM>0xfA)
					RightMoveMotorData.OutPWM=0xfA;

 
			}

		}
		else
			RightMoveMotorData.OutPWM=0;
    
	   if(RightMoveMotorData.MotorMode>0)
		 PWM0DTL=RightMoveMotorData.OutPWM;
	   else
		 RightStop();
		 
	}

}



 void SetXMotor(
    INT8U Leftmotor,
    INT8U LeftStartSpeed,
    INT8U LeftEndSpeed,
	INT8U LeftSlope,
    INT8U Rightmotor,
    INT8U RightStartSpeed,
    INT8U RightEndSpeed,
	INT8U RightSlope
)
{

	LeftMoveMotorData.Flag=0;
	RightMoveMotorData.Flag=0;
	RightMoveMotorData.LastPulsed=0;
	LeftMoveMotorData.LastPulsed=0;
	RightMoveMotorData.NowPulsed=0;
	LeftMoveMotorData.NowPulsed=0;

	RightMoveMotorData.MovePulsed=0;
	LeftMoveMotorData.MovePulsed=0;
	LeftMoveMotorData.Slope=LeftSlope;
	RightMoveMotorData.Slope=RightSlope;

	if(LeftStartSpeed==0XFF)
	{

	}
	else if(LeftStartSpeed==0XF8)
	{
		if(LeftMoveMotorData.EndSpeed<20)
			LeftMoveMotorData.EndSpeed++;
	}
	else if(LeftStartSpeed==0XF0)
	{
		if(LeftMoveMotorData.EndSpeed>2)
			LeftMoveMotorData.EndSpeed--;
	}
	else 
	{

		if(Leftmotor==1)
		{
			if(LeftMoveMotorData.MotorMode!=Leftmotor)
			{
				InitMotorLeftForward();
				LeftMoveMotorData.OutPWM=0X40;
				PWM0DL=LeftMoveMotorData.OutPWM;


			}

			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;			
			LeftMoveMotorData.MovePulsed=0;
		}
		else if(Leftmotor==2)
		{
			if(LeftMoveMotorData.MotorMode!=Leftmotor)
			{
				InitMotorLeftRetreat();
				LeftMoveMotorData.OutPWM=0X40;
				PWM0DL=LeftMoveMotorData.OutPWM;
			}
											  
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;			
			LeftMoveMotorData.MovePulsed=0;
		}
		else
		{
		LeftMoveMotorData.MotorMode=0;
			LeftStop();
		}
		LeftMoveMotorData.RunSpeed=LeftStartSpeed;
		LeftMoveMotorData.EndSpeed=LeftEndSpeed;

	}


	if(RightStartSpeed==0XFF)
	{

	}
	else if(RightStartSpeed==0XF8)
	{
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;	
			LeftMoveMotorData.MotorMode=Leftmotor;
			LeftMoveMotorData.LastPulsed=0;
			LeftMoveMotorData.NowPulsed=0;
		if(RightMoveMotorData.EndSpeed<20)
			RightMoveMotorData.EndSpeed++;
	}
	else if(RightStartSpeed==0XF0)
	{
		if(RightMoveMotorData.EndSpeed>2)
			RightMoveMotorData.EndSpeed--;
	}
	else 
	{

		if(Rightmotor==1)
		{
			if(RightMoveMotorData.MotorMode!=Rightmotor)
			{
				InitMotorRightForward();
				RightMoveMotorData.OutPWM=0X40;
				PWM0DTL=RightMoveMotorData.OutPWM;

			}

			RightMoveMotorData.MotorMode=Rightmotor;			
			RightMoveMotorData.LastPulsed=0;
			RightMoveMotorData.NowPulsed=0;			
			RightMoveMotorData.MotorMode=Rightmotor;
			RightMoveMotorData.LastPulsed=0;
			RightMoveMotorData.NowPulsed=0;
			RightMoveMotorData.MovePulsed=0;
		}
		else if(Rightmotor==2)
		{
			if(RightMoveMotorData.MotorMode!=Rightmotor)
			{
				InitMotorRightRetreat();
				RightMoveMotorData.OutPWM=0X40;
				PWM0DTL=RightMoveMotorData.OutPWM;

			}

			RightMoveMotorData.MotorMode=Rightmotor;			
			RightMoveMotorData.LastPulsed=0;
			RightMoveMotorData.NowPulsed=0;			
			RightMoveMotorData.MotorMode=Rightmotor;
			RightMoveMotorData.LastPulsed=0;
			RightMoveMotorData.NowPulsed=0;
			RightMoveMotorData.MovePulsed=0;
		}
		else
		{
		RightMoveMotorData.MotorMode=0;
			RightStop();
		}
		RightMoveMotorData.RunSpeed=RightStartSpeed;
		RightMoveMotorData.EndSpeed=RightEndSpeed;

	}

}








void AdjustSpeed()
{

	if(LeftMoveMotorData.RunSpeed>LeftMoveMotorData.EndSpeed)
	{
		LeftMoveMotorData.SlopeTime++;
		if(LeftMoveMotorData.SlopeTime>LeftMoveMotorData.Slope)
		{
			LeftMoveMotorData.SlopeTime=0;
			if(LeftMoveMotorData.RunSpeed>0)
				LeftMoveMotorData.RunSpeed--;
		}
	}
	else if(LeftMoveMotorData.RunSpeed<LeftMoveMotorData.EndSpeed)
	{
		LeftMoveMotorData.SlopeTime++;
		if(LeftMoveMotorData.SlopeTime>LeftMoveMotorData.Slope)
		{
			LeftMoveMotorData.SlopeTime=0;
			LeftMoveMotorData.RunSpeed++;
		}
	}
	if(RightMoveMotorData.RunSpeed>RightMoveMotorData.EndSpeed)
	{
		RightMoveMotorData.SlopeTime++;
		if(RightMoveMotorData.SlopeTime>RightMoveMotorData.Slope)
		{
			RightMoveMotorData.SlopeTime=0;
			if(RightMoveMotorData.RunSpeed>0)
				RightMoveMotorData.RunSpeed--;
		}
	}
	else if(RightMoveMotorData.RunSpeed<RightMoveMotorData.EndSpeed)
	{
		RightMoveMotorData.SlopeTime++;
		if(RightMoveMotorData.SlopeTime>RightMoveMotorData.Slope)
		{
			RightMoveMotorData.SlopeTime=0;
			RightMoveMotorData.RunSpeed++;
		}
	}
	///*
	if(LeftMoveMotorData.RMode==1)
	{
	if(RightMoveMotorData.NowPulsed>(LeftMoveMotorData.NowPulsed+100))
	{
	  RightMoveMotorData.RunSpeed=LeftMoveMotorData.RunSpeed-4;
	}
	else if(RightMoveMotorData.NowPulsed>(LeftMoveMotorData.NowPulsed+50))
	{
	  RightMoveMotorData.RunSpeed=LeftMoveMotorData.RunSpeed-3;
	}
	else if(RightMoveMotorData.NowPulsed>(LeftMoveMotorData.NowPulsed+30))
	{
	  RightMoveMotorData.RunSpeed=LeftMoveMotorData.RunSpeed-2;
	}
	else if(RightMoveMotorData.NowPulsed>(LeftMoveMotorData.NowPulsed+10))
	{
	 RightMoveMotorData.RunSpeed=LeftMoveMotorData.RunSpeed-1;
	}
	else if(LeftMoveMotorData.NowPulsed>(RightMoveMotorData.NowPulsed+100))
	{
	  LeftMoveMotorData.RunSpeed=RightMoveMotorData.RunSpeed-4;
	}
	else if(LeftMoveMotorData.NowPulsed>(RightMoveMotorData.NowPulsed+50))
	{
	  LeftMoveMotorData.RunSpeed=RightMoveMotorData.RunSpeed-3;
	}
	else if(LeftMoveMotorData.NowPulsed>(RightMoveMotorData.NowPulsed+30))
	{
	  LeftMoveMotorData.RunSpeed=RightMoveMotorData.RunSpeed-2;
	}
	else if(LeftMoveMotorData.NowPulsed>(RightMoveMotorData.NowPulsed+10))
	{
	  LeftMoveMotorData.RunSpeed=RightMoveMotorData.RunSpeed-1;
	}

    }
	//*/

}
void SetMotorcm(INT8U mode,INT16U Setcm)
{
  switch(mode)
  {
     case 1:
	 {
	   LeftMoveMotorData.RMode=1;
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=Setcm;
       RightMoveMotorData.SetCm=Setcm;
     }
	 break;
	 case 2:
	 {
	   LeftMoveMotorData.RMode=2;
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=LeftMoveMotorData.RunCm-Setcm;
       RightMoveMotorData.SetCm=RightMoveMotorData.RunCm-Setcm;
     }
	 break;
	 case 3:
	 {
	   LeftMoveMotorData.RMode=3;
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=LeftMoveMotorData.RunCm-Setcm/6.3;
       RightMoveMotorData.SetCm=Setcm/6.3;
     }
	 break;
	 case 4:
	 {
	   LeftMoveMotorData.RMode=4;
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=Setcm/6.3;
       RightMoveMotorData.SetCm=RightMoveMotorData.RunCm-Setcm/6.3;
     }
	 break;
     case 5:
	 {
	   LeftMoveMotorData.RMode=5;
	   LeftMoveMotorData.RunCm=0;
       RightMoveMotorData.RunCm=0;
       LeftMoveMotorData.SetCm=Setcm;
       RightMoveMotorData.SetCm=Setcm;
     }
	 break;
  }
}

