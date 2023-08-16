

#include "move_filter.h"

move_filter_struct motor1_speed_filter;

move_filter_struct motor2_speed_filter;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ƽ���˲�����
//  @param      void   
//  @return     void					
//  @since      ��Ҫ���ڶ������˲����洢Ŀ�����������n�����ݣ������ƽ��ֵ
//-------------------------------------------------------------------------------------------------------------------
void move_filter_calculate(move_filter_struct *move_filter, int32 new_data)
{
    //�����µ���ֵ ��ȥ��ĩβ����ֵ ������µĺ�
    move_filter->data_sum = move_filter->data_sum + new_data - move_filter->data_buffer[move_filter->index];
    //������ƽ��ֵ
    move_filter->data_average = move_filter->data_sum / move_filter->buffer_size;
    
    //������д�뻺����
    move_filter->data_buffer[move_filter->index] = new_data;
    move_filter->index++;
    if(move_filter->buffer_size <= move_filter->index)
    {
        move_filter->index = 0;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ƽ���˲���ʼ��
//  @param      void   
//  @return     void					
//  @since      ��Ҫ���ڶ������˲����洢Ŀ�����������n�����ݣ������ƽ��ֵ
//-------------------------------------------------------------------------------------------------------------------
void move_filter_init(move_filter_struct *move_filter)
{
    move_filter->data_average = 0;
    move_filter->data_sum = 0;
    move_filter->index = 0;
    //���û�������С
    move_filter->buffer_size = MOVE_AVERAGE_SIZE;  
    
    uint8 i;
    for(i=0; i < move_filter->buffer_size; i++)
	{
		move_filter->data_buffer[i] = 0;
	}
}






