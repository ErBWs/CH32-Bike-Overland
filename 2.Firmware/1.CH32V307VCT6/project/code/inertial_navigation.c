/*
 * inertial_navigation.c
 *
 *  Created on: Mar 24, 2023
 *      Author: sorrymaker
 */

#include "inertial_navigation.h"


_gps_st gps_data_array[GPS_MAX_POINT];
_gps_st gps_data;
_gps_use_st gps_use;
double first_point_latitude, first_point_longitude, second_point_latitude, second_point_longitude;

EasyKey_t key_read, key_write;
uint8 write_key_flag=0;
uint8 read_key_flag=0;
uint8 Bike_Start = 0;
void GPS_init(void)
{
    gps_init();
//    EasyKeyInit(&key_read, B0);
//    EasyKeyInit(&key_write, B12);
    exti_init(B0,EXTI_TRIGGER_BOTH);//r
    exti_init(D8,EXTI_TRIGGER_BOTH);//w
//    while(1)
//   {
//        if(read_key_flag==1)
//        {
//            read_key_flag = 0;
//        }
//        if(write_key_flag==1)
//        {
//            write_key_flag = 0;
//        }
//   }
//    gps_handler();
}

void gps_handler(void)
{
    static uint8 write_keep_flag=0;
    if(write_keep_flag==0)
    {
        /*�0�6�0�1�0�8�0�4�0�3�0�4buff�0�0�0�0�0�9�0�5*/
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;

        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//�0�5�0�2�0�7�0�9�0�8�0�5×é×�0�4±�0�0�0�0�0�4�0�6�0�5�0�4�0�0�0�8�0�2�0�8�0�5�0�6�0�6
        memset(&gps_use,0,sizeof(_gps_use_st));//�0�5�0�2�0�7�0�9�0�4�0�5�0�0�0�4�0�4�0�3�0�3�0�4×�0�4±�0�0�0�0�0�4�0�6�0�5�0�4�0�0�0�8�0�2�0�8�0�5�0�6�0�6
        write_keep_flag = 1;
        write_key_flag = 0;
    }
    while(gps_use.point_count < GPS_MAX_POINT&&write_keep_flag==1)
    {
        if(gps_tau1201_flag==1)
        {
            uint8 state = gps_data_parse();
            if(state==0)
            {
                if(write_key_flag==2)
                {
                     write_key_flag = 0;
                     write_keep_flag = 0;//�0�4�0�7�0�1ê�0�8�0�0�0�2ó�0�6�0�3�0�3�0�4�0�9�0�9�0�8�0�0�0�2�0�5�0�8�0�5�0�5�0�1�0�6�0�8±�0�0�0�3�0�0�0�6�0�3�0�7�0�2�0�9�0�3�0�8±�0�5�0�3�0�6�0�5�0�4�0�7�0�8�0�0�0�2�0�5�0�8�0�5�0�3�0�5
                     double count = gps_use.point_count;
                     SaveToFlashWithConversion(&count);
                     for(uint32 k=0;k<gps_use.point_count;k++)
                     {
                         SaveToFlashWithConversion(&gps_data_array[k].latitude);
                         SaveToFlashWithConversion(&gps_data_array[k].longitude);
                     }
                     FlashOperationEnd();
                     break;
                }
                if(write_key_flag==1&&write_keep_flag==1)
                {
                     if (gps_tau1201.state && (gps_tau1201.satellite_used >= 4))
                     {
<<<<<<< Updated upstream
//                         printf("gps_state:%d\r\n",gps_tau1201.state);
//                         printf("gps_satellite:%d\r\n",gps_tau1201.satellite_used);
//                         printf("save successful\r\n");
//                         printf("gps_point : %d\r\n",gps_use.point_count);
//                         printf("latitude:%.9f\r\n",gps_tau1201.latitude);
//                         printf("longitude:%.9f\r\n",gps_tau1201.longitude);
//                         ips114_show_float(10, 0, gps, num, pointnum)
                         gps_data_array[gps_use.point_count].latitude = gps_tau1201.latitude;//?
                         gps_data_array[gps_use.point_count].longitude = gps_tau1201.longitude;
                         ips114_show_float(10, 0, gps_data_array[gps_use.point_count].latitude, 3, 6);
                         ips114_show_float(10, 16, gps_data_array[gps_use.point_count].longitude, 3, 6);
=======
                         printf("gps_state:%d\r\n",gps_tau1201.state);
                         printf("gps_satellite:%d\r\n",gps_tau1201.satellite_used);
                         printf("save successful\r\n");
                         printf("gps_point : %d\r\n",gps_use.point_count);
                         printf("latitude:%.9f\r\n",gps_tau1201.latitude);
                         printf("longitude:%.9f\r\n",gps_tau1201.longitude);
                         gps_data_array[gps_use.point_count].latitude = gps_tau1201.latitude;
                         gps_data_array[gps_use.point_count].longitude = gps_tau1201.longitude;
>>>>>>> Stashed changes
                         gps_use.point_count++;
                         ips114_show_int(10, 32, gps_use.point_count, 2);
                     }
                     else
                     {
                         printf("satellite�0�5�0�2%d",gps_tau1201.satellite_used);
                     }
                     write_key_flag = 0;
                }
            }
            gps_tau1201_flag=0;
        }
     }
    if(write_keep_flag == 1&&gps_use.point_count==GPS_MAX_POINT)//�0�8±�0�9�0�9�0�8�0�0�0�7�0�7�0�8�0�5�0�7�0�3�0�3�0�7�0�8�0�2�0�8±�0�2ò�0�5�0�2�0�6�0�5�0�9�0�9�0�8�0�0�0�2�0�5�0�8�0�5�0�5�0�4�0�4�0�7�0�6�0�5Flash
    {
        write_keep_flag = 0;
        double count = gps_use.point_count;
        SaveToFlashWithConversion(&count);
        for(uint32 k=0;k<gps_use.point_count;k++)
        {
             SaveToFlashWithConversion(&gps_data_array[k].latitude);
             SaveToFlashWithConversion(&gps_data_array[k].longitude);
        }
        FlashOperationEnd();
    }
    if(read_key_flag==1)//�0�7�0�7Flash�0�9�0�9�0�8�0�0�0�5�0�1�0�1¨�0�6�0�5�0�8�0�3�0�5�0�3�0�4�0�7�0�8�0�0�0�8�0�2�0�8±�0�2ò�0�4�0�8×÷�0�7�0�1�0�3�0�5�0�4�0�7�0�8�0�0�0�1ê�0�6�0�7�0�2ó�0�2�0�7�0�4�0�5read�0�3�0�5
    {
        /*�0�6�0�1�0�8�0�4�0�3�0�4buff�0�0�0�0�0�9�0�5*/
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;
        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//�0�5�0�2�0�7�0�9�0�8�0�5×é×�0�4±�0�0�0�0�0�4�0�6�0�5�0�4�0�0�0�8�0�2�0�8�0�5�0�6�0�6
        memset(&gps_use,0,sizeof(_gps_use_st));//�0�5�0�2�0�7�0�9�0�4�0�5�0�0�0�4�0�4�0�3�0�3�0�4×�0�4±�0�0�0�0�0�4�0�6�0�5�0�4�0�0�0�8�0�2�0�8�0�5�0�6�0�6
        double count;
        ReadFlashWithConversion(&count);//�0�3�0�9�0�6�0�3�0�8�0�2�0�3�0�6�0�8�0�2�0�8�0�0�0�8�0�5
        gps_use.point_count=count;
        for(uint16 k=0;k<gps_use.point_count;k++)
        {
            ReadFlashWithConversion(&gps_data_array[k].latitude);
            ReadFlashWithConversion(&gps_data_array[k].longitude);
        }
        gps_data_array[0].is_used = 1;//设为已用状态
        gps_data = gps_data_array[0];//获得第一个目标点
        gps_use.use_point_count=1;
        read_key_flag = 0;
    }
    else if (read_key_flag==2) {//·�0�4�0�6�0�8
        if(gps_use.point_count!=0)
        {
            Bike_Start = 1;
        }
    }
}


