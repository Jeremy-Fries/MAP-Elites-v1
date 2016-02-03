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

using namespace std;


class State{
    friend class Simulator;
    friend class Craft;
    friend class Wrapper;
    
protected:
    double time, timestep, xpos, xvel;
    double zpos, zvel, phi, phivel, KEx, KEz, KEp, AOA, stallcheck, forceLift, forceDrag;
    double xWind, zWind;
    vector<double> state_variables_vec;
    vector<double> state_variables_UpLimit;
    vector<double> state_variables_LowLimit;
    int num_of_controls;
    vector<double> control_UpLimits;
    vector<double> control_LowLimits;
// --------------------------------------------------
public:
    void get_state(class Craft, double t, double ts);
        // 12/7 - changed to class craft from craft l.
    void initialize_translate_limits();
    vector<double> translate_function();
// --------------------------------------------------
    void printheader();
    void printround(ofstream & outfile, double);
    void printround_LY(ofstream &file, double, ofstream & wind);
};


void State::get_state(Craft l, double t, double ts){
    time = t;
    timestep = ts;
    xpos = l.frame.at(0).s;
    xvel = l.frame.at(0).sdot;
    zpos = l.frame.at(1).s;
    zvel = l.frame.at(1).sdot;
    phi = l.orientation.at(0).q;
    phivel = l.orientation.at(0).qdot;
    AOA = l.alpha;
    xWind = l.frame.at(0).WindSpeed;
    zWind = l.frame.at(1).WindSpeed;
    
    
    KEx = 0.5*pow(xvel,2)*l.mass;
    KEz = 0.5*pow(zvel,2)*l.mass;
    KEp = 0.5*pow(phivel,2)*l.inertia;
}
// --------------------------------------------------
// Initiailize limits for state variables and controls
void State::initialize_translate_limits(){
    num_of_controls=2;
    
    /// clear all vectors.
    state_variables_LowLimit.clear();
    state_variables_UpLimit.clear();
    control_LowLimits.clear();
    control_UpLimits.clear();
    
    state_variables_LowLimit.reserve(7);
    state_variables_UpLimit.reserve(7);
    control_LowLimits.reserve(2);
    control_UpLimits.reserve(2);

    
    // state variable upper limits
    //state_variables_UpLimit.push_back(2500.0);   // xpos [m]
    state_variables_UpLimit.push_back(70.0);   // time [s]
    state_variables_UpLimit.push_back(90.0);   // xvel [m/s]
    state_variables_UpLimit.push_back(30.0);   // zpos [m]
    state_variables_UpLimit.push_back(10.0);   // zvel [m/s]
    state_variables_UpLimit.push_back(0.5);    // sin(phi) [ratio of rad]
    state_variables_UpLimit.push_back(1.0);    // cos(phi) [ratio of rad]
    state_variables_UpLimit.push_back(0.2); /// phivel
    
    // state variable lower limits
    //state_variables_LowLimit.push_back(0.0);      // xpos [m]
    state_variables_LowLimit.push_back(-10.0);    // time [s]
    state_variables_LowLimit.push_back(40.0);   // xvel [m/s]
    state_variables_LowLimit.push_back(-5.0);      // zpos [m]
    state_variables_LowLimit.push_back(-10.0);   // zvel [m/s]
    state_variables_LowLimit.push_back(-0.5);    // sin(phi) [ratio of rad]
    state_variables_LowLimit.push_back(0.0);    // cos(phi) [ratio of rad]
    state_variables_LowLimit.push_back(-0.2); /// phivel
    
    // control upper limits
    control_UpLimits.push_back(000.0);    // thrust [N] /// previously 500
    control_UpLimits.push_back(5);     // torque [Nm]
    
    // control lower limits
    control_LowLimits.push_back(0);       // thrust [N]
    control_LowLimits.push_back(-5);     // torque [Nm]
}
// --------------------------------------------------

// TODO - 


// Translate function() takes information of craft and target, pushes into vector to go to NN. May need to be in simulator to have access to target.
vector<double> State::translate_function(){
    state_variables_vec.clear();
    state_variables_vec.reserve(7);
    //state_variables_vec.push_back(xpos);
    state_variables_vec.push_back(time);
    state_variables_vec.push_back(xvel);
    state_variables_vec.push_back(zpos);
    state_variables_vec.push_back(zvel);
    state_variables_vec.push_back(sine(phi));
    state_variables_vec.push_back(cosine(phi));
    state_variables_vec.push_back(phivel);
    //state_variables_vec.push_back(AOA);
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
void State::printround(ofstream & outfile, double thrust){
    
    //cout << time << "\t\t\t" << timestep << "\t\t\t" << xpos << "\t\t\t" << xvel << "\t\t\t" << zpos << "\t\t\t";
    //cout << zvel << "\t\t\t" << phi << "\t\t\t" << phivel << "\t\t\t" << KEx << "\t\t\t" << KEz << "\t\t\t" << KEp << endl;
    outfile << time << "\t\t\t" << timestep << "\t\t\t" << xpos << "\t\t\t" << xvel << "\t\t\t" << zpos << "\t\t\t";
    //outfile << time << "\t\t" << thrust << "\t\t" << xpos << "\t\t" << xvel << "\t\t" << zpos << "\t\t";
    outfile << zvel << "\t\t" << phi << "\t\t" << phivel << "\t\t" << KEx << "\t\t" << KEz << "\t\t" << KEp << "\t\t" << stallcheck << endl;
    outfile << stallcheck << "\t\t" << forceLift << endl;
    
}


void State::printround_LY(ofstream & file, double thrust, ofstream & windfile){
    file << xpos << "\t" << zpos << "\t" << thrust << "\t" << phi << endl;//<< "\t" <<  KEz << endl;
    windfile << "\t" << time << "\t" << xWind << "\t" << zWind << endl;
    
}

//void State::printround_SA(ofstream & file, double thrust, ofstream & wind){
////    file << xpos << "\t" << zpos << endl;//<< "\t" <<  KEz << endl;
////    file << time << "\t\t" << timestep << "\t\t" << xpos << "\t\t";
////    file << xvel  << "\t\t" << zpos  << "\t\t" << zvel << endl;
//    file << time << "\t\t\t" << timestep << "\t\t\t" << xpos << "\t\t\t" << xvel << "\t\t\t" << zpos << "\t\t\t";
//    file << zvel << "\t\t" << phi << "\t\t" << phivel << "\t\t" << KEx << "\t\t" << KEz << "\t\t" << KEp << "\t\t" << stallcheck << endl;
//    wind << time << "\t\t" << xWind << "\t\t" << zWind << endl;
//}


#endif /* State_hpp */
