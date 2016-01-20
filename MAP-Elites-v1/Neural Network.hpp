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




using namespace std;


class Node
{
    friend class Neural_Network;
    friend class Layer;
    
protected:
    
    
public:
    double element;
    
    
private:
    
    
};

class Layer
{
    friend class Neural_Network;
    friend class Node;
    
    
protected:
    
    
public:
    vector<Node> Nodes;
    int ID;
    void create_nodes(int number_nodes);
    
private:
    
    
};

//Node generator
void Layer::create_nodes(int layer_size)
{
    for(int i=0; i < layer_size; i++)
    {
        Node N;
        Nodes.push_back(N);
    }
    ////cout << "Number of nodes" << endl;
    ////cout << Nodes.size() << endl;
    ////cout << "\n" << endl;
}

class Neural_Network
{
    friend class Layer;
    friend class Node;
    friend class Dummy_simulator;
    friend class Dummy_EA;
    friend class Individual;
    friend class Scoreboard;
    friend class wrapper;
    
protected:
    void create_layer_sizes();
    void create_layers();
    
public:
    //Neural Network Framework
    vector<Layer> Layers;
    vector<int> layer_size;
    int hidden_layer_size;
    int number_controls;
    void initialize(int num_hidden, int num_controls);
    
    //Neruarl Network Communication Process
    void activation_function(vector<double> state);
    void take_input_limits(vector<double> lower, vector<double> upper);
    vector<double> state_variable_upper_limits;
    vector<double> state_variable_lower_limits;
    void take_output_limits(vector<double> lower, vector<double> upper);
    vector<double> control_upper_limits;
    vector<double> control_lower_limits;
    void take_num_hidden_units(int num_hidden);
    void take_num_controls(int num_controls);
    void take_weights(vector<double> in_to_hid, vector<double> hid_to_out);
    vector<double> input_to_hidden_layer_weights;
    vector<double> hidden_to_output_layer_weights;
    void take_state(vector<double> S);
    vector<double> state_variables;
    
    //Communication to Simulator
    vector<double> controls_for_simulator;
    vector<double> communication_to_simulator();
    
    //Input Layer
    void create_input_layer();
    void normalization();
    
    //Input to Hidden Layer
    void input_hidden_layer_connection();
    vector<double> input_to_hidden_layer_connection;
    vector<double> weighted_input_to_hidden_layer_connection;
    void input_to_hidden_layer_weight_multiplication();
    
    //Hidden Layer
    void sum_hidden_layer();
    void hidden_layer_sigmoid();
    
    //Hidden to Output Layer
    void hidden_output_layer_connection();
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
    
    
    //Text File Functions
    void write_state_variables_limits_to_text(bool display);    //FOR TESTING ONLY
    void write_weigths_to_text(bool display);   //FOR TESTING ONLY
    void write_control_limits_to_text(bool display);    //FOR TESTING ONLY
    void write_topography_to_text(bool display);    //FOR TESTING ONLY
    void write_to_text_file();  //FOR TESTING ONLY
    
    //Reset Funtions
    void Neural_Network_Reset(); //Use after each time step to reset the ANN and state variables
    void Experimental_Reset(); //Use after each experimental run to reset the ANN state variables and weights
    
private:
    
};


/////////////////////////////////////////////////////////////////
//Communication functions
//recieves input limits
void Neural_Network::take_input_limits(vector<double> low, vector<double> up)
{
    state_variable_lower_limits = low;
    state_variable_upper_limits = up;
}
//recieves output limits
void Neural_Network::take_output_limits(vector<double> low, vector<double> up)
{
    control_upper_limits = up;
    control_lower_limits = low;
}
//recieves number of hiddden layer nodes
void Neural_Network::take_num_hidden_units(int n)
{ /// repeated from initialize, but no harm.
    hidden_layer_size = n;
}
//recieves number of controls
void Neural_Network::take_num_controls(int n)
{ /// repeated from initialize, but to no harm.
    number_controls = n;
}
//recieves input to hidden layer and hidden to output layer weights
void Neural_Network::take_weights(vector<double> IH, vector<double> HO)
{
    input_to_hidden_layer_weights = IH;
    hidden_to_output_layer_weights = HO;
}
//recieves state variables
void Neural_Network::take_state(vector<double> S)
{
    state_variables=S;
    
}


//-----------------------------------------------------------------------------------------------------------------------------
//intitializes hidden and output layer sizes
void Neural_Network::initialize(int num_hidden, int num_controls)
{
    hidden_layer_size = num_hidden;
    number_controls = num_controls;
}


