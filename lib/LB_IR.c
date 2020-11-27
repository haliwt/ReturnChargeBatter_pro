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

 	  PITS3 |= 0x01;						//INT14,�ⲿ�жϵ�ƽѡ��,�������ͷ���������ж�
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
     
	 static INT16U rtime;
	 static INT8U timelong;
	 rtime++;
	 
	if(Remote1_ReadIR.ReadIRFlag==1) //IR_gpio �ж����� 1
	{
		   
		   rtime =0;
		   Remote1_ReadIR.Nowcount++ ;
		   Remote1_ReadIR.Inttime  ++;
		
		   
				if(P1_6==1)//if(Remote1_ReadIR.Inttime >=0x27)//if(Remote1_ReadIR.Nowcount>=0x20)//WT.EDIT 57ms if(Remote1_ReadIR.Nowcount>200)
				{
					if(Remote1_ReadIR.Inttime >=0x27){
						Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =1 ;
						Remote1_ReadIR.Inttime =0;
						Remote1_ReadIR.BitHigh++;
					}
					else {
					   Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =0 ;
					   Remote1_ReadIR.Inttime =0;
					   Remote1_ReadIR.BitLow++;

					}
				
					
				}
				else  {
					 
					   Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit] =0 ;
					   Remote1_ReadIR.Inttime =0;
					   Remote1_ReadIR.BitLow++;
					  
			  
	            }
	  
	}
    else if(P1_6==1 && rtime >30){
		Remote1_ReadIR.ReadIRFlag=2;

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
        if(Remote1_ReadIR.ReadIRBit>7)
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
		   
		  P->ReadIRFlag=3;
	}
	#if 1	
    if(  P->ReadIRFlag==3){
	                  P->ReadIRFlag=3;
					
		              Usart1Send[0]=2;
		            // Usart1Send[1]=0xAB ;//Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
                     //Usart1Send[2]=Remote1_ReadIR.Interrupt_IR2  ;//0xff;
				
	                 Usart1Send[2]=P->ReadIR[0];
				
				   // Usart1Send[3]=0x88;
	                SendCount=1;
	                SBUF=Usart1Send[SendCount];
                }
    #endif 
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
  * @?|��???  	?��?��o?��o?����oy
  * @2?��oy  	fui_i : ?��?��o?����o?��??
  * @?��|��???|�� ?T
  * @?��?�� 	Fcpu = 16MHz?��?fui_i = 1��o?��?��??��?��o?����o?��?????a1Ms
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
	 	 
		     return (3); //5ֱ������

	 }
	  if(Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] < 0x0D && Remote1_ReadIR.ReadASTAR[Remote1_ReadIR.ReadA_Time] > 0x0A){
	 	
		 Remote1_ReadIR.Timelock=0;
		 return (4); //5ֱ������
	 }
    else{
	      if(Remote1_ReadIR.ReadIR[1]==1) //left IR �����
		 	{

				return (1);
			   
		 	}
			else if(Remote1_ReadIR.ReadIR[1]==2){ //right IR

	          
			    
				  return (2);
			  
	              
			} //right IR ���ұ�
		         

	      
	
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


