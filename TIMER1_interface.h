
#ifndef _TIMER1_INTERFACE_H
#define _TIMER1_INTERFACE_H

void TIMER1_voidSERVO_init(void);
void servo(u16 TIMER1_value);
void TIMER1_voidICU_init(void);
void TIMER1_voidICU_SetTriggerEdge(u8 Copy_u8ICUEdgeType);
u16 TIMER1_voidICU_GeTICUValue(void);
void TIMER1_voidICU_SetCallBack(void (*Copy_pFun) (void));
void TIMER1_voidICU_ClearTimer1Value(void);


#endif