/*
 * complementary_filter.c
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#include "complementary_filter.h"

kalman_filter_t kalmanVelocity = {0};
kalman_filter_t kalmanDistanceX = {0};
kalman_filter_t kalmanDistanceY = {0};

carState carBodyState = {0};

/*
 * 一阶互补滤波
 * mag_gyro_z,yaw：x轴陀螺仪采集数据, 偏航角解算
 * weight：权重
 * dt：计算周期（s）
 * return：滤波后角度
 */
void Cal_YawAngle(float mag_gyro_z, float *Yaw )
{
    float d_gyro_angle = 0, dt = 0.0023f, weight = 0.2f;
    //陀螺仪积分

    d_gyro_angle = ((double)mag_gyro_z) * dt;
    if (gps_tau1201_flag == 1)
    {
            if (gps_tau1201.direction == *Yaw)  *Yaw = gps_tau1201.direction;
            if (gps_tau1201.direction < *Yaw)   *Yaw -= (mag_gyro_z - gps_tau1201.direction)*weight;
            if (gps_tau1201.direction > *Yaw)   *Yaw += (mag_gyro_z - gps_tau1201.direction)*weight;
    }
    *Yaw += d_gyro_angle;
}

double Pi_To_Pi(double angle)
{
    if(angle > pi)
        angle = angle - 2 * pi;
    else if (angle < -pi)
        angle = angle + 2 * pi;
    
    return angle;
}

double Degree_To_360(double angle)
{
    if (angle < 0)
    {
        angle += 360;
    }
    return angle;
}

double Degree_To_Degree(double angle)
{
    if(angle > 180)
        angle = angle - 360;
    else if(angle < -180)
        angle = angle + 360;
    
    return angle;
}

/*!
    \brief      num*(10^n)
    \param[in]  num
    \param[in]  n (n<=3 && n>=0)
    \retval     num*(10^n)
*/
int num_times_nth_power_of_10(int num, int n)
{
    switch (n)
    {
        case 0:num = num + 0;
            break;
        case 1:num = (num << 3) + (num << 1);
            break;
        case 2:num = (num << 6) + (num << 5) + (num << 2);
            break;
        case 3:num = (num << 10) - (num << 4) - (num << 3);
            break;
        default:
            while (n > 0) {
                num *= 10;
                n--;
            }
            break;
    }
    return num;
}

/*!
 *
 */
void kalman_config_v(kalman_filter_t *kalman) {
    kalman->q_pos = V_Q_POS;
    kalman->q_vel = 0.1f;
    kalman->r_pos = 0.2f;
    kalman->r_old_pos = kalman->r_pos;
    kalman->gps_valid_flag = 1;
    
    kalman->pos = 0;
    kalman->vel = 0.0f;
    kalman->bias = 0.0f;
    
    kalman->P[0][0] = 0;
    kalman->P[0][1] = 0;
    kalman->P[1][0] = 0;
    kalman->P[1][1] = 0;
}

void kalman_config_distance(kalman_filter_t *kalman, float pos_0) {
    kalman->q_pos = DIS_Q_POS;
    kalman->q_vel = 0.22f;
    kalman->r_pos = 3.0f;
    kalman->r_old_pos = kalman->r_pos;
    
    kalman->pos = pos_0;
    kalman->vel = 0.0f;
    kalman->bias = 0.0f;
    
    kalman->P[0][0] = 0;
    kalman->P[0][1] = 0;
    kalman->P[1][0] = 0;
    kalman->P[1][1] = 0;
}

