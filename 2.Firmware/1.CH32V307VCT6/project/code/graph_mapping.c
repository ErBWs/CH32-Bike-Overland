//
// Created by Mr.WU on 2023/4/16.
//
#include "graph_mapping.h"


//settings of B_spline curve
double GlobalNodeVector[NODE_VECTOR_SIZE]={0};
double GlobalNipFactorVector[NIP_FACTOR_VECTOR_SIZE]={0};
node_typedef GlobalRefNodeList[REF_NODE_LIST_SIZE]={0};
B_Constructor_typedef Global_B_Constructor;

//settings of graph

nodeGraph_typedef   GlobalGraph;
node_typedef        GlobalGraph_NodeBuffer[GRAPH_NODE_TOTAL]={0};
gpsData_typedef     GlobalBase_GPS_data = {0};

//settings of stanley
node_typedef Global_current_node;
float Global_v_now;
float Global_yaw;
float Global_pd_array[GRAPH_NODE_TOTAL-1] = {0};
stanleyController_typedef   Global_stanleyController;
void latlonTodxdy(double lat, double *dx_dlat, double *dy_dlon)
{
    double R = 6378137.0f;
    double f = 1.0f/298.257223563f;
    lat = ANGLE_TO_RAD(lat);
    double A,B,C;
    A = (1.0f - f*(2.0f-f)* pow(sin(lat),2));
    B = 1.0f-f*(2.0f-f);
    C = R / sqrt(A);
    *dx_dlat = 1.0f/A * B * C;
    *dy_dlon = C * cos(lat);
}
void WGS_84_ConvertToXY(double base_latitude, double base_longitude, gpsDataLink_typedef gpsDATA, nodeLink_typedef nodesDATA, uint16_t counts)
{
    double radLat1 ,radLat2, radLong1, radLong2, delta_lat, delta_long;
    radLat1 = ANGLE_TO_RAD(base_latitude);
    radLong1 = ANGLE_TO_RAD(base_longitude);
    for(uint16_t i=0;i<counts;i++)
    {
        radLat2 = ANGLE_TO_RAD(gpsDATA[i].latitude);
        radLong2 = ANGLE_TO_RAD(gpsDATA[i].longitude);
        //¼ÆËãx
        delta_lat = radLat2 - radLat1;
        delta_long = 0;
        double x = 2*asin( sqrt( pow( sin( delta_lat/2 ),2) + cos( radLat1 )*cos( radLat2)*pow( sin( delta_long/2 ),2 ) ));
        x *= EARTH_RADIUS;

        //¼ÆËãy
        delta_lat = 0;
        delta_long = radLong1  - radLong2;
        double y = 2*asin( sqrt( pow( sin( delta_lat/2 ),2) + cos( radLat2 )*cos( radLat2)*pow( sin( delta_long/2 ),2 ) ) );
        y *= EARTH_RADIUS;

        nodesDATA[i].X = x;
        nodesDATA[i].Y = y;
    }
}
uint8_t B_ConstructorInit(B_Constructor_typedef *constructor,uint8_t ref_counts,uint8_t order)
{
    memset(constructor,0, sizeof(B_Constructor_typedef));
    if(order<=0)
    {
        printf("Order input Wrong!");
        return 1;
    }
    constructor->B_n = ref_counts-1;
    constructor->B_p = order-1;
    constructor->B_m = constructor->B_n + constructor->B_p + 1;
    if(constructor->B_n-constructor->B_p-1<0)
    {
        constructor->B_p = constructor->B_n ;
        printf("Warning the order is not fit the counts of control-point! Auto Fixed.");
    }
    constructor->is_init = 1;
    return 0;
}
uint8_t B_ConstructorBuffLink(B_Constructor_typedef *constructor, double *NodeVector, double *NipFactorVector, nodeLink_typedef refNodeList)
{
    if(!constructor->is_init)
    {
        printf("constructor may not be initialized!");
        return 1;
    }
    memset(NodeVector,0, sizeof(double)*(constructor->B_m + 1));
    memset(NipFactorVector,0,sizeof(double)*(constructor->B_n + 1));
    memset(refNodeList,0, sizeof(node_typedef)*(constructor->B_n + 1));
    constructor->NodeVector = NodeVector;
    constructor->NipFactorVector = NipFactorVector;
    constructor->refNodeList = refNodeList;
    constructor->is_link = 1;
    return 0;
}
void GraphInit(nodeGraph_typedef *graph,nodeLink_typedef nodeBuff,gpsData_typedef *base_gps_data,uint16_t buff_total)
{
    memset(graph,0, sizeof(nodeGraph_typedef));
    memset(nodeBuff,0, sizeof(node_typedef)* buff_total);
    graph->base_gps_data = base_gps_data;
    graph->nodeBuff = nodeBuff;
    graph->total = buff_total;
    graph->is_init = 1;
}
uint8_t B_GraphRegister(nodeGraph_typedef *graph, B_Constructor_typedef *constructor)
{
    if(!graph->is_init)
    {
        printf("graph may not be initialized!");
        return 1;
    }
    if(!constructor->is_init&&constructor->is_link)
    {
        printf("constructor may not be initialized or buff-linked!");
        return 1;
    }
    graph->B_constructor = constructor;
    graph->has_constructor = 1;
    return 0;
}

