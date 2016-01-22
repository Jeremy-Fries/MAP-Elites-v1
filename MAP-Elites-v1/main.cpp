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
#include <map>

#include "LinDOF.hpp"
#include "RotDOF.hpp"
#include "anglemath.h"
#include "dynamics.h"
#include "Craft.hpp"
#include "State.hpp"
#include "Simulator.hpp"

#include "Neural Network.hpp"

#include "Individual.hpp"
#include "Map_space.hpp"
#include "Map_Elites.hpp"
#include "Wrapper.hpp"

// TODO - include any other files?

using namespace std;

#define TRIG_GRANULARITY 1000
double sine(double inp){
    //return sin(inp);
    
    double out;
    static map< int, double > sine_iomap;
    int input_int = inp*TRIG_GRANULARITY;
    if(sine_iomap.count(input_int) == 1)
    {out = sine_iomap.find(input_int)->second;}
    else{
        out = sin(inp);
        sine_iomap.insert(pair <int,double> (input_int,out));
    }
    return out;
}
double cosine(double inp){
    //return cos(inp);
    
    double out;
    static map< int, double > sine_iomap;
    int input_int = inp*TRIG_GRANULARITY;
    if(sine_iomap.count(input_int) == 1)
    {out = sine_iomap.find(input_int)->second;}
    else{
        out = cos(inp);
        sine_iomap.insert(pair <int,double> (input_int,out));
    }
    return out;
}


int submain(){
    cout << "IN submain()" << endl;
  
    Wrapper W;
    
    W.initialize_wrapper(10,10);
    
    W.fill_MAP();
    
    //W.run_single_individual();
    
    W.mutate_MAP();
    
    W.print_stuff();
    
    W.print_entire_map_solution();
    
    W.always_last();
    
    cout << endl << "OUT submain()" << endl;
    return 0;
}

int main() {
    srand(time(NULL));
// --------------------------------------------------
    submain();

    return 0;
}
