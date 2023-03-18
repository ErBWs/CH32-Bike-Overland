/*
 * sendware.h
 *
 *  Created on: 2021Äê12ÔÂ4ÈÕ
 *      Author: Lenovo
 */

#ifndef CODE_SENDWARE_H_
#define CODE_SENDWARE_H_

#include "zf_common_headfile.h"
#include "inc_all.h"


//#define BYTE0(x)   (*(char*)(&x))
//#define BYTE1(x)   (*((char*)(&x) + 1))
//#define BYTE2(x)   (*((char*)(&x) + 2))
//#define BYTE3(x)   (*((char*)(&x) + 3))

#define BYTE0(x)   (x & 0xff)
#define BYTE1(x)   ((x>>8) & 0xff )
#define BYTE2(x)   ((x>>16) & 0xff)
#define BYTE3(x)   ((x>>24) &0xff)

void vcan_sendware(void *wareaddr, uint32 waresize);
void ano_sendware(int16 yaw, int16 pitch, int16 roll, uint8 fu);

#endif /* CODE_SENDWARE_H_ */
