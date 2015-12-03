//
//  linDOF.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "linDOF.hpp"

//declare initializations of degree of freedom parameters
void linDOF::initialize(){
    s = rand()%100;     //linear position
    sdot = rand()%5;    //linear velocity
    sdotdot = 0;        //linear acceleration
    target = 0;         //target position
    
    //cout << s<<"\t\t"<<sdot<<"\t\t"<<endl;
}