void stanleyControllerInit(stanleyController_typedef *controller, float k_gain, float L, float *yaw, float *v_now,node_typedef *current_node)
{
    memset(controller,0, sizeof(stanleyController_typedef));
    controller->k_gain = k_gain;
    controller->L = L;
    controller->yaw = yaw;
    controller->v_now = v_now;
    controller->current_node = current_node;
    controller->is_init = 1;
}
uint8_t stanleyBuffLink(stanleyController_typedef *controller, float *pd_array,float *pdd_array,uint16_t point_total)
{
    if(!controller->is_init)
    {
        printf("stanley_controller may not be initialized!");
        return 1;
    }
    if(pd_array!=NULL)
        memset(pd_array,0,sizeof(float)*point_total-1);
    if(pd_array!=NULL)
        memset(pdd_array,0,sizeof(float)*point_total-2);
    controller->pd_array = pd_array;
    controller->pdd_array = pdd_array;
    controller->is_link =  1;
    return 0;
}
uint8_t stanley_GraphRegister(nodeGraph_typedef *graph, stanleyController_typedef *controller)
{
    if(!graph->is_init)
    {
        printf("graph may not be initialized!");
        return 1;
    }
    if(!controller->is_init&&controller->is_link)
    {
        printf("controller may not be initialized or buff-linked!");
        return 1;
    }
    graph->Stanley_controller = controller;
    graph->has_stanley = 1;
    return 0;
}
void unEven(double *NodeVector, uint8_t p, uint8_t n)
{
    double piecewise = n-p+1;
    uint8_t flag = 1;
    if(piecewise<=1)
    {
        for (int i = p+1; i < n+p+2; ++i)
            NodeVector[i] = 1;
    }
    else
    {
        while(flag!=piecewise)
        {
            NodeVector[p+flag] = NodeVector[p+flag-1]+ 1/piecewise;
            flag+=1;
        }
        for (int i = n+1; i < n+p+2; ++i)
            NodeVector[i] = 1;
    }
}
double BaseIterateFunc(uint8_t i, uint8_t p, double u,const double *NodeVector)
{
    double result;
    double lenght1,lenght2;
    if(p==0)
    {
        result = (u>=NodeVector[i] && u<=NodeVector[i+1])? 1:0;
    }
    else
    {
        lenght1 = NodeVector[i+p]- NodeVector[i];
        lenght2 = NodeVector[i+p+1]- NodeVector[i+1];
        lenght1 = lenght1==0? 1:lenght1;
        lenght2 = lenght2==0? 1:lenght2;
        result = (u- NodeVector[i])/lenght1 * BaseIterateFunc(i,p-1,u,NodeVector)+
                 (NodeVector[i+p+1]- u)/lenght2 * BaseIterateFunc(i+1,p-1,u,NodeVector);
    }
    return result;
}
uint8_t GraphReferNodeInput(nodeGraph_typedef *graph,const double *nodes_set, uint16_t counts)
{
    if(!graph->is_init || !graph->has_constructor)
    {
        printf("graph may not be initialized or has no B_constructor!");
        return 1;
    }
    B_Constructor_typedef *constructor;
    constructor = graph->B_constructor;
    for(uint16_t i=0;i<counts;i++)
    {
        constructor->refNodeList[i].X = *(nodes_set+2*i);
        constructor->refNodeList[i].Y = *(nodes_set+2*i+1);
    }
    return 0;
}
uint8_t GraphReferNodeConvertInput(nodeGraph_typedef *graph, gps_st *gps_set, uint16_t counts)
{
    if(!graph->is_init || !graph->has_constructor)
    {
        printf("graph may not be initialized or has no B_constructor!");
        return 1;
    }
    nodeLink_typedef refNodeList;
    gpsData_typedef base_gps_data;
    refNodeList = graph->B_constructor->refNodeList;
    base_gps_data = *graph->base_gps_data;
//    double dx_lat,dy_lon;
//    latlonTodxdy(base_gps_data.latitude,&dx_lat,&dy_lon);
//    refNodeList[0].X = ANGLE_TO_RAD(gps_set[0].latitude - base_gps_data.latitude)*dx_lat;
//    refNodeList[0].Y = ANGLE_TO_RAD(gps_set[0].longitude - base_gps_data.longitude)*dy_lon;
//    //=========test=========
    refNodeList[0].X = 0;
    refNodeList[0].Y = 0;
//    //=========test=========
    double tempX=0,tempY=0;
    for(uint16_t i=1;i<counts;i++)
    {
        tempX += normalXArray[i];
        tempY += normalYArray[i];
        refNodeList[i].X = tempX* cosf(ANGLE_TO_RAD(ref_angle))+ tempY* sinf(ANGLE_TO_RAD(ref_angle));
        refNodeList[i].Y = tempX* sinf(ANGLE_TO_RAD(ref_angle))+ tempY* cosf(ANGLE_TO_RAD(ref_angle));
    }
//    WGS_84_ConvertToXY(base_gps_data.latitude,base_gps_data.longitude,gps_set,constructor->refNodeList,counts);
    return 0;
}
uint8_t GraphPathGenerate(nodeGraph_typedef *graph)
{
    if(!graph->is_init || !graph->has_constructor)
    {
        printf("graph may not be initialized or has no B_constructor!");
        return 1;
    }
    double step,u;
    B_Constructor_typedef *constructor;
    step = (double)(1.0/(graph->total-1));
    constructor = graph->B_constructor;

    unEven(constructor->NodeVector,constructor->B_p,constructor->B_n);
    for(int k=0;k<=graph->total-1;k++)
    {
        u = k * step;
        for(int i=0;i<constructor->B_n+1;i++)
        {
            if(u>=i*step&&u<i+constructor->B_p+1)//avoid meaningless iterations
                constructor->NipFactorVector[i] = BaseIterateFunc(i,constructor->B_p,u,constructor->NodeVector);
            else
                constructor->NipFactorVector[i] = 0;
            graph->nodeBuff[k].X += constructor->NipFactorVector[i] * constructor->refNodeList[i].X;
            graph->nodeBuff[k].Y += constructor->NipFactorVector[i] * constructor->refNodeList[i].Y;
        }
    }
    constructor->is_interpolated = 1;
    return 0;
}

