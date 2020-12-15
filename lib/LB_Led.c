/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
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
	TCON1 = 0x00;						//T1定时器时钟为Fosc
	TMOD = 0x00;						//16位重装载定时器/计数器

	//Tim1计算时间 	= (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//定时0.1ms
	//反推初值 	= 65536 - ((1/10000) / (1/(Fosc / Timer分频系数)))
	//		   	= 65536 - ((1/10000) / (1/(16000000 / 12)))
	//			= 65536 - 133
	//			= 0xFf78
	TH1 = 0xFf;
	TL1 = 0x78;
	IE |= 0x08;							//打开T1中断
	TCON |= 0x40;						//使能T1
    
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
  //P2M1 = 0x60;                        //P2_1设置为施密特数字带上拉输入
  //P2M0 = 0xC2;                        //P21
  //P2_0=0;
  //P2_1=0;
  P3M4 = 0x60;                         //P3_4 = 输入下啦
  P3M5 = 0x60 ;
  

}
void SetIMPOutOn()
{
  P2_0=1;
  
}

 void SetIMPOutOff()
{
  P2_0=0;
}
/******************************************************************
	*
	*Function Name: void ReadIMP(void)
	*Function : impact 
	*
	*
	*
*******************************************************************/
void ReadIMP(void)
{
  if(P3_4 ==0 || P3_5==0)//if(P2_1)
     ImpStatus=1;
  else
   ImpStatus=0;
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

/****************************************************************
 	* * *
 	* Function Name:INT8U ReadKey(void)
 	* Function: Touch key of define function 
 	* Input Ref: NO
 	* Return Ref: KEY VALUE 
 	* 
 ***************************************************************/
INT8U  ReadKey(void)
{

  static INT8U  K1temp,K2temp,K12temp,keyValue;
  INT8U t_Key;
  t_Key=0;

  if(P0_1 ==1 && P0_0 ==1){

      if(K12temp<200){
   	   K12temp++;
	   BuzzerON();

	  }
	  else {
	     K12temp=0;
		BuzzerOff();
	  
	  }
	  
	 if(K12temp==190)
	  {
	    K12temp=201;
	    return(0x32);
	  }
	  
  }
  else {

  if(P0_1==1)  //right key Works SW1 
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

  if(P0_0==0)   //Left key Power ON SW2
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
	t_Key =10;  //woks Mode 
  }
  if(K2temp==190)
  {
    K2temp=201;

    t_Key =2;  //left  --Power On and Power down
  }
  return(t_Key);  
}

}



 INT8U ReadPowerDCIn(void)
{
  return(P1_0);
}

 INT8U ReadPowerRecharge(void)
{
  return(P1_7);
}
void InitBuzzer(void)
{

   
	P2M2 = 0xC2;						//P35????????????
	PWM3_MAP = 0x22;					//PWM3???P35??
		//???????	= 0xFF / (Fosc / PWM??????)		??Fosc????????????????
		//			= 0xFF /(16000000 / 4)			
		//			= 255 /4000000
		//			= 63.75us		??15.69KHZ		
	
		PWM3P = 0xc4;						//PWM?????0xFF
		//??Ч????????????????	
		//			= 0x55 / (Fosc / PWM??????)		??Fosc????????????????
		//			= 0x55 /(16000000 / 4)			
		//			= 85 /4000000
		//			= 21.25us		????? 21.25 / 63.75 = 34%
	
		PWM3D = 0x30;						//PWM????????
		PWM3C = 0x06;						//???PWM3??????ж??????????????32??? 
	
	
	//	P2M2 = 0x84;						//P01???????????????????????
	//	P2_2=0;

}
void BuzzerON()
{
 // BuzzerFlag=1; //WT.EDIT
// SetBuzzerTime(4); //WT.EDIT 
//  PWM3C = 0x96; 						//使能PWM3，关闭中断，允许输出，时钟32分频
//  P2_2=0;
}


void BuzzerOff()
{
 // BuzzerFlag=0; //WT.EDIT 
//  PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频
//  P2_2=1;
}

void SetBuzzerTime(INT8U time)
{
	BuzzerTime=time; //WT.EDIT
	
	PWM3C = 0x96; //WT.EDIT 						//使能PWM3，关闭中断，允许输出，时钟32分频	
}

void CheckBuzzer()
{
   if(BuzzerTime<200)
   {
     
     BuzzerTime--;

	 if(BuzzerTime<1)
	 {
	   PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频	
	 }
   }
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
     P2M1 = 0X51 ; //ReCharge input SMT pull down
     P1M0 = 0x51;  //DC INPUT pull down 
     P2_1 =0; 
	 P1_0 =0;

	     
   //P10 input GPIO PULL DOWN =DC detected ,outside charge batter connector
   

}
