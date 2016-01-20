////
////  Wrapper.hpp
////  Mapping_Elites v1
////
////  Created by Jeremy Fries on 11/16/15.
////  Copyright © 2015 Jeremy Fries. All rights reserved.
////
//
//class Wrapper;
//
//#ifndef Wrapper_hpp
//#define Wrapper_hpp
//
//#include <stdio.h>
//#include <iostream>
//#include <iterator>
//#include <vector>
//#include <algorithm>
//#include <ostream>
//
//
//
//#include "LinDOF.hpp"
//#include "RotDOF.hpp"
//#include "anglemath.h"
//#include "dynamics.h"
//#include "Craft.hpp"
//#include "State.hpp"
//#include "Simulator.hpp"
//
//#include "Neural Network.hpp"
//
//#include "Individual.hpp"
//#include "Map_space.hpp"
//#include "Map_Elites.hpp"
//
//
//using namespace std;
//
//class Wrapper{
//protected:
//    Map_Elites ME;
//    Map_Elites* pME = &ME;
//    Map_space mspace;
//    Map_space* pMspace =  &mspace;
//    Individual individual1;
//    Individual* pI = &individual1;
//    Neural_Network NN;
//    Neural_Network* pN = &NN;
//    Simulator Sim;
//    Simulator* pS = &Sim;
//    
//    
//public:
//    const int hidden_layer_size = 3;
//// --------------------------------------------------
//    void initialize_wrapper();
//    void wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2);
//// --------------------------------------------------
//        // Loop functions combine all
//    void wrapper_runs_sim(vector<double>,vector<double>);
//    void fill_MAP();
//    void mutate_MAP();
//    void run_single_individual(Individual& I);
//// --------------------------------------------------
//        // Interactions between - MAP and NN

//    
//// --------------------------------------------------
//        // Interactions between - MAP and SIM

//    
//// --------------------------------------------------
//        // Interactions between - NN and SIM

