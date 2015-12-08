//
//  Simulator.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/1/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Simulator.hpp"

// --------------------------------------------------
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
void Simulator::fitnessvector(){
    xpositions.push_back(currentstate.xpos);
    zpositions.push_back(currentstate.zpos);
    xvels.push_back(currentstate.xvel);
    zvels.push_back(currentstate.zvel);
    xke.push_back(currentstate.KEx);
    zke.push_back(currentstate.KEz);
    xaccels.push_back(lander.frame.at(0).sdotdot);
    zaccels.push_back(lander.frame.at(1).sdotdot);
    anglepos.push_back(currentstate.phi);
    anglevel.push_back(currentstate.phivel);
    angleaccel.push_back(lander.orientation.at(0).qdotdot);
    angleke.push_back(currentstate.KEp);
}
// --------------------------------------------------
void Simulator::initialize_sim(){
    linear = 2;         // TODO much later - set and get functions
    rotational = 1;     // TODO much later - set and get functions
    t = 0;
    tstep = 0.1;
    anglechange = 0;
    myfile.open("SimulatorData.txt");
    numalf = loadaero();
    fitness = 0;
    
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
    
    lander.initialize(linear, rotational);
    currentstate.initialize_translate_limits(); 
    currentstate.printheader();
    currentstate.get_state(lander, t, tstep);
    currentstate.printround(myfile);
    stateholder.push_back(currentstate);
    
    fitnessvector();
}
// --------------------------------------------------


// --------------------------------------------------
void Simulator::run_sim(vector<double> controls){
    // TODO - move target out of linDOF
    // TODO - NO LOOP here
    while(t<tmax && lander.frame.at(1).s > lander.frame.at(1).target){
        //controls = controller(currentstate);
        // TODO - controls from neural network
        
        forces = forcecalc(controls, lander, rhoair, aero);
        anglechange = anglechange + dynamicscalc(lander, forces, tstep, linear, rotational);
        t = t+tstep;
        
        currentstate.get_state(lander, t, tstep);
        stateholder.push_back(currentstate);
        currentstate.printround(myfile);
        fitnessvector();    // potentially comment out // potential tag/ searchable
    }
    
}
// --------------------------------------------------
void Simulator::end_sim(){
    cout << "\t Angle Change: \t"<< anglechange << endl;
    myfile.close();
    
}
// --------------------------------------------------