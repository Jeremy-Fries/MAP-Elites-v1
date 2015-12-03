//
//  Layer.hpp
//  Controller
//
//  Created by Scott Forer on 11/19/15.
//  Copyright © 2015 Scott Forer. All rights reserved.
//

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

#endif /* Layer_hpp */
