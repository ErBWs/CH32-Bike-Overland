// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/15.
//

#ifndef X7PRO_DRIVER_GPS_UBX_H
#define X7PRO_DRIVER_GPS_UBX_H

#include "ublox.h"

typedef struct {
    uint32_t timestamp_position; /**< Timestamp for position information */
    int32_t lat;                 /**< Latitude in 1E-7 degrees */
    int32_t lon;                 /**< Longitude in 1E-7 degrees */
    int32_t alt;                 /**< Altitude in 1E-3 meters (millimeters) above MSL  */
    
    uint32_t timestamp_variance;
    float s_variance_m_s; /**< speed accuracy estimate m/s */
    float c_variance_rad; /**< course accuracy estimate rad */
    uint8_t fix_type;     /**< 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.   */
    
    float eph; /**< GPS HDOP horizontal dilution of position in m */
    float epv; /**< GPS VDOP horizontal dilution of position in m */
    
    uint16_t noise_per_ms;      /**< */
    uint16_t jamming_indicator; /**< */
    
    uint32_t timestamp_velocity; /**< Timestamp for velocity informations */
    float vel_m_s;               /**< GPS ground speed (m/s) */
    float vel_n_m_s;             /**< North velocity in m/s */
    float vel_e_m_s;             /**< East velocity in m/s */
    float vel_d_m_s;             /**< Down velocity in m/s */
    float cog_rad;               /**< Course over ground (NOT heading, but direction of movement) in rad, -PI..PI */
    uint8_t vel_ned_valid;       /**< Flag to indicate if NED speed is valid */
    
    uint32_t timestamp_time; /**< Timestamp for time information */
    uint32_t time_gps_usec;  /**< Timestamp (microseconds in GPS format), this is the timestamp which comes from the gps module   */
    
    uint8_t satellites_used; /**< Number of satellites used */
    float hdop;
    float ndop;
    float edop;
    float vdop;
    float tdop;
    uint32_t alt_ellipsoid;
} gps_report_t;


err_t gps_ubx_init();
err_t gps_serial_rx_ind();
size_t gps_read(gps_report_t* report);


#endif //X7PRO_DRIVER_GPS_UBX_H
