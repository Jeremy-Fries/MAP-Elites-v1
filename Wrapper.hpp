//
//  Wrapper.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 11/16/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Wrapper_hpp
#define Wrapper_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>
#include "Map_Elites.hpp"
#include "Simulator.hpp"
#include "Neural Network.hpp"
//#include "Fake_Controller.hpp"

using namespace std;

class Wrapper{
protected:
    Map_Elites ME;
    Map_Elites* pME = &ME;
    Map_space mspace;
    Map_space* pMspace =  &mspace;
    Individual individual1;
    Individual* pI = &individual1;
    Neural_Network NN;
    Neural_Network* pN = &NN;
    Simulator Sim;
    Simulator* pS = &Sim;
    
    
public:
// --------------------------------------------------
        // Loop functions combine all
    void fill_MAP();
    void mutate_MAP();
// --------------------------------------------------
        // Interactions between - MAP and NN
    
    
    
    
    
// --------------------------------------------------
        // Interactions between - MAP and SIM
    
    
    
    
    
// --------------------------------------------------
        // Interactions between - NN and SIM
    
    
    
    
    
private:
    
    
    

    
};
#endif /* Wrapper_hpp */
