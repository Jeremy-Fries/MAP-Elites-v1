//  Wrapper.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 11/16/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class Wrapper;

#ifndef Wrapper_hpp
#define Wrapper_hpp

#define BUFFER 10

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
    friend class Map_Elites;
// --------------------------------------------------
protected:
    Map_Elites ME;
    Map_Elites* pME = &ME;
    Map_space mspace;
    Map_space* pMspace =  &mspace;
    Neural_Network NN;
    Neural_Network* pN = &NN;
    Simulator Sim;
    Simulator* pS = &Sim;
    
    int size_of_genome1, size_of_genome2;
    
// --------------------------------------------------
public:
    int hidden_layer_size;
    vector<double> best_fit;
// --------------------------------------------------
    void initialize_wrapper(int,int);
    void wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2);
    vector<double>& get_individual_1_IH(vector<double>);
    vector<double>& get_individual_1_HO(vector<double>);
    vector<double>& get_individual_2_IH(vector<double>);
    vector<double>& get_individual_2_HO(vector<double>);
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
    void always_last();
    void load_genome1();
    void load_genome2();
    void load_bins();
    void write_from_old_genomes();
    void clear_map();
// --------------------------------------------------
private:
    int isize_1, isize_2, imutate_amount_1, imutate_amount_2;
    double imutate_mag_1,imutate_mag_2;
    int bin1, bin2;
    double fit_rating;
    double phenotype_1, phenotype_2;
    int map_solutions;
    int in_layer_size, out_layer_size;
    vector < vector <double> > Map_of_genome1;
    vector < vector <double> > Map_of_genome2;
    vector < vector<int> > Map_of_bins;
    
    vector<double> igenome1_IH;
    vector<double> igenome1_HO;
    vector<double> igenome2_IH;
    vector<double> igenome2_HO;
};
// ------------------------------------------------------------------------------------------------ ^^ Declarations
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ------------------------------------------------------------------------------------------------ vv Definitions

// -------------------------------------------------------------------------------------------------------------------------------------------------    SETTINGS
// -------------------------------------------------------------------------------------------------------------------------------------------------
            // Initialize Wrapper
void Wrapper::initialize_wrapper(int FILL, int MUTATE){
    
    int states = 7;
    int outs = 2;
    
    hidden_layer_size = 5;
    
    /// PHENOTYPE LIMITS
    pME->set_map_params(20, 60, 0, 100, 10, 10, FILL, MUTATE);                                                   //-------- To Change Map Settings

    // (dim1_min, dim1_max, dim2_min, dim2_max, resolution 1,2, fill generation, mutate generation)
    //pME->display_Map_params();        // TODO - delete and add print()
    
    in_layer_size=(states+1)*hidden_layer_size;
    out_layer_size=(hidden_layer_size+1)*outs;
    int num_weights=in_layer_size+out_layer_size;
    
    wrapper_sets_I_params(num_weights, num_weights, 0.5, 0.5, 4, 2);        //-------- To Change Individual Settings

    // individual_size 1,2, mutate_magnitude 1,2, mutation_amount 1,2)
    // int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2
    
    Sim.myfile.open("SimulatorData.txt");
    Sim.windfile.open("WindProfiles.txt");

    NN.initialize(this->hidden_layer_size, Sim.currentstate.num_of_controls);
}
// -------------------------------------------------------------------------------------------------------------------------------------------------    SETTINGS
// -------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------- TODO - change
            // Fitness Function
