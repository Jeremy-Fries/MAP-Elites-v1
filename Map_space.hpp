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
#include "Genotype.hpp"

using namespace std;

class Map_space{
    friend class Table_space;
    friend class Genotype;
protected:
    
    
public:
// --------------------------------------------------
            // Phenotypes
    void set_phenotypes(double, double);
    double get_phenotype1();
    void display_phenotype1();
    double get_phenotype2();
    void display_phenotype2();
    double get_phenotype3();
    void display_phenotype3();
// --------------------------------------------------
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
    void build_phenotype();
    
    
// --------------------------------------------------
private:
    double phenotype1, phenotype2, phenotype3;
    double possible_phenotype1, possible_phenotype2, possible_phenotype3;
    double LB1, UB1, LB2, UB2, LB3, UB3;
    vector<double> LB_vec;
    vector<double> UB_vec;
    vector<double> phenotype;
    vector<double> possible_phenotype;
    
};
#endif /* Map_space_hpp */
