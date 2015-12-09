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
//    Map_space mspace;
//    Map_space* pMspace =  &mspace;
//    Individual individual1;
//    Individual* pI = &individual1;
//    Neural_Network NN;
//    Neural_Network* pN = &NN;
//    Simulator Sim;
//    Simulator* pS = &Sim;
    
    
public:
    const int hidden_layer_size = 3;
// --------------------------------------------------
    void initialize_wrapper();
    void wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2);
// --------------------------------------------------
        // Loop functions combine all
    void wrapper_runs_sim(vector<double>,vector<double>);
    void fill_MAP();
    void mutate_MAP();
    void run_single_individual();
// --------------------------------------------------
        // Interactions between - MAP and NN
    
    
    
    
    
// --------------------------------------------------
        // Interactions between - MAP and SIM
    
    
    
    
    
// --------------------------------------------------
        // Interactions between - NN and SIM
    
    
    
    
    
private:
    int isize_1, isize_2, imutate_amount_1, imutate_amount_2;
    double imutate_mag_1,imutate_mag_2;
    
    
    

    
};
#endif /* Wrapper_hpp */
