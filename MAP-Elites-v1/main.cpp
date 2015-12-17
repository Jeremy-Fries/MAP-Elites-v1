//
//  main.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

#include "LinDOF.hpp"
#include "RotDOF.hpp"
#include "anglemath.h"
#include "dynamics.h"
#include "Craft.hpp"
#include "State.hpp"
#include "Simulator.hpp"

#include "Node.hpp"
#include "Layer.hpp"
#include "Neural Network.hpp"

#include "Individual.hpp"
#include "Map_space.hpp"
#include "Map_Elites.hpp"
#include "Wrapper.hpp"

// TODO - include any other files?

using namespace std;

int submain(){
    cout << "IN submain()" << endl;
    
    
    Wrapper W;
    
    //double d1_min,d1_max,d2_min,d2_max;
    //int res1,res2,fill_gen,mutate_gen;
    
    W.initialize_wrapper();
    
    W.fill_MAP();
    //W.mutate_MAP();
    
    
    cout << "OUT submain()" << endl;
    return 0;
}

int main() {
    //srand(time(NULL));
// --------------------------------------------------
    submain();

    return 0;
}
