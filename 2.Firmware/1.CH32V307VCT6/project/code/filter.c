/*
 * filter.c
 *
 *  Created on: 2023��2��7��
 *      Author: sorrymaker
 */


#include "filter.h"

//******Kalman�˲���******//
//-------------------------------------------------------
static  float Q_angle=0.001, Q_gyro=0.001, R_angle=10, dt=0.006;
    //Q���󣬶�̬��Ӧ����
static float Pk[2][2] = { {1, 0}, {0, 1 }};

static float Pdot[4] ={0,0,0,0};

static float q_bias=0, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//-------------------------------------------------------
void Kalman_Filter(float Accel,float Gyro)
{
    imu_data.pit+=(Gyro-q_bias) * dt; ///Ԥ��ֵ
    Pdot[0]=Q_angle - Pk[0][1] - Pk[1][0];
    Pdot[1]= -Pk[1][1];
    Pdot[2]= -Pk[1][1];
    Pdot[3]=Q_gyro;

    Pk[0][0] += Pdot[0] * dt;
    Pk[0][1] += Pdot[1] * dt;
    Pk[1][0] += Pdot[2] * dt;
    Pk[1][1] += Pdot[3] * dt;

    angle_err = Accel -imu_data.pit;///����ֵ-Ԥ��ֵ

    PCt_0 =  Pk[0][0];
    PCt_1 =  Pk[1][0];

    E = R_angle + PCt_0;

    K_0 = PCt_0 / E; ///����������
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = Pk[0][1];

    Pk[0][0] -= K_0 * t_0;
    Pk[0][1] -= K_0 * t_1;
    Pk[1][0] -= K_1 * t_0;
    Pk[1][1] -= K_1 * t_1;

    imu_data.pit+= K_0 * angle_err; ///���ŽǶ� = Ԥ��ֵ + ���������� * ������ֵ - Ԥ��ֵ��
    q_bias  += K_1 * angle_err;
    //GYRO_Real.Y = Gyro-q_bias;
}


//#define ABS(x) ( (x)>0?(x):-(x) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
//-----Butterworth����-----//
Butter_Parameter Butter_80HZ_Parameter_Acce,Butter_60HZ_Parameter_Acce,Butter_51HZ_Parameter_Acce,
                 Butter_30HZ_Parameter_Acce,Butter_20HZ_Parameter_Acce,Butter_15HZ_Parameter_Acce,
                 Butter_10HZ_Parameter_Acce,Butter_5HZ_Parameter_Acce,Butter_2HZ_Parameter_Acce;
Butter_BufferData Butter_Buffer[3];
Butter_BufferData Butter_Buffer_Feedback[3];

/****************************************
     Butterworth��ͨ�˲�����ʼ����http://blog.csdn.net/u011992534/article/details/73743955
***************************************/
void Butterworth_Parameter_Init(void)
{
  set_cutoff_frequency(200, 80,&Butter_80HZ_Parameter_Acce);
  set_cutoff_frequency(200, 60,&Butter_60HZ_Parameter_Acce);
  set_cutoff_frequency(200, 51,&Butter_51HZ_Parameter_Acce);
  set_cutoff_frequency(200, 30,&Butter_30HZ_Parameter_Acce);
  set_cutoff_frequency(200, 20,&Butter_20HZ_Parameter_Acce);
  set_cutoff_frequency(200, 15,&Butter_15HZ_Parameter_Acce);
  set_cutoff_frequency(200, 10,&Butter_10HZ_Parameter_Acce);
  set_cutoff_frequency(200, 5 ,&Butter_5HZ_Parameter_Acce);
  set_cutoff_frequency(200, 2 ,&Butter_2HZ_Parameter_Acce);
}

/*************************************************
������: float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
˵��:   ���ٶȼƵ�ͨ�˲���
���:   float curr_input ��ǰ������ٶȼƣ��˲����������˲�������
����:   ��
��ע:   2��Butterworth��ͨ�˲���
*************************************************/
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
{
        /* ���ٶȼ�Butterworth�˲� */
    /* ��ȡ����x(n) */
        static int LPF_Cnt=0;
        Buffer->Input_Butter[2]=curr_input;
        if(LPF_Cnt>=100)
        {
    /* Butterworth�˲� */
        Buffer->Output_Butter[2]=
         Parameter->b[0] * Buffer->Input_Butter[2]
        +Parameter->b[1] * Buffer->Input_Butter[1]
    +Parameter->b[2] * Buffer->Input_Butter[0]
        -Parameter->a[1] * Buffer->Output_Butter[1]
        -Parameter->a[2] * Buffer->Output_Butter[0];
        }
        else
        {
          Buffer->Output_Butter[2]=Buffer->Input_Butter[2];
          LPF_Cnt++;
        }
    /* x(n) ���б��� */
        Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
        Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
    /* y(n) ���б��� */
        Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
        Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
        return Buffer->Output_Butter[2];
}

