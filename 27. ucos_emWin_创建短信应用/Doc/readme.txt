/*********************************************************************************************/

【*】 程序简介 
-工程名称：ucos_emWin_创建短信应用
-实验平台: 野火STM32 MINI 开发板
-MDK版本：5.16
-ST固件库版本：3.5.0
-emWin图形库版本：V5.32(STemWin1.2.0)


【 ！】功能简介：
增加短信应用的功能，

控制GSM模块发送短信

GSM板级驱动：bsp_gsm_usart.c、bsp_gsm_gprs.c

-应用界面的创建在MessageDLG.c文件中，点击图标后执行FUN_ICON5Clicked函数创建界面

-创建界面后在界面的回调函数_cbDialogMessage中执行各种响应操作


【 ！】实验操作：
连接好配套的3.2_2.8寸液晶屏，

连接好GSM模块,并给模块插入SIM卡：
	PA2<--->GSM_TXD
	PA3<--->GSM_RXD
	GND<--->GND

GSM模块需要使用DC电源供电。
给开发板上电并复位，点击短信应用，点击列表的To new 一栏可以发送新的短信


【*】注意事项：

-本应用对中文短信的电话号码支持不完善

/***************************************************************************************************************/

【*】 引脚分配

FLASH(W25Q64)：
FLASH芯片的SPI接口与STM32的SPI1相连。
		SCK	<--->PA5
		MISO<--->PA6
		MOSI<--->PA7
		CS	<--->PA4

液晶屏：
使用模拟时序产生8080时序与液晶屏驱动芯片ILI9341通讯.


		/*液晶控制信号线*/
		ILI9341_CS 	<--->	PC4      	//片选
		ILI9341_DC  <---> 	PC7			//选择输出命令还是数据
		ILI9341_WR 	<---> 	PC6			//写使能
		ILI9341_RD  <---> 	PC5			//读使能
		ILI9341_RST	<---> 	NRST		//STM32的复位引脚，上电同时复位液晶
		ILI9341_BK 	<---> 	PD2 		//背光引脚
		
		ILI9341_D0~D15 <---> PB0~PB15
		
触摸屏：
触摸屏控制芯片XPT2046与STM32的普通GPIO相连，使用模拟SPI进行通讯。
		XPT2046_SCK		<--->PE0
		XPT2046_MISO	<--->PE3
		XPT2046_MOSI	<--->PE2
		XPT2046_CS		<--->PD13
		
		XPT2046_PENIRQ	<--->PE4	//触摸信号，低电平表示有触摸

串口(TTL-USB TO USART)：
CH340的收发引脚与STM32的发收引脚相连。
	RX<--->PA9
	TX<--->PA10
	
/*********************************************************************************************/


/*********************************************************************************************/

【*】 版本

-程序版本：1.0
-发布日期：2017-06

-版本更新说明：首次发布

/*********************************************************************************************/

【*】 联系我们

-野火论坛    :http://www.firebbs.cn
-淘宝店铺    :https://fire-stm32.taobao.com

/*********************************************************************************************/