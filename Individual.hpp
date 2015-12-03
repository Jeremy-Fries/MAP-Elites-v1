//
//  Individual.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/26/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#ifndef Individual_hpp
#define Individual_hpp

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ostream>

using namespace std;

class Individual{
    friend class Map_space;
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
            // Fit Rating
    void set_fit_rating(double);
    double get_fit_rating();
    void display_fit_rating();
// --------------------------------------------------
            // Random # 0-1
    double rand01(void);
// --------------------------------------------------
            // individual Size1
    void set_individual_size1(int);
    int get_individual_size1();
    void display_individual_size1();
// --------------------------------------------------
            // individual Size2
    void set_individual_size2(int);
    int get_individual_size2();
    void display_individual_size2();
// --------------------------------------------------
            // Set individual Parameters
    void set_individual_params(int individual_size1,int individual_size2,double mutation_magnitude1,double mutation_magnitude2,int mutation_amount1,int mutation_amount2);
    void display_individual_params();
// --------------------------------------------------
            // individual
    void build_individuals();
            // Return individual1
    vector <double>& get_individual1();
            // Display individual1
    vector <double>& display_individual1();
            // Return individual2
    vector <double>& get_individual2();
            // Display individual2
    vector <double>& display_individual2();
// --------------------------------------------------
            // Mutate
    void set_mutation_magnitude1(double);
    void set_mutation_magnitude2(double);
    double get_mutation_magnitude1();
    double get_mutation_magnitude2();
    void display_mutation_magnitude1();
    void display_mutation_magnitude2();
    void set_mutation_amount1(int);
    void set_mutation_amount2(int);
    double get_mutation_amount1();
    double get_mutation_amount2();
    void display_mutation_amount1();
    void display_mutation_amount2();
    // TODO - display
    void mutate1();
    void mutate2();
// --------------------------------------------------
        // ------TODO------
    void crossover();
    
// --------------------------------------------------
private:
    double fit_rating;
    double phenotype1, phenotype2, phenotype3;
    int individual_size1, individual_size2;
    double mutation_magnitude1, mutation_magnitude2;
    int mutation_amount1, mutation_amount2;
    vector<double> genome1, genome2;        // TODO genome
    vector<double> phenotype;
    
    // vector <double> movement;
    // vector <double> parents;
    
};
#endif /* Individual_hpp */
