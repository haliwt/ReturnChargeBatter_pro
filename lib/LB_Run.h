/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  LB_Run_h
#define  LB_Run_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"
#include "..\include\HC89F0541.h"

#endif


//ȫ�ֱ�������
#ifdef  KAKA_Run_GB
#define KAKA_Run_EXT
#else
#define  KAKA_Run_EXT extern
#endif
#define  GroundMin  3 //WT.EDIT //12

KAKA_Run_EXT  idata  INT16U RunMs;
KAKA_Run_EXT  idata  INT16U EdgeErrordelayTime;
KAKA_Run_EXT  idata  INT16U KeydelayTime;
KAKA_Run_EXT  idata  INT16U KeyclearTime;
KAKA_Run_EXT  idata  INT16U KeyRunTime;
KAKA_Run_EXT  idata  INT16U InterruptTime; //WT.EDIT
KAKA_Run_EXT  idata  INT16U RecoderTime; //WT.EDIT 



KAKA_Run_EXT  idata INT8U FanPersent;
KAKA_Run_EXT  idata INT8U EdgePersent;
KAKA_Run_EXT  idata INT8U ReadTimeOver;//WT.EDIT




KAKA_Run_EXT  outdata	INT8U  Gong_Step;
KAKA_Run_EXT  outdata	INT8U  Enter3;
KAKA_Run_EXT  idata INT8U Mode;
KAKA_Run_EXT  idata INT8U ModeBackup;
KAKA_Run_EXT  idata INT8U Step;
KAKA_Run_EXT  idata INT8U RunStep;
KAKA_Run_EXT  idata INT8U EdgeCurrentCount2;

KAKA_Run_EXT  idata INT8U Run100MSecond;

KAKA_Run_EXT idata INT8U  MidGroundOffSecond;
KAKA_Run_EXT idata INT16U ImpSecond;


KAKA_Run_EXT  idata INT8U  CurrentMax;
KAKA_Run_EXT  idata INT8U  IMPTime;
KAKA_Run_EXT  idata INT8U  EdgeTime;
KAKA_Run_EXT  idata INT8U  Imp2Time;
KAKA_Run_EXT  idata INT8U  Imp2Second;


KAKA_Run_EXT  idata INT8U IMP;
KAKA_Run_EXT idata INT16U RunSecond;

KAKA_Run_EXT idata INT8U GroundSecond;
KAKA_Run_EXT idata INT16U NoImpSecond;



KAKA_Run_EXT idata INT16U SysSecond;
KAKA_Run_EXT idata INT16U TestSecond;


KAKA_Run_EXT  void  CheckRun();
KAKA_Run_EXT  INT8U  LowVoltageFlag;
KAKA_Run_EXT  void CheckMode(INT8U Key);
KAKA_Run_EXT  void RunRandom_Mode(INT8U randomStep);

#endif