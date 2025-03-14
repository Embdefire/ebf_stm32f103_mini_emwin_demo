/**
  ******************************************************************************
  * @file    PictureApp.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   演示如何显示图片
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 MINI 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "includes.h"
#include "desktop.h"



static void _cbMidWin(WM_MESSAGE * pMsg) ;
static void CreateMidWin(void);
static void CreateTopWin(void);


WIN_PARA WinPara;			//用户使用的窗口额外数据

/* 用于桌面ICONVIEW0图标的创建 */
static const BITMAP_ITEM _aBitmapItem[] = 
{
#if 0 //调试时，都使用同一个图标，可节省程序下载时间
	{&bmIdea,              "LED"},
	{&bmIdea,              "LED"},
	{&bmIdea,              "LED"},
	{&bmIdea,              "LED"},
  {&bmIdea,              "LED"},
  {&bmIdea,              "LED"},
  {&bmIdea,              "LED"},
  {&bmIdea,              "LED"},
//  {&bmIdea,              "LED"},

#elif (ICON_NAME_FORMAT == ICON_NAME_EN)
	//纯英文图标字符
  {&bmIdea,              "LED"},
	{&bmADC,              "ADC"},
	{&bmWeather,     	    "Weather"}, 
	{&bmClock,              "Clock"},
	{&bmPhone,  	 	        "Phone"},    
	{&bmMessages,  	 	   "Messages"},
	{&bmUSB,  	              "USB"},   	
	{&bmCalculator,    "Calculator"}, 

#elif (ICON_NAME_FORMAT == ICON_NAME_CH_GBK)
	//中文GBK编码字符
	{&bmIdea,              "LED"},
	{&bmADC,              "ADC"},
	{&bmWeather,     	    "天气"}, 
	{&bmClock,              "时钟"},
	{&bmPhone,  	 	        "电话"},    
	{&bmMessages,  	 	   "短信"},
	{&bmUSB,  	              "USB"},   	
	{&bmCalculator,    "计算器"}, 	
#elif (ICON_NAME_FORMAT == ICON_NAME_CH_UTF8)
	//中文UTF8编码，可以使用工程目录下的“U2C.exe”工具转换
	{&bmIdea,              "LED"},
	{&bmADC,              "ADC"},
	{&bmWeather,     	    "\xe5\xa4\xa9\xe6\xb0\x94"},   
	{&bmClock,              "\xe6\x97\xb6\xe9\x92\x9f"},  
	{&bmPhone,  	 	        "\xe7\x94\xb5\xe8\xaf\x9d"},    
	{&bmMessages,  	 	   "\xe7\x9f\xad\xe4\xbf\xa1"},
	{&bmUSB,  	              "USB"},   	
	{&bmCalculator,    "\xe8\xae\xa1\xe7\xae\x97\xe5\x99\xa8"},
#endif
};


uint8_t UserApp_Running=0;

uint8_t ICON_Clicked[12]   = {0};   /* ICONVIEW控件按下的标志，0表示未按下，1表示按下 */

/*时间结构体*/
extern struct rtc_time systmtime;


/*点击图标后执行的函数*/
extern void FUN_ICON0Clicked(void); 
extern void FUN_ICON1Clicked(void);  
extern void FUN_ICON2Clicked(void);  
extern void FUN_ICON3Clicked(void);  
extern void FUN_ICON4Clicked(void);  
//void FUN_ICON4Clicked(void)  {printf("FUN_ICON5Clicked\n");}
extern void FUN_ICON5Clicked(void);  
//void FUN_ICON5Clicked(void)  {printf("FUN_ICON5Clicked\n");}
extern void FUN_ICON6Clicked(void);  
//void FUN_ICON6Clicked(void)  {printf("FUN_ICON5Clicked\n");}
extern void FUN_ICON7Clicked(void);  

void FUN_ICON8Clicked(void)  {printf("FUN_ICON8Clicked\n");}
void FUN_ICON9Clicked(void)  {printf("FUN_ICON9Clicked\n");}
void FUN_ICON10Clicked(void) {printf("FUN_ICON10Clicked\n");}
void FUN_ICON11Clicked(void) {printf("FUN_ICON11Clicked\n");}

