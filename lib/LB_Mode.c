

//#define  KAKA_Mode_GB
#define  KAKA_BOW_GB
#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Mode.h"
#include "LB_Run.h"
#include "LB_Led.h"


#endif

/*******************************************************************
     * 
     * Function Name:  void Mode_OnePowerOnStatus(void)
     * Function Name : power on intial reference
     * Input Ref: NO
     * Return Ref: NO
     * 
********************************************************************/
 void Mode_PowerOnStatus(void)
 {
    static INT8U keypower;
    keypower = keypower ^ 0x01;
    if(keypower ==1){
       imode.PowerOnFlag =1;
       LedGreenON(); 
    }
    else{
       LedGreenOff();
       imode.PowerOnFlag = 0;
    }
}
/*******************************************************************
     * 
     * Function Name:  void Mode_WorksSelected(void)
     * Function Name : power on intial reference
     * Input Ref: NO
     * Return Ref: NO
     * 
********************************************************************/
void Mode_WorksSelection(void)
{
    
   if(imode.PowerOnFlag ==1){ //power on status is ON
        imode.ModeSelection ++ ; 
        if(imode.ModeSelection==1){
            imode.OneRandomMode =1;
            imode.TwoBowMode =0;
            imode.TreeeFixedPointMode =0;
        } 
        else if(imode.ModeSelection==2){
             imode.TwoBowMode =1;
             imode.OneRandomMode =0;
             imode.TreeeFixedPointMode =0;
        } 
        if(imode.ModeSelection==3){
            imode.TreeeFixedPointMode =1;
             imode.TwoBowMode =0;
            imode.OneRandomMode =0;
        }     
    }
}
/*******************************************************************
     * 
     * Function Name:  void Mode_OneRandonRun(void)
     * Function Name : robot run of random run
     * Input Ref: NO
     * Return Ref: NO
     * 
********************************************************************/
void Mode_OneRandomRun(void)
{
    if(imode.OneRandomMode ==1){

        RunRandom_Mode(1)  ;   
       

    }
}
/*******************************************************************
     * 
     * Function Name:  void Mode_ThreeFixedPointRun(void)
     * Function Name :
     * Input Ref: NO
     * Return Ref: NO
     * 
********************************************************************/
void Mode_ThreeFixedPointRun(void)
{
      
}