/// LYLY
void Wrapper::fitness_calculation(State current){
    fit_rating=0;
        //cout << "FIT0: " << fit_rating << endl;
    //cout << Sim.zpositions.size() << endl;
    
    //cout << endl << "KEx IS: " << current.KEx << endl;
    //cout << endl << "KEz IS: " << current.KEz << endl;
    //cout << endl << "KEp IS: " << current.KEp << endl;
    
    
    //// LANDING FITNESS CALCULATION
        /// must land (0)
        /// minimize x kinetic energy (1); z kinetic energy (2); rotational kinetic energy (3)
    //fit_rating -= current.KEx; // (1)
    //fit_rating -= current.KEz; // (2)
    //fit_rating -= current.KEp; // (3)
    //fit_rating -= current.zpos * current.zpos;
    
    /// GLIDING FITNESS CALCULATION
    //fit_rating += current.xpos;
    
        //cout << "FIT1: " << fit_rating << endl;
    if(current.zpos > 0){ /// still in air. (0)
        fit_rating = -99999999999999; /// TODO MAX_INT
    }
    
        //cout << "FIT2: " << fit_rating << endl;
    /// MINKE FITNESS CALCULATION
    double mass = 20.0;
    double gravity = 9.81;
    /// stay in air.
    //fit_rating += Sim.stateholder.size() * 1000;
    for(int i=0; i<Sim.stateholder.size(); i++){
        fit_rating -= Sim.stateholder.at(i).KEz;
        //cout << "FIT2.1: " << fit_rating << endl;
        fit_rating -= Sim.stateholder.at(i).KEx;
        //cout << "FIT2.2: " << fit_rating << endl;
        fit_rating -= Sim.stateholder.at(i).KEp;
        //cout << "FIT2.3: " << fit_rating << endl;
        fit_rating -= 1000 * Sim.stateholder.at(i).zpos * mass * gravity;
        //cout << "FIT2.4: " << fit_rating << endl;
    }
        
    
    //cout << "FIT3: " << fit_rating << endl;
        
    /// Hang Fitness Calculation
    //double tar1=0;
    //double tar2=0;
    
    //tar1 = fabs(current.phi - atan(1)*4/2);
    //tar1 = abs(current.KEz);
    //tar2 = abs(current.KEx);
    
    //fit_rating -=tar1;
    //fit_rating -=tar2;
    
    /// SOFT LANDING FITNESS:
    //fit_rating -=current.KEz;
    

}
// ----------------------------------------------------------------------------------- TODO - change
            // Phenotypes
void Wrapper::find_phenotypes(){
    /// PHENOTYPE CALCULATION
    
        /// x velocity at final time step
    //phenotype_1=Sim.currentstate.xvel;
    
        /// angular orientation at final time step
    //phenotype_2=Sim.currentstate.phi;
    
//----------------------------------------------------
        /// pheno 1 is time in air
    phenotype_1=Sim.currentstate.time;
    phenotype_2=Sim.currentstate.KEz;
    
    /// pheno 2 is
    //phenotype_2=Sim.currentstate.KEx;
    
        // ----------------------------------------------------
    /// for a Binary Selection Parallel Simulated Annealing.....
    //double r1 = ((double)rand() / RAND_MAX);
    //double r2 = ((double)rand() / RAND_MAX);
    //phenotype_1=r1*100;
    //phenotype_2=r2*100;
        // ----------------------------------------------------
}
// --------------------------------------------------
// Clear Map
void Wrapper::clear_map(){
    ME.Map.clear();
}
// -----------------------------------------------------------------------------------
// FOR BRAINS......... input to hidden and hidden to output
vector<double>& Wrapper::get_individual_1_IH(vector<double> igenome_1){
    igenome1_IH.clear();
    igenome1_IH.reserve(in_layer_size+BUFFER);
    for(int ih=0; ih<in_layer_size; ih++){
        igenome1_IH.push_back(igenome_1.at(ih));
    }
    return igenome1_IH;
}
vector<double>& Wrapper::get_individual_1_HO(vector<double> igenome_1){
    igenome1_HO.clear();
    igenome1_HO.reserve(out_layer_size+BUFFER);
    /// yes ho = in_layer_size, goes from in_layer_size to end of vector.
    for(int ho=in_layer_size; ho<(in_layer_size+out_layer_size); ho++){
        igenome1_HO.push_back(igenome_1.at(ho));
        }
    return igenome1_HO;
}
vector<double>& Wrapper::get_individual_2_IH(vector<double> igenome_2){
    igenome2_IH.clear();
    igenome2_IH.reserve(in_layer_size+BUFFER);
    for(int ih=0; ih<in_layer_size; ih++){
        igenome2_IH.push_back(igenome_2.at(ih));
    }
    return igenome2_IH;
}
vector<double>& Wrapper::get_individual_2_HO(vector<double> igenome_2){
    igenome2_HO.clear();
    igenome2_HO.reserve(out_layer_size+BUFFER);
    /// yes ho = in_layer_size, goes from in_layer_size to end of vector.
    for(int ho=in_layer_size; ho<(in_layer_size+out_layer_size); ho++){
        igenome2_HO.push_back(igenome_2.at(ho));
    }
    return igenome2_HO;
}
// -----------------------------------------------------------------------------------
            // Fill Map
