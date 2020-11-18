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

 typedef struct
{
	INT8U  NowVoltage;
	INT16U  Nowcount;//INT8U  Nowcount;
	INT8U  ReadIRBit;
	INT8U  ReadIRFlag;
	INT8U  ReadIRByte;
	INT8U  AABit;     
	INT8U  ReadIR[4];
	INT16U  ReadIRData[3];//INT8U  ReadIRData[3];
	INT8U  Runcontrol;
} ReadIRByte ;

KAKA_IR_EXT	 xdata ReadIRByte Remote1_ReadIR;



KAKA_IR_EXT void Init_IR();

KAKA_IR_EXT void Remote1_Count(void);
KAKA_IR_EXT void Read_Remote1IR();

KAKA_IR_EXT INT8U CheckHandsetIR();
KAKA_IR_EXT void CheckXReadIR(ReadIRByte *P); //WT.EDIT
KAKA_IR_EXT void Delay_ms(unsigned int fui_i);

#endif