//-----------------------------------------------------------------------------------------------------------------------------
//creates a vector of a layer sizes
void Neural_Network::create_layer_sizes()
{
    layer_size.clear();
    layer_size.push_back(state_variables.size() + 1);
    layer_size.push_back(hidden_layer_size + 1);
    layer_size.push_back(number_controls);
}


//-----------------------------------------------------------------------------------------------------------------------------
//Layer generator
//The components of each layer will be created based on the size of each layer
//the first layer is the input layer, the last layer is the output layer, and the other layers are the hidden layers
//For the VTOL project only one hidden layer is needed
void Neural_Network::create_layers()
{
    vector<Layer> L(3);        //intializes a vector of layers the size of the number of layers
    Layers = L;
    //cout << "Number of layers" << endl;
    //cout << Layers.size() << endl;
    //cout << "\n" << endl;
    for(int j = 0; j < Layers.size(); j++)
    {
        Layers.at(j).ID = j;
        Layers.at(j).create_nodes(layer_size.at(j));
    }
}


//-----------------------------------------------------------------------------------------------------------------------------
//initalize input layer
void Neural_Network::create_input_layer()
{
    ////cout << "Unnormalized Input Layer" << endl;
    ////cout << Layers.at(0).Nodes.size() << endl;
    
    
    //Layers.at(0).Nodes.clear();
    
    //for(int n=0; n<layer_size.at(0); n++){
    //Node N;
    //Layers.at(0).Nodes.push_back(N);
    //}
    
    for(int j = 0; j < state_variables.size(); j++)
    {
        
        Layers.at(0).Nodes.at(j).element = state_variables.at(j);
    }
    //for(int j = 0; j < Layers.at(0).Nodes.size() - 1; j++)
    //{
    //cout << Layers.at(0).Nodes.at(j).element << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Normalization function
//Creates the normalized state variables and pushes them into a vector using the unnormalized state variales and their respective limits
void Neural_Network::normalization()
{
    //Takes a state variable multiplies it by its lower limit and then divdes by the difference between the upper and lower limit
    for (int j = 0; j < state_variables.size(); j++)
    {
        Layers.at(0).Nodes.at(j).element = (state_variables.at(j) - state_variable_lower_limits.at(j))/(state_variable_upper_limits.at(j) - state_variable_lower_limits.at(j));
    }
    Layers.at(0).Nodes.at(state_variables.size()).element = 1;
    //    cout << "Normalized Input Layer" << endl;
    //    cout << Layers.at(0).Nodes.size() - 1 << endl;
    //    //Writes each normalized state variable to the console
    //    for(int j = 0; j < Layers.at(0).Nodes.size(); j++)
    //    {
    //        cout << Layers.at(0).Nodes.at(j).element << "\t";
    //    }
    //    cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//input layer to hidden layer connection
//makes copies(size of hidden layer) of each element of the input layer
void Neural_Network::input_hidden_layer_connection()
{
    vector<double> bb;
    for(int j = 0; j < Layers.at(0).Nodes.size(); j++)
    {
        for(int k = 0; k < Layers.at(1).Nodes.size() - 1; k++)
        {
            bb.push_back(Layers.at(0).Nodes.at(j).element);
        }
    }
    input_to_hidden_layer_connection = bb;
    //cout << "Unweighted input to hidden layer connection" << endl;
    //cout << input_to_hidden_layer_connection.size() << endl;
    //cout << hidden_to_output_layer_connection.size() << endl;
    //for(int i = 0; i <input_to_hidden_layer_connection.size(); i++)
    //{
    //cout << input_to_hidden_layer_connection.at(i) << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Weight Multiplication function
//takes the double value of node and multiplies it to each element in the weight vector
void Neural_Network::input_to_hidden_layer_weight_multiplication()
{
    for(int j = 0; j < input_to_hidden_layer_connection.size(); j++)
    {
        weighted_input_to_hidden_layer_connection.push_back(input_to_hidden_layer_connection.at(j) * input_to_hidden_layer_weights.at(j));
    }
    //cout << "Weighted input to hidden layer connections" << endl;
    //cout << weighted_input_to_hidden_layer_connection.size() << endl;
    //for(int i = 0; i < weighted_input_to_hidden_layer_connection.size(); i++)
    //{
    //cout << weighted_input_to_hidden_layer_connection.at(i) << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Summation of inputs
//the vector of type double will be given by the vector of type double returned from the weight multiplication fucntion
//takes the sum  of the inputs entering a node
void Neural_Network::sum_hidden_layer()
{
    //    cout << "xxxxxxx" << endl;
    //    for(int j = 0; j <Layers.at(1).Nodes.size(); j++)             //WTF?
    //    {
    //        cout << Layers.at(1).Nodes.at(j).element << endl;
    //    }
    for(int j = 0; j < Layers.at(1).Nodes.size() - 1; j++)
    {
        double z = 0;                   //reinitialize z to be 0
        double zz = 0;                  //reinitialize zz to be 0
        for(int k = 0; k < (weighted_input_to_hidden_layer_connection.size()/(Layers.at(1).Nodes.size() - 1)); k++)
        {
            z = weighted_input_to_hidden_layer_connection.at(j+k*(Layers.at(1).Nodes.size() - 1));
            zz += z;
        }
        Layers.at(1).Nodes.at(j).element = zz;
    }
    //cout << "Hidden Layer Before Sigmoid" << endl;
    //cout << Layers.at(1).Nodes.size() - 1 << endl;
    //for(int j = 0; j < Layers.at(1).Nodes.size() - 1; j++)
    //{
    //cout << Layers.at(1).Nodes.at(j).element << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Hidden layer sigmoid
//calls the sigmoid function for each element in the hidden layer
void Neural_Network::hidden_layer_sigmoid()
{
    //cout << Layers.at(1).Nodes.size() << endl;
    for(int j = 0; j < Layers.at(1).Nodes.size(); j++)
    {
        sigmoid_input = 0;
        sigmoid_input = Layers.at(1).Nodes.at(j).element;
        sigmoid_output = sigmoid_function();
        Layers.at(1).Nodes.at(j).element = sigmoid_output;
    }
    ////cout << "Hidden Layer After Sigmoid" << endl;
    //cout << Layers.at(1).Nodes.size() << endl;
    Layers.at(1).Nodes.at(hidden_layer_size).element = 1;
    //for(int j = 0; j < Layers.at(1).Nodes.size(); j++)
    //{
    //cout << Layers.at(1).Nodes.at(j).element << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//input layer to hidden layer connection
//makes copies(size of output layer) of each element of the hidden layer
void Neural_Network::hidden_output_layer_connection()
{
    vector<double> cc;
    for(int j = 0; j < Layers.at(1).Nodes.size(); j++)
    {
        for(int k = 0; k < Layers.at(2).Nodes.size(); k++)
        {
            cc.push_back(Layers.at(1).Nodes.at(j).element);
        }
    }
    hidden_to_output_layer_connection = cc;
    //cout << "Unweighted hidden to output layer connection" << endl;
    //cout << hidden_to_output_layer_connection.size() << endl;
    //for(int j = 0; j <hidden_to_output_layer_connection.size(); j++)
    //{
    //cout << hidden_to_output_layer_connection.at(j) << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Weight Multiplication function
//takes the double value of node and multiplies it to each element in the weight vector
void Neural_Network::hidden_to_output_layer_weight_multiplication()
{
    for(int j = 0; j < hidden_to_output_layer_connection.size(); j++)
    {
        weighted_hidden_to_output_layer_connection.push_back(hidden_to_output_layer_connection.at(j) * hidden_to_output_layer_weights.at(j));
    }
    //cout << "Weighted hidden to hidden layer connections" << endl;
    //cout << weighted_hidden_to_output_layer_connection.size() << endl;
    //for(int j = 0; j < weighted_hidden_to_output_layer_connection.size(); j++)
    //{
    //cout << weighted_hidden_to_output_layer_connection.at(j) << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Summation of inputs
//the vector of type double will be given by the vector of type double returned from the weight multiplication fucntion
//takes the sum  of the inputs entering a node
void Neural_Network::sum_output_layer()
// node function
{
    for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    {
        double z = 0;                   //reinitialize z to be 0
        double zz = 0;                  //reinitialize zz to be 0
        for(int k = 0; k < (weighted_hidden_to_output_layer_connection.size()/Layers.at(2).Nodes.size()); k++)
        {
            z = weighted_hidden_to_output_layer_connection.at(j+k*(Layers.at(2).Nodes.size()));
            zz += z;
        }
        Layers.at(2).Nodes.at(j).element = zz;
    }
    //cout << "Output Layer Before Sigmoid" << endl;
    //cout << Layers.at(2).Nodes.size() << endl;
    //for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    //{
    //cout << Layers.at(2).Nodes.at(j).element << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Output layer sigmoid
//calls the sigmoid function for each element in the output layer
void Neural_Network::output_layer_sigmoid()
{
    //cout << Layers.at(2).Nodes.size() << endl;
    for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    {
        sigmoid_input = 0;
        sigmoid_input = Layers.at(2).Nodes.at(j).element;
        sigmoid_output = sigmoid_function();
        Layers.at(2).Nodes.at(j).element = sigmoid_output;
    }
    //cout << "Output Layer After Sigmoid" << endl;
    //cout << Layers.at(2).Nodes.size() << endl;
    //for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    //{
    //cout << Layers.at(2).Nodes.at(j).element << "\t";
    //}
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Normalization function
//Creates the unnormalized control and pushes them into a vector using the normalized outputs and their respective limits
void Neural_Network::unnormalization()
{
    //Takes a state variable multiplies it by its lower limit and then divdes by the difference between the upper and lower limit
    for (int j = 0; j < number_controls; j++)
    {
        double real_output = (Layers.at(2).Nodes.at(j).element*(control_upper_limits.at(j) - control_lower_limits.at(j))) + control_lower_limits.at(j);
        Layers.at(2).Nodes.at(j).element = real_output;
    }
}


//-----------------------------------------------------------------------------------------------------------------------------
//Sigmoid Funtion
double Neural_Network::sigmoid_function()
{
    sigmoid_output = 0;
    sigmoid_output = 1/(1 + exp(-sigmoid_input));
    return(sigmoid_output);
}


//-----------------------------------------------------------------------------------------------------------------------------
//communication to simulator
vector<double> Neural_Network::communication_to_simulator()
{
    controls_for_simulator.clear();
    for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    {
        controls_for_simulator.push_back(Layers.at(2).Nodes.at(j).element);
    }
    return controls_for_simulator;
    
    //    cout << "Controls for Simulator" << endl;
    //    cout << controls_for_simulator.size() << endl;
    //    for(int j = 0; j < controls_for_simulator.size(); j++)
    //    {
    //        cout << controls_for_simulator.at(j) << "\t";
    //    }
    //cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Activation Function
//After the ANN structure has been made this function will execute gowing through the functions needed to get the controls then erase its contents
void Neural_Network::activation_function(vector<double> state)
{
    //Begin Communitcation To Neural Network
    take_state(state);
    //End Communication
    //Begin NN Frame Work
    if(layer_size.empty())
    {
        create_layer_sizes();
        create_layers();
    }
    //End NN Frame Work
    //cout << "Begin Neural Network Calculations" << endl;
    create_input_layer();
    normalization();
    input_hidden_layer_connection();
    input_to_hidden_layer_weight_multiplication();
    sum_hidden_layer();
    hidden_layer_sigmoid();
    sigmoid_function();
    hidden_output_layer_connection();
    hidden_to_output_layer_weight_multiplication();
    sum_output_layer();
    output_layer_sigmoid();
    unnormalization();
    //cout << "End Neural Network Calculations" << endl;
}



//-----------------------------------------------------------------------------------------------------------------------------
//Reset Funtion
//Use after each time step to reset the ANN and state variables
void Neural_Network::Neural_Network_Reset()
{
    state_variables.clear();
    input_to_hidden_layer_connection.clear();
    weighted_input_to_hidden_layer_connection.clear();
    hidden_to_output_layer_connection.clear();
    weighted_hidden_to_output_layer_connection.clear();
    controls.clear();
}


//Total reset function
//Resets the entire ANN
//Use after each experimental run to reset the ANN state variables and weights
void Neural_Network::Experimental_Reset()
{
    //cout << "Reset Neural Network" << endl;
    layer_size.clear();
    hidden_layer_size = 0;
    number_controls = 0;
    Layers.at(0).Nodes.clear();
    Layers.at(1).Nodes.clear();
    Layers.at(2).Nodes.clear();
    state_variables.clear();
    state_variable_upper_limits.clear();
    state_variable_lower_limits.clear();
    control_upper_limits.clear();
    control_lower_limits.clear();
    input_to_hidden_layer_weights.clear();
    hidden_to_output_layer_weights.clear();
    input_to_hidden_layer_connection.clear();
    weighted_input_to_hidden_layer_connection.clear();
    hidden_to_output_layer_connection.clear();
    weighted_hidden_to_output_layer_connection.clear();
    controls.clear();
}
#endif /* Neural_Network_hpp */