/**
  ******************************************************************************
  * @file    ADCDLG.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ADC��Ӧ�ô���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 MINI ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
// USER START (Optionally insert additional includes)
#include "includes.h"

// USER END
/**************************************************************************************
*
*       Defines
*
***************************************************************************************
*/
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/*--------------------  (ʹ��U2C.exeС��������)  ------------------------------------*/
/*
*  U2C.exeС����ʹ�÷������½�һ��TXT�ı��ļ��������ת���ı������ΪUTF8�����ʽ�ļ���
*  ��U2C.exeС���ߣ��ȵ����ļ��ļ���Ȼ��ѡ��"Convert"����ת������ɺ���ͬ·�������
*  ͬ��.c�ļ���
*/
#define UTF8_READ_ADC     "\xe7\x94\xb5\xe4\xbd\x8d\xe5\x99\xa8\xe7\x94\xb5\xe5\x8e\x8b\xe8\xaf\xbb\xe5\x8f\x96"  //��λ����ѹ��ȡ

// USER START (Optionally insert additional static data)
//�洢adcת������ı���
extern __IO uint16_t ADC_ConvertedValue;

// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateADC[] = {
  { FRAMEWIN_CreateIndirect, "ADC Converte", 0, 0, 0, 240, 320, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "ADC DATA", GUI_ID_TEXT0, 70, 30, 100, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "DATA", GUI_ID_TEXT1, 30, 50, 180, 20, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
// USER START (Optionally insert additional static code)

// USER END

/*********************************************************************
*
*       _UserDraw
*
* Function description
*   This routine is called by the GRAPH object before anything is drawn
*   and after the last drawing operation.
*/
static void _UserDraw(WM_HWIN hWin, int Stage) {
  if (Stage == GRAPH_DRAW_LAST) 
  {
    char acText[] = "ADCConvertedValue (V)";
    GUI_RECT Rect;
    GUI_RECT RectInvalid;
    int FontSizeY;

    GUI_SetFont(&GUI_Font13_ASCII);
    FontSizeY = GUI_GetFontSizeY();
    WM_GetInsideRect(&Rect);
    WM_GetInvalidRect(hWin, &RectInvalid);
    Rect.x1 = Rect.x0 + FontSizeY;
    GUI_SetColor(GUI_YELLOW);
    GUI_DispStringInRectEx(acText, &Rect, GUI_TA_HCENTER, strlen(acText), GUI_ROTATE_CCW);
  }
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialogADC(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  // USER START (Optionally insert additional variables)
  // USER END
  switch (pMsg->MsgId) {
  case WM_DELETE:
		APP_TRACE_DBG(("ADCapp delete\n"));
		ICON_Clicked[1] = 0;
		//ֹͣADC
		stopADC();
	
		UserApp_Running = 0;
		WM_DeleteWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0));
		tpad_flag=0;
		//�ָ�������
		Beep_Init();
	break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'ADC TEST'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetFont(hItem, GUI_FONT_16B_ASCII);
    FRAMEWIN_SetTitleHeight(hItem, 20);
		FRAMEWIN_SetTextColor(hItem,GUI_DARKGRAY);
		FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,0);
    //
    // Initialization of 'ADC DATA'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
    TEXT_SetFont(hItem, GUI_FONT_16B_ASCII);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'DATA'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_16B_ASCII);
    TEXT_SetText(hItem, "*********");
		TEXT_SetBkColor(hItem,GUI_WHITE);
    TEXT_SetTextColor(hItem, GUI_BLUE);
    // USER START (Optionally insert additional code for further widget initialization)
		/* enable adc1 and config adc1 to dma mode */
		ADCx_Init();
    // USER END
    break;
		// USER START (Optionally insert additional message handling)
  case WM_PAINT:	
		GUI_SetBkColor(APPBKCOLOR);
		GUI_SetColor(APPTEXTCOLOR);
		GUI_Clear();
		GUI_DispStringHCenterAt(UTF8_READ_ADC,115,10);
		break;
		// USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*Program Size: Code=134032 RO-data=67916 RW-data=2608 ZI-data=45824  
