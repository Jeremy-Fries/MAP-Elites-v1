//
//  rotDOF.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "rotDOF.hpp"



void rotDOF::initialize(){
    q = (rand()%60)*4*atan(1)/180; //Initializing orientation between 0 and 60 degrees with respect to the negative x-axis and converting to radians
    qdot = 0; 
    qdotdot = 0; //Initializing angular velocity and acceleration to 0 for simplicity.
    target = 0;
}