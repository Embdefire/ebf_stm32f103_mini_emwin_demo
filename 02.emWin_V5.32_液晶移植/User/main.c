/**
  ******************************************************************************
  * @file    main.c
  * @author  Ұ��
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   emWin��������������
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



/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	int i=0;
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
  
  /* ��ʼ����ʱ�� */
	SysTick_Init();
	
	/*CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı��������ģ�����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	/* ��ʼ��GUI */
  ILI9341_Init(); /* ��ǰ��ʼ��LCD��������GUI_Init����LCD_X_Config֮ǰȷ��LCD����оƬID: lcdid */
	GUI_Init();
	
	/* ��ʼ������ */
	USART_Config();
	
	/* ���ڵ�����Ϣ */
	printf("\r\n **********  emwin������ʾ����*********** \r\n"); 
	printf("\r\n ������֧������ \r\n"); 

	
	/* ��ʾ���� */
	GUI_DispStringAt("wildfire MINI board emWin test!",10,10);
	GUI_Delay(100);
	
	/* ����2��ʹ�ù̼������IO */
	while (1)
	{
			GUI_DispDecAt(i++,50,50,4);
			if(i>9999)
				i=0;
	}

}


/*********************************************END OF FILE**********************/
