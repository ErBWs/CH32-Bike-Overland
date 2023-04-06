/*
*				GPS NMEA0183Э���Ҫ������� 
*	
*	֧�ֽ��� RMC��GGA��VTG��HDT����Ϣ�ֶ���Ϣ�����ڽ�����ܱȽ����ˣ�
*   ��ֲԴ���߿����п�������µĽ������롣
*   ������ʽ��������ֶν����ķ�ʽ���ܴܺ�̶��Ͻ�ʡ�����ڴ�ռ䡣 
*   ���±�д����ת���������������ⲿ�⣬��ֲʱһ��ֻ�����NMEA0183.h
*   �ļ����ɡ� 
*
*   ����ʾ����
*   	
		char nmea[] = \
		"$GNRMC,102219.00,A,2239.11578,N,11406.59325,E,0.009,,291018,,,D*62\r\n"\
		"$GNVTG,,T,,M,0.009,N,0.017,K,D*37\r\n"\
		"$GNGGA,102220.00,2239.11583,N,11406.59338,E,2,09,1.30,112.7,M,-2.3,M,,0000*52\r\n";
		
		gps_nmea gps_nmea_temp;   /// �������ʱ�õ����ݴ�״̬����,ֻ������ʱʹ�� 
		gps_data gps_data1;       /// GPS�����õ����������ݣ��û���ʹ�� 
		unsigned int index = 0;
		
		for(index=0; index<sizeof(nmea); ++index)
		{
			if(nmea_decode(&gps_nmea_temp, &gps_data1, nmea[index])) ///���ý�������
			{
				/// ������Ϣ�γɹ� 
				... 
			} 
		} 
		
*   NMEA0183��������˼����Դ�ڿ�Դ�ɿش���(Ardupilot)�����Ը÷ݴ��뿪Դ�������ʹ�á�
*   ( ����Bug�����ܷ��� ! QQ: 2281280195 ) 
*       
*   ���ߣ� ouyanglei      	ʱ�䣺2018-11-16
*/


#ifndef NMEA0183_H
#define NMEA0183_H

#include <string.h>

/*************** �궨��  *******************/ 
#define current_time_ms() 1

#define GPS_LEAPSECONDS_MILLIS 18000UL
#define AP_SEC_PER_WEEK   (7UL * 86400UL)

/* ����ַ����Ƿ�Ϊ����0-9 */ 
#define IS_DIGITAL(x) ( ((x)>='0'&&(x)<='9')||(x)=='-'||(x)=='.' )
#define CHAR_TO_DIGITAL(x) ((x)-'0')
#define DIGITAL_TO_CHAR(x) ( (x)+'0' )

/**************** ö�������� ***************/
	/* �����ֶ�ö���� */ 
    typedef enum _sentence_types 
	{   /* ÿ��ö������ʾ���ֶε���ʼλ�ã���Щ�����ֶ���Ҫ10���ֶ��� */ 
        GPS_SENTENCE_RMC = 32,     /* RMC�ֶ� */
        GPS_SENTENCE_GGA = 64,		/* GGA�ֶ� */
        GPS_SENTENCE_VTG = 96,		/* VTG�ֶ� */
        GPS_SENTENCE_HDT = 128,    /* HDT�ֶ� */
        GPS_SENTENCE_OTHER = 0     /* Ĭ��û���ֶ� */
    }sentence_types;

