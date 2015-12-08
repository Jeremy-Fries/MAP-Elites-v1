//
//  Craft.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/1/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Craft.hpp"
// --------------------------------------------------

//declare initializations of craft parameters, including DOFs
void craft::initialize(int dl, int dr){
    mass = 20;
    inertia = 20;
    KEinitial = 0;
    sref = 0.02; // wing considered roughly rectangular with 20 cm chord length, 1 m span
    
    //Set up Linear DOFs
    for(int i=0;i<dl;i++){
        linDOF lin;
        lin.initialize();
        KEinitial = KEinitial + 0.5*mass*pow(lin.sdot,2);
        frame.push_back(lin);
    }
    
    //Set up Rotational DOFs
    for(int i=0;i<dr;i++){
        rotDOF rot;
        rot.initialize();
        KEinitial = KEinitial + 0.5*inertia*pow(rot.qdot,2);
        orientation.push_back(rot);
    }
    
    
    //Force x-component of velocity into negative direction
    frame.at(0).sdot = frame.at(0).sdot*-1;
}
// --------------------------------------------------










