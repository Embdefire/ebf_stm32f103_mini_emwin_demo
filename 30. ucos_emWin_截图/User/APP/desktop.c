/**
  ******************************************************************************
  * @file    PictureApp.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��ʾ�����ʾͼƬ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 MINI ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "includes.h"
#include "desktop.h"



static void _cbMidWin(WM_MESSAGE * pMsg) ;
static void CreateMidWin(void);
static void CreateTopWin(void);


WIN_PARA WinPara;			//�û�ʹ�õĴ��ڶ�������

/* ��������ICONVIEW0ͼ��Ĵ��� */
static const BITMAP_ITEM _aBitmapItem[] = 
{
#if 0 //����ʱ����ʹ��ͬһ��ͼ�꣬�ɽ�ʡ��������ʱ��
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
	//��Ӣ��ͼ���ַ�
  {&bmIdea,              "LED"},
	{&bmADC,              "ADC"},
	{&bmWeather,     	    "Weather"}, 
	{&bmClock,              "Clock"},
	{&bmPhone,  	 	        "Phone"},    
	{&bmMessages,  	 	   "Messages"},
	{&bmUSB,  	              "USB"},   	
	{&bmCalculator,    "Calculator"}, 

#elif (ICON_NAME_FORMAT == ICON_NAME_CH_GBK)
	//����GBK�����ַ�
	{&bmIdea,              "LED"},
	{&bmADC,              "ADC"},
	{&bmWeather,     	    "����"}, 
	{&bmClock,              "ʱ��"},
	{&bmPhone,  	 	        "�绰"},    
	{&bmMessages,  	 	   "����"},
	{&bmUSB,  	              "USB"},   	
	{&bmCalculator,    "������"}, 	
#elif (ICON_NAME_FORMAT == ICON_NAME_CH_UTF8)
	//����UTF8���룬����ʹ�ù���Ŀ¼�µġ�U2C.exe������ת��
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

uint8_t ICON_Clicked[12]   = {0};   /* ICONVIEW�ؼ����µı�־��0��ʾδ���£�1��ʾ���� */

/*ʱ��ṹ��*/
extern struct rtc_time systmtime;


/*���ͼ���ִ�еĺ���*/
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
  * @brief  CreateTopWin�����������Ĵ���
  * @param  none
  * @retval none
  */
static void CreateTopWin(void)
{
	WM_HWIN hText;
	/* ������ "BH-MINI"�ı� */
	hText = TEXT_CreateEx(0, 0, 200 , 20, WM_HBKWIN, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_LEFT|TEXT_CF_VCENTER, GUI_ID_TEXT0, "");
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);
	TEXT_SetText(hText,"BH-MINI");
	TEXT_SetTextColor(hText,STATUS_TEXT_COLOR);
	
	/* ״̬����ʱ����ʾ�ı� */
//	hText = TEXT_CreateEx(WinPara.xSizeLCD/2-50,0,100,WinPara.yPosWin,
//													WM_HBKWIN,WM_CF_SHOW|WM_CF_MEMDEV,
//													GUI_TA_HCENTER|TEXT_CF_VCENTER,
//													GUI_ID_TEXT1,
//													"11:56:00");
//	
//	//TEXT_SetBkColor(hText,GUI_INVALID_COLOR);
//	TEXT_SetTextColor(hText,STATUS_TEXT_COLOR);
//	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);
	
  	/* ״̬����CPU��ʾ�ı� */
	hText = TEXT_CreateEx(WinPara.xSizeLCD-200,0,200,20,
													WM_HBKWIN,WM_CF_SHOW|WM_CF_MEMDEV,
													GUI_TA_RIGHT|TEXT_CF_VCENTER,
													GUI_ID_STATUS_CPU_USAGE,
													"CPU: 10%");
													
	//TEXT_SetBkColor(hText,GUI_INVALID_COLOR);
	TEXT_SetTextColor(hText,STATUS_TEXT_COLOR);
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);
}




