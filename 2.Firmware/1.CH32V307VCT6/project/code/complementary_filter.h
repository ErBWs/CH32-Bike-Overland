/*
 * complementary_filter.h
 *
 *  Created on: Mar 15, 2023
 *      Author: sorrymaker
 */

#ifndef COMPLEMENTARY_FILTER_H_
#define COMPLEMENTARY_FILTER_H_

#include "inc_all.h"
#include "zf_common_headfile.h"

#define V_Q_POS     0.3f
#define DIS_Q_POS   0.8f
#define KNOT_To_MS(x)    ((x) * 0.514444f)

/*! \brief The data after performing Kalman fusion */
typedef struct {
    float v;
    float distance_north;
    float distance_east;
} kalman_data_t;

typedef struct {
    float q_pos; // Process noise variance for the position
    float q_vel; // Process noise variance for the velocity
    float r_pos; // Measurement noise variance - this is actually the variance of the measurement noise
    float r_old_pos;
    
    float pos;   // The pos calculated by the Kalman filter - part of the 2x1 state vector
    float vel;   // The gyro velocity calculated by the Kalman filter - part of the 2x1 state vector
    float bias;  // The bias of velocity
    
    float P[2][2]; // Error covariance 2x2 matrix
    unsigned char gps_valid_flag;
} kalman_filter_t;


typedef volatile struct {
    float x_velocity;
    float y_velocity;
    float acceleration;
    float yaw;
    float gpsvelocity;
    
    float velocity;
    float x_distance;
    float y_distance;
}carState;

extern kalman_data_t kalmanData;

extern kalman_filter_t kalmanVelocity;
extern kalman_filter_t kalmanDistanceX;
extern kalman_filter_t kalmanDistanceY;

extern carState carBodyState;

int num_times_nth_power_of_10(int num, int n);
double Cal_Angle(int16 gyro_x, int16 acc_y, int16 acc_z, int16 offset);
void Cal_YawAngle(float mag_gyro_z, float *yaw);
void gpsFusionyaw(float gpsangle, float *yaw);

void kalmanVelocityUpdata(carState *car, kalman_filter_t *kalmanVelocity, float dt);
void kalmanDistanceUpdata(carState *car, kalman_filter_t *kalmanDistanceX, kalman_filter_t *kalmanDistanceY, float dt);
void kalmanInit(carState *car, kalman_filter_t *kalmanDistanceX, kalman_filter_t *kalmanDistanceY, kalman_filter_t *kalmanVelocity, float *yaw);
double Pi_To_2Pi(double angle);
double Degree_To_360(double angle);

#endif /* COMPLEMENTARY_FILTER_H_ */