/**************** �ṹ�嶨�� ***************/    
    /* GPS��λ״̬ö���� */ 
    typedef enum _gps_status
	{
        NO_GPS = 0,              /* ��GPS */
        NO_FIX,                  /* ���յ�GPS��Ϣ����û�ж�λ */
        GPS_OK_FIX_2D,           /* 2D��λ */
        GPS_OK_FIX_3D,           /* 3D��λ */ 
        GPS_OK_FIX_3D_DGPS,      /* ����3D��λ */ 
        GPS_OK_FIX_3D_RTK_FLOAT, /* RTK�����״̬ */ 
        GPS_OK_FIX_3D_RTK_FIXED, /* RTK�̶���״̬ */
    }gps_status;
    
    /* GPS��λ�� */ 
    typedef struct _location 
	{
	    int alt:24;         /* ���θ߶� meters * 100  ��λΪ���� */
	    float lat;            /* γ�� *  ��ʱ������10**7��ԭʼ����*/
	    float lng;            /* ���� *  ��ʱ������10**7��ԭʼ����*/
	}Location;
    
    /* ���ݽ���״̬�ṹ�嶨�� */
    typedef struct _gps_nmea
    {
    	/* ���ݽ���״̬ */ 
    	unsigned char parity;    		   /* У������ */ 
    	unsigned char is_checksum_term;    /* ��ǰ�ֶ���ΪУ���� */
    	char term[15];           		   /* ��ǰ�ֶ��򻺳�����','Ϊ�ֶ���ָ�� */
    	unsigned char sentence_type;       /* �ֶ���𣬼�ö�� sentence_types*/
    	unsigned char term_number;         /* ��ǰ�ֶ������ */
    	unsigned char term_offset;         /* �ֶ�������ƫ���� */
    	unsigned char gps_data_good;       /* GPS������Ч״̬ */
    	
    	/* ���ݽ������ */
    	unsigned int new_time;                  /* UTCʱ�� */
    	unsigned int new_date;                  /* UTC���� */
    	float new_latitude;             		/* γ�� */
    	float new_longitude;            		/* ���� */
    	int new_altitude;             			/* ���θ߶� cm*/
    	float new_speed;                		/* ���� km/h */
    	float new_course;               		/* RMC��VTG�ֶδ�ƫ����Ϣ*/
    	float new_gps_yaw;              		/* HDT������Ϣ */
    	unsigned short new_hdop;                /* ˮƽ���� *100 */
    	unsigned char new_satellite_count;      /* ��ǰʹ�����ǵĿ��� */
    	unsigned char new_quality_indicator;    /* ��λ״̬ */

    	unsigned int last_RMC_ms;         	    /* �������ֶ�ʱ�� */
    	unsigned int last_GGA_ms;
    	unsigned int last_VTG_ms;
   		unsigned int last_HDT_ms;
	}gps_nmea;
	
	/* ʱ��ṹ�� */ 
	typedef struct _time
	{
		unsigned char year;
		unsigned short int month : 4;
		unsigned short int  : 4;
		unsigned short int day : 5;
		unsigned short int week : 3;
	}DateTime;
	
	/* GPS�������򣬹��ϲ�Ӧ�õ��� */ 
	typedef struct _gps_data {
        unsigned char instance; 		   /* GPSʵ������ */ 
        gps_status status;                 /* GPS��λ״̬ */
        Location location;                 /* GPS��λ���ĵ�ǰλ�� */
        DateTime date_time; 
        float ground_speed;                /* ����  m/s */
        float ground_course;               /* ���ٺ���  ��  ˳ʱ�� 0-360 */ 
        float gps_yaw;                     /* GPHDT�ֶκ�����Ϣ һ������˫���߲��� */
        unsigned short hdop;               /* ˮƽ����  cm */
        unsigned short vdop;               /* ��ֱ����  cm */
        unsigned char num_sats;            /* �ɼ����ǿ��� */
        unsigned char have_gps_yaw;        /* GPHDT�����ֶ���Ч */
        unsigned int last_gps_time_ms;     /* ����ȡGPS��Ϣʱ��ʱ��  ms */
    }gps_data;
    
    /* NMEA0183�ṹ����� */
    typedef struct _nmea0183
	{
		gps_nmea gpsParse;
		gps_data gpsData;
		unsigned char (*nmea_decode)(struct _nmea0183* pnmea, char c);		
	}NMEA0183; 
    
/**************** �������� ***************/

unsigned char nmea_decode(NMEA0183* pnmea, char c);

#endif


