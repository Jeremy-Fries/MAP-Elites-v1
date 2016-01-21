//
//  RotDOF.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class RotDOF;

#ifndef RotDOF_hpp
#define RotDOF_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

//----------------------------------
//Declaring a class of rotational degrees of freedom

using namespace std;

class RotDOF{
    friend class Craft;
public:
    double q, qdot, qdotdot;
    double target;
    
    void initialize();
};

void RotDOF::initialize(){
    //q = (rand()%60)*4*atan(1)/180; //Initializing orientation between 0 and 60 degrees with respect to the negative x-axis and converting to radians
    //q=0;
    q = (double) rand()/RAND_MAX * 2*3.141529;
    qdot = 0;
    qdotdot = 0; //Initializing angular velocity and acceleration to 0 for simplicity.
    target = 0;
}


#endif /* RotDOF_hpp */
