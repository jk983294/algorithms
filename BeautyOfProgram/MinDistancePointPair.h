#ifndef MINDISTANCEPOINTPAIR_H
#define MINDISTANCEPOINTPAIR_H

#include "myutility.h"
/************************************************************************/
/* 计算点对之间的最短距离                                                   */
/************************************************************************/
typedef struct mypoint{
    double x,y;
    double calc_distance(mypoint &other);
}mypoint;

class MinDistancePointPair{
public:
    vector<mypoint> points;
public:
    MinDistancePointPair(vector<double> &x, vector<double> &y);
    double brutal_force(int low,int up);        //暴力计算从 i 到 j 的最短距离
    double divide_conquer(int low,int up);
};

bool less_point_cmp(mypoint &a,mypoint &b);
void test_MinDistancePointPair();





#endif
