//
// Created by Mr.WU on 2023/4/15.
//
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#ifndef GRAPH_MAPPING_H
#define GRAPH_MAPPING_H

#ifndef EARTH_RADIUS
            #define EARTH_RADIUS 6378137
#endif
#ifndef PI
            #define PI                  (3.1415926535898)
#endif
#ifndef ANGLE_TO_RAD
            #define ANGLE_TO_RAD(x) 	((x) * PI / 180.0)
#endif

#define B_ORDER                 4
#define B_REFER_POINT_COUNTS    10

#define NODE_VECTOR_SIZE        ((B_ORDER-1)+(B_REFER_POINT_COUNTS-1)+2)
#define NIP_FACTOR_VECTOR_SIZE  (B_REFER_POINT_COUNTS)
#define REF_NODE_LIST_SIZE      (B_REFER_POINT_COUNTS)
#define GRAPH_NODE_TOTAL        (B_REFER_POINT_COUNTS+100)



typedef struct
{
    double      latitude;                                                       // 当前目标点经度
    double      longitude;                                                      // 当前目标点纬度
}gpsData_typedef,*gpsDataLink_typedef;

typedef struct
{
    double		X;
    double 		Y;
}node_typedef,*nodeLink_typedef;
typedef struct
{
    uint8_t B_n;
    uint8_t B_p;
    uint8_t B_m;
    uint8_t  is_init : 1;
    uint8_t  is_link : 1;
    uint8_t  is_interpolated : 1;
    double *NodeVector;
    double *NipFactorVector;
    nodeLink_typedef refNodeList;
}B_Constructor_typedef,*B_Constructor_Link_typedef;
typedef struct {
    node_typedef *current_node;
    float *pd_array;
    float *pdd_array;
    float *yaw;
    float *v_now;
    float error;
    float k_gain;
    float L;
    float theta;
    uint16_t target_index;
    uint8_t  is_init : 1;
    uint8_t  is_link : 1;
}stanleyController_typedef;
typedef struct
{
    nodeLink_typedef nodeBuff;
    gpsData_typedef *base_node;
    B_Constructor_typedef *B_constructor;
    stanleyController_typedef *Stanley_controller;
    uint16_t total;
    uint8_t  is_init : 1;
    uint8_t  has_constructor : 1;
    uint8_t  has_stanley : 1;
    uint8_t  is_finish : 1;
}nodeGraph_typedef,*graphLink_typedef;

extern double                   GlobalNodeVector[NODE_VECTOR_SIZE];
extern double                   GlobalNipFactorVector[NIP_FACTOR_VECTOR_SIZE];
extern node_typedef             GlobalRefNodeList[REF_NODE_LIST_SIZE];
extern B_Constructor_typedef    Global_B_Constructor;


extern nodeGraph_typedef        GlobalGraph;
extern node_typedef             GlobalGraph_NodeBuffer[GRAPH_NODE_TOTAL];
extern gpsData_typedef          GlobalBase_GPS_data;

extern node_typedef Global_current_node;
extern float Global_v_now;
extern stanleyController_typedef    Global_stanleyController;
extern float Global_pd_array[GRAPH_NODE_TOTAL-1];

void WGS_84_ConvertToXY(double base_latitude, double base_longitude, gpsDataLink_typedef gpsDATA, nodeLink_typedef nodesDATA, uint16_t counts);
void B_ConstructorInit(B_Constructor_typedef *constructor,uint8_t ref_counts,uint8_t order);
void B_ConstructorBuffLink(B_Constructor_typedef *constructor, double *NodeVector, double *NipFactorVector, nodeLink_typedef refNodeList);
void B_GraphRegister(nodeGraph_typedef *graph, B_Constructor_typedef *constructor);
void stanleyControllerInit(stanleyController_typedef *controller, float k_gain, float L, float *yaw, float *v_now,node_typedef *current_node);
void stanleyBuffLink(stanleyController_typedef *controller, float *pd_array,float *pdd_array,uint16_t point_total);
void stanley_GraphRegister(nodeGraph_typedef *graph, stanleyController_typedef *controller);
void GraphInit(nodeGraph_typedef *graph,nodeLink_typedef nodeBuff,gpsData_typedef *base_gps_data,uint16_t buff_total);
void unEven(double *NodeVector, uint8_t p, uint8_t n);
double BaseIterateFunc(uint8_t i, uint8_t p, double u,const double *NodeVector);
void GraphReferNodeInput(nodeGraph_typedef *graph,const double *nodes_set, uint16_t counts);
void GraphPathGenerate(nodeGraph_typedef *graph);

#endif //GRAPH_MAPPING_H
