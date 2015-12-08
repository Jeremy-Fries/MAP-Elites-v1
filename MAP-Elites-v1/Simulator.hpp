//
//  Simulator.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/1/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Simulator_hpp
#define Simulator_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>
#include "Craft.hpp"
#include "State.hpp"
#include "dynamics.h"
#include "anglemath.h"

using namespace std;

class Simulator{
    friend class Craft;
    friend class State;
    friend class Wrapper;
protected:
    int linear, rotational, numalf;
    double t, anglechange, fitness;
    double tstep;
    double const tmax = 60;
    double const rhoair = 1.2;

    int linear, rotational, numalf;     //number of linear and rotational DOFs, number of AOAs with CL and CD values
    double t, anglechange, fitness;     //time, rotational tracker, fitness value(likely to change)
    double const tstep = 0.1;           //simulation calculates values every 0.1 seconds
    double const tmax = 60;             //Maximum time that simulation will run for
    double const rhoair = 1.2;          //Density of air, used for aerodynamic calculations
    
    
    //holding values for fitness calculations

    vector<double> xpositions;
    vector<double> zpositions;
    vector<double> xvels;
    vector<double> zvels;
    vector<double> xke;
    vector<double> zke;
    vector<double> xaccels;
    vector<double> zaccels;
    vector<double> anglepos;
    vector<double> anglevel;
    vector<double> angleaccel;
    vector<double> angleke;
    
    //track past states - We might not need this if we are holding above fitness values.
    vector<State> stateholder;  // once craft and state class are intialized
    
    //Vectors for Communicating/Manipulating controls and forces
    //vector<double> controls;
    vector<double> forces;
    vector<vector<double> > aero;
    
    // Single craft parameters
    craft lander;
    State currentstate;
    ofstream myfile;
public:
// --------------------------------------------------
    int loadaero();
    void fitnessvector();
    void initialize_sim();
    void run_sim(vector<double>);
    void end_sim();
// --------------------------------------------------
    
// --------------------------------------------------
private:
    
    
    
    
  
    
    
    
    
    
};
#endif /* Simulator_hpp */
