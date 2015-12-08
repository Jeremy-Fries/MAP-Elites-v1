//
//  State.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include "Craft.hpp"

using namespace std;


class State{
    friend class Simulator;
    friend class Craft;
    friend class Wrapper;
    
protected:
    double time, timestep, xpos, xvel;
    double zpos, zvel, phi, phivel, KEx, KEz, KEp;
    vector<double> state_variables_vec;
    vector<double> state_variables_UpLimit;
    vector<double> state_variables_LowLimit;
    int num_of_controls;
    vector<double> control_UpLimits;
    vector<double> control_LowLimits;
// --------------------------------------------------
public:
    void get_state(class craft, double t, double ts);
        // 12/7 - changed to class craft from craft l.
    void initialize_translate_limits();
    vector<double> translate_function();
// --------------------------------------------------
    void printheader();
    void printround(ofstream & file);
  
    
    
};
#endif /* State_hpp */
