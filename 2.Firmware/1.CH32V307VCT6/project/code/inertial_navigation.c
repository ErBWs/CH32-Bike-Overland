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
        /*ï¿½0ï¿½6ï¿½0ï¿½1ï¿½0ï¿½8ï¿½0ï¿½4ï¿½0ï¿½3ï¿½0ï¿½4buffï¿½0ï¿½0ï¿½0ï¿½0ï¿½0ï¿½9ï¿½0ï¿½5*/
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;

        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//ï¿½0ï¿½5ï¿½0ï¿½2ï¿½0ï¿½7ï¿½0ï¿½9ï¿½0ï¿½8ï¿½0ï¿½5Ã—Ã©Ã—ï¿½0ï¿½4Â±ï¿½0ï¿½0ï¿½0ï¿½0ï¿½0ï¿½4ï¿½0ï¿½6ï¿½0ï¿½5ï¿½0ï¿½4ï¿½0ï¿½0ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½6ï¿½0ï¿½6
        memset(&gps_use,0,sizeof(_gps_use_st));//ï¿½0ï¿½5ï¿½0ï¿½2ï¿½0ï¿½7ï¿½0ï¿½9ï¿½0ï¿½4ï¿½0ï¿½5ï¿½0ï¿½0ï¿½0ï¿½4ï¿½0ï¿½4ï¿½0ï¿½3ï¿½0ï¿½3ï¿½0ï¿½4Ã—ï¿½0ï¿½4Â±ï¿½0ï¿½0ï¿½0ï¿½0ï¿½0ï¿½4ï¿½0ï¿½6ï¿½0ï¿½5ï¿½0ï¿½4ï¿½0ï¿½0ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½6ï¿½0ï¿½6
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
                     write_keep_flag = 0;//ï¿½0ï¿½4ï¿½0ï¿½7ï¿½0ï¿½1Ãªï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½2Ã³ï¿½0ï¿½6ï¿½0ï¿½3ï¿½0ï¿½3ï¿½0ï¿½4ï¿½0ï¿½9ï¿½0ï¿½9ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½2ï¿½0ï¿½5ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½5ï¿½0ï¿½1ï¿½0ï¿½6ï¿½0ï¿½8Â±ï¿½0ï¿½0ï¿½0ï¿½3ï¿½0ï¿½0ï¿½0ï¿½6ï¿½0ï¿½3ï¿½0ï¿½7ï¿½0ï¿½2ï¿½0ï¿½9ï¿½0ï¿½3ï¿½0ï¿½8Â±ï¿½0ï¿½5ï¿½0ï¿½3ï¿½0ï¿½6ï¿½0ï¿½5ï¿½0ï¿½4ï¿½0ï¿½7ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½2ï¿½0ï¿½5ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½3ï¿½0ï¿½5
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
                         printf("satelliteï¿½0ï¿½5ï¿½0ï¿½2%d",gps_tau1201.satellite_used);
                     }
                     write_key_flag = 0;
                }
            }
            gps_tau1201_flag=0;
        }
     }
    if(write_keep_flag == 1&&gps_use.point_count==GPS_MAX_POINT)//ï¿½0ï¿½8Â±ï¿½0ï¿½9ï¿½0ï¿½9ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½7ï¿½0ï¿½7ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½7ï¿½0ï¿½3ï¿½0ï¿½3ï¿½0ï¿½7ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½8Â±ï¿½0ï¿½2Ã²ï¿½0ï¿½5ï¿½0ï¿½2ï¿½0ï¿½6ï¿½0ï¿½5ï¿½0ï¿½9ï¿½0ï¿½9ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½2ï¿½0ï¿½5ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½5ï¿½0ï¿½4ï¿½0ï¿½4ï¿½0ï¿½7ï¿½0ï¿½6ï¿½0ï¿½5Flash
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
    if(read_key_flag==1)//ï¿½0ï¿½7ï¿½0ï¿½7Flashï¿½0ï¿½9ï¿½0ï¿½9ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½5ï¿½0ï¿½1ï¿½0ï¿½1Â¨ï¿½0ï¿½6ï¿½0ï¿½5ï¿½0ï¿½8ï¿½0ï¿½3ï¿½0ï¿½5ï¿½0ï¿½3ï¿½0ï¿½4ï¿½0ï¿½7ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½8Â±ï¿½0ï¿½2Ã²ï¿½0ï¿½4ï¿½0ï¿½8Ã—Ã·ï¿½0ï¿½7ï¿½0ï¿½1ï¿½0ï¿½3ï¿½0ï¿½5ï¿½0ï¿½4ï¿½0ï¿½7ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½1Ãªï¿½0ï¿½6ï¿½0ï¿½7ï¿½0ï¿½2Ã³ï¿½0ï¿½2ï¿½0ï¿½7ï¿½0ï¿½4ï¿½0ï¿½5readï¿½0ï¿½3ï¿½0ï¿½5
    {
        /*ï¿½0ï¿½6ï¿½0ï¿½1ï¿½0ï¿½8ï¿½0ï¿½4ï¿½0ï¿½3ï¿½0ï¿½4buffï¿½0ï¿½0ï¿½0ï¿½0ï¿½0ï¿½9ï¿½0ï¿½5*/
        flashBufIndex = 0;
        flashSecIndex = 63;
        flashPageIndex = 3;
        flash_buffer_clear();
        memset(gps_data_array,0,sizeof(_gps_st)*GPS_MAX_POINT);//ï¿½0ï¿½5ï¿½0ï¿½2ï¿½0ï¿½7ï¿½0ï¿½9ï¿½0ï¿½8ï¿½0ï¿½5Ã—Ã©Ã—ï¿½0ï¿½4Â±ï¿½0ï¿½0ï¿½0ï¿½0ï¿½0ï¿½4ï¿½0ï¿½6ï¿½0ï¿½5ï¿½0ï¿½4ï¿½0ï¿½0ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½6ï¿½0ï¿½6
        memset(&gps_use,0,sizeof(_gps_use_st));//ï¿½0ï¿½5ï¿½0ï¿½2ï¿½0ï¿½7ï¿½0ï¿½9ï¿½0ï¿½4ï¿½0ï¿½5ï¿½0ï¿½0ï¿½0ï¿½4ï¿½0ï¿½4ï¿½0ï¿½3ï¿½0ï¿½3ï¿½0ï¿½4Ã—ï¿½0ï¿½4Â±ï¿½0ï¿½0ï¿½0ï¿½0ï¿½0ï¿½4ï¿½0ï¿½6ï¿½0ï¿½5ï¿½0ï¿½4ï¿½0ï¿½0ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½8ï¿½0ï¿½5ï¿½0ï¿½6ï¿½0ï¿½6
        double count;
        ReadFlashWithConversion(&count);//ï¿½0ï¿½3ï¿½0ï¿½9ï¿½0ï¿½6ï¿½0ï¿½3ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½3ï¿½0ï¿½6ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½8ï¿½0ï¿½0ï¿½0ï¿½8ï¿½0ï¿½5
        gps_use.point_count=count;
        for(uint16 k=0;k<gps_use.point_count;k++)
        {
            ReadFlashWithConversion(&gps_data_array[k].latitude);
            ReadFlashWithConversion(&gps_data_array[k].longitude);
        }
        gps_data_array[0].is_used = 1;//è®¾ä¸ºå·²ç”¨çŠ¶æ€
        gps_data = gps_data_array[0];//è·å¾—ç¬¬ä¸€ä¸ªç›®æ ‡ç‚¹
        gps_use.use_point_count=1;
        read_key_flag = 0;
    }
    else if (read_key_flag==2) {//Â·ï¿½0ï¿½4ï¿½0ï¿½6ï¿½0ï¿½8
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
        //ï¿½0ï¿½0Ã¼ï¿½0ï¿½4ï¿½0ï¿½0ï¿½0ï¿½8Â±ï¿½0ï¿½5Â°ï¿½0ï¿½8ï¿½0ï¿½2ï¿½0ï¿½2ï¿½0ï¿½3ï¿½0ï¿½0ï¿½0ï¿½1Ã—ï¿½0ï¿½9ï¿½0ï¿½0ï¿½0ï¿½1
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
uint8 get_point(double latitude_now, double longitude_now,_gps_st *gps_data)//åªèƒ½åœ¨è§£æå®Œæ•°æ®åæ‰èƒ½è°ƒç”¨æ­¤å‡½æ•°
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
        min_distance = gps_result.points_distance;//å‡è®¾æœ€å°è·ç¦»ä¸ºåˆ—è¡¨é‡Œç¬¬ä¸€ä¸ªå¯¼èˆªç‚¹
        if(gps_use.use_point_count+EXTRA_FORECAST_POINT>=gps_use.point_count)
        {
            forecase_depth=gps_use.point_count-gps_use.use_point_count;//åŠ¨æ€æ·±åº¦æ›´æ–°
            forecase_depth = forecase_depth<0?0:forecase_depth;//é˜²æ­¢æœ€åä¸€ä¸ªç‚¹depthä¸ºè´Ÿæ•°
        }
        for(i=gps_use.use_point_count;i<gps_use.use_point_count+forecase_depth;i++)//ç­›é€‰å‡ºæŒ‡é¡¶å‰ç»åŒºé—´å†…çš„è·ç¦»æœ€çŸ­ä¸”æ»¡è¶³ç»™å®šè·ç¦»çš„å¯¼èˆªç‚¹
=======
        min_distance = gps_result.points_distance;//¼ÙÉè×îĞ¡¾àÀëÎªÁĞ±íÀïµÚÒ»¸öµ¼º½µã
        if(gps_use.use_point_count+forecase_depth>=gps_use.point_count)
        {
            forecase_depth = (gps_use.point_count-1)-gps_use.use_point_count;//¶¯Ì¬Éî¶È¸üĞÂ
            forecase_depth = forecase_depth<0?0:forecase_depth;//·ÀÖ¹×îºóÒ»¸öµãdepthÎª¸ºÊı
        }
        for(i=gps_use.use_point_count;i<=gps_use.use_point_count+forecase_depth;i++)//É¸Ñ¡³öÖ¸¶¥Ç°Õ°Çø¼äÄÚµÄ¾àÀë×î¶ÌÇÒÂú×ã¸ø¶¨¾àÀëµÄµ¼º½µã
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
            for(k=min_index;k--;k>=gps_use.use_point_count)//ç¦ç”¨ä¸‹ä¸€ä¸ªç›®æ ‡ç‚¹ä»¥åŠå‰é¢å¯èƒ½å·²ç»ç•¥è¿‡çš„å¯¼èˆªèŠ‚ç‚¹
=======
            for(k=min_index;k>=gps_use.use_point_count;k--)//½ûÓÃÏÂÒ»¸öÄ¿±êµãÒÔ¼°Ç°Ãæ¿ÉÄÜÒÑ¾­ÂÔ¹ıµÄµ¼º½½Úµã
>>>>>>> Stashed changes
            {
                gps_data_array[k].is_used = 1;
                gps_use.use_point_count++;
            }
<<<<<<< Updated upstream
            *gps_data = gps_data_array[k];//èµ‹äºˆæ–°çš„ç›®æ ‡ç‚¹
            printf("CHANGE-POINT\n");
=======
            if(min_index+1 != gps_use.point_count)
            {
                *gps_data = gps_data_array[min_index+1];//¸³ÓèĞÂµÄÄ¿±êµã M     0+90


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



