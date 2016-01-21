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
#include <cmath>
#include <fstream>
#include <iomanip>

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

using namespace std;

class Wrapper{
    
    //friend class Neural_Network;
    
// --------------------------------------------------
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
   
// --------------------------------------------------
public:
    int hidden_layer_size;
    vector<double> best_fit;
// --------------------------------------------------
    void initialize_wrapper();
    void wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2);
// --------------------------------------------------
            // Main Wrapper functions
    void wrapper_runs_sim(vector<double>,vector<double>);
    void find_phenotypes();
    void fitness_calculation(State);
    void rand_bin();
    void fill_MAP();
    void mutate_MAP();
    void run_single_individual();
    void print_stuff();
    void print_entire_map_solution();
    
    
// --------------------------------------------------
    // Phenotypes: min, max,            integral output, range, calc d", # of pts d' is + or -, sum of average slopes,
// --------------------------------------------------
private:
    int isize_1, isize_2, imutate_amount_1, imutate_amount_2;
    double imutate_mag_1,imutate_mag_2;
    int bin1, bin2;
    
    double fit_rating;
    double phenotype_1, phenotype_2;
};
// ------------------------------------------------------------------------------------------------ ^^ Declarations
// ------------------------------------------------------------------------------------------------ vv Definitions
// --------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------- To Change Settings
void Wrapper::initialize_wrapper(){
    
    int states = 6;
    int outs = 2;
    
    hidden_layer_size = 3;
    
    pME->set_map_params(0, 6.5, 0, 100000, 5, 5, 10, 1000);
    // (dim1_min, dim1_max, dim2_min, dim2_max, resolution1,2, fill generation, mutate generation)
    
    //pME->display_Map_params();
    
    wrapper_sets_I_params((states+1)*hidden_layer_size, (hidden_layer_size+1)*outs, 0.1, 0.1, 4, 2);
    // individual_size 1,2, mutate_magnitude 1,2, mutation_amount 1,2)
    
    Sim.myfile.open("SimulatorData.txt");
    
}
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
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


// ----------------------------------------------------------------------------------- TODO - change calculation
// Fitness Function
void Wrapper::fitness_calculation(State current){
    fit_rating=0;
    
    cout << endl << "Fitness in " << fit_rating << endl;
    
    //// LANDING FITNESS CALCULATION
    /// must land (0)
    /// minimize x kinetic energy (1); z kinetic energy (2); rotational kinetic energy (3)
    cout << endl << endl;
    cout << Sim.zpositions.size() << endl;
    
    //if(current.zpos > 0){ /// still in air. (0)
    //    fit_rating = -9999999999999; /// TODO MAX_INT
    //}
    
    cout << endl << "KEx IS: " << current.KEx << endl;
    cout << endl << "KEz IS: " << current.KEz << endl;
    cout << endl << "KEp IS: " << current.KEp << endl;
    //fit_rating -= current.KEx; // (1)
    //fit_rating -= current.KEz; // (2)
    //fit_rating -= current.KEp; // (3)
    //fit_rating -= current.zpos * current.zpos;
    
    fit_rating += current.xpos;
    
    cout << endl << "fitness is; " << fit_rating << endl;
    cout << endl << "Fitness OUT!? " << fit_rating << endl;
}
// ----------------------------------------------------------------------------------- TODO - change
// Phenotypes
void Wrapper::find_phenotypes(){
    /// x position at final time step
    phenotype_1=Sim.currentstate.xvel; /// LYJF
    /// angular orientation at final time step
    phenotype_2=Sim.currentstate.phi; /// LYJF

    
    /// for a binary selection parallel simulated annealing.....
    //double r1 = ((double)rand() / RAND_MAX);
    //double r2 = ((double)rand() / RAND_MAX);
    //phenotype_1=r1*100;
    //phenotype_2=r2*100;
    
    //cout << a << " , " << b << endl;
}
// --------------------------------------------------------------------------------------------------------
// Rand bin function
void Wrapper::rand_bin(){
    //rand()%(max-min)+min;
    bin1=0;
    bin2=0;
    int b1_min=0;
    int b2_min=0;
    int b1_max=ME.get_resolution1();
    int b2_max=ME.get_resolution2();
    bin1=rand()%(b1_max-b1_min)+b1_min;
    bin2=rand()%(b2_max-b2_min)+b2_min;
    //cout << "bin to mutate is: (" << bin1 << "," << bin2 << ")" << endl;
}
// -----------------------------------------------------------------------------------
            // Fill Map