uint8_t GraphNode_Diff(nodeGraph_typedef *graph)
{
    if(!graph->is_init || !graph->has_constructor || !graph->has_stanley)
    {
        printf("graph may not be initialized or has no B_constructor or no stanley!");
        return 1;
    }
    stanleyController_typedef *controller = graph->Stanley_controller;
    nodeLink_typedef node_list = graph->nodeBuff;
    for(int i=0;i<graph->total-1;i++)
    {
        // pd(i) = (p(i+1,2)-p(i,2))/(p(i+1,1)-p(i,1));
        controller->pd_array[i] = (float)((node_list[i+1].Y-node_list[i].Y)/(node_list[i+1].X-node_list[i].X));
    }
    controller->pd_array[graph->total-1] = controller->pd_array[graph->total-2];//give the final node's pd from the last node's
    return 0;
}
#define FORECAST_FACTOR 2
static uint8_t Stanley_CalculateIndexError(nodeGraph_typedef *graph)
{
    if(!graph->is_init || !graph->has_constructor || !graph->has_stanley)
    {
        printf("graph may not be initialized or has no B_constructor or no stanley!");
        return 1;
    }
    stanleyController_typedef *controller = graph->Stanley_controller;
    nodeLink_typedef node_list = graph->nodeBuff;
    double x,y,min_distance,temp;float yaw;int32_t N;uint16_t min_index;
    x = controller->current_node->X;
    y = controller->current_node->Y;
    yaw = *controller->yaw;
    N = FORECAST_FACTOR;
    x += controller->L * cosf(yaw);
    y += controller->L * sinf(yaw);

    if(controller->target_index+N +1 > graph->total-1)
    {
        N = graph->total-1 - controller->target_index -1;
    }
    for(uint16_t i=controller->target_index; i<=(uint16_t)(controller->target_index+N+1); i++)
    {
        temp = sqrt(pow(node_list[i].X - x,2)+pow(node_list[i].Y - y,2));
        if(i==controller->target_index)
        {
            min_distance = temp;
            min_index = controller->target_index;
        }
        else if (temp < min_distance)
        {
            min_distance = temp;
            min_index = i;
        }
    }
    controller->target_index = min_index;
    controller->error = (float)((y - node_list[min_index].Y)*(x-node_list[min_index].X)<0 ? -min_distance:min_distance);
    return 0;
}
#define PiPi(x)   if(x > PI)            \
                    x-=2*PI;            \
                    else if(x < -PI)    \
                    x+=2*PI;
uint8_t Stanley_Control(nodeGraph_typedef *graph)
{
    if(graph->is_finish)return 0;
    stanleyController_typedef *controller = graph->Stanley_controller;
    nodeLink_typedef node_list = graph->nodeBuff;
    uint8_t state = Stanley_CalculateIndexError(graph);
    if(state == 1)
        return 1;
    double target_x,target_y,x,y;float delta,temp,alpha=0;
    float yaw;
    if(controller->target_index!=graph->total-1)
    {
        target_x = node_list[controller->target_index+1].X;
        target_y = node_list[controller->target_index+1].Y;
        x = controller->current_node->X;
        y = controller->current_node->Y;
        yaw = *controller->yaw;
        temp = (float)atan2((target_y-y),(target_x-x));
        temp = (float)Pi_To_2Pi(temp);
//        temp = (float)((target_x-x)<0 ? temp+PI:temp);
        delta = temp - yaw;
        PiPi(delta);
        if(*controller->v_now!=0.0)
            alpha = atanf((controller->k_gain * controller->error)/ (*controller->v_now));
        controller->theta =  delta+alpha;
//        BlueToothPrintf("%f\n",RAD_TO_ANGLE(delta));
//        BlueToothPrintf("%f\n",RAD_TO_ANGLE(alpha));
    }
    else
    {
        graph->is_finish = 1;
    }
    return 0;
}










