/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  LB_IR_h
#define  LB_IR_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//ȫ�ֱ�������
#ifdef  KAKA_IR_GB
#define KAKA_IR_EXT
#else
#define  KAKA_IR_EXT extern
#endif

#define IR1   0
#define IR3   0
#define IR2   1

 typedef struct
{
	
	INT16U  Nowcount;
	INT16U  Inttime ; //记录中断时间 
	INT16U  AABit; 
	INT8U  NowVoltage;
	INT8U  ReadIRBit;
	INT8U  ReadIRFlag;
	INT8U  ReadIRByte;
	    
	INT8U  ReadIR[4];
	INT8U  ReadIRData[12];//WT.EDIT [3]
	INT8U  ReadASTAR[6][2]; //
	INT8U  ReadOpenList[8];  //执行开发列表的值，
	INT8U  ReadCloseList[8];  //关闭列表值，不再执行，边界
	INT8U  Runcontrol;
	INT8U  ReadA_Time;   //WT.EDIT
	INT8U  Interrupt_IR2;   //WT.EDIT
	INT8U  BitHigh;
	INT8U  BitLow;
	INT8U  recordTime;
	INT8U  Timelock;
} ReadIRByte ;

KAKA_IR_EXT	 xdata ReadIRByte Remote1_ReadIR;



KAKA_IR_EXT void Init_IR();
KAKA_IR_EXT void Iint_T5(void);

//KAKA_IR_EXT void Remote1_Count(void);
//KAKA_IR_EXT void Remote11_Count(void); //WT.EIDT
KAKA_IR_EXT void Remote1_Count(void);


KAKA_IR_EXT void Read_Remote1IR(void);

KAKA_IR_EXT INT8U CheckHandsetIR();

KAKA_IR_EXT void Delay_ms(unsigned int fui_i);
KAKA_IR_EXT INT8U AutoBack_ChargeBatter(void);
KAKA_IR_EXT INT8U max4(INT8U a ,INT8U b ,INT8U c ,INT8U d);

#endif