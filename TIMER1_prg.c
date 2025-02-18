/****************************************************************************************************************************/
/***************** Author : Abdelrhman Rabie **********************************************************************************/
/***************** File :  TIMER1.c ***********************************************************************************/
/***************** Date : 20/11/2022  ***************************************************************************************/
/***************** Version : 2.0  *******************************************************************************************/
/***************** Description : Drive For TIMER1 (SERVO -- ICU) ****************************************************************************/
/****************************************************************************************************************************/

#include "LSTD_Types.h"
#include "LUTILS.h"
#include "TIMER1_private.h"
#include "TIMER1_cfg.h"
#include "TIMER1_interface.h"
/*************************************************************************************************************************************
 *                                                           SERVO Timer 1                                                             *
 **************************************************************************************************************************************/
void TIMER1_voidSERVO_init(void)
{
	L_UTILS_SET_BIT(TCCR1A_Register,1);
	L_UTILS_CLEAR_BIT(TCCR1A_Register,0);
	L_UTILS_SET_BIT(TCCR1A_Register,7);
	L_UTILS_CLEAR_BIT(TCCR1A_Register,6);

	L_UTILS_SET_BIT(TCCR1B_Register,4);
	L_UTILS_SET_BIT(TCCR1B_Register,3);
	L_UTILS_SET_BIT(TCCR1B_Register,1);
	L_UTILS_CLEAR_BIT(TCCR1B_Register,0);
	L_UTILS_CLEAR_BIT(TCCR1B_Register,2);
	L_UTILS_CLEAR_BIT(TCCR1B_Register,5);


	ICR1H_Register =(u8)(20000>>8);
	ICR1L_Register = (u8)(20000);
}
void servo(u16 TIMER1_value)
{
	OCR1AH_Register=(u8)(TIMER1_value>>8);
	OCR1AL_Register=(u8)TIMER1_value;

}
/*************************************************************************************************************************************
 *                                                           ICU Timer 1                                                             *
 **************************************************************************************************************************************/
static void(*Timer1_pICUSetCallBack)(void);
/************************************************************************************************************************************/
void TIMER1_voidICU_init(void)
{
	 L_UTILS_SET_BIT(TCCR1B_Register,6);
	 L_UTILS_SET_BIT(TIMSK_Register,5);

	 L_UTILS_CLEAR_BIT(TCCR1B_Register,0);
	 L_UTILS_SET_BIT(TCCR1B_Register,1);
	 L_UTILS_CLEAR_BIT(TCCR1B_Register,2);
}
void TIMER1_voidICU_SetTriggerEdge(u8 Copy_u8ICUEdgeType)
{
   if(Copy_u8ICUEdgeType==RISING_EDGY)
   {
	  L_UTILS_SET_BIT(TCCR1B_Register,6);
   }
   else if(Copy_u8ICUEdgeType==FALLING_EDGY)
   {
	  L_UTILS_CLEAR_BIT(TCCR1B_Register,6);
   }
}
u16 TIMER1_voidICU_GeTICUValue(void)
{
	 return ICR1_Register;
}
void TIMER1_voidICU_SetCallBack(void (*Copy_pFun) (void))
{
	 Timer1_pICUSetCallBack = Copy_pFun;
}
void TIMER1_voidICU_ClearTimer1Value(void)
{
	 TCNT1_Register = 0;
}
void __vector_6 (void)
{
	if (Timer1_pICUSetCallBack!=0)
	{
		Timer1_pICUSetCallBack();
	}
}
