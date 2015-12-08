//
//  Craft.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/1/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Craft_hpp
#define Craft_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include "State.hpp"
#include "linDOF.hpp"
#include "rotDOF.hpp"

using namespace std;
// --------------------------------------------------
//declare a craft with a reference frame and values for mass and moment of inertia
class craft{
    friend class State;
    friend class Simulator;
    friend class linDOF;
    friend class rotDOF;
public:
    vector<linDOF> frame;
    vector<rotDOF> orientation;
    double mass, inertia, KEinitial;
    double sref;
// --------------------------------------------------
    void initialize(int l, int r);
};


#endif /* Craft_hpp */