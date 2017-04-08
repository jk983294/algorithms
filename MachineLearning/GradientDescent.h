#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H
#include <iostream>
#include <vector>
#include "Vector.h"
#include "Matrix.h"
using namespace std;


/************************************************************************/
/* 适用于无约束优化问题，目标函数有一阶导数，精度要求不很高的情况
迭代终止准则:
1 根据两次迭代的绝对误差
2 根据目标函数梯度的模足够小
适用于求函数的局部最小值，如果是局部最大值，使用梯度上升法
搜索极小值，必须向负梯度方向(-dy/dx)搜索
输入为(x1, x2 ...  xn, y )  拟合 y = theta0 + theta1*x1 + ... + thetan*xn
目标函数是  使得误差函数最小   J(theta) = sigma (pow( ( h_theta(xi) - yi), 2))    */
/************************************************************************/
class GradientDescent{
public:
    Vector<double> y , theta;
    Vector<Vector<double> > x_matrix;               //按行存储
    int demision , x_cnt;                           //维数，x的个数
    double learning_rate, precision, iter_cnt;      //学习速率,精度,迭代次数
public:
    GradientDescent(string path);
    //每次迭代更新参数值时使用的样本，Batch使用了所有的样本，Stochastic每次使用一个样本
    void batch_gradient_descent();
    void stochastic_gradient_descent();

    double estimation_under_current_theta(Vector<double> &x);
    void print_theta();
};

void test_GradientDescent();

#endif
