//
//  Layer.hpp
//  Controller
//
//  Created by Scott Forer on 11/19/15.
//  Copyright © 2015 Scott Forer. All rights reserved.
//

class Layer;

#ifndef Layer_hpp
#define Layer_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iomanip>

#include "Node.hpp"

using namespace std;

class Layer
{
    friend class Neural_Network;
    friend class Node;
    friend class Dummy_simulator;
    friend class Dummy_EA;
    
protected:
    
    
public:
    vector<Node> Nodes;
    int ID;
    void create_nodes(int number_nodes);

private:
    
    
};

void Layer::create_nodes(int layer_size)
{
    for(int i=0; i<layer_size; i++)
    {
        Node N;
        Nodes.push_back(N);
    }
    ////cout << "Number of nodes" << endl;
    ////cout << Nodes.size() << endl;
    ////cout << "\n" << endl;
}

#endif /* Layer_hpp */
