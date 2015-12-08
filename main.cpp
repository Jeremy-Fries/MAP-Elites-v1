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
#include "Wrapper.hpp"
#include "Map_Elites.hpp"
#include "Map_space.hpp"
#include "Individual.hpp"
#include "Neural Network.hpp"
#include "Dummy Simulator.hpp"  // Delete - only for NN
#include "Dummy EA.hpp"         // Delete - only for NN

// TODO - include any other files?

using namespace std;

class Map_Elites;
class Map_space;
class Individual;

int main() {
    srand(time(NULL));
// --------------------------------------------------
            // Set Random Numbers
    //srand(time(NULL));
// --------------------------------------------------
            // Set Objects
//    Map_Elites me1;
//    Map_Elites* pMap = &me1;
//    Map_space map_space1;
//    Map_space* pSpace =  &map_space1;
//    Individual individual1;
//    Individual* pI = &individual1;
//    Neural_Network NN;
//    Dummy_simulator DS;
//    Dummy_EA EA;
//    
    
    pMap->set_map_params(0, 10, 0, 10, 4, 4, 10, 50);
        // (dim1_min, dim1_max, dim2_min, dim2_max, resolution1,2, fill generation, mutate generation)
  
    pI->set_individual_params(18, 8, 0.1, 0.1, 4, 2);
        // individual_size 1,2, mutate_magnitude 1,2, mutation_amount 1,2)
// --------------------------------------------------
            // Nueral Network       // Move to Wrapper??
    
    
    EA.create_weights(DS.sim_number_state_variable_inputs, DS.sim_hidden_layer_size, DS.sim_number_controls);
    
    DS.create_state_variables();
    DS.create_state_variable_limits();
    
    // Loop - Start
    NN.activation_function(DS.sim_state_variable_inputs, DS.sim_state_variable_upper_limits, DS.sim_state_variable_lower_limits, DS.sim_hidden_layer_size, DS.sim_number_controls, DS.sim_control_upper_limits, DS.sim_control_lower_limits, EA.ea_input_to_hidden_layer_weights, EA.ea_hidden_to_output_layer_weights, DS.controls_for_simulator);
    NN.write_to_text_file();
    
    NN.reset_neural_network();      // Not ran at last
    // Loop - end
    
    //second iteration test
    //    NN.activation_function(DS.sim_state_variable_inputs, DS.sim_state_variable_upper_limits, DS.sim_state_variable_lower_limits, DS.sim_hidden_layer_size, DS.sim_number_controls, DS.sim_control_upper_limits, DS.sim_control_lower_limits, EA.ea_input_to_hidden_layer_weights, EA.ea_hidden_to_output_layer_weights, DS.controls_for_simulator);
    cout << "controled solution" << endl;
    cout << "8.76773	8.61136" << endl;
    
    
    
    
    
    
    
// --------------------------------------------------
/*
 

 
            TODO- main and sub main
 
 
 
     // LOOP- fill map with new individuals for #
 
 
 
 
 
 */
    
    // LOOP- fill map with new individuals for #
    // LOOP- mutate individuals in map for #
    
    
    // TODO - test() set pheno to geno and run out of scope test
    
    

    return 0;
}
