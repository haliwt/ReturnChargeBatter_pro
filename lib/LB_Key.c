#include "lb_key.h"
#include "lb_ir.h"


/****************************************************
	*
	*Function Name: uint8_t HDKey_Scan(uint8_t mode)
	*Function :
	*Inpute Ref: 0 ---不支持连续按键
	*Return Ref: 0 --没有按键按下， 1---有按键按下
	*
*****************************************************/
INT8U HDKey_Scan(INT8U Nmode)
{
	
		static INT8U  key_up=1;	 //°´¼üËÉ¿ª±êÖ¾
		if(Nmode==1)key_up=1;	// 支持连续按键
        if(key_up && POWER_KEY ==1 && WORKS_KEY ==1)
        {
            key_up =0 ;
			Delay_ms(20);
		   if(POWER_KEY ==1 && WORKS_KEY ==1)  return POWER_WORKS_PRES;
        }
        else if(key_up && POWER_KEY== 1)
		{
		    key_up =0 ;
			Delay_ms(20);
			if(POWER_KEY== 1 )  return POWER_PRES;
		
		}
        else if(key_up && WORKS_KEY==1)
        {

            key_up =0 ;
			Delay_ms(20);
			if(WORKS_KEY== 1 )  return WORKS_PRES;
        }
        else if(key_up && (POWER_KEY==0 &&  WORKS_PRES==0))key_up =0;
       
        return key_up;
		
}