/*!
    \brief      Kalman Fusion
    \param[in]  kalman:Kalman Structures
    \param[in]  new_pos
    \param[in]  new_vel
    \param[in]  dt:Timestamp between two fusions
    \param[in]  angle_flag:Timestamp between two fusions
    \retval     Position after fusion
    \note       The pos should be in degrees and the rate should be in degrees per second
                and the delta time in seconds
*/
float kalman_update(kalman_filter_t *kalman, float new_pos, float new_vel, float dt)
{
    if (kalman->gps_valid_flag == 1)
        kalman->r_pos = kalman->r_old_pos;
    else if (kalman->gps_valid_flag == 2)
        kalman->r_pos = 20;
    else if (kalman->gps_valid_flag == 0)
        kalman->r_pos = 100000;
    
    if (kalman->q_pos == V_Q_POS)
        kalman->gps_valid_flag = 2;
    else if (kalman->q_pos == DIS_Q_POS)
        kalman->gps_valid_flag = 0;
    
    /* Discrete Kalman filter time update equations - Time Update ("Predict") */
    /* Update xhat - Project the state ahead */
    /* Step 1 */
    kalman->vel = new_vel - kalman->bias;
    kalman->pos += dt * kalman->vel;
    
    /* Update estimation error covariance - Project the error covariance ahead */
    /* Step 2 */
    kalman->P[0][0] += dt * (dt * kalman->P[1][1] + kalman->P[0][1] + kalman->P[1][0]) + kalman->q_pos;
    kalman->P[0][1] += dt * kalman->P[1][1] + kalman->q_pos;
    kalman->P[1][0] += dt * kalman->P[1][1] + kalman->q_vel;
    kalman->P[1][1] += kalman->q_vel;
    
    /* Calculate pos and velocity - Update estimate with measurement zk (new_pos) */
    /* Step 3 */
    /* pos difference */
    float y = new_pos - kalman->pos;
    
    /* Discrete Kalman filter measurement update equations - Measurement Update ("Correct") */
    /* Calculate Kalman gain - Compute the Kalman gain */
    /* Step 4 */
    /* Estimate error */
    float S = kalman->P[0][0] + kalman->r_pos;
    
    /* Step 5 */
    float K[2];
    K[0] = kalman->P[0][0] / S;
    K[1] = kalman->P[1][0] / S;
    
    /* Step 6 */
    kalman->pos += K[0] * y;
    kalman->vel += K[1] * y;
    
    /* Calculate estimation error covariance - Update the error covariance */
    /* Step 7 */
    float P00_temp = kalman->P[0][0];
    float P01_temp = kalman->P[0][1];
    
    kalman->P[0][0] -= K[0] * P00_temp;
    kalman->P[0][1] -= K[0] * P01_temp;
    kalman->P[1][0] -= K[1] * P00_temp;
    kalman->P[1][1] -= K[1] * P01_temp;
    
    return kalman->pos;
}

void sensorVelocityDataConversion(carState *car)
{
    car->acceleration = imu_data.w_acc.x / 1000;

    float temp = (float)gps_tau1201.speed;
//    int v_decimal = num_times_nth_power_of_10(1,gps_tau1201.speed);
    car->gpsvelocity = KNOT_To_MS(temp);
}

void kalmanVelocityUpdata(carState *car, kalman_filter_t *kalmanVelocity, float dt)
{
    sensorVelocityDataConversion(car);
    float lastVelocity = car->velocity;
    float Weight = 0.3f;
    car->velocity = kalman_update(kalmanVelocity,car->gpsvelocity,car->acceleration,dt);
    car->velocity = Weight * car->velocity + (1-Weight) * lastVelocity;
    kalmanVelocity->gps_valid_flag = 1;
}

void senserDistanceDataConversion(carState *car)
{
    car->yaw = ANGLE_TO_RAD(car->yaw);
    car->x_velocity = car->velocity * cosf(car->yaw);
    car->y_velocity = car->velocity * sinf(car->yaw);
}

void kalmanDistanceUpdata(carState *car, kalman_filter_t *kalmanDistanceX, kalman_filter_t *kalmanDistanceY, float dt)
{
    senserDistanceDataConversion(car);
    car->x_distance = kalman_update(kalmanDistanceX, car->x_distance, car->x_velocity, dt);
    car->y_distance = kalman_update(kalmanDistanceY,car->y_distance,car->y_velocity, dt);
}

void kalmanInit(carState *car, kalman_filter_t *kalmanDistanceX, kalman_filter_t *kalmanDistanceY, kalman_filter_t *kalmanVelocity, float *yaw)
{
    car->yaw = *yaw;
    kalman_config_v(kalmanVelocity);
    kalman_config_distance(kalmanDistanceX,car->x_distance);
    kalman_config_distance(kalmanDistanceY,car->y_distance);
}
