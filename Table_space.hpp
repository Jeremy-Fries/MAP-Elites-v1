//
//  Table_space.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Table_space_hpp
#define Table_space_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>
#include "Map_space.hpp"

using namespace std;

class Table_space{
    friend class Map_space;
    
protected:
    int resolution1, resolution2;
    double dim1_min, dim2_min, dim3_min,
    dim1_max, dim2_max, dim3_max;
    int num_spacing1, num_spacing2, num_spacing3;
    double spacing1,  spacing2, spacing3;
    
// --------------------------------------------------
public:
// --------------------------------------------------
            // Min of dim1
    void set_min_dim1(double);
    double get_min_dim1();
    void display_min_dim1();
            // Min of dim2
    void set_min_dim2(double);
    double get_min_dim2();
    void display_min_dim2();
            // Min of dim3
    void set_min_dim3(double);
    double get_min_dim3();
    void display_min_dim3();
            // Max of dim1
    void set_max_dim1(double);
    double get_max_dim1();
    void display_max_dim1();
            // Max of dim2
    void set_max_dim2(double);
    double get_max_dim2();
    void display_max_dim2();
            // Max of dim3
    void set_max_dim3(double);
    double get_max_dim3();
    void display_max_dim3();
// --------------------------------------------------
            // Resolution
    void set_resolution(int,int);
    int get_resolution1();
    void display_resolution1();
    int get_resolution2();
    void display_resolution2();
// --------------------------------------------------
    void build_table();
    void place_genome();
// --------------------------------------------------
private:
    vector<Map_space> Row;
    vector< vector<Map_space> >Table;
    
    
    
    
};
#endif /* Table_space_hpp */