//private:
//    int isize_1, isize_2, imutate_amount_1, imutate_amount_2;
//    double imutate_mag_1,imutate_mag_2;
//};
//
//// --------------------------------------------------
//void Wrapper::initialize_wrapper(){
//    
//    int states = 6;
//    int outs = 2;
//    
//    pME->set_map_params(0, 10, 0, 10, 4, 4, 10, 50);
//    // (dim1_min, dim1_max, dim2_min, dim2_max, resolution1,2, fill generation, mutate generation)
//    
//    wrapper_sets_I_params((states+1)*hidden_layer_size, (hidden_layer_size+1)*outs, 0.1, 0.1, 4, 2);
//    // individual_size 1,2, mutate_magnitude 1,2, mutation_amount 1,2)
//}
//// --------------------------------------------------
//void Wrapper::wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2){
//    isize_1=size1;
//    isize_2=size2;
//    imutate_mag_1=mut_mag1;
//    imutate_mag_2=mut_mag2;
//    imutate_amount_1=mut_amo1;
//    imutate_amount_2=mut_amo2;
//    
//    /// assigns values to actual individual.
//    //individual1.set_individual_params(size1,size2,mut_mag1,mut_mag2,mut_amo1,mut_amo2);
//    //set_individual_params(int individual_size1,int individual_size2,double mutation_magnitude1,double mutation_magnitude2,int mutation_amount1,int mutation_amount2);
//}
//// --------------------------------------------------
//// Pass new individual or mutation from table to NN and Sim to run and recieve fitness/phenotypes
////void Wrapper::wrapper_runs_sim(I.get_individual1(),I.get_individual2()){
//
//// ONCE NN functions are fixed, implement loop here
//
//
////};
//// --------------------------------------------------
//void Wrapper::fill_MAP(){
//    int fill_gen = ME.get_fill_generation();
//    
//    for (int g=0; g<fill_gen; g++){
//        /// create objects
//        Individual I;
//        Simulator Sim;
//        Neural_Network NN;
//        
//        /// initialize individual
//        I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
//        I.build_individual();
//        
//        /// initialize NN.
//        NN.initialize(this->hidden_layer_size, Sim.currentstate.num_of_controls);
//        
//        NN.communication_from_EA(I.get_individual1(), I.get_individual2());
//        Sim.initialize_sim();
//        
//        NN.take_input_limits(Sim.currentstate.state_variables_LowLimit, Sim.currentstate.state_variables_UpLimit);
//        NN.take_output_limits(Sim.currentstate.control_LowLimits, Sim.currentstate.control_UpLimits);
//        NN.take_num_hidden_units(this->hidden_layer_size); /// repeated from initialize, but no harm.
//        NN.take_num_controls(Sim.currentstate.num_of_controls); /// repeated from initialize, but to no harm.
//        NN.take_weights(I.get_individual1(), I.get_individual2()); /// repeated from communication_from_EA, but to no harm.
//        
//        I.display_individual_size1();
//        I.display_individual_size2();
//        
//        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
//        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
//            /// while the simulator still has time left on the clock
//            /// AND
//            /// the craft is above ground level:
//            
//            //NN.communication_from_simulator_deprecated(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
//            //vector<double> SPOT(2);
////            NN.activation_function_deprecated(
////                                   Sim.currentstate.translate_function(),
////                                   Sim.currentstate.state_variables_UpLimit,
////                                   Sim.currentstate.state_variables_LowLimit,
////                                   hidden_layer_size,
////                                   Sim.currentstate.num_of_controls,
////                                   Sim.currentstate.control_UpLimits,
////                                   Sim.currentstate.control_LowLimits,
////                                   I.get_individual1(),
////                                   I.get_individual2(),
////                                   SPOT
////                                   );
//            //cout << "Time: " << Sim.t << endl;
//            
//            vector<double> action = NN.activation_function(Sim.currentstate.translate_function());
//            
//            //vector<double> activation_function(vector<double> state);
//            //void take_input_limits(vector<double> lower, vector<double> upper);
//            //void take_output_limits(vector<double> lower, vector<double> upper);
//            //void take_num_hidden_units(int num_hidden);
//            //void take_num_controls(int num_controls);
//            //void take_weights(vector<double> in_to_hid, vector<double> hid_to_out);
//            
//            Sim.run_sim(action);
//            
//            
//            NN.reset_neural_network();                      // Do we want this??
//        }
//        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
//        
//        // fitness function from Sim
//        // I.set_fit_rating( double );
//        // get phenotypes from Sim
//        // I.set_phenotypes( double , double );
//        // ME.place_individual_in_map(I);
//    }
//}
//// --------------------------------------------------
//void Wrapper::mutate_MAP(){
//    int mut_gen = ME.get_mutate_generation();
//    for (int g=0; g<mut_gen; g++){
//        Simulator Sim;
//        Neural_Network NN;
//        
//        // p1 and p2 rand numbers OR -> rand placment function() modifiable
//        //ME.individual_from_map(p1, p2);
//        NN.communication_from_EA(ME.get_temp_individual1(), ME.get_temp_individual2());
//        Sim.initialize_sim();
//        /// %%% /// %%% BEGIN SIMULATION LOOP %%% /// %%% ///
//        while (Sim.t<Sim.tmax && Sim.lander.frame.at(1).s > Sim.lander.frame.at(1).target){
//            /// while the simulator still has time left on the clock
//            /// AND
//            /// the craft is above ground level:
//            
//            NN.communication_from_simulator_deprecated(Sim.currentstate.translate_function(), Sim.currentstate.state_variables_UpLimit, Sim.currentstate.state_variables_LowLimit, hidden_layer_size, Sim.currentstate.num_of_controls, Sim.currentstate.control_UpLimits, Sim.currentstate.control_LowLimits);
//            Sim.run_sim(NN.communication_to_simulator());
//            NN.reset_neural_network();                      // Do we want this??
//        }
//        /// %%% /// %%% END SIMULATION LOOP %%% /// %%% ///
//        // fitness function from Sim
//        // I.set_fit_rating( double );
//        // get phenotypes from Sim
//        // I.set_phenotypes( double , double );
//        // ME.place_individual_in_map(I);
//    }
//}
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
//// --------------------------------------------------
//
//
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
#include <cmath>
#include <fstream>
#include <iomanip>
#include "Individual.hpp"
#include "Map_space.hpp"
#include "Map_Elites.hpp"

