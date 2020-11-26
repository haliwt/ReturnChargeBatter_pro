/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
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
#define setbit(x,y)    	 		x|=(1<<y)          //将X的第Y位置1
#define clrbit(x,y)   	 		x&=~(1<<y)        //将X的第Y位清0
#define reversebit(x,y) 	 	x^=(1<<y)        //取反
#define getbit(x,y)  			((x) >> (y)&1)    //读取位

INT16U   Rtime;


void Iint_T5(void)
{
 /**********************************TIM5????3?ê??ˉ**************************************/
    P1M6 = 0x68;//P3M3 = 0x62;                        //P33éè???aé?à-ê?è?    
	T5_MAP = 0x16;						//T52????úó3é?P33???ú
	T5CON = 0x3F;						//256分频，16位下降沿捕获
	T5CON1 = 0x00;						//T5捕获选择 T5脚的变化
	TH5 = 0x00;
	TL5 = 0x00;
	IE1 |= 0x10;						//′ò?aT5?D??
	EA = 1;



}


void Init_IR()
{

    #if 1
	P1M6 = 0x62;//0x68;			        	//P1_6设置为带SMT(施密特功能)上拉输入

 	 PITS3 |= 0x00;						//INT14,外部中断电平选择,红外接收头，上升沿中断
	 //PITS3 |=(1<<4);   //01 下降沿出发
	//PITS3 &=~(1<<5); //set 0 
	
	PINTE1 |= 0x40;						//使能INT14

	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;
	Remote1_ReadIR.ReadIRFlag=0;
   #endif 

}


/**************************************************************
	*
	*Function Name:void Remote11_Count(void)
	*Fucntion :在定时器T1,0.1ms中断函数中执行,判断高电平时间ir2
    *          IR1
	*
	*
**************************************************************/
#if IR2

void Remote12_Count(void)
{
     
	 static INT16U rtime;
	 static INT8U timelong;
	 rtime++;
	 
	if(Remote1_ReadIR.ReadIRFlag==1) //IR_gpio 中断中置 1
	{
		   
		   rtime =0;
		   Remote1_ReadIR.Nowcount++ ;
		   if(Remote1_ReadIR.Nowcount==1)Remote1_ReadIR.Inttime  ++;
		   if( Remote1_ReadIR.Nowcount==2){
		   	     timelong =Remote1_ReadIR.Inttime; 
				 Remote1_ReadIR.Nowcount=0;
		        Remote1_ReadIR.Inttime=0;
		  	}
			
		   
				if(timelong >4)//if(Remote1_ReadIR.Inttime >=0x27)//if(Remote1_ReadIR.Nowcount>=0x20)//WT.EDIT 57ms if(Remote1_ReadIR.Nowcount>200)
				{
					
					Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =1 ;
					Remote1_ReadIR.Inttime =0;
                    Remote1_ReadIR.BitHigh++;
				
					
				}
				else  {
					 
					   Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =0 ;
					   Remote1_ReadIR.Inttime =0;
					   Remote1_ReadIR.BitLow++;
					  
			  
	            }
	  
		    }
	if(P1_6==1 && rtime >20){
		Remote1_ReadIR.ReadIRFlag=2;

	}
    if(Remote1_ReadIR.ReadIRBit ==11 ){
   	    Remote1_ReadIR.ReadIRFlag=2;
	}

}
#endif




/**************************************************************
	*
	*Function Name:void Read_Remote11IR(void)
	*Fucntion :GPIO ,中断函数中执行,IR2
	*Input Ref:NO
	*Return Ref: NO
	*
**************************************************************/
#if IR2

void Read_Remote12IR(void)
{

	Remote1_ReadIR.NowVoltage=P1_6; //remotoe receive GPIO
	if(Remote1_ReadIR.ReadIRBit!=11){
    if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==0))//input interrupt program
	{
		Remote1_ReadIR.ReadIRFlag=1;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit=0;
	    Remote1_ReadIR.Inttime =0;
		Remote1_ReadIR.BitLow=0;
		Remote1_ReadIR.BitHigh =0;
		Remote1_ReadIR.recordTime =0;//WT.EDIT
		
		
	}
    else if((Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1))
	{
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Runcontrol=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;
		
      
		 Remote1_ReadIR.ReadIRBit++; //bit numbers add 
        if(Remote1_ReadIR.ReadIRBit>10)
			Remote1_ReadIR.ReadIRFlag=2;
		 
		
		
	}
	

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
	
	INT8U temp,j;
	static INT8U right,left,n;

	
	if(P->ReadIRFlag==2){ // ir receive of Byte(8 bit)

      
		  for(j=0;j<8;j++){
	   	
		  temp= temp | (Remote1_ReadIR.ReadIRData[(7-j)]<< j);
		     // temp= temp | (Remote1_ReadIR.ReadIRData[j]<< j);
          }
		   P->ReadIR[0] =temp;
		   
		 P->ReadIRFlag=4;
	}
		
    if( P->ReadIRFlag==4){
	                  P->ReadIRFlag=3;
					  right =0;
					  left =0;
					  n=0;
		              Usart1Send[0]=5;
				
	                 Usart1Send[1]=P->ReadIR[0];
				
					
		
					Usart1Send[2]=0x88;
	                SendCount=1;
	                SBUF=Usart1Send[SendCount];
                    
					
					
				
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

  if(Remote1_ReadIR.ReadIRFlag==3)
   {
   
	//  KeyclearTime=0;
     Remote1_ReadIR.ReadIRFlag=0;
	
	 Remote1_ReadIR.BitHigh=0;
	 Remote1_ReadIR.BitLow =0 ;
	 Remote1_ReadIR.ReadIRBit=0; 
	  Remote1_ReadIR.recordTime =0;//WT.EDIT
	  Remote1_ReadIR.Inttime=0;

	  
	 // KK = AutoBack_ChargeBatter();
	  return (KK);
	 
   }
   
  return(KK);
}

/*******************************************************
  * @?|ì???  	?¨?¨o?ào?￥¨oy
  * @2?¨oy  	fui_i : ?¨?¨o?à¨o?à??
  * @?¤|ì???|ì ?T
  * @?á?é 	Fcpu = 16MHz?ê?fui_i = 1¨o?à?ê??¨?¨o?à¨o?à?????a1Ms
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
/********************************************************************
	*
	*Function Name:AutoBack_ChargeBatter(void)
	*Function : To cheded ir of value
	*Input Ref: NO
	*Return Ref: NO 
	*
********************************************************************/
INT8U  AutoBack_ChargeBatter(void)
{
	

     if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] >= 0x0D){
	 	 
		     return (3); //5直线行走

	 }
	  if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] < 0x0D && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] > 0x0A){
	 	
		 Remote1_ReadIR.Timelock=0;
		 return (4); //5直线行走
	 }
    else{
	      if(Remote1_ReadIR.ReadIR[1]==1) //left IR 在左边
		 	{

				return (1);
			   
		 	}
			else if(Remote1_ReadIR.ReadIR[1]==2){ //right IR

	          
			    
				  return (2);
			  
	              
			} //right IR 在右边
		         

	      
	
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
    res = max2(a,b);        //由max2返回赋值给res 
    res = max2(res,c);      //将res，c的值分别传入到max2中的a,c继续比较 a b的最大值（即比较res与c中的最大值） 
    res = max2(res,d);
    return res;             //返回res的值给max4函数 
    
}


