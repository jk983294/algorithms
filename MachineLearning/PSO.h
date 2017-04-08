#ifndef PSO_H
#define PSO_H
#include "Vector.h"

/************************************************************************/
/* 粒子群优化                                                             */
/************************************************************************/

class Particle
{
public:
    vector<double> position; // equivalent to x-Values and/or solution
    vector<double> velocity, bestPosition; // best position found so far by this Particle
    double fitness, bestFitness;
public:
    Particle(){};
    Particle(vector<double> &position, double fitness, vector<double> &velocity, vector<double> &bestPosition, double bestFitness);
    void set(vector<double> &position, double fitness, vector<double> &velocity, vector<double> &bestPosition, double bestFitness);
    string ToString();
}; // class Particle


#endif
