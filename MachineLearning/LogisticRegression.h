#ifndef LogisticRegression_H
#define LogisticRegression_H

#include <iostream>
#include <vector>
#include "Vector.h"
#include "Matrix.h"
using namespace std;


/************************************************************************/
/* 可用于概率预测，也可用于分类
只有在feature和target是线性关系时，才能用Logistic Regression
各feature之间不需要满足条件独立假设，但各个feature的贡献是独立计算的
主要适用于二分类，大于某阈值为一类，小于为另一类
训练的时候可以按照求似然函数的导数，使用梯度上升算法使得似然函数最大化*/
/************************************************************************/
class LogisticRegression{
public:
    Vector<double> y , theta;
    Vector<Vector<double> > x_matrix;                   //按行存储
    int demision , x_cnt;                               //维数，x的个数
    double learning_rate, precision, iter_cnt;          //学习速率,精度,迭代次数
public:
    LogisticRegression(string path);
    //每次迭代更新参数值时使用的样本，Batch使用了所有的样本
    void batch_gradient_descent();

    double estimation_under_current_theta(Vector<double> &x);
    void print_theta();
};

void test_LogisticRegression();




#endif
