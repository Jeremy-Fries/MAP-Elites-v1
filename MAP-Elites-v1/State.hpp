//
//  State.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class State;

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
//#include "State.cpp"

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


void State::get_state(craft l, double t, double ts){
    time = t;
    timestep = ts;
    xpos = l.frame.at(0).s;
    xvel = l.frame.at(0).sdot;
    zpos = l.frame.at(1).s;
    zvel = l.frame.at(1).sdot;
    phi = l.orientation.at(0).q;
    phivel = l.orientation.at(0).qdot;
    
    KEx = 0.5*pow(xvel,2)*l.mass;
    KEz = 0.5*pow(zvel,2)*l.mass;
    KEp = 0.5*pow(phivel,2)*l.inertia;
}
// --------------------------------------------------
// Initiailize limits for state variables and controls
void State::initialize_translate_limits(){
    num_of_controls=2;
    // state variable upper limits
    state_variables_UpLimit.push_back(500.0);   // xpos [m]
    state_variables_UpLimit.push_back(100.0);   // xvel [m/s]
    state_variables_UpLimit.push_back(500.0);   // zpos [m]
    state_variables_UpLimit.push_back(100.0);   // zvel [m/s]
    state_variables_UpLimit.push_back(3.14);    // sin(phi) [rad]
    state_variables_UpLimit.push_back(3.14);    // cos(phi) [rad]
    
    // state variable lower limits
    state_variables_LowLimit.push_back(0.0);      // xpos [m]
    state_variables_LowLimit.push_back(-100.0);   // xvel [m/s]
    state_variables_LowLimit.push_back(0.0);      // zpos [m]
    state_variables_LowLimit.push_back(-100.0);   // zvel [m/s]
    state_variables_LowLimit.push_back(-3.14);    // sin(phi) [rad]
    state_variables_LowLimit.push_back(-3.14);    // cos(phi) [rad]
    
    // control upper limits
    control_UpLimits.push_back(500.0);    // thrust [N]
    control_UpLimits.push_back(50.0);     // torque [Nm]
    
    // control lower limits
    control_LowLimits.push_back(0.0);       // thrust [N]
    control_LowLimits.push_back(-50.0);     // torque [Nm]
}
// --------------------------------------------------
// Translate function() takes information of craft and target, pushes into vector to go to NN. May need to be in simulator to have access to target.
vector<double> State::translate_function(){
    state_variables_vec.clear();
    state_variables_vec.push_back(xpos);
    state_variables_vec.push_back(xvel);
    state_variables_vec.push_back(zpos);
    state_variables_vec.push_back(zvel);
    state_variables_vec.push_back(sin(phi));
    state_variables_vec.push_back(cos(phi));
    //cout << "state_variable vector size is: " << state_variables_vec.size();
    return state_variables_vec;
}
// --------------------------------------------------
//print header for keeping track of positions
void State::printheader(){
    cout << "Time \t TStep \t\t X-Pos \t X-Velocity \t Z-Pos \t Z-Velocity \t Pitch \t Omega \t Kinetic Energy" << endl;
}
// --------------------------------------------------
//print values for each round
//file is the output file to be read by MatLab
void State::printround(ofstream & file){
    
    cout << time << "\t\t\t" << timestep << "\t\t\t" << xpos << "\t\t\t" << xvel << "\t\t\t" << zpos << "\t\t\t";
    cout << zvel << "\t\t\t" << phi << "\t\t\t" << phivel << "\t\t\t" << KEx << "\t\t\t" << KEz << "\t\t\t" << KEp << endl;
    file << time << "\t\t\t" << timestep << "\t\t\t" << xpos << "\t\t\t" << xvel << "\t\t\t" << zpos << "\t\t\t";
    file << zvel << "\t\t\t" << phi << "\t\t\t" << phivel << "\t\t\t" << KEx << "\t\t\t" << KEz << "\t\t\t" << KEp << endl;
}


#endif /* State_hpp */
