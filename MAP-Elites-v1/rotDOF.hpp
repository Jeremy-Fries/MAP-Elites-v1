//
//  rotDOF.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef rotDOF_hpp
#define rotDOF_hpp

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

class rotDOF{
    friend class Craft;
public:
    double q, qdot, qdotdot;
    double target;
    
    void initialize();
};

#endif /* rotDOF_hpp */