/*
*********************************************************************************************************
*	�� �� ��: _cbTimeWin
*	����˵��: ʱ����ʾ���ڵĻص����� 
*	��    �Σ�WM_MESSAGE * pMsg
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void _cbTimeWin(WM_MESSAGE * pMsg) 
{
	char text_buffer[40]={0};

	switch (pMsg->MsgId) 
	{

		/* �ػ���Ϣ*/
		case WM_PAINT:	
			
					GUI_SetBkColor(GUI_DARKGRAY);

					GUI_Clear();	

		break;
		
		case WM_TIMER:		
				if(UserApp_Running==1)
				{
					WM_RestartTimer(pMsg->Data.v, 1000);
					break; 
				}   
				if(!(bsp_result&BSP_RTC))
				{
					/* ת��rtcֵ������ʱ��*/
					RTC_TimeCovr(&systmtime);
					
					//ʱ����
//					sprintf(text_buffer,"%02d:%02d:%02d",systmtime.tm_hour,systmtime.tm_min,systmtime.tm_sec);
					
					//ʱ��
					sprintf(text_buffer,"%02d:%02d",systmtime.tm_hour,systmtime.tm_min);

//					TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text_buffer);				
				
					//ѡ�������ǰ����
					WM_SelectWindow(pMsg->hWin);
				
					GUI_SetColor(GUI_WHITE);
					GUI_SetBkColor(GUI_DARKGRAY);
//					GUI_Clear();	

					GUI_SetFont(GUI_FONT_D24X32);
					GUI_DispStringHCenterAt(text_buffer,TIMEWIN_xSize/2,8);
					
					//�ָ�����Ĭ�ϵı�������
					WM_SelectWindow(WM_HBKWIN);

				}	
				WM_RestartTimer(pMsg->Data.v, 500);		
				
			break;
		
	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: CreateTimeWin
*	����˵��: ����ʱ����ʾ����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void CreateTimeWin(void)
{
	
	WM_HWIN TIMEWIN;
	
	TIMEWIN = WM_CreateWindowAsChild(	TIMEWIN_xPos,											
																				TIMEWIN_yPos,
																				TIMEWIN_xSize,
																				TIMEWIN_ySize,	
																				WM_HBKWIN, 
																				WM_CF_SHOW|WM_CF_MEMDEV,
																				_cbTimeWin, 
																				0
																				);
//	GUI_Delay(10);
	
	//�������ڶ�ʱ�����Զ�ʱ����ʱ��ʹ������Ϣ
	/*TIMEWIN_TIMER =*/ WM_CreateTimer(TIMEWIN, GUI_ID_STATUS_CPU_USAGE+10, 500, 0);

	
//	GUI_Clear();	
	/* ��ʱ����ʾ�ı� */
	
//	WM_SelectWindow(TIMEWIN);

//	GUI_SetFont(&GUI_FontD80);
//	GUI_DispStringHCenterAt("11:56:00",200/2,130);
//	
//	WM_SelectWindow(WM_HBKWIN);
	
}


/**
  * @brief  CreateMidWin�������м�Ĵ���
  * @param  none
  * @retval none
  */
static void CreateMidWin(void)
{
	uint8_t i=0;
	WM_HWIN MIDWIN;
	
#if (ICON_NAME_FORMAT == ICON_NAME_CH_GBK)
	//�洢ת����utf8�����ģ�ע�ⳤ�ȣ�������ÿ����4�ֽ���
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
					/*��ָ��λ�ô���ָ���ߴ��ICONVIEW1 С����*/
					MIDWIN=ICONVIEW_CreateEx(
											 ICONVIEW_XPos, 					          /* С���ߵ��������أ��ڸ������У�*/
											 ICONVIEW_YPos, 								     /* С���ߵ��������أ��ڸ������У�*/
											 WinPara.xSizeWin-ICONVIEW_XPos,	  /* С���ߵ�ˮƽ�ߴ磨��λ�����أ�*/
											 WinPara.ySizeWin - ICONVIEW_YPos , 			      /* С���ߵĴ�ֱ�ߴ磨��λ�����أ�*/
											 WinPara.hWinMid, 				          /* �����ڵľ�������Ϊ0 ������С���߽���Ϊ���棨�������ڣ����Ӵ��� */
											 WM_CF_SHOW|WM_CF_MEMDEV|WM_CF_HASTRANS,         /* ���ڴ�����ǡ�ΪʹС���������ɼ���ͨ��ʹ�� WM_CF_SHOW */ 
											 0,//ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* Ĭ����0�����������ʾ������������ֱ������ */
											 GUI_ID_ICONVIEW0, 			            /* С���ߵĴ���ID */
											 ICONVIEW_Width, 				            /* ͼ���ˮƽ�ߴ� */
											 ICONVIEW_Height+20);				        /* ͼ��Ĵ�ֱ�ߴ� */
		GUI_Delay(20);
									 
		/* ��ICONVIEW С���������ͼ�� */
		for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) 
		{
			#if (ICON_NAME_FORMAT == ICON_NAME_CH_GBK)
				//GBK�ַ�תUTF8
				COM_gbk2utf8(_aBitmapItem[i].pText,utf8_pText);
				ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem[i].pBitmap,utf8_pText);			
			#else
				//ֱ��ʹ���ַ�
				ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem[i].pBitmap,_aBitmapItem[i].pText);
			#endif			
		}		
		

		/* ����С���ߵı���ɫ 32 λ��ɫֵ��ǰ8 λ������alpha��ϴ���Ч��*/
		ICONVIEW_SetBkColor(MIDWIN, ICONVIEW_CI_SEL, ICON_COLOR | 0x80000000);

		/* �������� */
