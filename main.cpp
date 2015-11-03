//
//  main.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include "Map_space.hpp"
#include "Table_space.hpp"
#include "Genotype.hpp"

using namespace std;

class Table_space;
class Map_space;
class Genotype;


int main() {
// --------------------------------------------------
            // Set Random Numbers
    //srand(time(NULL));
// --------------------------------------------------
            // Set Objects
    Table_space table_space1;
    Table_space* pT = &table_space1;
    Map_space map_space1;
    Map_space* pM =  &map_space1;
    Genotype genotype1;
    Genotype* pG = &genotype1;
    
    pT->set_min_dim1(0);
    pT->set_max_dim1(10);
    pT->set_min_dim2(0);
    pT->set_max_dim2(10);
    pT->set_resolution(4,4);    // ->(dim1,dim2)
  
    pG->set_genotype_size1(18);     // 
    pG->set_genotype_size2(8);
    pG->set_mutation_magnitude1(0.1);
    pG->set_mutation_magnitude2(0.1);
    // --------------------------------------------------
    pT->build_table();
    
    // LOOP- fill table with new genotypes for #
    // LOOP- mutate genotypes in table for #
    
    
    
    

    return 0;
}
