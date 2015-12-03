//
//  Layer.cpp
//  Controller
//
//  Created by Scott Forer on 11/19/15.
//  Copyright © 2015 Scott Forer. All rights reserved.
//

#include "Layer.hpp"

//-----------------------------------------------------------------------------------------------------------------------------
//Node generator
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