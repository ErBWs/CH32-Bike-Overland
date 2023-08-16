#ifndef _move_filter_h_
#define _move_filter_h_

#include "zf_common_typedef.h"

#define MOVE_AVERAGE_SIZE   6  //���建������С


typedef struct
{
	uint8 index;            //�±�
    uint8 buffer_size;      //buffer��С
	int32 data_buffer[MOVE_AVERAGE_SIZE];  //������
	int32 data_sum;         //���ݺ�
	int32 data_average;     //����ƽ��ֵ
}move_filter_struct ;




extern move_filter_struct motor1_speed_filter;

extern move_filter_struct motor2_speed_filter;






extern move_filter_struct motor1_speed_filter;


void move_filter_calculate(move_filter_struct *move_average, int32 new_data);
void move_filter_init(move_filter_struct *move_average);



#endif

