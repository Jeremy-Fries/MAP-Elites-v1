//
//  Wrapper.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 11/16/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Wrapper.hpp"

// --------------------------------------------------
// Run sim loop
//  sim.initialize_sim();
//  sim.run_sim();
//  sim.end_sim();

// --------------------------------------------------
// Run NN loop

//// Loop - Start
//NN.activation_function(DS.sim_state_variable_inputs, DS.sim_state_variable_upper_limits, DS.sim_state_variable_lower_limits, DS.sim_hidden_layer_size, DS.sim_number_controls, DS.sim_control_upper_limits, DS.sim_control_lower_limits, EA.ea_input_to_hidden_layer_weights, EA.ea_hidden_to_output_layer_weights, DS.controls_for_simulator);
//NN.write_to_text_file();

//NN.reset_neural_network();      // Not ran at last
// Loop - end

//second iteration test
//    NN.activation_function(DS.sim_state_variable_inputs, DS.sim_state_variable_upper_limits, DS.sim_state_variable_lower_limits, DS.sim_hidden_layer_size, DS.sim_number_controls, DS.sim_control_upper_limits, DS.sim_control_lower_limits, EA.ea_input_to_hidden_layer_weights, EA.ea_hidden_to_output_layer_weights, DS.controls_for_simulator);
//cout << "controled solution" << endl;
//cout << "8.76773	8.61136" << endl;

// --------------------------------------------------
void Wrapper::initialize_wrapper(){
    pME->set_map_params(0, 10, 0, 10, 4, 4, 10, 50);
    // (dim1_min, dim1_max, dim2_min, dim2_max, resolution1,2, fill generation, mutate generation)
    
    wrapper_sets_I_params(18, 8, 0.1, 0.1, 4, 2);
    // individual_size 1,2, mutate_magnitude 1,2, mutation_amount 1,2)
}
// --------------------------------------------------
void Wrapper::wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2){
    size1=isize_1;
    size2=isize_2;
    mut_mag1=imutate_mag_1;
    mut_mag2=imutate_mag_2;
    mut_amo1=imutate_amount_1;
    mut_amo2=imutate_amount_2;
}
// --------------------------------------------------
// Pass new individual or mutation from table to NN and Sim to run and recieve fitness/phenotypes
//void Wrapper::wrapper_runs_sim(I.get_individual1(),I.get_individual2()){
    
    // ONCE NN functions are fixed, implement loop here
    
    
//};
// --------------------------------------------------
void Wrapper::fill_MAP(){
    int fill_gen = ME.get_fill_generation();
    
    for (int g=0; g<fill_gen; g++){
        Individual I;
        Simulator Sim;
        Neural_Network NN;
        I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
        I.build_individual();
        NN.communication_from_EA(I.get_individual1(), I.get_individual2());
        Sim.initialize_sim();
        while (Sim.t<Sim.tmax || Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            NN.communication_from_simulator(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
            Sim.run_sim(NN.communication_to_simulator());
            NN.reset_neural_network();                      // Do we want this??
        }
        // fitness function from Sim
        // I.set_fit_rating( double );
        // get phenotypes from Sim
        // I.set_phenotypes( double , double );
        // ME.place_individual_in_map(I);
    }
}
// --------------------------------------------------
void Wrapper::mutate_MAP(){
    int mut_gen = ME.get_mutate_generation();
    for (int g=0; g<mut_gen; g++){
        Simulator Sim;
        Neural_Network NN;
        
    // p1 and p2 rand numbers OR -> rand placment function() modifiable
        //ME.individual_from_map(p1, p2);
        NN.communication_from_EA(ME.get_temp_individual1(), ME.get_temp_individual2());
        Sim.initialize_sim();
        while (Sim.t<Sim.tmax || Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            NN.communication_from_simulator(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
            Sim.run_sim(NN.communication_to_simulator());
            NN.reset_neural_network();                      // Do we want this??
        }
        // fitness function from Sim
        // I.set_fit_rating( double );
        // get phenotypes from Sim
        // I.set_phenotypes( double , double );
        // ME.place_individual_in_map(I);
    }
}
// --------------------------------------------------

























