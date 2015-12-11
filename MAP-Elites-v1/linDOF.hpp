//
//  linDOF.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class linDOF;

#ifndef linDOF_hpp
#define linDOF_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

//declare linear degrees of freedom parameters

class linDOF{
    friend class Craft;
public:
    double s, sdot, sdotdot;
    double target;      // TODO - Move target to sim
    
    void initialize();
};


//declare initializations of degree of freedom parameters
void linDOF::initialize(){
    s = rand()%100;     //linear position
    sdot = rand()%5;    //linear velocity
    sdotdot = 0;        //linear acceleration
    target = 0;         //target position
    
    //cout << s<<"\t\t"<<sdot<<"\t\t"<<endl;
}

#endif /* linDOF_hpp */
