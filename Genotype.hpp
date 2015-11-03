//
//  Genotype.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/26/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Genotype_hpp
#define Genotype_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>

using namespace std;

class Genotype{
    friend class Map_space;
protected:
    
    
    
public:
// --------------------------------------------------
    double rand01(void);
// --------------------------------------------------
            // Genotype Size1
    void set_genotype_size1(int);
    int get_genotype_size1();
    void display_genotype_size1();
// --------------------------------------------------
    // Genotype Size2
    void set_genotype_size2(int);
    int get_genotype_size2();
    void display_genotype_size2();
    // --------------------------------------------------
            // Fit Rating
    void set_fit_rating(double);
    double get_fit_rating();
    void display_fit_rating();
// --------------------------------------------------
            // Build Genotype1
    //void build_genotype1();
            // Return Genotype1
    vector <double>& get_genotype1();
            // Display Genotype1
    vector <double>& display_genotype1();
// --------------------------------------------------
    // Build Genotype2
    //void build_genotype2();
    // Return Genotype2
    vector <double>& get_genotype2();
    // Display Genotype2
    vector <double>& display_genotype2();
    // --------------------------------------------------

    void build_genotypes();
// --------------------------------------------------
    void set_mutation_magnitude1(double);
    void set_mutation_magnitude2(double);
    double get_mutation_magnitude1();
    double get_mutation_magnitude2();
    void mutate1();
    void mutate2();
// --------------------------------------------------
        // ------TODO------
    void crossover();
    
// --------------------------------------------------
private:
    int genotype_size1, genotype_size2;
    double fit_rating;
    double mutation_magnitude1, mutation_magnitude2;
    vector<double> genotype_vec1, genotype_vec2;
    
    // vector <double> movement;
    // vector <double> parents;
    
    
    

    
    
    
    
    
    
};
#endif /* Genotype_hpp */
