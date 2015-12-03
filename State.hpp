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
    friend class Craft;
public:
    double time, timestep, xpos, xvel;
    double zpos, zvel, phi, phivel, KEx, KEz, KEp;
    
    void get_state(craft l, double t, double ts);
    void printheader();
    void printround(ofstream & file);
    
};





#endif /* State_hpp */