void FUN_ICON12Clicked(void) {printf("FUN_ICON12Clicked\n");}


/**
  * @brief  CreateTopWin，创建顶部的窗口
  * @param  none
  * @retval none
  */
static void CreateTopWin(void)
{
	WM_HWIN hText;
	/* 顶部的 "BH-MINI"文本 */
	hText = TEXT_CreateEx(0, 0, 200 , WinPara.yPosWin, WM_HBKWIN, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_LEFT|TEXT_CF_VCENTER, GUI_ID_TEXT0, "");
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);
	TEXT_SetText(hText,"BH-MINI");
	TEXT_SetTextColor(hText,STATUS_TEXT_COLOR);
	
	/* 状态栏的时间显示文本 */
	hText = TEXT_CreateEx(WinPara.xSizeLCD/2-50,0,100,WinPara.yPosWin,
													WM_HBKWIN,WM_CF_SHOW|WM_CF_MEMDEV,
													GUI_TA_HCENTER|TEXT_CF_VCENTER,
													GUI_ID_TEXT1,
													"11:56:00");
	
	//TEXT_SetBkColor(hText,GUI_INVALID_COLOR);
	TEXT_SetTextColor(hText,STATUS_TEXT_COLOR);
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);
  	/* 状态栏的时间显示文本 */
	hText = TEXT_CreateEx(WinPara.xSizeLCD-200,0,200,WinPara.yPosWin,
													WM_HBKWIN,WM_CF_SHOW|WM_CF_MEMDEV,
													GUI_TA_RIGHT|TEXT_CF_VCENTER,
													GUI_ID_STATUS_CPU_USAGE,
													"CPU: 10%");
													
	//TEXT_SetBkColor(hText,GUI_INVALID_COLOR);
	TEXT_SetTextColor(hText,STATUS_TEXT_COLOR);
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);
}



/**
  * @brief  CreateMidWin，创建中间的窗口
  * @param  none
  * @retval none
  */
static void CreateMidWin(void)
{
	uint8_t i=0;
	WM_HWIN MIDWIN;
	
#if (ICON_NAME_FORMAT == ICON_NAME_CH_GBK)
	//存储转换成utf8的中文，注意长度，按中文每个字4字节算
  char utf8_pText[20];	
#endif
	
	WinPara.hWinMid= WM_CreateWindowAsChild(
											WinPara.xPosWin,											
											WinPara.yPosWin,
											WinPara.xSizeWin,
											WinPara.ySizeWin,	
											WM_HBKWIN, 
											WM_CF_SHOW|WM_CF_MEMDEV,
											_cbMidWin, 
											sizeof(WIN_PARA *)
											);
/*-------------------------------------------------------------------------------------*/
					/*在指定位置创建指定尺寸的ICONVIEW1 小工具*/
					MIDWIN=ICONVIEW_CreateEx(
											 ICONVIEW_XPos, 					          /* 小工具的最左像素（在父坐标中）*/
											 ICONVIEW_YPos, 								     /* 小工具的最上像素（在父坐标中）*/
											 WinPara.xSizeWin-ICONVIEW_XPos,	  /* 小工具的水平尺寸（单位：像素）*/
											 WinPara.ySizeWin - ICONVIEW_YPos , 			      /* 小工具的垂直尺寸（单位：像素）*/
											 WinPara.hWinMid, 				          /* 父窗口的句柄。如果为0 ，则新小工具将成为桌面（顶级窗口）的子窗口 */
											 WM_CF_SHOW|WM_CF_MEMDEV|WM_CF_HASTRANS,         /* 窗口创建标记。为使小工具立即可见，通常使用 WM_CF_SHOW */ 
											 0,//ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* 默认是0，如果不够显示可设置增减垂直滚动条 */
											 GUI_ID_ICONVIEW0, 			            /* 小工具的窗口ID */
											 ICONVIEW_Width, 				            /* 图标的水平尺寸 */
											 ICONVIEW_Height+20);				        /* 图标的垂直尺寸 */
		GUI_Delay(20);
									 
		/* 向ICONVIEW 小工具添加新图标 */
		for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) 
		{
			#if (ICON_NAME_FORMAT == ICON_NAME_CH_GBK)
				//GBK字符转UTF8
				COM_gbk2utf8(_aBitmapItem[i].pText,utf8_pText);
				ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem[i].pBitmap,utf8_pText);			
			#else
				//直接使用字符
				ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem[i].pBitmap,_aBitmapItem[i].pText);
			#endif			
		}		
		

		/* 设置小工具的背景色 32 位颜色值的前8 位可用于alpha混合处理效果*/
		ICONVIEW_SetBkColor(MIDWIN, ICONVIEW_CI_SEL, ICON_COLOR | 0x80000000);

		/* 设置字体 */
