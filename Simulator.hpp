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
    int linear, rotational, numalf;
    double t, anglechange, fitness;
    double const tstep = 0.1;
    double const tmax = 60;
    double const rhoair = 1.2;
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
    vector<State> stateholder;  // once craft and state class are intialized
    vector<double> controls;
    vector<double> forces;
    vector<vector<double> > aero;
    craft lander;
    State currentstate;
    ofstream myfile;
public:
// --------------------------------------------------
    int loadaero();
    void fitnessvector();
    void initialize_sim();
    void run_sim();
    void end_sim();
// --------------------------------------------------
    
// --------------------------------------------------
private:
    
    
    
    
  
    
    
    
    
    
};
#endif /* Simulator_hpp */