using namespace std;

class Wrapper{
    
    // --------------------------------------------------
protected:
    Map_Elites ME;
    Map_Elites* pME = &ME;
    Map_space mspace;
    Map_space* pMspace =  &mspace;
    Individual individual1;
    Individual* pI = &individual1;
    // --------------------------------------------------
public:
    const int hidden_layer_size = 3;
    vector<double> best_fit;
    // --------------------------------------------------
    void initialize_wrapper();
    void wrapper_sets_I_params(int size1, int size2, double mut_mag1, double mut_mag2, int mut_amo1, int mut_amo2);
    // --------------------------------------------------
    // Loop functions combine all
    void wrapper_runs_sim(vector<double>,vector<double>);
    void fill_MAP();
    void rand_bin();
    void mutate_MAP();
    void run_single_individual();
    void print_stuff();             // TODO - Change name
    // ----------------------------------------------------------------------------------- P0 Functions
    // P0 functions
    void build_real_set();
    void empty_soln_set();
    void fitness_P0();
    double f_1(double, double, double);
    double f_2(double, double, double);
    double real_func();
    double approx_func();
    void fill_MAP_P0();
    void new_x_pos();
    void set_x_pos(double);
    double get_x_pos();
    void display_x_pos();
    void find_phenotypes();
    void display_phenotypes();
    void graph_final();
    
    // Phenotypes: min, max,            integral output, range, calc d", # of pts d' is + or -, sum of average slopes,
    // --------------------------------------------------
private:
    int isize_1, isize_2, imutate_amount_1, imutate_amount_2;
    double imutate_mag_1,imutate_mag_2;
    int bin1, bin2;
    
