#ifndef __LB_KEY_H
#define __LB_KEY_H

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"
#include "..\include\HC89F0541.h"

#endif

//globle vaiable
#ifdef  KAKA_Key_GB
#define KAKA_Key_EXT
#else
#define  KAKA_Key_EXT extern
#endif

typedef INT8U uint8_t ;

#define  POWER_KEY    P0_0    //SW2 -input IO POWER KEY
#define  WORKS_KEY    P0_1    //SW1- works modes cycle KEY 

#define  POWER_PRES   0x01 
#define  WORKS_PRES   0x02
#define  POWER_WORKS_PRES    0x03  




KAKA_Key_EXT INT8U HDKey_Scan(INT8U mode);

#endif 