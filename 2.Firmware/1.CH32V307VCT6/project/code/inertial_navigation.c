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
    exti_init(B0,EXTI_TRIGGER_FALLING);//r
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
    gps_handler();
}

void gps_handler(void)
{
    static uint8 write_keep_flag=0;
    if(write_keep_flag==0)
    {
        /*³õÊ¼»¯buffÖ¸Õë*/
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;

        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//Çå¿ÕÊý×é×¼±¸Â¼ÈëÐÂµÄÊý¾Ý
        memset(&gps_use,0,sizeof(_gps_use_st));//Çå¿Õ¼ÇÂ¼ÐÅÏ¢×¼±¸Â¼ÈëÐÂµÄÊý¾Ý
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
                     write_keep_flag = 0;//Ð´ÍêµãºóÈ¡Ïû¶ÁµãÄ£Ê½£¬ÒÔ±ãÏÂÒ»´ÎËæÊ±½øÈëÐ´µãÄ£Ê½¡£
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
                         gps_use.point_count++;
                         ips114_show_int(10, 32, gps_use.point_count, 2);
                     }
                     else
                     {
                         printf("satellite£º%d",gps_tau1201.satellite_used);
                     }
                     write_key_flag = 0;
                }
            }
            gps_tau1201_flag=0;
        }
     }
    if(write_keep_flag == 1&&gps_use.point_count==GPS_MAX_POINT)//µ±¶Áµã´ïµ½ÉÏÏÞµÄÊ±ºòÇå³ý¶ÁµãÄ£Ê½²¢Ð´ÈëFlash
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
    if(read_key_flag==1)//´ÓFlash¶Áµã£¬Í¨³£ÔÚ²»Ð´µãµÄÊ±ºòÆð×÷ÓÃ¡£Ð´µãÍê³ÉºóÎÞÐëread¡£
    {
        /*³õÊ¼»¯buffÖ¸Õë*/
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;
        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//Çå¿ÕÊý×é×¼±¸Â¼ÈëÐÂµÄÊý¾Ý
        memset(&gps_use,0,sizeof(_gps_use_st));//Çå¿Õ¼ÇÂ¼ÐÅÏ¢×¼±¸Â¼ÈëÐÂµÄÊý¾Ý
        double count;
        ReadFlashWithConversion(&count);//»ñÈ¡Ô­ÏÈµÄµãÊý
        gps_use.point_count=count;
        for(uint16 k=0;k<gps_use.point_count;k++)
        {
            ReadFlashWithConversion(&gps_data_array[k].latitude);
            ReadFlashWithConversion(&gps_data_array[k].longitude);
        }
        gps_data = gps_data_array[0];//»ñµÃµÚÒ»¸öÄ¿±êµã
        read_key_flag = 0;
    }
    else if (read_key_flag==2) {//·¢³µ
        if(gps_use.point_count!=0)
        {
            Bike_Start = 1;
        }
    }
}


void two_points_message(double latitude_now, double longitude_now, _gps_st *gps_data)
{
    double gps_distance,gps_azimuth;
    if (gps_use.use_point_count > GPS_MAX_POINT)
    {
        printf("no_other_gps_points\r\n");
    }
    else
    {
        //¸üÐÂµ±Ç°µÄÎ»ÖÃ×ËÌ¬
        gps_distance = get_two_points_distance(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);
        gps_azimuth = get_two_points_azimuth(latitude_now, longitude_now, gps_data->latitude, gps_data->longitude);

        gps_use.points_distance = gps_distance;
        gps_use.points_azimuth = gps_azimuth;
//        printf("%f\n",gps_data->latitude);
//        printf("%f\n",gps_data->longitude);
//        printf("%.9f\n",gps_use.points_distance);
//        printf("%.9f\n",gps_use.points_azimuth);
    }
}

double yaw_gps_delta( double azimuth, float yaw)
{
    double delta;
//0<azimut<90
if (azimuth>0&&azimuth<90)
{
    if (yaw>0&&yaw<azimuth)
    {
        delta = azimuth - yaw;
    }
    else if (yaw>(azimuth+180)&&yaw<360)
    {
        delta = 360 - yaw + azimuth;
    }
    else
    {
        delta = yaw - azimuth;
    }
}
//90<azimut<180
if (azimuth>90&&azimuth<180)
{
   if (yaw>0 && yaw<azimuth)
   {
       delta = azimuth - yaw;
   }
   else if(yaw>(azimuth+180)&&yaw<360)
   {
       delta = 360-yaw+azimuth;
   }
   else
   {
       delta = yaw - azimuth;
   }
}
//180<azimut<270
if (azimuth>180&&azimuth<270)
{
    if (yaw>(azimuth-180)&&yaw<azimuth)
    {
        delta = azimuth - yaw;
    }
    else if (yaw>0 && yaw<(azimuth-180))
    {
        delta = 360 - azimuth + yaw;
    }
    else if(yaw>azimuth && yaw<360)
    {
        delta = yaw - azimuth;
    }
}
//270<azimut<360
if (azimuth>270&&azimuth<360)
{
    if (yaw>(azimuth-180)&&yaw<azimuth)
    {
        delta = azimuth - yaw;
    }
    else if (yaw>azimuth&&yaw<360)
    {
        delta = yaw - azimuth;
    }
    else
    {
        delta = 360 - azimuth + yaw;
    }
}
    return delta;
}

void change_point(_gps_st *gps_data)
{
    if (gps_use.points_distance < 2)
    {
        //¸üÐÂÏÂÒ»¸öÄ¿±êµã
//        ReadFlashWithConversion(&gps_data->latitude);
//        ReadFlashWithConversion(&gps_data->longitude);
//        printf("CHANGE-POINT\n");
        gps_use.use_point_count++;
    }
}