    // P0 variables
    vector <double> real_set;
    vector <double> soln_set;
    double real_value;
    double approx_value;
    double x_pos;
    double calc_fit_rating;
    double fit_rating;
    double phenotype_1, phenotype_2;
};
// ----------------------------------------------------------------------------------- P0 Functions------------------------------
void Wrapper::build_real_set(){
    // [ a1 b1 a2 b2]
    // Creates [1 1 0 0]
    real_set.clear();
    real_set.push_back(1);
    real_set.push_back(1);
    real_set.push_back(0);
    real_set.push_back(0);
}
// ----------------------------------------------------------------------------------- P0 Functions
double Wrapper::f_1(double x, double a1, double b1){
    double f = (a1*(x*x)) + b1;
    return f;
}
double Wrapper::f_2(double x, double a2, double b2){
    double f = (a2*x)+b2;
    return f;
}
// ----------------------------------------------------------------------------------- P0 Functions
// Real Function Value - real coefficient_set's value at x_pos
double Wrapper::real_func(){
    double x = get_x_pos();                                 // P0 TODO - set x pos
    double a, b;
    a = f_1(x, real_set.at(0), real_set.at(1));
    b = f_2(x, real_set.at(2), real_set.at(3));
    real_value = (a + b);
    //cout << endl << "real value is: " << real_value << endl;
    return real_value;
}
// Approx function Value - solution_set's value at x_pos
double Wrapper::approx_func(){
    double x = get_x_pos();
    double a, b;
    a = f_1(x, soln_set.at(0), soln_set.at(1));
    b = f_2(x, soln_set.at(2), soln_set.at(3));
    approx_value = (a + b);
    //cout << endl << "Approximate Value is: " << approx_value << endl;
    return approx_value;
}
// ----------------------------------------------------------------------------------- P0 Functions
// Set x position to desired value
void Wrapper::new_x_pos(){
    double pre_x = ((double)rand() / RAND_MAX);
    double x = pre_x * 2 * 3.1416;
    x_pos = x;
}
// Set x position
void Wrapper::set_x_pos(double x){
    x_pos=x;
}
// Get x position
double Wrapper::get_x_pos(){
    return x_pos;
}
// Display x position
void Wrapper::display_x_pos(){
    cout << "\t x_pos is: " << x_pos << endl;
}
// ----------------------------------------------------------------------------------- P0 Functions
void Wrapper::fitness_P0(){
    calc_fit_rating=0;
    fit_rating=0;
    for (int q = 0; q < 20; q++){
        new_x_pos();
        calc_fit_rating -= abs(real_func() - approx_func());
    }
    fit_rating=calc_fit_rating;
}
// ----------------------------------------------------------------------------------- P0 Functions
// Phenotypes
void Wrapper::find_phenotypes(){
    phenotype_1=0;
    phenotype_2=0;
    //double x = get_x_pos();
    //double a, b;
    //a = f_1(x, soln_set.at(0), soln_set.at(1));
    //b = f_2(x, soln_set.at(2), soln_set.at(3));
    double r1 = ((double)rand() / RAND_MAX);
    double r2 = ((double)rand() / RAND_MAX);
    phenotype_1=r1*100;
    phenotype_2=r2*100;
    //cout << a << " , " << b << endl;
}
// ----------------------------------------------------------------------------------- P0 Functions
// Results for best Individual to grap
void Wrapper::graph_final(){
    soln_set.empty();       // only for P0
    soln_set=ME.get_best_individual1();     // when implmented error.
    ofstream myfile;
    myfile.open ("Graph_approx_function.txt");
    for (int xx=0; xx<100; xx++){
        set_x_pos(xx);
        double in_x=get_x_pos();
        double out_y=approx_func();
        myfile << fixed << setprecision(8) << in_x << "\t\t" << out_y << "\n";
    }
    myfile.close();
}
// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------
//
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
// -------------------------------------------------------------------------------------------------------- To Change Settings
void Wrapper::initialize_wrapper(){
    
    pME->set_map_params(0, 100, 0, 100, 10, 10, 100, 1000000);
    // (dim1_min, dim1_max, dim2_min, dim2_max, resolution1,2, fill generation, mutate generation)
    
    //pME->display_Map_params();
    
    wrapper_sets_I_params(4, 0, 1, 0, 2, 0); // P0 - only one genome in individual.
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
// ----------------------------------------------------------------------------------- P0 Functions
void Wrapper::fill_MAP_P0(){
    int fill_gen = ME.get_fill_generation();
    int fill_round=0;
    build_real_set();
    
    for (int g=0; g<fill_gen; g++){
        //cout << "fill round is: " << g << endl;
        Individual I;
        I.set_individual_params(isize_1, isize_2, imutate_mag_1, imutate_mag_2, imutate_amount_1, imutate_amount_2);
        //I.display_individual_params();
        
        I.build_individual();
        //I.display_individual1();
        //I.display_individual2();
        
        soln_set.empty();       // only for P0
        soln_set=I.genome1;     // only for P0
        fitness_P0();
        I.set_fit_rating(fit_rating);
        //I.display_fit_rating();
        set_x_pos(10);   // at x=10, the value of a and b are the phenotypes    // only for P0
        find_phenotypes();
        I.set_phenotypes(phenotype_1,phenotype_2);
        //I.display_phenotype1();
        //I.display_phenotype2();
        
        ME.challenger = I;
        ME.place_individual_in_map();
        fill_round++;
        // push_back best fit rating to vector
        
    }
    cout << "completed " << fill_round << " FILL rounds" << endl;
}
// --------------------------------------------------
void Wrapper::mutate_MAP(){                         // TODO - Remove Comments for main program--------------------
    int mut_gen = ME.get_mutate_generation();
    int mutation_round=0;
    for (int g=0; g<mut_gen; g++){
        //cout << "mutation round is: " << g << endl;
        soln_set.empty();       // only for P0
        rand_bin();                             // random bin location
        ME.individual_from_map(bin1, bin2);     // copy Individual's vectors at bin location
        ME.challenger.mutate1();
        soln_set=ME.challenger.get_individual1();     // only for P0
        fitness_P0();                           // fitness for new Individual
        ME.challenger.set_fit_rating(fit_rating);
        //ME.challenger.display_fit_rating();
        set_x_pos(10);   // at x=10, the value of a and b are the phenotypes--- NOT in USE    // only for P0
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
//    fitness_P0();
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

// TODO - functions
// choose bin from map and test function
//




#endif /* Wrapper_hpp */




//#endif /* Wrapper_hpp */