void Wrapper::fill_MAP(){
    int fill_gen = ME.get_fill_generation();
    int fill_round=0;
    
    for (int g=0; g<fill_gen; g++){
        Individual I;
        
        I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
        I.build_individual();
        //I.display_individual1();    // comment out
        //I.display_individual2();    // comment out

        // NN.initialize(this->hidden_layer_size, Sim.currentstate.num_of_controls);       // TODO - Why is this here? Moved to initialize_wrapper().
        
        Sim.initialize_sim();
    
        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
        NN.take_output_limits(Sim.currentstate.control_LowLimits, Sim.currentstate.control_UpLimits);
        NN.take_num_hidden_units(this->hidden_layer_size); /// repeated from initialize, but no harm.
        NN.take_num_controls(Sim.currentstate.num_of_controls); /// repeated from initialize, but to no harm.
        
        // need to change
        //NN.take_weights(I.get_individual1(), I.get_individual2());
        
        NN.take_weights(get_individual_1_IH(I.get_individual1()), get_individual_1_HO(I.get_individual2()));
        
        
            /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
            
            // if stall() swich brain
            //NN.take_weights(get_individual_2_IH(I.get_individual1()), get_individual_2_HO(I.get_individual2()));
            
            
                /// while Sim still has time AND the Craft is above ground level.
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
        
        if(rand()%1000 < 100){
            cout << endl << "FILL Round is ---- " << g << " of " << fill_gen << endl;
        }
        
    }
    cout << "completed " << fill_round << " FILL rounds" << endl;
}
// --------------------------------------------------
            // Mutate Map