#if (ICON_NAME_FORMAT == ICON_NAME_CH_GBK || ICON_NAME_FORMAT == ICON_NAME_CH_UTF8)
		/* �������� */
		ICONVIEW_SetFont(MIDWIN, &FONT_XINSONGTI_16);
#elif (ICON_NAME_FORMAT == ICON_NAME_EN)
		/* ��Ӣ�����壨ֱ��ʹ����������Ҳ�ǿ��Եģ� */
		ICONVIEW_SetFont(MIDWIN, GUI_FONT_10_ASCII);
#endif
		
		/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
		ICONVIEW_SetSel(MIDWIN,-1);
		/* ����ͼ����x ��y �����ϵļ�ࡣ*/
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, ICONVIEW_XSpace);
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, ICONVIEW_YSpace);
		/* ���ö��뷽ʽ ��5.22�汾�����¼���� */
		ICONVIEW_SetIconAlign(MIDWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
		
/*-------------------------------------------------------------------------------------*/
}

/**
  * @brief  �ص��������м䴰�ڵĻص����������������ػ����Ϣ
	* @param  pMsg:����WM_MESSAGE���ݵ�����
  * @retval none
  */
static void _cbMidWin(WM_MESSAGE * pMsg) 
{
	int NCode, Id;
		
	//ָʾ��ǰͼ���Ƿ񱻰���
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
						
						/* ICON�ؼ������Ϣ */
						case WM_NOTIFICATION_CLICKED:
							selecting =1;
							break;
						
						/* ICON�ؼ��ͷ���Ϣ */
						case WM_NOTIFICATION_RELEASED: 
              UserApp_Running=1;
							
							selecting =0;
							WM_InvalidateWindow(pMsg->hWin);
						
							/* ����Ӧѡ�� */
							switch(ICONVIEW_GetSel(pMsg->hWinSrc))
							{
								
								/* RGBLED *******************************************************************/
								case 0:	
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;

									FUN_ICON0Clicked();			
									break;	
								
								/* Music ***********************************************************************/
								case 1:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;

									FUN_ICON1Clicked();
									break;
								
								/* Recorder *********************************************************************/
								case 2:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON2Clicked();	
									break;
								
								/* Weather *******************************************************************/
								case 3:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON3Clicked();
									break;
								
								/* Compass  ******************************************************************/
								case 4:	
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON4Clicked();            
									break;	
								
								/* Clock ***********************************************************************/
								case 5:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON5Clicked();
									break;
								
								/* Safari *********************************************************************/
								case 6:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
 									FUN_ICON6Clicked();	
									break;
								
								/* Camera ********************************************************************/
								case 7:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON7Clicked();
                  GUI_Delay(50);
									break;
								
								/* Phone **********************************************************************/
								case 8:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON8Clicked();
									break;
								
								/* Message ********************************************************************/
								case 9:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON9Clicked();
									break;
								
								/* Photos ******************************************************************/
								case 10:					
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON10Clicked();
									break;
								
								/* USB *******************************************************************/
								case 11:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON11Clicked();
									break;		
								/* Calculator *******************************************************************/
								case 12:
									//��¼ͼ�걻���µı�־
									ICON_Clicked[pMsg->hWinSrc] = 1;
								
									FUN_ICON12Clicked();
									break;                           
								}
							 break;
						}
					break;
			}
			break;
			
		/* �ػ���Ϣ*/
		case WM_PAINT:
			{
				GUI_SetBkColor(DTCOLOR);
				GUI_Clear();
				
				//��ͼ�겻�Ǳ����£�ѡ��Ϊ-1��ͼ�꣬�����ͼ���ѡ�п�
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
  * @brief  ����bsp��ʼ���ı�־��鲢���������Ϣ
  * @param  ��  
  * @retval ��
  */
void emWinMainApp(void)
{
	
	
	  GUI_Delay(1);

}
	

/*
*********************************************************************************************************
*	�� �� ��: _cbBkWindow
*	����˵��: ���洰�ڵĻص����� 
*	��    �Σ�WM_MESSAGE * pMsg
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void _cbBkWindow(WM_MESSAGE * pMsg) 
{
	char text_buffer[20]={0};
	WM_HWIN hItem;

	switch (pMsg->MsgId) 
	{
		/* �ػ���Ϣ*/
		case WM_PAINT:		
				GUI_SetBkColor(DTCOLOR);
				GUI_Clear();	
//        ICONVIEW_SetSel(WM_GetDialogItem(WinPara.hWinMid, GUI_ID_ICONVIEW0),-1);
		break;
		
		case WM_TIMER:
					if(UserApp_Running==1)
					{
						WM_RestartTimer(pMsg->Data.v, 2000);
						break; 
					}    
				
//				if(!(bsp_result&BSP_RTC))
//				{					
//					/* ת��rtcֵ������ʱ��*/
//					RTC_TimeCovr(&systmtime);

//					sprintf(text_buffer,"%02d:%02d:%02d",systmtime.tm_hour,systmtime.tm_min,systmtime.tm_sec);
//					TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text_buffer);
//				}			

			
				hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_STATUS_CPU_USAGE);
				//������Ƿ����
				if(hItem != 0)
				{
					sprintf(text_buffer,"CPU:% 2d%%",(uint8_t)(OSStatTaskCPUUsage/100));
					TEXT_SetText(hItem,text_buffer);
					WM_RestartTimer(pMsg->Data.v, 1000);
				}
			break;
	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/**
* @brief  ����������ʾGUI������
* @param  ��  
* @retval ��
*/
void  AppTaskDesktop (void  )
{
	GUI_SetColor(GUI_WHITE);
  GUI_SetFont(GUI_FONT_20B_ASCII);
  GUI_DispStringHCenterAt("Starting...\nWait a moment",120,50);
  GUI_Delay(50);
	
	//׼������2�����ڣ�������ʹ�õ����û���������������ڻص�������ʹ��
	WinPara.xSizeLCD = LCD_GetXSize();				            //LCD��Ļ�ߴ�
	WinPara.ySizeLCD = LCD_GetYSize();				            //LCD��Ļ�ߴ�
	WinPara.xPosWin	 = MIDWIN_xPos;							          //���ڵ���ʼλ��
	WinPara.yPosWin  = MIDWIN_yPos;							          //���ڵ���ʼλ��
	WinPara.xSizeWin = WinPara.xSizeLCD;						      //���ڳߴ�
	WinPara.ySizeWin = WinPara.ySizeLCD-WinPara.yPosWin;	//���ڳߴ�

	//ʹ��FLEXƤ��
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

	//�������ڻص�����
	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
	//�������ڶ�ʱ�����Զ�ʱ����CPUʹ������Ϣ
	WM_CreateTimer(WM_HBKWIN, 0, 1000, 0);


	/* �������� ״̬���������ڡ�ʱ�䴰��*/
	CreateTopWin();
	CreateTimeWin();
	CreateMidWin();
	

  while(1)
  {			
    emWinMainApp();
  }
}

/*********************************************END OF FILE**********************/

