#ifndef __DESKTOP_H
#define	__DESKTOP_H

#include "stm32f10x.h"
#include "GUI.h"
#include "Dialog.h"




//桌面颜色
#define DTCOLOR         0X200000
//图标背景颜色
#define ICON_COLOR     GUI_LIGHTCYAN
//状态栏字体颜色
#define STATUS_TEXT_COLOR		 GUI_WHITE

//图标尺寸及位置
#define ICONVIEW_Width      48  /* 控件ICONVIEW图标的宽                         */  
#define ICONVIEW_Height     48  /* 控件ICONVIEW图标的高，包括图标的Y方向间距    */  
#define ICONVIEW_XSpace     10  /* 控件ICONVIEW图标的X方向间距                  */ 
#define ICONVIEW_YSpace     12  /* 控件ICONVIEW图标的Y方向间距                  */ 
#define ICONVIEW_XPos       3  /* 控件ICONVIEW边沿与图标的X方向调整距离              */
#define ICONVIEW_YPos       10  /* 控件ICONVIEW边沿与图标的Y方向调整距离              */
#define MIDWIN_yPos         20  /* 中间窗口Y方向起始位置即顶部文字可用高度  */
#define MIDWIN_xPos          0  /* 中间窗口X方向起始位置                    */

//GUI_ID
#define GUI_ID_STATUS_CPU_USAGE 		(GUI_ID_USER+10)


//用于记录桌面窗口参数
typedef struct WIN_PARA{			//窗口使用到的用户定义参数，方便在回调函数中使用
	int xSizeLCD, ySizeLCD;			//LCD屏幕尺寸
	int xPosWin,  yPosWin;			//窗口的起始位置
	int xSizeWin, ySizeWin;			//窗口尺寸	
	WM_HWIN hWinMid;				//主显示窗的句柄（中部）	
}WIN_PARA;

/* 用于桌面ICONVIEW图标的创建 */
typedef struct {
  const GUI_BITMAP * pBitmap;
  const char       * pText;
} BITMAP_ITEM;

//APP 的图标数组
extern GUI_CONST_STORAGE GUI_BITMAP bmIdea;
extern GUI_CONST_STORAGE GUI_BITMAP bmCalculator;
extern GUI_CONST_STORAGE GUI_BITMAP bmClock;
extern GUI_CONST_STORAGE GUI_BITMAP bmCompass;
extern GUI_CONST_STORAGE GUI_BITMAP bmMessages;
extern GUI_CONST_STORAGE GUI_BITMAP bmMusic;
extern GUI_CONST_STORAGE GUI_BITMAP bmPhone;
extern GUI_CONST_STORAGE GUI_BITMAP bmPhotos;
extern GUI_CONST_STORAGE GUI_BITMAP bmVideos;
extern GUI_CONST_STORAGE GUI_BITMAP bmSafari;
extern GUI_CONST_STORAGE GUI_BITMAP bmWeather;
extern GUI_CONST_STORAGE GUI_BITMAP bmwifi;
extern GUI_CONST_STORAGE GUI_BITMAP bmSiri;
extern GUI_CONST_STORAGE GUI_BITMAP bmCamera;
extern GUI_CONST_STORAGE GUI_BITMAP bmUSB;


/*函数声明*/
void  AppTaskDesktop (void  );

#endif /* __DESKTOP_H */