*       CreateADC TEST
*/
void FUN_ICON1Clicked(void)
{
	WM_HWIN 			hWin;
	WM_HWIN      hGraph;
	GRAPH_DATA_Handle  	hData;

	GRAPH_SCALE_Handle 	hScaleVert,hScaleH;
	uint8_t i=0;  
	char pValue[25]={0};
	
	
	//�洢ADC�����ĸ���������
	float data;
	
	APP_TRACE_DBG(("ADCapp create\n"));
	
	hWin=GUI_CreateDialogBox(_aDialogCreateADC, GUI_COUNTOF(_aDialogCreateADC), _cbDialogADC, WM_HBKWIN, 0, 0);
	
	hGraph      = GRAPH_CreateEx (5, 80, 220, 200, WM_GetClientWindow(hWin), WM_CF_SHOW , 0, GUI_ID_GRAPH0);
	hData       = GRAPH_DATA_YT_Create(GUI_RED,  /* ��������Ҫʹ�õ���ɫ */
																				 250,  /* ������������ */
																				 0,  /* ָ��Ҫ��ӵ���������ݵ�ָ�롣��ָ��Ӧָ��һ��I16ֵ��*/
																				 0); /* Ҫ��ӵ�����������*/
										
	hScaleVert  = GRAPH_SCALE_Create(25,                      /* �����ͼ��С���ߵ����/���ߵ�λ�á� */        
																			 GUI_TA_RIGHT,            /* ���ڻ��Ʊ�ŵ��ı����뷽ʽ */
																			 GRAPH_SCALE_CF_VERTICAL, /* ������ֱ�̶ȶ��� */ 
																			 50);

	hScaleH = GRAPH_SCALE_Create(190, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);
    
	GRAPH_SCALE_SetTextColor(hScaleH, GUI_YELLOW);

	WIDGET_SetEffect(hGraph, &WIDGET_Effect_Simple);
						   
	/* ���ñ߿�ĳߴ� ���ϡ��¡����ң� */
	GRAPH_SetBorder (hGraph,   /* ��� */
											0,   /* ��߿�ĳߴ� */
											0,   /* �ϱ߿�ĳߴ� */
											0,   /* �ұ߿�ĳߴ� */
											0); /* �±߿�ĳߴ� */
								
	/* �����û����ƺ������˺�����С�����ڻ��ƹ����е��ã�ʹӦ�ó����ܹ������û���������� */							
	GRAPH_SetUserDraw     (hGraph, _UserDraw);

	 GRAPH_SetGridDistY(hGraph, 50);
	 GRAPH_SetGridVis(hGraph, 1);
	 GRAPH_SetGridFixedX(hGraph, 1);
	/* �������ݵĶ��뷽ʽ ���������Ҷ��� */
	GRAPH_DATA_YT_SetAlign(hData,  GRAPH_ALIGN_RIGHT);

	/* 
		�����ڼ���Ҫ���Ƶı�ŵ�����
	    1. ��ʹ������ʱ���̶ȶ���ĵ�λΪ �����ء�����˸�������Ӧ������ֵת��Ϊ����ĵ�λ
	*/
	GRAPH_SCALE_SetFactor   (hScaleVert, 0.02f);
	
	/*
		�������������򸺷����� ���ƶ����̶ȶ����ƫ�ơ�
		1. ˮƽ�̶ȶ�����������ĵױ߿�ʼ�򶥲����б�ǣ���ֱ�̶ȶ������� ��ˮƽ�̶ȣ���ʼ���ұ�
		   ���б�ǣ����е�һ��λ������㡣���������£���ϣ����һ��λ������㡣����̶�Ҫ������
		   �� ���ƶ�����Ӧ�����ƫ�ƣ�Ҫ�򸺷��� ���ƶ�����Ӧ��Ӹ�ֵ��
	*/
	/* �������ڻ��Ʊ�ŵ��ı���ɫ��*/
	GRAPH_SCALE_SetTextColor(hScaleVert, GUI_YELLOW);
	
	/* �����ݶ��󸽼ӵ�����ͼ��С���ߡ� */
	GRAPH_AttachData (hGraph, hData);
	/* ���̶ȶ��󸽼ӵ�����ͼ��С���ߡ� */
	GRAPH_AttachScale(hGraph, hScaleVert);
	GRAPH_AttachScale(hGraph, hScaleH);
	
	while(UserApp_Running)
	{
		i++;
		if(i>=50)
		{
			data=(float)ADC_ConvertedValue;
			//printf("\r\n1 The current AD value = %f  \r\n", data);
			data=data*3.3/4096;		
			//printf("\r\nThe current AD value = 0x%04X -> %f\r\n", ADC_ConvertedValue,data); 
			sprintf(pValue,"0x%04X --> %fV",ADC_ConvertedValue,data);
			pValue[24]='\0';
			
			TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT1), pValue);
			GRAPH_DATA_YT_AddValue(hData,data*50);
			i=0;
		}
		if(tpad_flag)WM_DeleteWindow(hWin);
		GUI_Delay(10); 
	}
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
