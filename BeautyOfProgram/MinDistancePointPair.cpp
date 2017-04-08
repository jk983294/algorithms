#include "MinDistancePointPair.h"


void test_MinDistancePointPair(){
    double x[] = { 1, 4, 6, 7, 9, 3, 11, 8, 10, 15};
    double y[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 6};
    vector<double> xx, yy;
    int size = sizeof(x)/sizeof(double);
    to_vector(x,size,xx);
    to_vector(y,size,yy);

    MinDistancePointPair mdpp(xx, yy);
    cout<<mdpp.brutal_force(0, size-1)<<endl;
    cout<<mdpp.divide_conquer(0, size-1)<<endl;
}



MinDistancePointPair::MinDistancePointPair(vector<double> &x, vector<double> &y){
    points.resize(x.size());
    for (unsigned int i =0; i < x.size(); ++i){
        points[i].x = x[i];
        points[i].y = y[i];
    }
    sort(points.begin(), points.end(), less_point_cmp);
}
double MinDistancePointPair::divide_conquer(int low,int up){
    if (up - low <= 2){             // 3个点暴力解出来
        return brutal_force(low, up);
    }
    int middle = (low + up ) /2 , i , j;
    double minest, middlevalue, lowvalue, upvalue;
    minest = min(divide_conquer(low,middle),divide_conquer(middle + 1, up));
    if( (up - low) % 2 == 0 ){      //奇数个点
        middlevalue = (points[middle].x + points[middle+1].x)/2;
    } else{
        middlevalue = points[middle].x;
    }                               //偶数个点
    lowvalue = middlevalue - minest;
    upvalue = middlevalue + minest;
    for(i = middle; i>=low && points[i].x > lowvalue; --i);
        if(points[i].x < lowvalue)
            ++i;
    for(j = middle+1; j<=up && points[j].x < upvalue; ++j);
        if(points[j].x > upvalue)
            --j;
    return min(minest, brutal_force(i,j));
}
double MinDistancePointPair::brutal_force(int low,int up){
    double mindistance = BIGDOUBLE, tmpdist;
    for (int i = low; i <= up; ++i)    {
        for (int j = i+1; j <= up; ++j)    {
            tmpdist = points[i].calc_distance(points[j]);
            if(tmpdist < mindistance){
                mindistance = tmpdist;
            }
        }
    }
    return mindistance;
}
double mypoint::calc_distance(mypoint &other){
    return sqrt( (x-other.x)*(x-other.x) + (y-other.y)*(y-other.y) );
}
bool less_point_cmp(mypoint &a,mypoint &b){
    return a.x < b.x;
}
