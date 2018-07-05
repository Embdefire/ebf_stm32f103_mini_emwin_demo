/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����ƴ�����뷨
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./usart/rx_data_queue.h"
#include "./flash/bsp_spi_flash.h"
#include "py_app.h"


#include <string.h>
#include <stdlib.h>


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
		
	//��ʼ��FLASH
	SPI_FLASH_Init();

	//��ʼ�����ڽ��ն���
	rx_queue_init();
	
	/* ����һ���ַ��� */
	printf("\r\nThis is an PingYin searching demo.\r\n");
	printf("\r\nPlease input PingYin to search.\r\n");

  while(1)
	{	
		//��ѯ�Ƿ���յ���������
		search_char();
	}	
}
/*********************************************END OF FILE**********************/
