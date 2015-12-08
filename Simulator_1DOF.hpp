//
//  Simulator_1DOF.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 11/16/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Simulator_1DOF_hpp
#define Simulator_1DOF_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Wrapper.hpp"

using namespace std;

class Simulator_1DOF{
    friend class Wrapper;
    
protected:
    double position, velocity, time,tstep, g, m, accel;
    double E;
    double fit_rating;
    
    double s, sdot, sdotdot;
    double mass, gravity, force;
    double target, energy;


// --------------------------------------------------
public:
    void initialize_dof();
    void initialize_sim1();
// --------------------------------------------------
    double dynamicscalc(double position, double velocity, double accel);
// --------------------------------------------------
    void run_simulation();
// --------------------------------------------------
    void calc_fitness();
// --------------------------------------------------
    
    
    
    
private:

    

    
    
    
    
    
    

};
#endif /* Simulator_1DOF_hpp */
