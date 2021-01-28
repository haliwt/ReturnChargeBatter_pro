/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  LB_AD_h
#define  LB_AD_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"
#include "..\include\HC89F0541.h"

#endif


//ȫ�ֱ�������
#ifdef  KAKA_AD_GB
#define KAKA_AD_EXT
#else
#define  KAKA_AD_EXT extern
#endif
KAKA_AD_EXT INT8U ADCtl;
KAKA_AD_EXT INT8U ADTime;
KAKA_AD_EXT INT8U ADFlag;

KAKA_AD_EXT INT8U ADFlashFlag;

KAKA_AD_EXT INT16U AD5ms[9];

KAKA_AD_EXT  INT8U  WallAD[4][2];
KAKA_AD_EXT  INT8U outdata  WallAD100Ms[4][8];
KAKA_AD_EXT INT16U outdata LCurrentAD[8];
KAKA_AD_EXT INT16U outdata RCurrentAD[8];
KAKA_AD_EXT INT16U outdata FanCurrentAD[8];
KAKA_AD_EXT INT16U outdata EdgeCurrentAD[8];
KAKA_AD_EXT INT16U outdata BatteryAD[9];
KAKA_AD_EXT INT8U WallDp[4];
KAKA_AD_EXT INT8U  outdata  LCurrent;
KAKA_AD_EXT INT8U  outdata  RCurrent;
KAKA_AD_EXT INT8U  Battery_LowVoltage;
KAKA_AD_EXT INT8U  Battery_HigVoltage;
KAKA_AD_EXT INT16U  LCurrentMax;
KAKA_AD_EXT INT16U  RCurrentMax;
KAKA_AD_EXT INT16U  FanCurrent;
KAKA_AD_EXT INT16U  EdgeCurrent;
KAKA_AD_EXT INT16U  EdgeCurrentCount;
KAKA_AD_EXT INT16U  Voltage;
KAKA_AD_EXT INT16U  EdgeCurrentLessCount;
KAKA_AD_EXT INT16U  Battery_Voltage;

KAKA_AD_EXT INT16U  EdgeCurrentOverCount;
KAKA_AD_EXT	void InitADIO(void);

KAKA_AD_EXT	void ReadAD5ms();
KAKA_AD_EXT	void ReadADAvg();
KAKA_AD_EXT	void CheckLCurrent();
KAKA_AD_EXT	void CheckRCurrent();
KAKA_AD_EXT	void CheckVoltage();
KAKA_AD_EXT	void CheckWall();
KAKA_AD_EXT  void CheckEdgeCurrent()	;
KAKA_AD_EXT  void CheckFanCurrent();
KAKA_AD_EXT  void BatteryLowVoltage_Detection(void);//WT.EDIT 2021.01.10
#endif