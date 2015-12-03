//
//  Simulator_1DOF.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 11/16/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Simulator_1DOF.hpp"

void Simulator_1DOF::initialize_dof(){
    s = rand()%1000;
    sdot = -5;
    gravity = -9.81;
    mass = 10;
    sdotdot = gravity + force/mass;
    target = 0;
    energy = 0.5*mass*pow(sdot,2)-mass*gravity*s;
    
    cout << "0.00 \t\t" << s << "\t\t" << sdot << "\t\t" << energy << endl;
}

// --------------------------------------------------
void Simulator_1DOF::initialize_sim1(){
    time = 0;
    tstep = 0.01;
    m = mass;
    g = gravity;
}
// --------------------------------------------------
double Simulator_1DOF::dynamicscalc(double position, double velocity, double accel){
    double accelprev = accel;
    double velocityprev = velocity;
    double force = 10; //jeremy(position, velocity, time);    // Pass in controller
    accel = force/m + g;
    velocity = velocity + 0.5*tstep*(accelprev+accel);
    position = position + 0.5*tstep*(velocity+velocityprev);
    time += tstep;
    double energy = 0.5*m*pow(velocity,2)-m*g*position;
    return energy; // calc KE, PE, combine later
}
// --------------------------------------------------
void Simulator_1DOF::run_simulation(){
    initialize_dof();
    initialize_sim1();
    while((position>target) || time<20){
        
        E = dynamicscalc(s, sdot, sdotdot);
        cout << setiosflags(ios::fixed) << setprecision(2) << time << "\t\t" << s << "\t\t" << sdot << "\t\t" << E<< "\n";
    }
}
// --------------------------------------------------
void Simulator_1DOF::calc_fitness(){


}
// --------------------------------------------------
// integral energy over time
// average energy per timestep
// 

// --------------------------------------------------


// --------------------------------------------------