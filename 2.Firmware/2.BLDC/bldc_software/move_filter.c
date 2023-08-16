

#include "move_filter.h"

move_filter_struct motor1_speed_filter;

move_filter_struct motor2_speed_filter;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      滑动平均滤波计算
//  @param      void   
//  @return     void					
//  @since      主要用于对数据滤波，存储目标数据最近的n个数据，并求出平均值
//-------------------------------------------------------------------------------------------------------------------
void move_filter_calculate(move_filter_struct *move_filter, int32 new_data)
{
    //加上新的数值 减去最末尾的数值 求得最新的和
    move_filter->data_sum = move_filter->data_sum + new_data - move_filter->data_buffer[move_filter->index];
    //重新求平均值
    move_filter->data_average = move_filter->data_sum / move_filter->buffer_size;
    
    //将数据写入缓冲区
    move_filter->data_buffer[move_filter->index] = new_data;
    move_filter->index++;
    if(move_filter->buffer_size <= move_filter->index)
    {
        move_filter->index = 0;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      滑动平均滤波初始化
//  @param      void   
//  @return     void					
//  @since      主要用于对数据滤波，存储目标数据最近的n个数据，并求出平均值
//-------------------------------------------------------------------------------------------------------------------
void move_filter_init(move_filter_struct *move_filter)
{
    move_filter->data_average = 0;
    move_filter->data_sum = 0;
    move_filter->index = 0;
    //设置缓冲区大小
    move_filter->buffer_size = MOVE_AVERAGE_SIZE;  
    
    uint8 i;
    for(i=0; i < move_filter->buffer_size; i++)
	{
		move_filter->data_buffer[i] = 0;
	}
}