// discrete low pass filter, cuts out the
// high frequency noise that can drive the controller crazy
//derivative = _last_derivative + _d_lpf_alpha * (derivative - _last_derivative);
float set_lpf_alpha(int16_t cutoff_frequency, float time_step)
{
    // calculate alpha
    float lpf_alpha;
    float rc = 1/(2*3.14*cutoff_frequency);
    lpf_alpha = time_step / (time_step + rc);
    return lpf_alpha;
}

/************************************************************************/
void set_cutoff_frequency(float sample_frequent, float cutoff_frequent,Butter_Parameter *LPF)
{
    float fr = sample_frequent / cutoff_frequent;
    float ohm = tanf(M_PI_F / fr);
    float c = 1.0f + 2.0f * cosf(M_PI_F / 4.0f) * ohm + ohm * ohm;
    if (cutoff_frequent <= 0.0f) {
        // no filtering
        return;
    }
    LPF->b[0] = ohm * ohm / c;
    LPF->b[1] = 2.0f * LPF->b[0];
    LPF->b[2] = LPF->b[0];
    LPF->a[0]=1.0f;
    LPF->a[1] = 2.0f * (ohm * ohm - 1.0f) / c;
    LPF->a[2] = (1.0f - 2.0f * cosf(M_PI_F / 4.0f) * ohm + ohm * ohm) / c;
}

void steepest_descend(int32 arr[],uint8 len,_steepest_st *steepest,uint8 step_num,int32 in)
{
    uint8 updw = 1;//0 dw,1up
    int16 i;
    uint8 step_cnt=0;
    uint8 step_slope_factor=1;
    uint8 on = 1;
    int8 pn = 1;
    //float last = 0;
    float step = 0;
    int32 start_point = 0;
    int32 pow_sum = 0;

    steepest->lst_out = steepest->now_out;

    if( ++(steepest->cnt) >= len )
    {
        (steepest->cnt) = 0; //now
    }

    //last = arr[ (steepest->cnt) ];

    arr[ (steepest->cnt) ] = in;

    step = (float)(in - steepest->lst_out)/step_num ;//�ݶ�

    if(ABS(step)<1)//��������<1���ж���Ч
    {
        if(ABS(step)*step_num<2)
        {
            step = 0;
        }
        else
        {
          step = (step > 0) ? 1.0f : -1.0f;
        }
    }

    start_point = steepest->lst_out;
    do
    {
        //start_point = steepest->lst_out;
        for(i=0;i<len;i++)
        {
//          j = steepest->cnt + i + 1;
//          if( j >= len )
//          {
//              j = j - len; //˳������
//          }
            pow_sum += my_pow(arr[i] - start_point );// /step_num;//������С����**

            //start_point += pn *(step_slope_factor *step/len);
        }

        if(pow_sum - steepest->lst_pow_sum > 0)
        {
            if(updw==0)
            {
                on = 0;
            }
            updw = 1;//������
            pn = (pn == 1 )? -1:1;

        }
        else
        {
            updw = 0; //�����½�
            if(step_slope_factor<step_num)
            {
                step_slope_factor++;
            }
        }

        steepest->lst_pow_sum = pow_sum;
        pow_sum = 0;
        start_point += pn *step;//����

        if(++step_cnt > step_num)//���Ƽ������
        {
            on = 0;
        }
            //////
            if(step_slope_factor>=2)//�����½�����1�Σ���ʡʱ�䣬���������ͺ���cpuʱ���ԣ�ɲ���
            {
                on = 0;

            }
            //////

    }
    while(on==1);

    steepest->now_out = start_point ;//0.5f *(start_point + steepest->lst_out);//

    steepest->now_velocity_xdt = steepest->now_out - steepest->lst_out;
}
 void Moving_Average(float moavarray[],uint16 len ,uint16 *fil_cnt,float in,float *out)
{
    uint16 width_num;
    float last;

    width_num = len ;

    if( ++*fil_cnt >= width_num )
    {
        *fil_cnt = 0; //now
    }

    last = moavarray[ *fil_cnt ];

    moavarray[ *fil_cnt ] = in;

    *out += ( in - ( last  ) )/(float)( width_num ) ;
    //*out += 0.00001f *(in - *out);
    *out += 0.00001f *LIMIT((in - *out),-1,1);  //���ݾ����������

}
void LPF_1(float hz,float time,float in,float *out)
{
    *out += ( 1 / ( 1 + 1 / ( hz *6.28f *time ) ) ) *( in - *out );

}
void limit_filter(float T,float hz,_lf_t *data,float in)
{
    float abs_t;
    LPF_1(hz,T,  in,&(data->lpf_1));
    abs_t = ABS(data->lpf_1);
    data->out = LIMIT(in,-abs_t,abs_t);

}
void fix_inte_filter(float dT,_fix_inte_filter_st *data)
{

    data->out += (data->in_est_d + data->e ) *dT;

    data->e = data->fix_kp *(data->in_obs - data->out);

    if(data->e_limit>0)
    {
        data->e = LIMIT(data->e,-data->e_limit,data->e_limit);
    }
}

