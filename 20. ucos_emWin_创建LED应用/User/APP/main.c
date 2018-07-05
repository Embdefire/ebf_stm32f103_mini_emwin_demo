/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ucos_emWin_FatFs��ֲ_�ⲿ�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F103 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */


/*
*********************************************************************************************************
*                                             �����ļ�
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                               �궨��
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             ������ƿ�TCB
*********************************************************************************************************
*/

static  OS_TCB   AppTaskStartTCB;
static  OS_TCB   AppTaskKeyScanTCB;
static  OS_TCB		BSPTaskTouchPadScanTCB;
static  OS_TCB   AppTaskDesktopTCB;


/*
*********************************************************************************************************
*                                              ջ�ռ�STACKS
*********************************************************************************************************
*/
__align(8) static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
__align(8) static  CPU_STK  BSPTaskTouchPadScanStk[BSP_TASK_TOUCHPAD_SCAN_STK_SIZE];
__align(8) static  CPU_STK  AppTaskKeyScanStk[APP_TASK_KEY_SCAN_STK_SIZE];
__align(8) static  CPU_STK  AppTaskDesktopStk[APP_TASK_DESKTOP_STK_SIZE];


/*
*********************************************************************************************************
*                                             ��������
*********************************************************************************************************
*/

static  void  AppTaskStart  (void *p_arg);
static  void  BSPTaskCreate (void);
static  void  AppTaskCreate(void);

extern void TOUCH_Calibrate(void);



/*
*********************************************************************************************************
*                                            
*********************************************************************************************************
*/


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int  main (void)
{
    OS_ERR  os_err;

    OSInit(&os_err);                                               		/* ��ʼ�� uC/OS-III.                                      */

		//������������
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                // ����TCB                               
                 (CPU_CHAR   *)"App Task Start", 								// ��������                             
                 (OS_TASK_PTR ) AppTaskStart,									  // ������ָ��                                
                 (void       *) 0,																	// ��ѡ��������
                 (OS_PRIO     ) APP_TASK_START_PRIO,							// ���ȼ�
                 (CPU_STK    *)&AppTaskStartStk[0],							// ����ջ����ַ
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,		// ջ��ˮӡ������
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,        //ջ��С
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),//��ѡ����
                 (OS_ERR     *)&os_err);															//�������

		 //������
		if(os_err!=OS_ERR_NONE)  bsp_result|=BSP_OS;

		//��ʼִ�����񣬴Ӵ˴���ʼ��ucosϵͳ����
    OSStart(&os_err);  

	  //�����������ĳ�������ucos���ȣ���Ӧ���е��˴�
		if(os_err!=OS_ERR_NONE)  bsp_result|=BSP_OS;
		
		BSP_TRACE_INFO(("OS err:0x%x",bsp_result));    
		
}


/**
  * @brief  ��������������Ҫ���ucos��BSP��GUI�Լ���������ĳ�ʼ��
  * @param  p_arg: OSTaskCreate����ʱ���������ָ��
  * @retval ��
  */
static  void  AppTaskStart (void *p_arg)
{
    OS_ERR      os_err;

   (void)p_arg;
  	CPU_Init();	//��ʼ��CPU

		BSP_Init();  //��ʼ��BSP  	
		

		BSP_Tick_Init();//��ʼ��systick

    Mem_Init(); 	//��ʼ���洢������                                     

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&os_err); //����������ʱCPUʹ����                            
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif


	APP_TRACE_DBG(("\r\n���ڴ���������Ӧ������..."));

	//������������
	BSPTaskCreate();
	//����Ӧ������
	AppTaskCreate();  

	//���Ӳ������
	Hardware_Error_Check();
	
 //������ѭ��
	while (DEF_TRUE) 
	{                                        
//			LED2_TOGGLE ;
			APP_TRACE_DBG(("cpuʹ����:%.2f%%\n",((float)OSStatTaskCPUUsage/100)));

  		//��ʱ����������������ѭ���ڶ�Ӧ������1ms��ʱ
		  //�ر��Ǹ����ȼ�������������ʱ�����������ȼ�������ܻ��޻���ִ��
			OSTimeDly(1000u, 
									OS_OPT_TIME_DLY,
									&os_err);
	}	
		
}

/**
  * @brief  ����������
  * @param  ��
  * @retval ��
  */
void  AppTaskKeyScan  (void )
{

	OS_ERR  os_err;
	
		  /* �����¼���־�� flag_grp */
  OSFlagCreate ((OS_FLAG_GRP  *)&key_flag_grp,        //ָ���¼���־���ָ��
                (CPU_CHAR     *)"KEY Flag",  //�¼���־�������
                (OS_FLAGS      )0,                //�¼���־��ĳ�ʼֵ
                (OS_ERR       *)&os_err);					  //���ش�������


	while(1)
	{
			GUI_TOUCH_Exec();
		
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
			{
						OSFlagPost ((OS_FLAG_GRP  *)&key_flag_grp,                             //����־���BIT0��0
													(OS_FLAGS      )EVEN_KEY1_DOWN,
													(OS_OPT        )OS_OPT_POST_FLAG_SET,
													(OS_ERR       *)&os_err);
			}
			else
			{
			
			}
			
			if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )
			{
						OSFlagPost ((OS_FLAG_GRP  *)&key_flag_grp,                             //����־���BIT0��0
													(OS_FLAGS      )EVEN_KEY2_DOWN,
													(OS_OPT        )OS_OPT_POST_FLAG_SET,
													(OS_ERR       *)&os_err);
			}
			else
			{
			
			}
			
			//��ʱ����������������ѭ���ڶ�Ӧ������1ms��ʱ
		  //�ر��Ǹ����ȼ�������������ʱ�����������ȼ�������ܻ��޻���ִ��
			OSTimeDly(10u, 
									OS_OPT_TIME_DLY,
									&os_err);

			
	}
}
	
	
/**
  * @brief  �������������簴������ʱɨ���
  * @param  ��
  * @retval ��
  */