void Wrapper::mutate_MAP(){
    int mut_gen = ME.get_mutate_generation();
    int mutation_round=0;
    
    for (int g=0; g<mut_gen; g++){
        
        rand_bin();                             // random bin location
        ME.individual_from_map(bin1, bin2);     // copy Individual's vectors at bin location
        ME.challenger.mutate1();
        ME.challenger.mutate2();
        
        Sim.initialize_sim();
        
        //NN.take_weights(ME.challenger.get_individual1(), ME.challenger.get_individual2());
        NN.take_weights(get_individual_1_IH(ME.challenger.get_individual1()), get_individual_1_HO(ME.challenger.get_individual2()));
        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
        NN.take_output_limits(Sim.currentstate.control_LowLimits,Sim.currentstate.control_UpLimits);
        
            /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
                /// while Sim still has time AND the Craft above ground level.
            NN.activation_function(Sim.currentstate.state_variables_vec);
            Sim.run_timestep(NN.communication_to_simulator());
            NN.Neural_Network_Reset();
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
        
        if(rand()%1000 < 100){
            cout << endl << "MUTATE Round is ---- " << g << " of " << mut_gen << endl;
        }
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
    ME.print_corresponding_genome1();
    ME.print_corresponding_genome2();
    ME.print_corresponding_bins();
}
// --------------------------------------------------

void Wrapper::print_entire_map_solution(){
    map_solutions=0;
    
    for(int element=0; element<ME.full_bins.size();element++){
        cout << endl << "Bin ID: " << ME.full_bins.at(element).id << endl;
    
        Sim.initialize_sim();
        
        // --------------------------------------------- Display
//        cout << endl << "Genome 1 is:  " << endl;
//        ME.full_bins.at(element).current_individual.at(0).display_individual1();
//        cout << endl << endl << "Genome 2 is:  " << endl;
//        ME.full_bins.at(element).current_individual.at(0).display_individual2();
        // ---------------------------------------------
        
        NN.take_weights(ME.full_bins.at(element).current_individual.at(0).get_individual1() , ME.full_bins.at(element).current_individual.at(0).get_individual2());
        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
        NN.take_output_limits(Sim.currentstate.control_LowLimits,Sim.currentstate.control_UpLimits);
    
    
        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
                /// while Sim still has time AND the Craft above ground level.
            NN.activation_function(Sim.currentstate.state_variables_vec);
            Sim.run_final_timestep(NN.communication_to_simulator());
            vector<double> CC = NN.communication_to_simulator();
            NN.Neural_Network_Reset();                      
        }
        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
        map_solutions++;
    }
    cout << endl << endl << "Number of Solutions OUTPUTTED: " << map_solutions << endl;
    cout << endl << "Number of Solutions is: " << ME.full_bins.size()  << endl;
}
// --------------------------------------------------
void Wrapper::load_genome1(){
    ifstream co("print_corresponding_genome1.txt");
    
    // Get rid of txt file location.
    
    double read;
    vector<double> apush;
    
    cout << "WE GET INTO THIS FUNCTION " << endl;
    while(co >> read){
        apush.push_back(read);
        cout <<"SIZE OF APUSH IS: " << apush.size() << endl;
        cout <<"SIZE OF GENOME 1 IS: " << Map_of_genome1.size() << endl;
        if(apush.size()>=size_of_genome1){
            Map_of_genome1.push_back(apush);
            cout << "SIZE OF APUSH IS: " << apush.size() << endl;
            apush.clear();
        }
    }
    //cout << "GENOME ONE IS: " << endl;
    //for(int i=0; i< Map_of_genome1.size(); i++){
    //    cout << Map_of_genome1.at(i) << "\t";
    //}
    //cout << endl;
    
    cout << endl << "Starting size Map of old genome 1 is: " << Map_of_genome1.size() << endl;
    cout << endl << "Starting size of old genome 1 is: " << Map_of_genome1.at(0).size() << endl;
}
// --------------------------------------------------
void Wrapper::load_genome2(){
    ifstream co("print_corresponding_genome2.txt");
    
    double read;
    vector<double> apush;
    
    while(co >> read){
        apush.push_back(read);
        
        if(apush.size()>=size_of_genome2){
            Map_of_genome2.push_back(apush);
            apush.clear();
        }
    }
    cout << endl << "Starting size Map of old genome 2 is: " << Map_of_genome2.size() << endl;
    cout << endl << "Starting size of old genome 2 is: " << Map_of_genome2.at(0).size() << endl;
}
// --------------------------------------------------
//write
void Wrapper::write_from_old_genomes(){
    /// Read from txt file
    Map_of_genome1.clear();
    Map_of_genome2.clear();
    
    load_genome1();
    cout << endl << "Starting size of old genome 1 is: " << Map_of_genome1.at(0).size() << endl;
    load_genome2();
    cout << endl << "Starting size of old genome 2 is: " << Map_of_genome2.at(0).size() << endl;
    
    int old_placed_counter=0;
    if (Map_of_genome1.size()== Map_of_genome2.size()){
        for (int i=0;i<Map_of_genome1.size();i++){
            Individual I;
            I.set_individual_params(Map_of_genome1.at(i).size(), Map_of_genome2.at(i).size(), imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
            I.build_individual_1_from_another(Map_of_genome1.at(i));
            I.build_individual_2_from_another(Map_of_genome2.at(i));
    
            Sim.initialize_sim();
            
            NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
            NN.take_output_limits(Sim.currentstate.control_LowLimits, Sim.currentstate.control_UpLimits);
            NN.take_num_hidden_units(this->hidden_layer_size); /// repeated from initialize, but no harm.
            NN.take_num_controls(Sim.currentstate.num_of_controls); /// repeated from initialize, but to no harm.
            NN.take_weights(I.get_individual1(), I.get_individual2());
            
            /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
            while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
                /// while Sim still has time AND the Craft is above ground level.
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
            old_placed_counter++;
        }
    }
    else {
        cout << endl << "Error, Genomes from txt file are NOT the same size." << endl;
    }
    cout << endl << "Quantity of Old Genomes Placed is: " << old_placed_counter << endl;
}
// --------------------------------------------------
// //write
//void Wrapper::write_from_old_genomes(){
//        /// Read from txt file
//    load_genome1();
//    load_genome2();
//    load_bins();
//        /// build map from old map of genomes
//    
//    ME.build_map_from_old(Map_of_genome1,Map_of_genome2, Map_of_bins);
//    // Sim loop to tack on fitness
//    
//    // ----=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-VVVVVV
//    // get rid of bin vec,
//    // iterate through old genome vecs running each through the sim to find fit and phenos, place into map, don't need old bins then.
//    
//    // for all bins go through and check if occupied, if so run sim and get fitness and phenotypes.
//    for(int row_value=0; row_value<ME.num_spacing1; row_value++){
//        for(int element_value=0; element_value<ME.num_spacing2; element_value++){
//    
//            if(ME.Map.at(row_value).at(element_value).full_bin_check()==0){
//            
//                // make sure can only grab an occupied bin, make another function otherwise.
//                //ME.individual_from_map(row_value, element_value);     // copy Individual's vectors at bin location
//        
//                Sim.initialize_sim();
//        
//                NN.take_weights(ME.Map.at(row_value).at(element_value).current_individual.at(0).get_individual1(), ME.Map.at(row_value).at(element_value).current_individual.at(0).get_individual2());
//                NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
//                NN.take_output_limits(Sim.currentstate.control_LowLimits,Sim.currentstate.control_UpLimits);
//        
//                /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
//                while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
//                    /// while Sim still has time AND the Craft above ground level.
//                    NN.activation_function(Sim.currentstate.state_variables_vec);
//                    Sim.run_timestep(NN.communication_to_simulator());
//                    NN.Neural_Network_Reset();
//                }
//                /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
//        
//                State current;
//                current = Sim.currentstate;
//        
//                fitness_calculation(current);                           // fitness for new Individual
//                ME.Map.at(row_value).at(element_value).current_individual.at(0).set_fit_rating(fit_rating);
//                //ME.challenger.display_fit_rating();
//        
//                find_phenotypes();
//                ME.Map.at(row_value).at(element_value).current_individual.at(0).set_phenotypes(phenotype_1,phenotype_2);
//                //ME.challenger.display_phenotype1();
//                //ME.challenger.display_phenotype2();
//                //ME.place_individual_in_map();
//        
//            }
//        }
//    }
//}
//
// run






// --------------------------------------------------
            // Wrapper sets Individual
void Wrapper::wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2){
    cout << endl << " size of first layer is: " << size1 << endl;
    cout << endl << " size of last layer is: " << size2 << endl;
    
    isize_1=size1;
    isize_2=size2;
    imutate_mag_1=mut_mag1;
    imutate_mag_2=mut_mag2;
    imutate_amount_1=mut_amo1;
    imutate_amount_2=mut_amo2;
    /// assigns values to actual individual.
    
    size_of_genome1=size1;  // For ME input_genome()
    size_of_genome2=size2;
}
// --------------------------------------------------
            // Random Bin
void Wrapper::rand_bin(){
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
// --------------------------------------------------
void Wrapper::always_last(){
    Sim.myfile.close();
    Sim.windfile.close();
}
// --------------------------------------------------





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
