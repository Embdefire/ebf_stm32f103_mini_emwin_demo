/**
  ******************************************************************************
  * @file    main.c
  * @author  Ұ��
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   emwin ʹ��XBF����
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
#include ".\lcd\bsp_xpt2046_lcd.h"
#include ".\usart\bsp_usart.h"
#include ".\SysTick\bsp_SysTick.h"
#include ".\led\bsp_led.h"
#include "GUIFont_Port.h"   

#include "ff.h"


extern void Fatfs_MainTask(void);


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
	
	XPT2046_Init();
  
  /* ��ʼ����ʱ�� */
	SysTick_Init();
	
	/*CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı��������ģ�����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	/* ��ʼ��GUI */
	GUI_Init();
	
	/* ��ʼ������ */
	USART_Config();
	
	/* ���ڵ�����Ϣ */
	printf("emWin FatFs demo\r\n");
	
		//����XBF���壬ʹ��UTF8����
	Creat_XBF_Font();
	GUI_UC_SetEncodeUTF8();
	GUI_SetDefaultFont(&FONT_XINSONGTI_16);
	
	Fatfs_MainTask();


}


/*********************************************END OF FILE**********************/
