/**
  ******************************************************************************
  * @file    main.c
  * @author  野火
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   emWin基础例程主函数
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	int i=0;
	/* LED 端口初始化 */
	LED_GPIO_Config();	
  
  /* 初始化定时器 */
	SysTick_Init();
	
	/*CRC和emWin没有关系，只是他们为了库的保护而做的，这样STemWin的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	/* 初始化GUI */
  ILI9341_Init(); /* 提前初始化LCD驱动，在GUI_Init调用LCD_X_Config之前确认LCD驱动芯片ID: lcdid */
	GUI_Init();
	
	/* 初始化串口 */
	USART_Config();
	
	/* 串口调试信息 */
	printf("\r\n **********  emwin基础显示例程*********** \r\n"); 
	printf("\r\n 本程序不支持中文 \r\n"); 

	
	/* 显示测试 */
	GUI_DispStringAt("wildfire MINI board emWin test!",10,10);
	GUI_Delay(100);
	
	/* 方法2，使用固件库控制IO */
	while (1)
	{
			GUI_DispDecAt(i++,50,50,4);
			if(i>9999)
				i=0;
	}

}


/*********************************************END OF FILE**********************/
