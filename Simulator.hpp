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
protected:
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
    vector<double> controls;
    vector<double> forces;
    vector<vector<double> > aero;
    
    // Single craft parameters
    craft lander;
    State currentstate;
    ofstream myfile;
public:
// --------------------------------------------------
    int loadaero();             //reads CL and CD values from .txt file
    void fitnessvector();       //Pushes current values into vectors for fitness calcs
    void initialize_sim();      //Initializes values, clear previous values
    void run_sim();             //Main simulator function
    void end_sim();             //Close data file and output final rotation value.
// --------------------------------------------------
    
// --------------------------------------------------
private:
    
    
    
    
  
    
    
    
    
    
};
#endif /* Simulator_hpp */
