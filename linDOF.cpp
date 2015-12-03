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
    s = rand()%100;
    sdot = rand()%5;
    sdotdot = 0;
    target = 0;
    
    //cout << s<<"\t\t"<<sdot<<"\t\t"<<endl;
}