/**
  ******************************************************************************
  * @file    main.c
  * @author  Ұ��
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   emwin�ٶȲ��Գ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"

#include "GUI.h"
#include ".\lcd\bsp_ili9341_lcd.h"
#include ".\usart\bsp_usart.h"
#include ".\SysTick\bsp_SysTick.h"
#include ".\led\bsp_led.h"

#include "GUIDEMO.h"


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
  
  /* ��ʼ����ʱ�� */
	SysTick_Init();
	
	/*CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı��������ģ�����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	/* ��ʼ��GUI */
	GUI_Init();
	
	/* ��ʼ������ */
	USART_Config();
	
	printf("\r\n ********** emwin�ٶȲ��Գ���*********** \r\n"); 
	
 GUI_SetColor(GUI_WHITE);   
	/* ��ʾ���� */
	GUI_DispStringAt(" emWin Speed test Demo",10,10);
	GUI_Delay(2000);
   

	//��ֲ������ʱ��ע��Ҫ�������ļ��е�ջ�ռ����ô�һ��

	//emwin�ٷ�demo���޸�guidemo.h�ļ��еĺ��������ʾӦ��
	GUIDEMO_Main();


}


/*********************************************END OF FILE**********************/
