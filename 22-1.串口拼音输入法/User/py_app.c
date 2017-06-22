/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ƴ������Ӧ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include <stdlib.h>
#include "./usart/rx_data_queue.h"
#include "stm32f10x.h"
#include "py_app.h"


extern char *PYSearch(unsigned char *msg , int *num);
static uint8_t select_char(char *char_list,int char_num);

/**
  * @brief  ���������ƴ�������ַ�����������Ҫ��while��ѭ������
  */
void search_char(void)
{
	QUEUE_DATA_TYPE *rx_data;	
	
	char *ptr;
	static uint16_t  s_Hznum=0;          
		
	/*�ӻ�������ȡ���ݣ����д���*/
	rx_data = cbRead(&rx_queue); 

	if(rx_data != NULL)//������зǿ�
	{		
		//�����ַ���������������ֱ������ַ���
		*(rx_data->head+rx_data->len) = '\0';
		
		ptr = PYSearch((unsigned char *)rx_data->head, (int *)&s_Hznum);
			
		QUEUE_DEBUG("receive data:%s",rx_data->head);
		
		//ʹ�������ݱ������cbReadFinish���¶�ָ��
		cbReadFinish(&rx_queue);

		if (ptr != '\0')
		{
			uint8_t result;
			
			QUEUE_DEBUG("pyserach:%s",ptr);
			QUEUE_DEBUG("pynum:%d",s_Hznum);
			
			QUEUE_DEBUG("Please input num between:[1-%d] to select char,",s_Hznum);
			QUEUE_DEBUG("Input \"q\" to quit selecting,");

			do
			{ 
				result = select_char(ptr,s_Hznum);
			}while(result != 0 && result != 2  );
		}

	}
}


//���ѡ����ַ�
//����0��ѡ������
//����1��û�м�⵽����
//����2���ô��˳�ѡ��
//����3��ѡ�����
uint8_t select_char(char *char_list,int char_num)
{
	QUEUE_DATA_TYPE *rx_data;		
	
	int select_num;
	char select_char[4];
	uint8_t result = 1;
		
	/*�ӻ�������ȡ���ݣ����д���*/
	rx_data = cbRead(&rx_queue); 

	if(rx_data != NULL)//������зǿ�
	{		
		//�����ַ���������������ֱ������ַ���
		*(rx_data->head+rx_data->len) = '\0';
		
		select_num = atoi(rx_data->head);
		
		if( select_num > 0 && select_num <= char_num)
		{					
			//���ַ����ݴ洢��STM32FLASH���ǲ���ֱ���޸ĵ�
			//�����ַ����ݵ��ڴ棬������ӽ�������
			memcpy(select_char,&char_list[(select_num-1)*3],3);
			select_char[3] = '\0';
			
			QUEUE_DEBUG("select_num = %d,select_char = %s",select_num,select_char);
			
			result = 0;
		}	
		else if(strcmp(rx_data->head,"q")==0)
		{
			QUEUE_DEBUG("quit selecting!");		
		
			result = 2;

		}
		else	
		{
			QUEUE_DEBUG("select error!");	
			QUEUE_DEBUG("Please input num between:[1-%d] to select char,",char_num);
			QUEUE_DEBUG("Input \"q\" to quit selecting.");			
				
			result = 3;
		}				

		//ʹ�������ݱ������cbReadFinish���¶�ָ��
		cbReadFinish(&rx_queue);
	}
	else
	{
		result = 1;
	}
	
	return result;
}
