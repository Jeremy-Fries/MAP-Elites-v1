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
    
    // time, timestep, x-position, x-velocity
    double time, timestep, xpos, xvel;
    //z-position, z-velocity, angle from negative x-axis, angular velocity, kinetic energies
    double zpos, zvel, phi, phivel, KEx, KEz, KEp;
    
    void get_state(craft l, double t, double ts); //put all current values into the state class
    void printheader();     //print header for keeping track of positions
    void printround(ofstream & file);       //print values for each round to screen and file
    
};





#endif /* State_hpp */
