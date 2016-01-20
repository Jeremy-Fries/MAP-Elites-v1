//
//  Simulator.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/1/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class Simulator;

#ifndef Simulator_hpp
#define Simulator_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>

/*
#include "Wrapper.hpp"

///
#include "Individual.hpp"
#include "Map_space.hpp"
#include "Map_Elites.hpp"

///
//#include "Simulator.hpp"
#include "State.hpp"
#include "dynamics.h"
#include "anglemath.h"
#include "Craft.hpp"

///
#include "Neural Network.hpp"
#include "Layer.hpp"
#include "Node.hpp"
 */

#include "State.hpp"
#include "Craft.hpp"
#include "State.hpp"


using namespace std;

class Simulator{
    friend class Craft;
    friend class State;
    friend class Wrapper;
    
protected:
    int linear, rotational, numalf;     //number of linear and rotational DOFs, number of AOAs with CL and CD values
    double t, anglechange, fitness;     //time, rotational tracker, fitness value(likely to change)
    double tstep;                       //simulation calculates values every 0.1 seconds set in initialize
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
    Craft lander;
    State currentstate;
    ofstream myfile;
public:
// --------------------------------------------------
    int loadaero();
    void fitnessvector();
    void initialize_sim();
    void run_sim();
    void run_timestep(vector<double>);
    void end_sim();
// --------------------------------------------------
    
// --------------------------------------------------
private:
    
};


int Simulator::loadaero(){
    ifstream co("aerocoeff.txt");
    
    double read;
    vector<double> apush;
    int counter = 0;
    
    while(co >> read){
        apush.push_back(read);
        
        if(apush.size()>=3){
            aero.push_back(apush);
            apush.clear();
            counter++;
        }
    }
    return counter;
}

// --------------------------------------------------
//Pushes back current positions, velocities, accelerations, and energies into vectors to be stored for fitness
void Simulator::fitnessvector(){
    xpositions.push_back(currentstate.xpos);    //Positions in X-direction
    zpositions.push_back(currentstate.zpos);    //Positions in Z-direction
    xvels.push_back(currentstate.xvel);         //Velocities in X-direction
    zvels.push_back(currentstate.zvel);         //Velocities in Z-direction
    xke.push_back(currentstate.KEx);            //Kinetic Energy in X-direction
    zke.push_back(currentstate.KEz);            //Kinetic Energy in Z-direction
    xaccels.push_back(lander.frame.at(0).sdotdot);  //Acceleration in X-direction
    zaccels.push_back(lander.frame.at(1).sdotdot);  //Acceleration in Z-direction
    anglepos.push_back(currentstate.phi);           //Angular Position
    anglevel.push_back(currentstate.phivel);        //Angular Velocity
    angleaccel.push_back(lander.orientation.at(0).qdotdot);     //Angular acceleration
    angleke.push_back(currentstate.KEp);        //Rotational Kinetic Energy
}

// --------------------------------------------------
//Initialize the simulator
void Simulator::initialize_sim(){
    
    linear = 2;         // Number of Linear DOFs        // TODO much later - set and get functions
    rotational = 1;     // Number of Rotational DOFs    // TODO much later - set and get functions
    t = 0;
    tstep = 0.1;
    anglechange = 0;
    myfile.open("SimulatorData.txt"); //Open output file for data
    numalf = loadaero();              //Return the number of angles we have CL and CD values for
    fitness = 0;
    
    
    //Clear all values that may have been previously held for simulation runs
    stateholder.clear();
    lander.frame.clear();
    lander.orientation.clear();
    xpositions.clear();
    zpositions.clear();
    xvels.clear();
    zvels.clear();
    xke.clear();
    zke.clear();
    xaccels.clear();
    zaccels.clear();
    anglepos.clear();
    anglevel.clear();
    angleaccel.clear();
    angleke.clear();
    
    
    lander.initialize(linear, rotational);          //Initialize Craft
    currentstate.initialize_translate_limits();
    currentstate.printheader();                     //Output Header in XCode Screen
    currentstate.get_state(lander, t, tstep);       //Modify current state based on simulator outputs
    currentstate.printround(myfile);                //Output simulator outputs to screen and file
    stateholder.push_back(currentstate);            //Pushback currentstate into vector for tracking
        
    fitnessvector();             //Put current data into vectors for later calculating fitness
}
// --------------------------------------------------
void Simulator::run_sim(){ /// AVOID
    // TODO - move target out of linDOF
//    vector<double> controls;
//    
//    NN.activation_function(this->currentstate.translate_function());
//    controls = NN.communication_to_simulator();
//    
//    forces = forcecalc(controls, lander, rhoair, aero);
//    anglechange = anglechange + dynamicscalc(lander, forces, tstep, linear, rotational);
//    t = t+tstep;
//    currentstate.get_state(lander, t, tstep);       //update current state
//    stateholder.push_back(currentstate);            //pushback current state into vector
//    currentstate.printround(myfile);                //Output simulator outputs to screen and file
//    fitnessvector();    // potentially comment out // potential tag/ searchable
//    
//    NN.Neural_Network_Reset();
}

void Simulator::run_timestep(vector<double> controls){
    forces = forcecalc(controls, lander, rhoair, aero);
    anglechange = anglechange + dynamicscalc(lander, forces, tstep, linear, rotational);
    t = t+tstep;
    currentstate.get_state(lander, t, tstep);       //update current state
    stateholder.push_back(currentstate);            //pushback current state into vector
    //currentstate.printround(myfile);                //Output simulator outputs to screen and file
    fitnessvector();    // potentially comment out // potential tag/ searchable
}

// Runs the simulator while time is less than max time and lander is above ground
// --------------------------------------------------
void Simulator::end_sim(){
    cout << "\t Angle Change: \t"<< anglechange << endl;    //Output total rotation of craft throughout the the simulation
    myfile.close();
    
}


#endif /* Simulator_hpp */
