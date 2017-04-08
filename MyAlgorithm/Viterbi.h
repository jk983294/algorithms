#ifndef VITERBI_H
#define VITERBI_H

#include <iostream>
#include <fstream>
using namespace std;

/**
求栅格网络(Lattice Net)的最短距离
**/


class Viterbi{
public:
    vector<int> states;     // ith step has states[i] states
    vector<int> path;       //ith step through state[path[i]]
    vector<vector<int> > prenode;   //record the previous node of the shortest path for every step
    vector<vector<double> > distance;  //record distance from start to current state
    vector<double **> transform_matrix; //transform_matrix[i] is transform probability of step i to step i+1
    int steps;
public:
    Viterbi(int steps,  vector<int> &states, vector<double **> &transform_matrix);
    Viterbi(string filepath);
    void calculate();
    void print();
};
void Viterbi::calculate(){
    //init
    for(int j=0; j< states[0]; j++){  prenode[0][j] = -1;   distance[0][j] = 0; }
    //calculate
    double minvalue;    int minindex;
    double** matrix;
    for(int i =0; i< steps-1; i++){     //i = n-1 steps
        cout<<"step "<<i<<endl;
        matrix = transform_matrix[i];
        for(int j=0; j< states[i+1]; j++){  //ith step has j states
            minvalue = distance[i][0]+matrix[0][j];     minindex = 0;
            for(int k=0; k< states[i]; k++){
                if(distance[i][k]+matrix[k][j] < minvalue){
                    minvalue = distance[i][k]+matrix[k][j];     minindex = k;
                }
            }
            distance[i+1][j] = minvalue;    prenode[i+1][j] = minindex;
        }
    }
    path[steps-1] = 0;  //  end node
    for(int i = steps -1; i>0; i--){
        path[i-1] = prenode[i][path[i]] ;
    }
}
Viterbi::Viterbi(string filepath){
    ifstream ifs(filepath.c_str());
    ifs>>steps;
    states.resize(steps);   transform_matrix.resize(steps-1);
    int x,y,i,j,k;    double **matrix;
    for(i =0; i< steps; i++){   ifs>>states[i];}
    for(i =0; i< steps-1; i++){
        ifs>>x>>y;
        matrix = new double*[x];
        for(j=0; j<x;j++){ matrix[j] = new double[y]; }
        for(j=0; j<x;j++){  for(k=0; k<y;k++){  ifs>>matrix[j][k];  }}
        transform_matrix[i] = matrix;
    }
    prenode.resize(steps);  distance.resize(steps); path.resize(steps);
    for(int i =0; i< steps; i++){
        prenode[i].resize(states[i]);
        distance[i].resize(states[i]);
    }
}
Viterbi::Viterbi(int steps,  vector<int> &states, vector<double **> &transform_matrix){
    this->steps = steps;
    this->states = states;
    this->transform_matrix = transform_matrix;

    prenode.resize(steps);  distance.resize(steps); path.resize(steps);
    for(int i =0; i< steps; i++){
        prenode[i].resize(states[i]);
        distance[i].resize(states[i]);
    }
}
void Viterbi::print(){
    cout<<"states for each step:"<<endl;
    for(int i =0; i< steps; i++){  cout<<states[i]<<" "; }
    cout<<endl<<"transform matrix :"<<endl;
    for(int i =0; i< steps-1; i++){
        double** matrix = transform_matrix[i];
        cout<<"transform matrix "<<i<<" : "<<endl;
        cout<<states[i]<<" : "<<states[i+1]<<endl;
        for(int j =0; j< states[i]; j++ ){
            for(int k =0; k< states[i+1]; k++ ){    cout<<matrix[j][k]<<" ";    }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl<<"previous node:"<<endl;
    for(int i =0; i< steps; i++){
        for(int j =0; j< states[i]; j++ ){  cout<<prenode[i][j]<<" "; } cout<<endl;
    }
    cout<<endl<<"distance :"<<endl;
    for(int i =0; i< steps; i++){
        for(int j =0; j< states[i]; j++ ){  cout<<distance[i][j]<<" "; } cout<<endl;
    }
    cout<<"path:"<<endl;
    for(int i =0; i< steps; i++){  cout<<path[i]<<" "; }
}

void test_Viterbi(){
//    int steps = 4;
//    vector<int> states(steps);      states[0] = states[3] = 1;   states[1] = states[2] = 2;
//    vector<double **> transform_matrix(3);
////    double matrix0[1][2] = {{0.6,0.4}};
//    double** matrix = new double*[1];
//    matrix[0] = new double[2];
//    matrix[0][0] = 0.6; matrix[0][1] = 0.4;
//    transform_matrix[0] = matrix;
////    double matrix1[2][2] = {{0.7,0.3},{0.6,0.4}};
//    matrix = new double*[2];
//    matrix[0] = new double[2];  matrix[1] = new double[2];
//    matrix[0][0] = 0.7; matrix[0][1] = 0.3; matrix[1][0] = 0.6; matrix[1][1] = 0.4;
//    transform_matrix[1] = matrix;
////    double matrix2[2][1] = {{0.3},{0.7}};
//    matrix = new double*[2];
//    matrix[0] = new double[1];  matrix[1] = new double[1];
//    matrix[0][0] = 0.3;  matrix[1][0] = 0.7;
//    transform_matrix[2] = matrix;
//
//    Viterbi v(steps,states,transform_matrix);
    Viterbi v("ViterbiConf.txt");
    v.print();
    v.calculate();
    v.print();
}

#endif
