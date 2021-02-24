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
#define  WallMin 	30		//50

KAKA_Run_EXT  INT8U Mode;
KAKA_Run_EXT  INT8U Step;
KAKA_Run_EXT  INT8U RunMode;
KAKA_Run_EXT  INT8U RunStep;
KAKA_Run_EXT  INT8U SubRunStep;
KAKA_Run_EXT  INT8U ReceiveIR_Flag;
KAKA_Run_EXT  INT8U RunNoIRsenorTime;
KAKA_Run_EXT  INT8U RunNoIRsenorLastStep;
KAKA_Run_EXT  INT16U RunMs;
KAKA_Run_EXT  INT8U  EdgeTime;
KAKA_Run_EXT INT8U chargeflag;
KAKA_Run_EXT INT8U  TOP_impact; //impact top flag
KAKA_Run_EXT INT8U  TOP_Right;
KAKA_Run_EXT INT8U  TOP_Left;
KAKA_Run_EXT  INT8U BatteryRechargeFlag;//WT.EDIT
KAKA_Run_EXT  INT16U Imp2Time;
KAKA_Run_EXT  INT8U twinkle;  //WT.EDIT 
KAKA_Run_EXT  INT16U  Plugging;
KAKA_Run_EXT  INT8U  topir_flag;
KAKA_Run_EXT  INT8U  topir_left;
KAKA_Run_EXT  INT16U ImpSecond;
KAKA_Run_EXT  INT16U Imp2Second;

KAKA_Run_EXT  INT8U  CurrentMax;
KAKA_Run_EXT  INT16U WallSecond;
KAKA_Run_EXT  INT16U NoImpSecond;
KAKA_Run_EXT  INT16U battDetect1sFlag;
KAKA_Run_EXT  INT8U Run100MSecond;
KAKA_Run_EXT  INT8U MidWallOffSecond;
KAKA_Run_EXT  INT8U ModeStopTime; //WT.EDIT
KAKA_Run_EXT  idata INT16U RunSecond;
KAKA_Run_EXT  void  CheckRun();
KAKA_Run_EXT  INT8U  LowVoltageFlag;
KAKA_Run_EXT  void CheckMode(INT8U Key);
KAKA_Run_EXT  void InitSysclk(INT8U SYS);
KAKA_Run_EXT  void Delay_ms(INT16U fui_i);
KAKA_Run_EXT  void Auto_ReChargeBattery(void);
KAKA_Run_EXT   void CleanMode_BOW(void);
KAKA_Run_EXT   void CleanMode_Random(void);

//vic 2020.12.23 add
#define  WallModeMin 10
#define  WallModeNormal 30
#define  WallModeMax	50	
KAKA_Run_EXT void circleMode(void);
KAKA_Run_EXT void wallMode(void);

KAKA_Run_EXT INT8U T1msFlag;

//vic 2020.12.24
#define KEY1			P3_4//POWER_KEY  //WT.EDIT
#define KEY2			P3_5//MODES_KEY 
#define LED_R			P2_3
#define LED_G			P3_3
KAKA_Run_EXT INT8U SysFlag;

enum{
		IDEL = 0,
		CLEAN,
		FIND,
		BAT,
		BAT_FINISH,
		WALL,
		OVER
};

KAKA_Run_EXT void sysMode(INT8U val);
KAKA_Run_EXT void LedTip(INT8U state);
//vic 2020.12.25
KAKA_Run_EXT void rechargeBatMode(void);

KAKA_Run_EXT INT8U findRechargeFlag;
KAKA_Run_EXT INT8U wallRechargeModeFlag;   //特殊的沿墙模式，用来找充电座

KAKA_Run_EXT  INT8U  CheckTime;
KAKA_Run_EXT  INT8U  oldMode;
KAKA_Run_EXT 	INT8U lastMode;
KAKA_Run_EXT void getOutMode(void);
KAKA_Run_EXT void battVoltDetect(void);
#endif