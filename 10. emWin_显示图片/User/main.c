/**
  ******************************************************************************
  * @file    main.c
  * @author  Ұ��
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   emwin ��ʾͼƬ
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
#include ".\key\bsp_key.h"  
#include "GUIFont_Port.h"   

#include "ff.h"

#include "GUIFont_Port.h"   

FATFS fs;													/* Work area (file system object) for logical drives */


extern void drawbmp(void);
extern void drawJPEG(void);
extern void drawpng(void);
extern void drawgif(void);


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{		
	
	GUI_RECT info_text ={0,100,240,200};
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
	
	Key_GPIO_Config();
	
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
	printf("emWin picture demo\r\n");
	
		//����XBF���壬ʹ��UTF8����
	Creat_XBF_Font();
	GUI_UC_SetEncodeUTF8();
	GUI_SetDefaultFont(&FONT_XINSONGTI_16);
	
	GUI_SetBkColor(GUI_WHITE);
  GUI_Clear(); 
  GUI_SetFont(GUI_FONT_8X16_ASCII);
  GUI_SetColor(GUI_BLUE);
	
	info_text.x0 = 10;
	info_text.x1 = 240-10;
	info_text.y0 = 100;
	info_text.y1 = 200;

	GUI_DispStringInRectWrap("Press 'KEY1' to show BMP format picture",
															&info_text,
															GUI_TA_CENTER,
															GUI_WRAPMODE_WORD) ;
	
	//�����ļ�ϵͳ�������ȹ����ļ�ϵͳ����ʾ�ļ�ϵͳ�е�ͼƬ	
	f_mount(&fs,"1:",1);	
	
	while(1)
	{	
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
		{
			drawbmp();

			LED2_TOGGLE;
		}   
    
	  GUI_Delay(10);
	}


}


/*********************************************END OF FILE**********************/