void Wrapper::fill_MAP(){
    int fill_gen = ME.get_fill_generation();
    int fill_round=0;
    
    for (int g=0; g<fill_gen; g++){
        //cout << "fill round is: " << g << endl;
        
        Individual I;
        //Simulator Sim;
        //Neural_Network NN;
        
        I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
        //I.display_individual_params();
        
        I.build_individual();
        //I.display_individual1();
        //I.display_individual2();

        /// initialize NN.
        NN.initialize(this->hidden_layer_size, Sim.currentstate.num_of_controls);
        
        Sim.initialize_sim();
    
        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
        NN.take_output_limits(Sim.currentstate.control_LowLimits, Sim.currentstate.control_UpLimits);
        NN.take_num_hidden_units(this->hidden_layer_size); /// repeated from initialize, but no harm.
        NN.take_num_controls(Sim.currentstate.num_of_controls); /// repeated from initialize, but to no harm.
        NN.take_weights(I.get_individual1(), I.get_individual2());
        
        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            /// while the simulator still has time left on the clock
            /// AND
            /// the craft is above ground level:
        
            //NN.communication_from_simulator_deprecated(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
            //vector<double> SPOT(2);
        //           NN.activation_function_deprecated(
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
        
           
        
            //vector<double> activation_function(vector<double> state);
            //void take_input_limits(vector<double> lower, vector<double> upper);
            //void take_output_limits(vector<double> lower, vector<double> upper);
            //void take_num_hidden_units(int num_hidden);
            //void take_num_controls(int num_controls);
            //void take_weights(vector<double> in_to_hid, vector<double> hid_to_out);
            NN.activation_function(Sim.currentstate.translate_function());
            
            Sim.run_timestep(NN.communication_to_simulator());
            
            NN.Neural_Network_Reset();
        }
        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
        
        State current;
        current = Sim.currentstate;
      
        fitness_calculation(current);
        I.set_fit_rating(fit_rating);
        //I.display_fit_rating();

        
        
        find_phenotypes();
        I.set_phenotypes(phenotype_1,phenotype_2);
        //I.display_phenotype1();
        //I.display_phenotype2();
        
        ME.challenger = I;
        ME.place_individual_in_map();
        fill_round++;

        
    }
    cout << "completed " << fill_round << " FILL rounds" << endl;
}
// --------------------------------------------------
            // Mutate Map
void Wrapper::mutate_MAP(){                         // TODO - Remove Comments for main program--------------------
    int mut_gen = ME.get_mutate_generation();
    int mutation_round=0;
    for (int g=0; g<mut_gen; g++){
        //cout << "mutation round is: " << g << endl;
        
        rand_bin();                             // random bin location
        ME.individual_from_map(bin1, bin2);     // copy Individual's vectors at bin location
        ME.challenger.mutate1();
        ME.challenger.mutate2();
        
        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        
        //Simulator Sim;
        Sim.initialize_sim();
        //Neural_Network NN;
        
        //ME.individual_from_map(p1, p2);
        NN.take_weights(ME.challenger.get_individual1(), ME.challenger.get_individual2());
        
        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
        NN.take_output_limits(Sim.currentstate.control_LowLimits,Sim.currentstate.control_UpLimits);
        

        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            /// while the simulator still has time left on the clock
            /// AND
            /// the craft is above ground level:
            
            NN.activation_function(Sim.currentstate.state_variables_vec);
            
            //NN.communication_from_simulator_deprecated(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
            Sim.run_timestep(NN.communication_to_simulator());
            NN.Neural_Network_Reset();                      // Do we want this??
        }
        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
        
        State current;
        current = Sim.currentstate;
        
        fitness_calculation(current);                           // fitness for new Individual
        ME.challenger.set_fit_rating(fit_rating);
        //ME.challenger.display_fit_rating();
        
        
        find_phenotypes();
        ME.challenger.set_phenotypes(phenotype_1,phenotype_2);
        //ME.challenger.display_phenotype1();
        //ME.challenger.display_phenotype2();
        ME.place_individual_in_map();
        mutation_round++;
    }
    cout << "completed " << mutation_round << " MUTATION rounds" << endl;
}
// --------------------------------------------------
            // Print stuff