#if (ICON_NAME_FORMAT == ICON_NAME_CH_GBK || ICON_NAME_FORMAT == ICON_NAME_CH_UTF8)
		/* 中文字体 */
		ICONVIEW_SetFont(MIDWIN, &FONT_XINSONGTI_16);
#elif (ICON_NAME_FORMAT == ICON_NAME_EN)
		/* 纯英文字体（直接使用中文字体也是可以的） */
		ICONVIEW_SetFont(MIDWIN, GUI_FONT_10_ASCII);
#endif
		
		/* 设置初始选择的图标为 -1 (表示尚未选择)*/
		ICONVIEW_SetSel(MIDWIN,-1);
		/* 设置图标在x 或y 方向上的间距。*/
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, ICONVIEW_XSpace);
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, ICONVIEW_YSpace);
		/* 设置对齐方式 在5.22版本中最新加入的 */
		ICONVIEW_SetIconAlign(MIDWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
		
/*-------------------------------------------------------------------------------------*/
}

/**
  * @brief  回调函数，中间窗口的回调函数，处理触摸、重绘等消息
	* @param  pMsg:包含WM_MESSAGE数据的内容
  * @retval none
  */
static void _cbMidWin(WM_MESSAGE * pMsg) 
{
	int NCode, Id;
		
	//指示当前图标是否被按下
	static uint8_t selecting = 0;

	switch (pMsg->MsgId) 
	{
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) 
			{
				case GUI_ID_ICONVIEW0:
					switch (NCode) 
					{
						case WM_NOTIFICATION_MOVED_OUT:
							selecting =0;
							WM_InvalidateWindow(pMsg->hWin);
							break;
						
						/* ICON控件点击消息 */
						case WM_NOTIFICATION_CLICKED:
							selecting =1;
							break;
						
						/* ICON控件释放消息 */
						case WM_NOTIFICATION_RELEASED: 
              UserApp_Running=1;
							
							selecting =0;
							WM_InvalidateWindow(pMsg->hWin);
						
							/* 打开相应选项 */
							switch(ICONVIEW_GetSel(pMsg->hWinSrc))
							{
								
								/* RGBLED *******************************************************************/
								case 0:	
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;

									FUN_ICON0Clicked();			
									break;	
								
								/* Music ***********************************************************************/
								case 1:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;

									FUN_ICON1Clicked();
									break;
								
								/* Recorder *********************************************************************/
								case 2:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON2Clicked();	
									break;
								
								/* Weather *******************************************************************/
								case 3:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON3Clicked();
									break;
								
								/* Compass  ******************************************************************/
								case 4:	
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON4Clicked();            
									break;	
								
								/* Clock ***********************************************************************/
								case 5:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON5Clicked();
									break;
								
								/* Safari *********************************************************************/
								case 6:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
 									FUN_ICON6Clicked();	
									break;
								
								/* Camera ********************************************************************/
								case 7:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON7Clicked();
                  GUI_Delay(50);
									break;
								
								/* Phone **********************************************************************/
								case 8:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON8Clicked();
									break;
								
								/* Message ********************************************************************/
								case 9:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON9Clicked();
									break;
								
								/* Photos ******************************************************************/
								case 10:					
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON10Clicked();
									break;
								
								/* USB *******************************************************************/
								case 11:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON11Clicked();
									break;		
								/* Calculator *******************************************************************/
								case 12:
									//记录图标被按下的标志
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON12Clicked();
									break;                           
								}
							 break;
						}
					break;
			}
			break;
			
		/* 重绘消息*/
		case WM_PAINT:
			{
				GUI_SetBkColor(DTCOLOR);
				GUI_Clear();
				
				//若图标不是被按下，选择为-1项图标，以清空图标的选中框
				if(selecting == 0)
		       ICONVIEW_SetSel(WM_GetDialogItem(WinPara.hWinMid, GUI_ID_ICONVIEW0),-1);

			}			
		break;			

	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/**
  * @brief  根据bsp初始化的标志检查并输出错误信息
  * @param  无  
  * @retval 无
  */
void emWinMainApp(void)
{
	
	
	  GUI_Delay(1);

}
	

/*
*********************************************************************************************************
*	函 数 名: _cbBkWindow
*	功能说明: 桌面窗口的回调函数 
*	形    参：WM_MESSAGE * pMsg
*	返 回 值: 无
*********************************************************************************************************
*/
void _cbBkWindow(WM_MESSAGE * pMsg) 
{
	char text_buffer[20]={0};
	WM_HWIN hItem;

	switch (pMsg->MsgId) 
	{
		/* 重绘消息*/
		case WM_PAINT:		
				GUI_SetBkColor(DTCOLOR);
				GUI_Clear();	
//        ICONVIEW_SetSel(WM_GetDialogItem(WinPara.hWinMid, GUI_ID_ICONVIEW0),-1);
		break;
		
		case WM_TIMER:
					if(UserApp_Running==1)
					{
						WM_RestartTimer(pMsg->Data.v, 1000);
						break; 
					}    
				
				if(!(bsp_result&BSP_RTC))
				{					
					/* 转换rtc值至北京时间*/
					RTC_TimeCovr(&systmtime);

					sprintf(text_buffer,"%02d:%02d:%02d",systmtime.tm_hour,systmtime.tm_min,systmtime.tm_sec);
					TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text_buffer);
				}			

			
				hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_STATUS_CPU_USAGE);
				//检测句柄是否存在
				if(hItem != 0)
				{
					sprintf(text_buffer,"CPU:% 2d%%",(uint8_t)(OSStatTaskCPUUsage/100));
					TEXT_SetText(hItem,text_buffer);
					WM_RestartTimer(pMsg->Data.v, 500);
				}
			break;
	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/**
* @brief  任务函数，显示GUI的桌面
* @param  无  
* @retval 无
*/
void  AppTaskDesktop (void  )
{
	GUI_SetColor(GUI_WHITE);
  GUI_SetFont(GUI_FONT_20B_ASCII);
  GUI_DispStringHCenterAt("Starting...\nWait a moment",120,50);
  GUI_Delay(50);
	
	//准备建立2个窗口，以下是使用到的用户定义参数，方便在回调函数中使用
	WinPara.xSizeLCD = LCD_GetXSize();				            //LCD屏幕尺寸
	WinPara.ySizeLCD = LCD_GetYSize();				            //LCD屏幕尺寸
	WinPara.xPosWin	 = MIDWIN_xPos;							          //窗口的起始位置
	WinPara.yPosWin  = MIDWIN_yPos;							          //窗口的起始位置
	WinPara.xSizeWin = WinPara.xSizeLCD;						      //窗口尺寸
	WinPara.ySizeWin = WinPara.ySizeLCD-WinPara.yPosWin;	//窗口尺寸

	//使用FLEX皮肤
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);

	//背景窗口回调函数
	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
	//创建窗口定时器，以定时更新CPU使用率信息
	WM_CreateTimer(WM_HBKWIN, 0, 500, 0);


	/* 创建窗口 状态栏、主窗口*/
	CreateTopWin();
	CreateMidWin();

  while(1)
  {			
    emWinMainApp();
  }
}

/*********************************************END OF FILE**********************/

