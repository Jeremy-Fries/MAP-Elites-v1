//
//  Wrapper.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 11/16/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class Wrapper;

#ifndef Wrapper_hpp
#define Wrapper_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>



#include "linDOF.hpp"
#include "rotDOF.hpp"
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
//#include "Wrapper.hpp"



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
    const int hidden_layer_size = 3;
// --------------------------------------------------
    void initialize_wrapper();
    void wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2);
// --------------------------------------------------
        // Loop functions combine all
    void wrapper_runs_sim(vector<double>,vector<double>);
    void fill_MAP();
    void mutate_MAP();
    void run_single_individual(Individual& I);
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



// --------------------------------------------------
// Run sim loop
//  sim.initialize_sim();
//  sim.run_sim();
//  sim.end_sim();      // only closes txt file and couts

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
    
    int states = 6;
    int outs = 2;
    
    pME->set_map_params(0, 10, 0, 10, 4, 4, 10, 50);
    // (dim1_min, dim1_max, dim2_min, dim2_max, resolution1,2, fill generation, mutate generation)
    
    wrapper_sets_I_params((states+1)*hidden_layer_size, (hidden_layer_size+1)*outs, 0.1, 0.1, 4, 2);
    // individual_size 1,2, mutate_magnitude 1,2, mutation_amount 1,2)
}
// --------------------------------------------------
void Wrapper::wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2){
    isize_1=size1;
    isize_2=size2;
    imutate_mag_1=mut_mag1;
    imutate_mag_2=mut_mag2;
    imutate_amount_1=mut_amo1;
    imutate_amount_2=mut_amo2;
    
    /// assigns values to actual individual.
    //individual1.set_individual_params(size1,size2,mut_mag1,mut_mag2,mut_amo1,mut_amo2);
    //set_individual_params(int individual_size1,int individual_size2,double mutation_magnitude1,double mutation_magnitude2,int mutation_amount1,int mutation_amount2);
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
        /// create objects
        Individual I;
        Simulator Sim;
        Neural_Network NN;
        
        /// initialize individual
        I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
        I.build_individual();
        
        /// initialize NN.
        NN.initialize(this->hidden_layer_size, Sim.currentstate.num_of_controls);
        
        NN.communication_from_EA(I.get_individual1(), I.get_individual2());
        Sim.initialize_sim();
        
        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
        NN.take_output_limits(Sim.currentstate.control_LowLimits, Sim.currentstate.control_UpLimits);
        NN.take_num_hidden_units(this->hidden_layer_size); /// repeated from initialize, but no harm.
        NN.take_num_controls(Sim.currentstate.num_of_controls); /// repeated from initialize, but to no harm.
        NN.take_weights(I.get_individual1(), I.get_individual2()); /// repeated from communication_from_EA, but to no harm.
        
        I.display_individual_size1();
        I.display_individual_size2();
        
        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            /// while the simulator still has time left on the clock
            /// AND
            /// the craft is above ground level:
            
            //NN.communication_from_simulator_deprecated(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
            //vector<double> SPOT(2);
//            NN.activation_function_deprecated(
//                                   Sim.currentstate.translate_function(),
//                                   Sim.currentstate.state_variables_UpLimit,
//                                   Sim.currentstate.state_variables_LowLimit,
//                                   hidden_layer_size,
//                                   Sim.currentstate.num_of_controls,
//                                   Sim.currentstate.control_UpLimits,
//                                   Sim.currentstate.control_LowLimits,
//                                   I.get_individual1(),
//                                   I.get_individual2(),
//                                   SPOT
//                                   );
            //cout << "Time: " << Sim.t << endl;
            
            vector<double> action = NN.activation_function(Sim.currentstate.translate_function());
            
            //vector<double> activation_function(vector<double> state);
            //void take_input_limits(vector<double> lower, vector<double> upper);
            //void take_output_limits(vector<double> lower, vector<double> upper);
            //void take_num_hidden_units(int num_hidden);
            //void take_num_controls(int num_controls);
            //void take_weights(vector<double> in_to_hid, vector<double> hid_to_out);
            
            Sim.run_sim(action);
            
            
            NN.reset_neural_network();                      // Do we want this??
        }
        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
        
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
        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            /// while the simulator still has time left on the clock
            /// AND
            /// the craft is above ground level:
            
            NN.communication_from_simulator_deprecated(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
            Sim.run_sim(NN.communication_to_simulator());
            NN.reset_neural_network();                      // Do we want this??
        }
        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
        // fitness function from Sim
        // I.set_fit_rating( double );
        // get phenotypes from Sim
        // I.set_phenotypes( double , double );
        // ME.place_individual_in_map(I);
    }
}
// --------------------------------------------------
// Run single test, modifiable weights of NN, recieve fit_rating and phenotypes.

void Wrapper::run_single_individual(Individual& I){
    Simulator Sim;
    Neural_Network NN;
    I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
    
    // TODO - User inputs all weights.
    // TODO -Able to change how weights are generated, access to different random functions.
    
    I.build_individual(); // TODO - change
    
    Sim.initialize_sim();
    
    NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
    NN.take_output_limits(Sim.currentstate.control_LowLimits, Sim.currentstate.control_UpLimits);
    NN.take_num_hidden_units(this->hidden_layer_size); /// repeated from initialize, but no harm.
    NN.take_num_controls(Sim.currentstate.num_of_controls); /// repeated from initialize, but to no harm.
    NN.take_weights(I.get_individual1(), I.get_individual2()); /// repeated from communication_from_EA, but to no harm.

    
    NN.communication_from_EA(I.get_individual1(), I.get_individual2());
    while (Sim.t<Sim.tmax || Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
        vector<double> action;
        action = NN.activation_function(Sim.currentstate.translate_function());
        Sim.run_sim(action);
        NN.reset_neural_network();                      // Do we want this??
    }
    // fitness function from Sim
    // I.set_fit_rating( double );
    // get phenotypes from Sim
    // I.set_phenotypes( double , double );
    // ME.place_individual_in_map(I);
}
// --------------------------------------------------




#endif /* Wrapper_hpp */
