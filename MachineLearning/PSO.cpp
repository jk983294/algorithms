#include "PSO.h"


Particle::Particle(vector<double> &position, double fitness, vector<double> &velocity, vector<double> &bestPosition, double bestFitness){
    this->position = position;
    this->fitness = fitness;
    this->velocity = velocity;
    this->bestPosition = bestPosition;
    this->bestFitness = bestFitness;
}
void Particle::set(vector<double> &position, double fitness, vector<double> &velocity, vector<double> &bestPosition, double bestFitness){
    this->position = position;
    this->fitness = fitness;
    this->velocity = velocity;
    this->bestPosition = bestPosition;
    this->bestFitness = bestFitness;
}
string Particle::ToString(){
    stringstream s;
    s<<"=========================="<<endl<<"Position: "<< position<< endl
        <<"Fitness = "<< fitness << endl<< "Velocity: "<< velocity<<endl;
    s<< "Best Position: "<< bestPosition<<endl<< "Best Fitness = " << bestFitness << endl
        << "=========================="<<endl;
    return s.str();
}
