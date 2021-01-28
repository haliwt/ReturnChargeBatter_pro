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
INT8U ForwardFlag;

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

	PWM1PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM1PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM1DH = 0x00;						//PWM1��4λռ�ձ�0x01
	PWM1DL = 0x00;						//PWM1��8λռ�ձ�0x55
	PWM1DTH = 0x00;						//PWM11��4λռ�ձ�0x01
	PWM1DTL = 0x00;						//PWM11��8λռ�ձ�0x55
	PWMEN |= 0x22;						//ʹ��PWM1�Լ�PWM11
	//SetFan(0);
	//SetEdge(0);
}


 void InitMotorForward(void)
{
    P1_1=0;  //right 
    P1_2=0;
	
    P1_3=0; //left
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P13��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xA0;	//WT.EDIT					//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xA0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=1;
}
 void InitMotorForward_TOPIR(void)
{
    P1_1=0;  //right 
    P1_2=0;
	
    P1_3=0; //left
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P13��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xA0;	//WT.EDIT					//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xA0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	
}
 void InitMotorRetreat(void)
{
    P1_1=0;
    P1_2=0;
	
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=1;
}
  void InitMotorRetreat_TOPIR(void)
{
    P1_1=0;
    P1_2=0;
	
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xB0;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xB0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=1;
}
 void InitMotorRetreatMax(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xf5;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xf5;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=1;
}
/***************************************************************
	*
	*Function Name:void InitMotorForwardRight(void)
	*Function :Line run 
	*
	*
	*
***************************************************************/
 void InitMotorForwardRight(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P13��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0x90;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x90;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=2;
}


 void InitMotorForwardLeft(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
	PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
	PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x90;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x90;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=3;
}


 void InitMotorForwardRightSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0x90;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x90;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=5;
}
 /***************************************************************
	 *
	 *Function Name:void InitMotorForwardRightSlow(void)
	 *Function :Line run slowly
	 *
	 *
	 *
 ***************************************************************/

 void InitMotorForwardLeftSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0x90;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x90;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=6;
}
 /***************************************************************
	*
	*Function Name:void InitMotorForwardRightSlow(void)
	*Function :Line run slowly
	*
	*
	*
***************************************************************/
 void InitMotorForwardSlow(void)
{
    P1_1=0;  //right
    P1_2=0;   //left
    P1_3=0;   //right
    P1_4=0;  //left
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xC0;	//WT.EDIT 					//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xC0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=0;
}
  /***************************************************************
	*
	*Function Name:void InitMotorForwardRightSlow_Target(void)
	*Function :Line run slowly
	*
	*
	*
***************************************************************/
 void InitMotorForwardSlow_Target(void)
{
    P1_1=0;  //right
    P1_2=0;   //left
    P1_3=0;   //right
    P1_4=0;  //left
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xA0;	//WT.EDIT 					//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xA0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=0;
}
 /***************************************************************
	*
	*Function Name:void InitMotorForwardRightSlow(void)
	*Function :Line run slowly
	*
	*
	*
***************************************************************/
 void SetMotorForwardPWMUP()
{
	if(ForwardFlag==1)
	{
	  if(PWM0DL<0xd0)					 
	   PWM0DL += 3;				 
	   //PWM0DTH = 0x00;
	  if(PWM0DTL<0xd0)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==2)
	{
	  if(PWM0DL<0xa0)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0xe5)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==3)
	{
	  if(PWM0DL<0xf5)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0xa0)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==4)
	{
	  if(PWM0DL<0xf5)					 
	   PWM0DL += 2;				 
	  if(PWM0DTL<0xf5)						 
	   PWM0DTL += 2;
	}
	else if(ForwardFlag==5)
	{
	  if(PWM0DL<0xb0)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0x90)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==6)
	{
	  if(PWM0DL<0x90)					 
	   PWM0DL += 3;				 
	  if(PWM0DTL<0xb0)						 
	   PWM0DTL += 3;
	}
	else if(ForwardFlag==7)
	{
	  if(PWM0DL>0xC0)					 
	   PWM0DL -= 1;				 
	  if(PWM0DTL>0x90)						 
	   PWM0DTL -= 2;
	}
	else if(ForwardFlag==8)
	{
	  if(PWM0DL<0xd0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xa0)						 
	   PWM0DTL += 1;
	}	
	else if(ForwardFlag==9)
	{
	  if(PWM0DL<0xee)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xb0)						 
	   PWM0DTL += 1;
	}
	else if(ForwardFlag==10)
	{
	  if(PWM0DL>0x90)					 
	   PWM0DL -= 2;				 
	  if(PWM0DTL>0xC0)						 
	   PWM0DTL -= 1;
	}
	else if(ForwardFlag==11)
	{
	  if(PWM0DL<0xa0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xD0)						 
	   PWM0DTL += 1;
	}
	else if(ForwardFlag==12)
	{
	  if(PWM0DL<0xb0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xee)						 
	   PWM0DTL += 1;
	}	
	else if(ForwardFlag==13)
	{
	  if(PWM0DL<0xc0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xc0)						 
	   PWM0DTL += 1;
	}	
		else if(ForwardFlag == 14){   //���ּ��٣�΢���Ƕ�
		if(PWM0DL<0x90 && PWM0DTL==0xb0){
			PWM0DL -= 1;	
			if(PWM0DL<=0x90)
				PWM0DTL= 0xb1;
		}
		else{		
			if(PWM0DTL<0xc0)
				PWM0DTL += 2;
			PWM0DL += 2;
			if(PWM0DL>=0xc0){
				PWM0DL = 0xc0;
				PWM0DTL = 0xc0;
				ForwardFlag = 15;
			}
		}
	}
	else if(ForwardFlag == 15){   //����ת���ڳ�ֱ��
	  if(PWM0DL>0xc0)					 
	   PWM0DL -= 2;			
		else
			PWM0DL += 2;
		
	  if(PWM0DTL>0xc0)						 
	   PWM0DTL -= 2;
		else
		PWM0DTL += 2;
		
	}
	else if(ForwardFlag == 16){   //���ּ��٣�΢���Ƕ�
	  if(PWM0DL>0xb0)					 
	   PWM0DL -= 1;				 
	  if(PWM0DTL<0xd0)						 
	   PWM0DTL += 1;
	}
	else if(ForwardFlag == 17){   //С������ת
	  if(PWM0DL>0xC0)
			PWM0DL -= 1;	
	  else
			PWM0DL += 1;	
		
	  if(PWM0DTL<0xB8)					
	   PWM0DTL += 1;
		else
		PWM0DTL -= 1;
	}
	else if(ForwardFlag==18)
	{
	  if(PWM0DL<0xa0)					 
	   PWM0DL += 1;				 
	  if(PWM0DTL<0xa0)						 
	   PWM0DTL += 1;
	}	
	else if(ForwardFlag == 19){   //С������ת
	  if(PWM0DL>0xf0)
			PWM0DL -= 2;	
	  else
			PWM0DL += 2;	
		
	  if(PWM0DTL<0xb0)					
	   PWM0DTL += 2;
		else
		PWM0DTL -= 2;
	}	
	return;
}
void InitMotorRight(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;	//0x10					//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0xA0;	 //WT.EDIT 					//PWM0��8λռ�ձ�0x55  //WT.EDTI 
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=4;
}
void InitMotorRight_TOPIR(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
    PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	//����ģʽ�£�PWM0��PWM01����һ�����ڼĴ���
	//PWM0��ռ�ձȵ���ʹ��			PWM0���ռ�ձȼĴ���
	//PWM01��ռ�ձȵ���ʹ��			PWM0��������Ĵ���

	//���ڼ��� 	= 0x03ff / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x03ff / (16000000 / 8)			
	// 			= 1023   /2000000
	//			= 511.5us		   		Լ1.955kHz

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;	//0x10					//���ڵ�8λ����Ϊ0xFF

	//ռ�ձȼ���= 0x0155 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x0155 / (16000000 / 8)			
	// 			= 341 	 / 2000000
	//			= 170.5us		   ռ�ձ�Ϊ 170.5/511.5 = 33.3%

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0xA0;	 //WT.EDIT 					//PWM0��8λռ�ձ�0x55  //WT.EDTI 
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x90;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	
}