static  void  BSPTaskCreate (void)
{
	OS_ERR  os_err;

		//����ɨ������
	OSTaskCreate((OS_TCB     *)&AppTaskKeyScanTCB,             // ����TCB                               
							 (CPU_CHAR   *)"Key Scan", 									// ��������                             
							 (OS_TASK_PTR ) AppTaskKeyScan,									  // ������ָ��                                
							 (void       *) 0,																	// ��ѡ��������
							 (OS_PRIO     ) APP_TASK_KEY_SCAN_PRIO,					// ���ȼ�
							 (CPU_STK    *)&AppTaskKeyScanStk[0],							// ����ջ����ַ
							 (CPU_STK_SIZE) APP_TASK_KEY_SCAN_STK_SIZE / 10,				// ջ��ˮӡ������
							 (CPU_STK_SIZE) APP_TASK_KEY_SCAN_STK_SIZE,        		//ջ��С
							 (OS_MSG_QTY  ) 0u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),//��ѡ����
							 (OS_ERR     *)&os_err);															//�������
							 
							 
	//�������ݴ�������ɨ������
	OSTaskCreate((OS_TCB     *)&BSPTaskTouchPadScanTCB,             // ����TCB                               
							 (CPU_CHAR   *)"Touch Pad", 									// ��������                             
							 (OS_TASK_PTR ) BSPTaskTouchPadScan,									  // ������ָ��                                
							 (void       *) 0,																	// ��ѡ��������
							 (OS_PRIO     ) BSP_TASK_TOUCHPAD_SCAN_PRIO,					// ���ȼ�
							 (CPU_STK    *)&BSPTaskTouchPadScanStk[0],							// ����ջ����ַ
							 (CPU_STK_SIZE) BSP_TASK_TOUCHPAD_SCAN_STK_SIZE / 10,				// ջ��ˮӡ������
							 (CPU_STK_SIZE) BSP_TASK_TOUCHPAD_SCAN_STK_SIZE,        		//ջ��С
							 (OS_MSG_QTY  ) 0u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),//��ѡ����
							 (OS_ERR     *)&os_err);			


}

/**
  * @brief  ����Ӧ������ĺ��������ᱻ������������Դ���Ӧ��
  * @param  ��
  * @retval ��
  */
static  void  AppTaskCreate (void)
{
	OS_ERR  os_err;

	//�ж��Ƿ���ҪУ׼
	if (IsCal == CALADD_FLAG)
	{
			//����Ӧ������,��������
		OSTaskCreate((OS_TCB     *)&AppTaskDesktopTCB,             // ����TCB                               
								 (CPU_CHAR   *)"GUI Task", 									// ��������                             
								 (OS_TASK_PTR ) AppTaskDesktop,									  // ������ָ��                                
								 (void       *) 0,																	// ��ѡ��������
								 (OS_PRIO     ) APP_TASK_DESKTOP_PRIO,					// ���ȼ�
								 (CPU_STK    *)&AppTaskDesktopStk[0],							// ����ջ����ַ
								 (CPU_STK_SIZE) APP_TASK_DESKTOP_STK_SIZE / 10,				// ջ��ˮӡ������
								 (CPU_STK_SIZE) APP_TASK_DESKTOP_STK_SIZE,        		//ջ��С
								 (OS_MSG_QTY  ) 0u,
								 (OS_TICK     ) 0u,
								 (void       *) 0,
								 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),//��ѡ����
								 (OS_ERR     *)&os_err);															//�������
	}
	else
	{
		//����У׼����
		OSTaskCreate((OS_TCB     *)&AppTaskDesktopTCB,             // ����TCB                               
								 (CPU_CHAR   *)"GUI Task", 									// ��������                             
								 (OS_TASK_PTR ) TOUCH_Calibrate,									  // ������ָ��                                
								 (void       *) 0,																	// ��ѡ��������
								 (OS_PRIO     ) APP_TASK_DESKTOP_PRIO,					// ���ȼ�
								 (CPU_STK    *)&AppTaskDesktopStk[0],							// ����ջ����ַ
								 (CPU_STK_SIZE) APP_TASK_DESKTOP_STK_SIZE / 10,				// ջ��ˮӡ������
								 (CPU_STK_SIZE) APP_TASK_DESKTOP_STK_SIZE,        		//ջ��С
								 (OS_MSG_QTY  ) 0u,
								 (OS_TICK     ) 0u,
								 (void       *) 0,
								 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),//��ѡ����
								 (OS_ERR     *)&os_err);															//�������

	}

}

/*********************************************END OF FILE**********************/

