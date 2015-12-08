//
//  Neural Network.hpp
//  Controller
//
//  Created by Scott Forer on 11/19/15.
//  Copyright © 2015 Scott Forer. All rights reserved.
//

#ifndef Neural_Network_hpp
#define Neural_Network_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "Layer.hpp"
using namespace std;

class Neural_Network
{
    friend class Layer;
    friend class Node;
    friend class Dummy_simulator;
    friend class Dummy_EA;
    friend class Wrapper;
    
protected:
    void create_layer_sizes();
    void create_layers();

public:
    //Neural Network Framework
    vector<Layer> Layers;
    vector<int> layer_size;
    int hidden_layer_size;
    int number_controls;
    void initialize();

    //Communication with Simulator
    vector<double> state_variables;
    vector<double> state_variable_upper_limits;
    vector<double> state_variable_lower_limits;
    void communication_from_simulator(vector<double> sim_state_variable_inputs, vector<double> sim_state_variable_upper_limits, vector<double> sim_state_variable_lower_limits, int sim_hidden_layer_size, int sim_number_controls, vector<double> sim_control_upper_limits, vector<double> sim_control_lower_limits);
    vector<double> control_upper_limits;
    vector<double> control_lower_limits;
    vector<double> controls_for_simulator;
    vector<double> communication_to_simulator();
    
    //Communication with EA
    vector<double> input_to_hidden_layer_weights;
    vector<double> hidden_to_output_layer_weights;
    void communication_to_EA();
    void communication_from_EA(vector<double> ea_input_to_hidden_layer_weights, vector<double> ea_hidden_to_output_layer_weights);
    
    //Input Layer
    void create_input_layer();
    void normalization();
    
    //Input to Hidden Layer
    void input_hidden_layer_connection();
    vector<double> bb;
    vector<double> input_to_hidden_layer_connection;
    vector<double> weighted_input_to_hidden_layer_connection;
    void input_to_hidden_layer_weight_multiplication();
    
    //Hidden Layer
    void sum_hidden_layer();
    void hidden_layer_sigmoid();
    
    //Hidden to Output Layer
    void hidden_output_layer_connection();
    vector<double> cc;
    vector<double> hidden_to_output_layer_connection;
    vector<double> weighted_hidden_to_output_layer_connection;
    void hidden_to_output_layer_weight_multiplication();
    
    //Output Layer
    void sum_output_layer();
    void output_layer_sigmoid();
    void unnormalization();
    vector<double> controls;
    
    //Sigmoid Function
    double sigmoid_input;
    double sigmoid_output;
    double sigmoid_function();
    
    //Neruarl Network Process
    void activation_function(vector<double> sim_state_variable_inputs, vector<double> sim_state_variable_upper_limits, vector<double> sim_state_variable_lower_limits, int sim_hidden_layer_size, int sim_number_controls, vector<double> sim_control_upper_limits, vector<double> sim_control_lower_limits, vector<double> ea_input_to_hidden_layer_weights, vector<double> ea_hidden_to_output_layer_weights, vector<double> controls_for_simulator);
    
    //Text File Functions
    void write_state_variables_limits_to_text(bool display);
    void write_weigths_to_text(bool display);
    void write_control_limits_to_text(bool display);
    void write_topography_to_text(bool display);
    void write_to_text_file();
    
    //Reset Funtion
    void reset_neural_network();
    void total_neural_network_reset();

private:
    
    
};



#endif /* Neural_Network_hpp */