void Wrapper::print_stuff(){
    ME.how_many_full_bins();
    ME.best_fit_bin();
    ME.print_fit_ratings_of_map();
    ME.print_best_occupants_fitness();
    ME.print_all_occupants();
    ME.print_best_parents_fitness();
    ME.print_best_parents_id();
    ME.print_best_full_trace();
    ME.print_heat_map();
    Sim.myfile.close();
}
// --------------------------------------------------

void Wrapper::print_entire_map_solution(){
    for(int element=0; element<full_bins.size();element++){

        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
    
        Sim.initialize_sim();
        NN.take_weights(ME.full_bins.at(element).get_individual1, ME.full_bins.at(element).get_individual2);
    
        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
        NN.take_output_limits(Sim.currentstate.control_LowLimits,Sim.currentstate.control_UpLimits);
    
    
        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            /// while the simulator still has time left on the clock
            /// AND
            /// the craft is above ground level:
        
            NN.activation_function(Sim.currentstate.state_variables_vec);
        
            //NN.communication_from_simulator_deprecated(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
            Sim.run_timestep(NN.communication_to_simulator());
            Sim.currentstate.printround(myfile,controls.at(0));
        
            NN.Neural_Network_Reset();                      
        }
        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
    }
}


// Run single test, modifiable weights of NN, recieve fit_rating and phenotypes.
// TODO - User inputs all weights.
// TODO - Able to change how weights are generated, access to different random functions.
//void Wrapper::run_single_individual(){
//    build_real_set();
//
//    Individual I;
//    I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
//    //I.display_individual_params();
//
//    I.build_individual();
//    I.display_individual1();
//    I.display_individual2();
//
//    empty_soln_set();
//    soln_set=I.genome1;
//    fitness_calculation();
//    I.set_fit_rating(fit_rating);
//    I.display_fit_rating();
//    set_x_pos(10);   // at x=10, the value of a and b are the phenotypes
//    //find_phenotypes();
//    I.set_phenotypes(75,5);
//    I.display_phenotype1();
//    I.display_phenotype2();
//
//    ME.place_individual_in_map(I);
//}
// fitness function from Sim
// I.set_fit_rating( double );
// get phenotypes from Sim
// I.set_phenotypes( double , double );
// ME.place_individual_in_map(I);

// --------------------------------------------------
//// --------------------------------------------------
//// Run single test, modifiable weights of NN, recieve fit_rating and phenotypes.
//
//void Wrapper::run_single_individual(Individual& I){
//    Simulator Sim;
//    Neural_Network NN;
//    I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
//
//    // TODO - User inputs all weights.
//    // TODO -Able to change how weights are generated, access to different random functions.
//
//    I.build_individual(); // TODO - change
//
//    Sim.initialize_sim();
//
//    NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
//    NN.take_output_limits(Sim.currentstate.control_LowLimits, Sim.currentstate.control_UpLimits);
//    NN.take_num_hidden_units(this->hidden_layer_size); /// repeated from initialize, but no harm.
//    NN.take_num_controls(Sim.currentstate.num_of_controls); /// repeated from initialize, but to no harm.
//    NN.take_weights(I.get_individual1(), I.get_individual2()); /// repeated from communication_from_EA, but to no harm.
//
//
//    NN.communication_from_EA(I.get_individual1(), I.get_individual2());
//    while (Sim.t<Sim.tmax || Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
//        vector<double> action;
//        action = NN.activation_function(Sim.currentstate.translate_function());
//        Sim.run_sim(action);
//        NN.reset_neural_network();                      // Do we want this??
//    }
//    // fitness function from Sim
//    // I.set_fit_rating( double );
//    // get phenotypes from Sim
//    // I.set_phenotypes( double , double );
//    // ME.place_individual_in_map(I);
//}



#endif /* Wrapper_hpp */
