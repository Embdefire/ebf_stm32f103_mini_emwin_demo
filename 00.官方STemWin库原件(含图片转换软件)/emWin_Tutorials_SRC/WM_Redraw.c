/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : WM_Redraw.c
Purpose     : Demonstrates the redrawing mechanism of the window manager
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

----------------------------------------------------------------------
*/

#include "GUI.h"
#include "WM.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       static code
*
********************************************************************
*/
/*******************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_ClearRect(0, 50, 319, 239);
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbWindow
*/
static void _cbWindow(WM_MESSAGE* pMsg) {
  GUI_RECT Rect;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetInsideRect(&Rect);
    GUI_SetBkColor(GUI_RED);
    GUI_SetColor(GUI_YELLOW);
    GUI_ClearRectEx(&Rect);
    GUI_DrawRectEx(&Rect);
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringHCenterAt("Foreground window", 75, 40);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _MoveWindow
*/
static void _MoveWindow(const char* pText) {
  WM_HWIN hWnd;
  int     i;

  //
  // Create foreground window
  //
  hWnd = WM_CreateWindow(10, 50, 150, 100, WM_CF_SHOW, _cbWindow, 0);
  GUI_Delay(500);
  //
  // Move foreground window
  //
  for (i = 0; i < 40; i++) {
    WM_MoveWindow(hWnd, 2, 2);
    GUI_Delay(10);
  }
  //
  // Show text before deleting window if we have one
  //
  if (pText) {
    GUI_DispStringAt(pText, 5, 50);
    GUI_Delay(2500);
  }
  //
  // Delete foreground window
  //
  WM_DeleteWindow(hWnd);
  WM_Invalidate(WM_HBKWIN);
  GUI_Exec();
}

/*******************************************************************
*
*       _DemoRedraw
*/
static void _DemoRedraw(void) {
  WM_CALLBACK * _cbOldBk;

  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WM_Redraw - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);
  while(1) {
    //
    // Move a window over background
    //
    _MoveWindow("Background has not been redrawn");
    //
    // Clear background
    //
    GUI_ClearRect(0, 50, 319, 239);
    GUI_Delay(1000);
    //
    // Set callback for background window
    //
    _cbOldBk = WM_SetCallback(WM_HBKWIN, _cbBkWindow);
    //
    // Move a window over background
    //
    _MoveWindow("Background has been redrawn");
    //
    // Delete callback for Background window
    //
    WM_SetCallback(WM_HBKWIN, _cbOldBk);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  _DemoRedraw();
}

/*************************** End of file ****************************/
