//
//  Craft.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/1/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class Craft;

#ifndef Craft_hpp
#define Craft_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

#include "LinDOF.hpp"
#include "RotDOF.hpp"

using namespace std;
// --------------------------------------------------
//declare a craft with a reference frame and values for mass and moment of inertia
class Craft{
    friend class State;
    friend class Simulator;
    friend class LinDOF;
    friend class RotDOF;
public:
    vector<LinDOF> frame;
    vector<RotDOF> orientation;
    double mass, inertia, KEinitial;
    double sref;
// --------------------------------------------------
    void initialize(int l, int r);
};
///////////

void Craft::initialize(int dl, int dr){
    mass = 20;
    inertia = 20;
    KEinitial = 0;
    sref = 0.02; // wing considered roughly rectangular with 20 cm chord length, 1 m span
    
    //Set up Linear DOFs
    for(int i=0;i<dl;i++){
        LinDOF lin;
        lin.initialize();
        KEinitial = KEinitial + 0.5*mass*pow(lin.sdot,2);
        frame.push_back(lin);
    }
    
    //Set up Rotational DOFs
    for(int i=0;i<dr;i++){
        RotDOF rot;
        rot.initialize();
        KEinitial = KEinitial + 0.5*inertia*pow(rot.qdot,2);
        orientation.push_back(rot);
    }
    
    
    //Force x-component of velocity into negative direction
    frame.at(0).sdot = frame.at(0).sdot*-1;
}

#endif /* Craft_hpp */