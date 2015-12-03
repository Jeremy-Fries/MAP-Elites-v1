//
//  Map_space.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Map_space_hpp
#define Map_space_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>
#include "Individual.hpp"

using namespace std;

class Map_space{
    friend class Map_Elites;
    friend class Individual;
protected:
    
    
public:
// --------------------------------------------------
    void display_space();
            // Lower Bound 1
    void set_LB1(int);
    int get_LB1();
    void display_LB1();
            // Lower Bound 2
    void set_LB2(int);
    int get_LB2();
    void display_LB2();
            // Lower Bound 3
    void set_LB3(int);
    int get_LB3();
    void display_LB3();
            // Upper Bound 1
    void set_UB1(int);
    int get_UB1();
    void display_UB1();
                // Upper Bound 2
    void set_UB2(int);
    int get_UB2();
    void display_UB2();
            // Upper Bound 3
    void set_UB3(int);
    int get_UB3();
    void display_UB3();
// --------------------------------------------------
    void build_map_space();
// --------------------------------------------------
    void set_best_fit();
    void compare_new_individual();
    int get_counter();
    void display_counter();
// --------------------------------------------------
private:
    int counter=0;
    double LB1, UB1, LB2, UB2, LB3, UB3;
    double best_fit_rating;
    vector<double> LB_vec;
    vector<double> UB_vec;
    vector<Individual> current_individual;
};
#endif /* Map_space_hpp */
