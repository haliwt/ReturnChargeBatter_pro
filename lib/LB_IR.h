/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_IR_h
#define  LB_IR_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
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
	INT16U  Inttime ; //璁板綍涓柇鏃堕棿    
	INT8U  NowVoltage;
	INT8U  ReadIRBit;
	INT8U  ReadIRFlag;
	INT8U  ReadIRByte;
	INT8U  AABit;     
	INT8U  ReadIR[4];
	INT8U  ReadIRData[12];//WT.EDIT [3]
	INT8U  Runcontrol;
	INT8U  Interrupt_IR1;   //WT.EDIT
	INT8U  Interrupt_IR2;   //WT.EDIT
	INT8U  BitHigh;
	INT8U  BitLow;
} ReadIRByte ;

KAKA_IR_EXT	 xdata ReadIRByte Remote1_ReadIR;



KAKA_IR_EXT void Init_IR();
KAKA_IR_EXT void Iint_T5(void);

KAKA_IR_EXT void Remote1_Count(void);
KAKA_IR_EXT void Remote11_Count(void); //WT.EIDT
KAKA_IR_EXT void Remote12_Count(void); //WT.EIDT

KAKA_IR_EXT void Read_Remote1IR();
KAKA_IR_EXT void Read_Remote11IR(); //WT.EDIT
KAKA_IR_EXT void Read_Remote12IR(); //WT.EDIT

KAKA_IR_EXT INT8U CheckHandsetIR();

KAKA_IR_EXT void Delay_ms(unsigned int fui_i);

#endif