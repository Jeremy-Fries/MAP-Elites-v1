//
//  Map_Elites.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Map_Elites_hpp
#define Map_Elites_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>
#include "Map_space.hpp"

using namespace std;

class Map_Elites{
    friend class Map_space;
    
protected:
    int resolution1, resolution2;
    double dim1_min, dim2_min, dim3_min,
    dim1_max, dim2_max, dim3_max;
    int num_spacing1, num_spacing2, num_spacing3;
    double spacing1,  spacing2, spacing3;
    Individual I;
    int fill_generation, mutate_generation;
    double out_scope1, out_scope2;
    
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
        // Fill Generation
    void set_fill_generation(int);
    int get_fill_generation();
    void display_fill_generation();
// --------------------------------------------------
            // Mutate Generation
    void set_mutate_generation(int);
    int get_mutate_generation();
    void display_mutate_generation();
    // --------------------------------------------------
                // Map Parameters
    void set_map_params(double dim1_min,double dim1_max,double dim2_min,double dim2_max,int resolution1,int resolution2, int fill_generation, int mutate_generation);
    void display_Map_params();
    void set_out_scope_magnitude();
// --------------------------------------------------
            // Makes Map
    void initialize_map();
    void place_individual_in_map(Individual Passed_I);
    void individual_from_map(double p1, double p2);
    vector<double>& get_temp_individual1();
    vector<double>& get_temp_individual2();
// --------------------------------------------------
    void fill_Map();
    
// --------------------------------------------------
private:
    vector<Map_space> Row;
    vector< vector<Map_space> >Map;
    
    vector<double> temp_individual1, temp_individual2;
    
    
    
};
#endif /* Map_Elites_hpp */
