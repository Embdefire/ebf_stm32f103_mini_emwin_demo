/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   emwin + ucosIII 基础显示例程
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F103 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */


/*
*********************************************************************************************************
*                                             包含文件
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                               宏定义
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             任务控制块TCB
*********************************************************************************************************
*/

static  OS_TCB   AppTaskStartTCB;
static  OS_TCB   AppTaskGUIBaseTCB;


/*
*********************************************************************************************************
*                                              栈空间STACKS
*********************************************************************************************************
*/

__align(8) static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
__align(8) static  CPU_STK  AppTaskGUIBaseStk[APP_TASK_GUI_BASE_STK_SIZE];


/*
*********************************************************************************************************
*                                             函数声明
*********************************************************************************************************
*/

static  void  AppTaskStart  (void *p_arg);
static  void  AppTaskCreate(void);

extern  void GUIBase_Test(void);

/*
*********************************************************************************************************
*                                            
*********************************************************************************************************
*/


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int  main (void)
{
    OS_ERR  os_err;

    OSInit(&os_err);                                               		/* 初始化 uC/OS-III.                                      */

		//创建启动任务
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                // 任务TCB                               
                 (CPU_CHAR   *)"App Task Start", 								// 任务名称                             
                 (OS_TASK_PTR ) AppTaskStart,									  // 任务函数指针                                
                 (void       *) 0,																	// 可选输入数据
                 (OS_PRIO     ) APP_TASK_START_PRIO,							// 优先级
                 (CPU_STK    *)&AppTaskStartStk[0],							// 任务栈基地址
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,		// 栈“水印”限制
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,        //栈大小
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),//可选配置
                 (OS_ERR     *)&os_err);															//错误代码

		//开始执行任务，从此处开始由ucos系统调度
    OSStart(&os_err);                                              
		
		
}


/**
  * @brief  启动任务函数，主要完成ucos、BSP、GUI以及其它任务的初始化
  * @param  p_arg: OSTaskCreate创建时传入的数据指针
  * @retval 无
  */
static  void  AppTaskStart (void *p_arg)
{
    OS_ERR      os_err;

   (void)p_arg;
  
		BSP_Init();  //初始化BSP  	
		
		CPU_Init();	//初始化CPU

		BSP_Tick_Init();//初始化systick

    Mem_Init(); 	//初始化存储管理器                                     

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&os_err); //计算无任务时CPU使用率                            
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif


	APP_TRACE_DBG(("正在创建应用任务...\n\r"));

	
	//创建应用任务
	AppTaskCreate();  

 //任务死循环
	while (DEF_TRUE) 
	{                                        
			LED2_TOGGLE ;
			APP_TRACE_DBG(("cpu使用率:%.2f%%\n",((float)OSStatTaskCPUUsage/100)));

  		//延时，所有任务函数的死循环内都应有至少1ms延时
		  //特别是高优先级的任务，若无延时，其它低优先级任务可能会无机会执行
			OSTimeDly(1000u, 
									OS_OPT_TIME_DLY,
									&os_err);
	}	
		
}


/**
  * @brief  创建应用任务的函数，它会被启动任务调用以创建应用
  * @param  无
  * @retval 无
  */
static  void  AppTaskCreate (void)
{
	OS_ERR  os_err;

		//创建应用任务
	OSTaskCreate((OS_TCB     *)&AppTaskGUIBaseTCB,             // 任务TCB                               
							 (CPU_CHAR   *)"GUI Base Test", 									// 任务名称                             
							 (OS_TASK_PTR ) GUIBase_Test,									  // 任务函数指针                                
							 (void       *) 0,																	// 可选输入数据
							 (OS_PRIO     ) APP_TASK_GUI_BASE_PRIO,					// 优先级
							 (CPU_STK    *)&AppTaskGUIBaseStk[0],							// 任务栈基地址
							 (CPU_STK_SIZE) APP_TASK_GUI_BASE_STK_SIZE / 10,				// 栈“水印”限制
							 (CPU_STK_SIZE) APP_TASK_GUI_BASE_STK_SIZE,        		//栈大小
							 (OS_MSG_QTY  ) 0u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),//可选配置
							 (OS_ERR     *)&os_err);															//错误代码


}

/*********************************************END OF FILE**********************/