/***************************************************************
	*
	*Function Name:void InitMotorLeft(void)
	*Function :turn round CCW 
	*
	*
	*
***************************************************************/
 void InitMotorLeft(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P13��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0x90;	//WT.EDIT					//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xA0;		//WT.EDIT 				//PWM01��8λռ�ձ�0x55 
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=4;
}
 /***************************************************************
	*
	*Function Name: void InitMotorLeft_TOPIR(void)
	*Function :turn round CCW 
	*
	*
	*
***************************************************************/
 void InitMotorLeft_TOPIR(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P13��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xB0;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xD0;	//WT.EDIT 2022.01.23				//PWM01��8λռ�ձ�0x55 
	PWMEN |= 0x11;					
}
/***************************************************************
	*
	*Function Name:void InitMotorRight(void)
	*Function :Line run BACK 
	*
	*
	*
***************************************************************/
 void InitMotorRightMax(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xa0;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xa0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=4;
}
 void InitMotorLeftMax(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P13��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xa0;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xa0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=4;
}
void InitMotorRightSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xa4;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xa4;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=0;
}

 void InitMotorLeftSlow(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P13��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xa4;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xa4;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=0;
}

void SetStop()
{
  ForwardFlag=0;
   PWMEN &= 0xee;
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
}


void SetFan(INT8U status)
{
   PWM1DTL = status;
}
void SetEdge(INT8U status)
{
   PWM1DL = status;
}





 void InitMotorForwardRightUp1(void)
{
    P1_1=0;
    P1_2=0;
    P1_3=0;
    P1_4=0;
		PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
		PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
    PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
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
	PWM0DL = 0xb0;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xc0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=7;
}

 void InitMotorForwardRightUp2(void)
{
	ForwardFlag=8;
}

 void InitMotorForwardRightUp3(void)
{
	ForwardFlag=9;
}


 void InitMotorForwardLeftUp1(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
	PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
	PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF


	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0xb0;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0xc0;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=10;
}

 void InitMotorForwardLeftUp2(void)
{
	ForwardFlag=11;
}
	 
 void InitMotorForwardLeftUp3(void)
{
	ForwardFlag=12;
}


