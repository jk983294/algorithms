#include "MyUtility.h"

/**
 * 计算点对之间的最短距离
 */
struct Point {
    double x, y;
    double calc_distance(Point &other);
};

class MinDistancePointPair {
public:
    vector<Point> points;

public:
    MinDistancePointPair(vector<double> &x, vector<double> &y);
    double brutal_force(int low, int up);  //暴力计算从 i 到 j 的最短距离
    double divide_conquer(int low, int up);
};

bool less_point_cmp(Point &a, Point &b);  // sort by x

int main() {
    //计算点对之间的最短距离  No. 2.11
    vector<double> xx{1, 4, 6, 7, 9, 3, 11, 8, 10, 15}, yy{2, 3, 4, 5, 6, 7, 8, 9, 10, 6};
    int size = xx.size();

    MinDistancePointPair mdpp(xx, yy);
    cout << mdpp.brutal_force(0, size - 1) << endl;
    cout << mdpp.divide_conquer(0, size - 1) << endl;
    return 0;
}

MinDistancePointPair::MinDistancePointPair(vector<double> &x, vector<double> &y) {
    points.resize(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        points[i].x = x[i];
        points[i].y = y[i];
    }
    sort(points.begin(), points.end(), less_point_cmp);
}
double MinDistancePointPair::divide_conquer(int low, int up) {
    if (up - low <= 2) {  // 3个点暴力解出来
        return brutal_force(low, up);
    }
    int middle = (low + up) / 2, i, j;
    double minValue, middleValue, lowValue, upValue;
    minValue = min(divide_conquer(low, middle), divide_conquer(middle + 1, up));
    if ((up - low) % 2 == 0) {  // 奇数个点
        middleValue = (points[middle].x + points[middle + 1].x) / 2;
    } else {
        middleValue = points[middle].x;
    }  // 偶数个点
    lowValue = middleValue - minValue;
    upValue = middleValue + minValue;
    for (i = middle; i >= low && points[i].x > lowValue; --i)
        ;
    if (points[i].x < lowValue) ++i;
    for (j = middle + 1; j <= up && points[j].x < upValue; ++j)
        ;
    if (points[j].x > upValue) --j;
    return min(minValue, brutal_force(i, j));
}

double MinDistancePointPair::brutal_force(int low, int up) {
    double minDistance = std::numeric_limits<double>::max(), tmpDist;
    for (int i = low; i <= up; ++i) {
        for (int j = i + 1; j <= up; ++j) {
            tmpDist = points[i].calc_distance(points[j]);
            if (tmpDist < minDistance) {
                minDistance = tmpDist;
            }
        }
    }
    return minDistance;
}
double Point::calc_distance(Point &other) {
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}
bool less_point_cmp(Point &a, Point &b) { return a.x < b.x; }
