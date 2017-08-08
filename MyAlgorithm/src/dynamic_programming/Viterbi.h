#ifndef VITERBI_H
#define VITERBI_H

#include <fstream>
#include <iostream>

using namespace std;

/**
 * 求栅格网络(Lattice Net)的最短距离
 */
class Viterbi {
public:
    vector<int> states;                  // ith step has states[i] states
    vector<int> path;                    // ith step through state[path[i]]
    vector<vector<int> > prenode;        // record the previous node of the shortest path for every step
    vector<vector<double> > distance;    // record distance from start to current state
    vector<double **> transform_matrix;  // transform_matrix[i] is transform probability of step i to step i+1
    int steps;

public:
    Viterbi(int steps, vector<int> &states, vector<double **> &transform_matrix);
    Viterbi(string filePath);
    void calculate();
    void print();
};
void Viterbi::calculate() {
    // init
    for (int j = 0; j < states[0]; j++) {
        prenode[0][j] = -1;
        distance[0][j] = 0;
    }
    // calculate
    double minValue;
    int minIndex;
    double **matrix;
    for (int i = 0; i < steps - 1; i++) {  // i = n-1 steps
        matrix = transform_matrix[i];
        for (int j = 0; j < states[i + 1]; j++) {  // ith step has j states
            minValue = distance[i][0] + matrix[0][j];
            minIndex = 0;
            for (int k = 0; k < states[i]; k++) {
                if (distance[i][k] + matrix[k][j] < minValue) {
                    minValue = distance[i][k] + matrix[k][j];
                    minIndex = k;
                }
            }
            distance[i + 1][j] = minValue;
            prenode[i + 1][j] = minIndex;
        }
    }
    path[steps - 1] = 0;  //  end node
    for (int i = steps - 1; i > 0; i--) {
        path[i - 1] = prenode[i][path[i]];
    }
}
Viterbi::Viterbi(string filePath) {
    ifstream ifs(filePath.c_str());
    ifs >> steps;
    states.resize(steps);
    transform_matrix.resize(steps - 1);
    int x, y, i, j, k;
    double **matrix;
    for (i = 0; i < steps; i++) {
        ifs >> states[i];
    }
    for (i = 0; i < steps - 1; i++) {
        ifs >> x >> y;
        matrix = new double *[x];
        for (j = 0; j < x; j++) {
            matrix[j] = new double[y];
        }
        for (j = 0; j < x; j++) {
            for (k = 0; k < y; k++) {
                ifs >> matrix[j][k];
            }
        }
        transform_matrix[i] = matrix;
    }
    prenode.resize(steps);
    distance.resize(steps);
    path.resize(steps);
    for (int i = 0; i < steps; i++) {
        prenode[i].resize(states[i]);
        distance[i].resize(states[i]);
    }
}
Viterbi::Viterbi(int steps, vector<int> &states, vector<double **> &transform_matrix) {
    this->steps = steps;
    this->states = states;
    this->transform_matrix = transform_matrix;

    prenode.resize(steps);
    distance.resize(steps);
    path.resize(steps);
    for (int i = 0; i < steps; i++) {
        prenode[i].resize(states[i]);
        distance[i].resize(states[i]);
    }
}
void Viterbi::print() {
    cout << "states for each step:" << endl;
    for (int i = 0; i < steps; i++) {
        cout << states[i] << " ";
    }
    cout << endl << "transform matrix :" << endl;
    for (int i = 0; i < steps - 1; i++) {
        double **matrix = transform_matrix[i];
        cout << "transform matrix " << i << " : " << endl;
        cout << states[i] << " : " << states[i + 1] << endl;
        for (int j = 0; j < states[i]; j++) {
            for (int k = 0; k < states[i + 1]; k++) {
                cout << matrix[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl << "previous node:" << endl;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < states[i]; j++) {
            cout << prenode[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "distance :" << endl;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < states[i]; j++) {
            cout << distance[i][j] << " ";
        }
        cout << endl;
    }
    cout << "path:" << endl;
    for (int i = 0; i < steps; i++) {
        cout << path[i] << " ";
    }
}

#endif