void InitMotorRightCircle(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
	PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
	PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						


	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x60;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=13;
}

void InitMotorRightCircleRecharge(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x13;					//PWM0ͨ��ӳ��P14��
	PWM01_MAP = 0x11;					//PWM01ͨ��ӳ��P11��
	PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
	PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						


	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x60;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=18;
}


 void InitMotorLeftCircle(void)
{
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;
	PWM0_MAP = 0x14;					//PWM0ͨ��ӳ��P13��
	PWM01_MAP = 0x12;					//PWM01ͨ��ӳ��P12��
  PWM0C = 0x01;						//PWM0����Ч��PWM01����Ч��ʱ��8��Ƶ 
  PWMM |= 0x10;						//PWM0�����ڻ���ģʽ						

	PWM0PH = 0x01;						//���ڸ�4λ����Ϊ0x03
	PWM0PL = 0x0;						//���ڵ�8λ����Ϊ0xFF

	PWM0DH = 0x00;						//PWM0��4λռ�ձ�0x01
	PWM0DL = 0x60;						//PWM0��8λռ�ձ�0x55
	PWM0DTH = 0x00;						//PWM01��4λռ�ձ�0x01
	PWM0DTL = 0x60;						//PWM01��8λռ�ձ�0x55
	PWMEN |= 0x11;						//ʹ��PWM0�Լ�PWM01
	ForwardFlag=13;
}

void InitMoterAdjustLeft(void)
{
	ForwardFlag = 14;
}

void InitMoterAdjustLeftMore(void)
{
	ForwardFlag = 16;
}

void InitMoterAdjustForward(void)
{
	ForwardFlag = 15;
}

void InitMotorRightLittle(void)
{
		ForwardFlag = 17;
}
