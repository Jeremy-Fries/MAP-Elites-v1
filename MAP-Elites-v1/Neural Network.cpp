//
//  Neural Network.cpp
//  Controller
//
//  Created by Scott Forer on 11/19/15.
//  Copyright © 2015 Scott Forer. All rights reserved.
//

#include "Neural Network.hpp"

//-----------------------------------------------------------------------------------------------------------------------------
//Gets needed information from simulator
void Neural_Network::communication_from_simulator(vector<double> sim_state_variable_inputs, vector<double> sim_state_variable_upper_limits, vector<double> sim_state_variable_lower_limits, int sim_hidden_layer_size, int sim_number_controls, vector<double> sim_control_upper_limits, vector<double> sim_control_lower_limits)
{
    for(int j = 0; j < sim_state_variable_inputs.size(); j++)
    {
        state_variables.push_back(sim_state_variable_inputs.at(j));
    }
    if (state_variable_upper_limits.empty())
    {
        for(int j = 0; j < state_variables.size(); j++)
        {
            state_variable_upper_limits.push_back(sim_state_variable_upper_limits.at(j));
            state_variable_lower_limits.push_back(sim_state_variable_lower_limits.at(j));
        }
    }
    ////cout << "Unnormalized State Variable Inputs" << endl;
    ////cout << state_variables.size() << endl;
    ////for(int j = 0; j < sim_state_variable_inputs.size(); j++)
    ////{
        ////cout << state_variables.at(j) << "\t";
    ////}
    ////cout << "\n" << endl;
    if (hidden_layer_size == 0)
    {
    hidden_layer_size = sim_hidden_layer_size;
    number_controls = sim_number_controls;
    }
    if (control_upper_limits.empty())
    {
        for(int j = 0; j < number_controls; j++)
        {
            control_upper_limits.push_back(sim_control_upper_limits.at(j));
            control_lower_limits.push_back(sim_control_lower_limits.at(j));
        }
    }
    ////cout << "Control Upper Limits" << endl;
    ////cout << control_upper_limits.size() << endl;
    ////for(int j = 0; j < control_upper_limits.size(); j++)
    ////{
       //// cout << control_upper_limits.at(j) << "\t";
    ////}
    ////cout << "\n" << endl;
    ////cout << "Control Lower Limits" << endl;
    ////cout << control_lower_limits.size() << endl;
    ////for(int j = 0; j < control_upper_limits.size(); j++)
    ////{
        ////cout << control_upper_limits.at(j) << "\t";
    ////}
    ////cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Gets weights from EA
void Neural_Network::communication_from_EA(vector<double> ea_input_to_hidden_layer_weights, vector<double> ea_hidden_to_output_layer_weights)
{
    if (input_to_hidden_layer_weights.empty())
    {
        for(int j = 0; j < ea_input_to_hidden_layer_weights.size(); j++)
        {
            input_to_hidden_layer_weights.push_back(ea_input_to_hidden_layer_weights.at(j));
        }
    }
    ////cout << "Input to hidden layer weights" << endl;
    ////cout << input_to_hidden_layer_weights.size() << endl;
    ////for(int j = 0; j < ea_input_to_hidden_layer_weights.size(); j++)
    ////{
        ////cout << input_to_hidden_layer_weights.at(j) << "\t";
    ////}
    ////cout << "\n" << endl;
    if (hidden_to_output_layer_weights.empty())
    {
        for(int j = 0; j < ea_hidden_to_output_layer_weights.size(); j++)
        {
            hidden_to_output_layer_weights.push_back(ea_hidden_to_output_layer_weights.at(j));
        }
    }
    ////cout << "Hidden to ouput layer weights" << endl;
    ////cout << hidden_to_output_layer_weights.size() << endl;
    ////for(int j = 0; j < ea_hidden_to_output_layer_weights.size(); j++)
    ////{
        ////cout << hidden_to_output_layer_weights.at(j) << "\t";
    ////}
    ////cout << "\n" << endl;
    
}


//-----------------------------------------------------------------------------------------------------------------------------
//intitializes hidden and output layer sizes
void Neural_Network::initialize()
{
    hidden_layer_size = 0;
    number_controls = 0;
}




//-----------------------------------------------------------------------------------------------------------------------------
//creates a vector of a layer sizes
void Neural_Network::create_layer_sizes()
{
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
    ////cout << "Number of layers" << endl;
    ////cout << Layers.size() << endl;
    ////cout << "\n" << endl;
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
    for(int j = 0; j < state_variables.size(); j++)
    {
        Layers.at(0).Nodes.at(j).element = state_variables.at(j);
    }
    ////for(int j = 0; j < Layers.at(0).Nodes.size() - 1; j++)
    ////{
        ////cout << Layers.at(0).Nodes.at(j).element << "\t";
    ////}
    ////cout << "\n" << endl;
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
    ////cout << "Normalized Input Layer" << endl;
    ////cout << Layers.at(0).Nodes.size() - 1 << endl;
    //Writes each normalized state variable to the console
    ////for(int j = 0; j < Layers.at(0).Nodes.size(); j++)
    ////{
        ////cout << Layers.at(0).Nodes.at(j).element << "\t";
    ////}
    ////cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//input layer to hidden layer connection
//makes copies(size of hidden layer) of each element of the input layer
void Neural_Network::input_hidden_layer_connection()
{
    for(int j = 0; j < Layers.at(0).Nodes.size(); j++)
    {
        for(int k = 0; k < Layers.at(1).Nodes.size() - 1; k++)
        {
            bb.push_back(Layers.at(0).Nodes.at(j).element);
        }
    }
    input_to_hidden_layer_connection = bb;
    ////cout << "Unweighted input to hidden layer connection" << endl;
    ////cout << input_to_hidden_layer_connection.size() << endl;
    //cout << hidden_to_output_layer_connection.size() << endl;
    ////for(int i = 0; i <input_to_hidden_layer_connection.size(); i++)
    ////{
        ////cout << input_to_hidden_layer_connection.at(i) << "\t";
    ////}
    ////cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Weight Multiplication function
//takes the double value of node and multiplies it to each element in the weight vector
void Neural_Network::input_to_hidden_layer_weight_multiplication()
{
    for(int i = 0; i < input_to_hidden_layer_connection.size(); i++)
    {
        weighted_input_to_hidden_layer_connection.push_back(input_to_hidden_layer_connection.at(i) * input_to_hidden_layer_weights.at(i));
    }
    ////cout << "Weighted input to hidden layer connections" << endl;
    ////cout << weighted_input_to_hidden_layer_connection.size() << endl;
    ////for(int i = 0; i < weighted_input_to_hidden_layer_connection.size(); i++)
    ////{
        ////cout << weighted_input_to_hidden_layer_connection.at(i) << "\t";
    ////}
    ////cout << "\n" << endl;
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
    ////cout << "Hidden Layer Before Sigmoid" << endl;
    ////cout << Layers.at(1).Nodes.size() - 1 << endl;
    ////for(int j = 0; j < Layers.at(1).Nodes.size() - 1; j++)
    ////{
        ////cout << Layers.at(1).Nodes.at(j).element << "\t";
    ////}
    ////cout << "\n" << endl;
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
    ////cout << Layers.at(1).Nodes.size() << endl;
    Layers.at(1).Nodes.at(hidden_layer_size).element = 1;
    ////for(int j = 0; j < Layers.at(1).Nodes.size(); j++)
    ////{
        ////cout << Layers.at(1).Nodes.at(j).element << "\t";
    ////}
    ////cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//input layer to hidden layer connection
//makes copies(size of output layer) of each element of the hidden layer
void Neural_Network::hidden_output_layer_connection()
{
    for(int j = 0; j < Layers.at(1).Nodes.size(); j++)
    {
        for(int k = 0; k < Layers.at(2).Nodes.size(); k++)
        {
            cc.push_back(Layers.at(1).Nodes.at(j).element);
        }
    }
    hidden_to_output_layer_connection = cc;
    ////cout << "Unweighted hidden to output layer connection" << endl;
    ////cout << hidden_to_output_layer_connection.size() << endl;
    ////for(int j = 0; j <hidden_to_output_layer_connection.size(); j++)
    ////{
        ////cout << hidden_to_output_layer_connection.at(j) << "\t";
    ////}
    ////cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Weight Multiplication function
//takes the double value of node and multiplies it to each element in the weight vector
void Neural_Network::hidden_to_output_layer_weight_multiplication()
{
    for(int i = 0; i < hidden_to_output_layer_connection.size(); i++)
    {
        weighted_hidden_to_output_layer_connection.push_back(hidden_to_output_layer_connection.at(i) * hidden_to_output_layer_weights.at(i));
    }
    ////cout << "Weighted hidden to hidden layer connections" << endl;
    ////cout << weighted_hidden_to_output_layer_connection.size() << endl;
    ////for(int i = 0; i < weighted_hidden_to_output_layer_connection.size(); i++)
    ////{
        ////cout << weighted_hidden_to_output_layer_connection.at(i) << "\t";
    ////}
    ////cout << "\n" << endl;
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
    ////cout << "Output Layer Before Sigmoid" << endl;
    ////cout << Layers.at(2).Nodes.size() << endl;
    ////for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    ////{
        ////cout << Layers.at(2).Nodes.at(j).element << "\t";
    ////}
    ////cout << "\n" << endl;
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
    ////cout << "Output Layer After Sigmoid" << endl;
    ////cout << Layers.at(2).Nodes.size() << endl;
    ////for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    ////{
        ////cout << Layers.at(2).Nodes.at(j).element << "\t";
    ////}
    ////cout << "\n" << endl;
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
    ////cout << "Controls" << endl;
    //cout << Layers.at(2).Nodes.size() << endl;
    //Writes each normalized state variable to the console
    //    for(int j = 0; j < number_controls; j++)
    //    {
    //        cout << Layers.at(2).Nodes.at(j).element << "\t";
    //    }
    ////for(int j = 0; j < Layers.at(2).Nodes.size(); j++)
    ////{
        ////controls.push_back(Layers.at(2).Nodes.at(j).element);
    ////}
    ////cout << controls.size() << endl;
    ////for(int j = 0; j < controls.size(); j++)
    ////{
        ////cout << controls.at(j) << endl;
    ////}
    ////cout << "\n" << endl;
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
    controls_for_simulator.empty();
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
    ////cout << "\n" << endl;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Activation Function
//After the ANN structure has been made this function will execute gowing through the functions needed to get the controls then erase its contents
void Neural_Network::activation_function(vector<double> sim_state_variable_inputs, vector<double> sim_state_variable_upper_limits, vector<double> sim_state_variable_lower_limits, int sim_hidden_layer_size, int sim_number_controls, vector<double> sim_control_upper_limits, vector<double> sim_control_lower_limits, vector<double> ea_input_to_hidden_layer_weights, vector<double> ea_hidden_to_output_layer_weights, vector<double> controls_for_simulator)
{
    //Begin Communitcation To Neural Network
    communication_from_simulator(sim_state_variable_inputs, sim_state_variable_upper_limits, sim_state_variable_lower_limits, sim_hidden_layer_size, sim_number_controls, sim_control_upper_limits, sim_control_lower_limits);
    communication_from_EA(ea_input_to_hidden_layer_weights, ea_hidden_to_output_layer_weights);
    //End Communication
    //Begin NN Frame Work
    if(layer_size.empty())
    {
    create_layer_sizes();
    create_layers();
    }
    //End NN Frame Work
    ////cout << "Begin Neural Network Calculations" << endl;
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
    //Begin Communitcation From Neural Network
    communication_to_simulator();
    //End Communitcation From Neural Network
}


//-----------------------------------------------------------------------------------------------------------------------------
//Write state vairables to text file
void Neural_Network::write_state_variables_limits_to_text(bool display)
{
    ofstream File1;
    File1.open("State Variable Limits.txt");
    if(display)
        File1 << "State Variable Upper Limits \n" << endl;
    {
        for (int j = 0; j < state_variable_upper_limits.size(); j++)
            File1 << setprecision(4) << state_variable_upper_limits.at(j) << "\t";
    }
    File1 << "\n" << endl;
    File1 << "State Variable Lower Limits \n" << endl;
    {
        for (int j = 0; j < state_variable_lower_limits.size(); j++)
            File1 << setprecision(4) << state_variable_lower_limits.at(j) << "\t";
    }
    File1.close();
}


//-----------------------------------------------------------------------------------------------------------------------------
//Write weigths to text file
void Neural_Network::write_weigths_to_text(bool display)
{
    ofstream File2;
    File2.open("Weights.txt");
    if(display)
        File2 << "Input To Hidden Layer Weigths \n" << endl;
    {
        for (int j = 0; j < input_to_hidden_layer_weights.size(); j++)
            File2 << setprecision(4) << input_to_hidden_layer_weights.at(j) << "\t";
    }
    File2 << "\n" << endl;
    File2 << "Hidden To Output Layer Weigths \n" << endl;
    {
        for (int j = 0; j < hidden_to_output_layer_weights.size(); j++)
            File2 << setprecision(4) << hidden_to_output_layer_weights.at(j) << "\t";
    }
    File2.close();
}


//-----------------------------------------------------------------------------------------------------------------------------
//Write control limits to text file
void Neural_Network::write_control_limits_to_text(bool display)
{
    ofstream File3;
    File3.open("Control Limits.txt");
    if(display)
        File3 << "Control Upper Limits \n" << endl;
    {
        for (int j = 0; j < control_upper_limits.size(); j++)
            File3 << setprecision(4) << control_upper_limits.at(j) << "\t";
    }
    File3 << "\n" << endl;
    File3 << "Control Lower Limits \n" << endl;
    {
        for (int j = 0; j < control_lower_limits.size(); j++)
            File3 << setprecision(4) << control_lower_limits.at(j) << "\t";
    }
    File3.close();
}


//-----------------------------------------------------------------------------------------------------------------------------
//Write Layer sizes to text file
//Sizes include the baising term
void Neural_Network::write_topography_to_text(bool display)
{
    ofstream File4;
    File4.open("Topography.txt");
    if(display)
        File4 << "Layer Sizes \n" << endl;
    {
        for (int j = 0; j < Layers.size(); j++)
            File4 << Layers.at(j).Nodes.size() << "\t";
    }
    File4.close();
}


//-----------------------------------------------------------------------------------------------------------------------------
//Calls each write to text file function
void Neural_Network::write_to_text_file()
{
    write_state_variables_limits_to_text(true);
    write_weigths_to_text(true);
    write_control_limits_to_text(true);
    write_topography_to_text(true);
}


//-----------------------------------------------------------------------------------------------------------------------------
//Reset Funtion
void Neural_Network::reset_neural_network()
{
    //cout << "Reset Neural Network" << endl;
    //cout << "Input Layer Size" << endl;
    Layers.at(0).Nodes.clear();
    //cout << Layers.at(0).Nodes.size() << endl;
    //cout << "Hidden Layer Size" << endl;
    Layers.at(1).Nodes.clear();
    //cout << Layers.at(1).Nodes.size() << endl;
    //cout << "Output Layer Size" << endl;
    Layers.at(2).Nodes.clear();
    //cout << Layers.at(1).Nodes.size() << endl;
    //cout << "State Variable Size" << endl;
    state_variables.clear();
    //cout << state_variables.size() << endl;
    //cout << "BB Place Holder Size" << endl;
    bb.clear();
    //cout << bb.size() << endl;
    //cout << "Input To Hidden Layer Connection Size" << endl;
    input_to_hidden_layer_connection.clear();
    //cout << input_to_hidden_layer_connection.size() << endl;
    //cout << "Weighted Input To Hidden Layer Connection Size" << endl;
    weighted_input_to_hidden_layer_connection.clear();
    //cout << weighted_input_to_hidden_layer_connection.size() << endl;
    //cout << "CC Place Holder Size" << endl;
    cc.clear();
    //cout << cc.size() << endl;
    //cout << "Hidden To Output Layer Connection Size" << endl;
    hidden_to_output_layer_connection.clear();
    //cout << hidden_to_output_layer_connection.size() << endl;
    //cout << "Weighted Hidden To Output Layer Connection Size" << endl;
    weighted_hidden_to_output_layer_connection.clear();
    //cout << weighted_hidden_to_output_layer_connection.size() << endl;
    controls.clear();
    //cout << "Control Size" << endl;
    //cout << controls.size() << endl;
}
        

void Neural_Network::total_neural_network_reset()
{
    //cout << "Reset Neural Network" << endl;
    layer_size.clear();
    hidden_layer_size = 0;
    number_controls = 0;
    //cout << layer_size.size() << endl;
    //cout << "Input Layer Size" << endl;
    Layers.at(0).Nodes.clear();
    //cout << Layers.at(0).Nodes.size() << endl;
    //cout << "Hidden Layer Size" << endl;
    Layers.at(1).Nodes.clear();
    //cout << Layers.at(1).Nodes.size() << endl;
    //cout << "Output Layer Size" << endl;
    Layers.at(2).Nodes.clear();
    //cout << Layers.at(1).Nodes.size() << endl;
    //cout << "State Variable Size" << endl;
    state_variables.clear();
    //cout << state_variables.size() << endl;
    //cout << "State Variable Upper Limits Size" << endl;
    state_variable_upper_limits.clear();
    //cout << state_variable_upper_limits.size() << endl;
    //cout << "State Variable Lower Limits Size" << endl;
    state_variable_lower_limits.clear();
    //cout << state_variable_lower_limits.size() << endl;
    //cout << "Control Upper Limits Size" << endl;
    control_upper_limits.clear();
    //cout << control_upper_limits.size() << endl;
    //cout << "Control Lower Limits Size" << endl;
    control_lower_limits.clear();
    //cout << control_lower_limits.size() << endl;
    //cout << "Input To Hidden Layer Weights Size" << endl;
    input_to_hidden_layer_weights.clear();
    //cout << input_to_hidden_layer_weights.size() << endl;
    //cout << "Hidden To Output Layer Weights Size" << endl;
    hidden_to_output_layer_weights.clear();
    //cout << hidden_to_output_layer_weights.size() << endl;
    //cout << "BB Place Holder Size" << endl;
    bb.clear();
    //cout << bb.size() << endl;
    //cout << "Input To Hidden Layer Connection Size" << endl;
    input_to_hidden_layer_connection.clear();
    //cout << input_to_hidden_layer_connection.size() << endl;
    //cout << "Weighted Input To Hidden Layer Connection Size" << endl;
    weighted_input_to_hidden_layer_connection.clear();
    //cout << weighted_input_to_hidden_layer_connection.size() << endl;
    //cout << "CC Place Holder Size" << endl;
    cc.clear();
    //cout << cc.size() << endl;
    //cout << "Hidden To Output Layer Connection Size" << endl;
    hidden_to_output_layer_connection.clear();
    //cout << hidden_to_output_layer_connection.size() << endl;
    //cout << "Weighted Hidden To Output Layer Connection Size" << endl;
    weighted_hidden_to_output_layer_connection.clear();
    //cout << weighted_hidden_to_output_layer_connection.size() << endl;
    controls.clear();
    //cout << "Control Size" << endl;
    //cout << controls.size() << endl;
}
