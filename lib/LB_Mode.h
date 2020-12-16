#ifndef __LB_MODE_H
#define __LB_MODE_H


#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"

#endif

//globle vaiable
//全局变量声明
#ifdef  KAKA_BOW_GB
#define KAKA_BOW_EXT
#else
#define  KAKA_BOW_EXT extern
#endif


typedef struct 
{
    INT8U PowerOnFlag ; //power on flag 
    INT8U ModeSelection; 
    INT8U OneRandomMode ;  //
    INT8U TwoBowMode;
    INT8U TreeeFixedPointMode;
}LB_Mode;

 KAKA_BOW_EXT LB_Mode idata imode;

KAKA_BOW_EXT void Mode_PowerOnStatus(void);

KAKA_BOW_EXT void Mode_WorksSelection(void);

 KAKA_BOW_EXT void Mode_OneRandomRun(void);

 KAKA_BOW_EXT void Mode_TwoBowRun(void);

KAKA_BOW_EXT void Mode_ThreeFixedPointRun(void);

//KAKA_Led_EXT void Mode_ThreeEdgewagsRun(void) ;

 KAKA_BOW_EXT void Mode_FourReChargeBatter(void);  //batter auto be recharge 











#endif 
