//
//  LinDOF.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class LinDOF;

#ifndef LinDOF_hpp
#define LinDOF_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

//declare linear degrees of freedom parameters

class LinDOF{
    friend class Craft;
public:
    double s, sdot, sdotdot, WindSpeed;
    double target;      // TODO - Move target to sim
    
    void initialize();
};


//declare initializations of degree of freedom parameters
void LinDOF::initialize(){
    s = 25;     //linear position
    sdot = 70; //~130min    //linear velocity
    //sdot = 100;
    sdotdot = 0;        //linear acceleration
    target = 0;         //target position
    WindSpeed = 0;
    
    //cout << s<<"\t\t"<<sdot<<"\t\t"<<endl;
}

#endif /* LinDOF_hpp */
