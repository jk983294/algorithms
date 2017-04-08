#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Vector.h"
#include "PSO.h"
using namespace std;

class NeuralNetwork
{
public:
    int numInput, numHidden, numOutput;                             //输入、隐藏、输出节点个数
    vector<double> inputs, ihOutputs, outputs;                      //输入、输入层到隐藏层、输出向量
    vector<double> ihSums, hoSums;                                  //输入层到隐藏层、隐藏层到输出层的加权和
    vector<double> ihBiases, hoBiases;                              //输入层到隐藏层、隐藏层到输出层的偏移
    vector<vector<double> > ihWeights, hoWeights;                   //输入层到隐藏层、隐藏层到输出层的权重
public:
    NeuralNetwork(int numInput, int numHidden, int numOutput);
    void SetWeights(vector<double> weights);
    vector<double> ComputeOutputs(vector<double> currInputs);       // t = f( weight*input + b )
    vector<double> Train(vector<vector<double> > &trainMatrix);
    double CrossEntropy(vector<vector<double> > &trainData, vector<double> &weights);
    double Test(vector<vector<double> > &testMatrix);               // returns the accuracy (percent correct predictions)

    //激励函数
    double SigmoidFunction(double x);
    vector<double> Softmax(vector<double> &hoSums);                 //Sigmoid的一般式 sigma = 1
    double StepFunction(double x);                                  //阶跃函数

};



void test_nn();
//util
int max_index(vector<double> &array);


#endif