void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data,_gps_use_st *gps_result)
{
    double gps_distance,gps_azimuth;
    if (gps_result->use_point_count > GPS_MAX_POINT)
    {
        printf("no_other_gps_points\r\n");
    }
    else
    {
        //�0�0ü�0�4�0�0�0�8±�0�5°�0�8�0�2�0�2�0�3�0�0�0�1×�0�9�0�0�0�1
        gps_distance = get_two_points_distance(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);
        gps_azimuth = get_two_points_azimuth(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);

        gps_result->points_distance = gps_distance;
        gps_result->points_azimuth = gps_azimuth;
//        printf("%f\n",gps_data->latitude);
//        printf("%f\n",gps_data->longitude);
//        printf("%.9f\n",gps_result->points_distance);
//        printf("%.9f\n",gps_result->points_azimuth);

    }
}

float yaw_gps_delta( float azimuth, float yaw)
{
    double delta;
<<<<<<< Updated upstream
//0<azimut<90
if(azimuth>0&&azimuth<90)
{
    if (yaw>0&&yaw<azimuth)
=======
    //0<azimut<90
    if(azimuth>0&&azimuth<90)
>>>>>>> Stashed changes
    {
        if (yaw>0&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>(azimuth+180)&&yaw<360)
        {
            delta = 360 - yaw + azimuth;
            return delta;
        }
        else
        {
            delta = yaw - azimuth;
            return -delta;
        }
    }
    //90<azimut<180
    if (azimuth>90&&azimuth<180)
    {
       if (yaw>0 && yaw<azimuth)
       {
           delta = azimuth - yaw;
           return delta;
       }
       else if(yaw>(azimuth+180)&&yaw<360)
       {
           delta = 360-yaw+azimuth;
           return delta;
       }
       else
       {
           delta = yaw - azimuth;
           return -delta;
       }
    }
    //180<azimut<270
    if (azimuth>180&&azimuth<270)
    {
        if (yaw>(azimuth-180)&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return -delta;
        }
        else if (yaw>0 && yaw<(azimuth-180))
        {
            delta = 360 - azimuth + yaw;
            return delta;
        }
        else if(yaw>azimuth && yaw<360)
        {
            delta = yaw - azimuth;
            return delta;
        }
    }
    //270<azimut<360
    if (azimuth>270&&azimuth<360)
    {
        if (yaw>(azimuth-180)&&yaw<azimuth)
        {
            delta = azimuth - yaw;
            return delta;
        }
        else if (yaw>azimuth&&yaw<360)
        {
            delta = yaw - azimuth;
            return -delta;
        }
        else
        {
            delta = 360 - azimuth + yaw;
            return -delta;
        }
    }
}


<<<<<<< Updated upstream
#define EXTRA_FORECAST_POINT 2
=======
#define EXTRA_FORECAST_POINT 0
>>>>>>> Stashed changes
#define DISTANCE_LIMITATION 1
uint8 get_point(double latitude_now, double longitude_now,_gps_st *gps_data)//只能在解析完数据后才能调用此函数
{
    double min_distance;
    double min_azimuth;
    uint8 state = 0;
    uint8 i,k;
    uint8 min_index = gps_use.use_point_count;
    uint8 forecase_depth = EXTRA_FORECAST_POINT;
    _gps_use_st gps_result;
    while(1)
    {
        if(gps_use.use_point_count>=gps_use.point_count)
        {
            state = 1;
            break;
        }
        two_points_message(latitude_now,longitude_now,&gps_data_array[min_index],&gps_result);
<<<<<<< Updated upstream
        min_distance = gps_result.points_distance;//假设最小距离为列表里第一个导航点
        if(gps_use.use_point_count+EXTRA_FORECAST_POINT>=gps_use.point_count)
        {
            forecase_depth=gps_use.point_count-gps_use.use_point_count;//动态深度更新
            forecase_depth = forecase_depth<0?0:forecase_depth;//防止最后一个点depth为负数
        }
        for(i=gps_use.use_point_count;i<gps_use.use_point_count+forecase_depth;i++)//筛选出指顶前瞻区间内的距离最短且满足给定距离的导航点
=======
        min_distance = gps_result.points_distance;//������С����Ϊ�б����һ��������
        if(gps_use.use_point_count+forecase_depth>=gps_use.point_count)
        {
            forecase_depth = (gps_use.point_count-1)-gps_use.use_point_count;//��̬��ȸ���
            forecase_depth = forecase_depth<0?0:forecase_depth;//��ֹ���һ����depthΪ����
        }
        for(i=gps_use.use_point_count;i<=gps_use.use_point_count+forecase_depth;i++)//ɸѡ��ָ��ǰհ�����ڵľ�������������������ĵ�����
>>>>>>> Stashed changes
        {
            two_points_message(latitude_now,longitude_now,&gps_data_array[i],&gps_result);
            if(gps_result.points_distance<min_distance)
            {
                min_index = i;
                min_distance = gps_result.points_distance;
                min_azimuth = gps_result.points_azimuth;
            }
        }
        if(min_distance<DISTANCE_LIMITATION)
        {
<<<<<<< Updated upstream
            for(k=min_index;k--;k>=gps_use.use_point_count)//禁用下一个目标点以及前面可能已经略过的导航节点
=======
            for(k=min_index;k>=gps_use.use_point_count;k--)//������һ��Ŀ����Լ�ǰ������Ѿ��Թ��ĵ����ڵ�
>>>>>>> Stashed changes
            {
                gps_data_array[k].is_used = 1;
                gps_use.use_point_count++;
            }
<<<<<<< Updated upstream
            *gps_data = gps_data_array[k];//赋予新的目标点
            printf("CHANGE-POINT\n");
=======
            if(min_index+1 != gps_use.point_count)
            {
                *gps_data = gps_data_array[min_index+1];//�����µ�Ŀ��� M     0+90


                printf("CHANGE-POINT\n");
            }
            else {
                printf("OVER-OF-POINTS\n");
            }
>>>>>>> Stashed changes
        }
        break;
    }
    return state;
}



