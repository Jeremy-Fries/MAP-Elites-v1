//
//  Genotype.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/26/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Genotype.hpp"

// --------------------------------------------------
// Random Number between 0 and 1
double Genotype::rand01(){
    double r = ((double)rand() / RAND_MAX);
    return r;
}
// --------------------------------------------------
            // Genotype Size1
void Genotype::set_genotype_size1(int s){    // sized for neural network
    genotype_size1=s;
}
int Genotype::get_genotype_size1(){
    return genotype_size1;
}
void Genotype::display_genotype_size1(){
cout << endl << "Genotpye Size 1 is: " << genotype_size1 << endl;
}
// --------------------------------------------------
            // Genotype Size2
void Genotype::set_genotype_size2(int s){    // sized for neural network
    genotype_size2=s;
}
int Genotype::get_genotype_size2(){
    return genotype_size2;
}
void Genotype::display_genotype_size2(){
    cout << endl << "Genotpye Size 2 is: " << genotype_size2 << endl;
}
// --------------------------------------------------
            // Fit Rating
void Genotype::set_fit_rating(double r){
    fit_rating=r;
}
double Genotype::get_fit_rating(){
    return fit_rating;
}
void Genotype::display_fit_rating(){
cout << endl << "Fit Rating is: " << fit_rating << endl;
}
// --------------------------------------------------
            // Build Genotypes
void Genotype::build_genotypes(){
    for (int s = 0; s < genotype_size1; s++)
    {
        genotype_vec1.push_back(rand01());	// random 0 - 1
    }
    for (int s = 0; s < genotype_size2; s++)
    {
        genotype_vec2.push_back(rand01());	// random 0 - 1
    }
}
// --------------------------------------------------
            // Get Genotype1
vector<double>& Genotype::get_genotype1() {
    return genotype_vec1;
}
// --------------------------------------------------
            // Display Genotype1
vector<double>& Genotype::display_genotype1() {
    //cout << endl << "Genotype is: " << endl;
    std::copy(genotype_vec1.begin(), genotype_vec1.end(), std::ostream_iterator<double>(std::cout, " "));
    return genotype_vec1;
}
// --------------------------------------------------
            // Get Genotype2
vector<double>& Genotype::get_genotype2() {
    return genotype_vec2;
}
// --------------------------------------------------
            // Display Genotype2
vector<double>& Genotype::display_genotype2() {
    //cout << endl << "Genotype is: " << endl;
    std::copy(genotype_vec2.begin(), genotype_vec2.end(), std::ostream_iterator<double>(std::cout, " "));
    return genotype_vec2;
}
// --------------------------------------------------
            // Mutation Magnitude
void Genotype::set_mutation_magnitude1(double m1){
    mutation_magnitude1= m1;
}
double Genotype::get_mutation_magnitude1(){
    return mutation_magnitude1;
}
void Genotype::set_mutation_magnitude2(double m2){
    mutation_magnitude2= m2;
}
double Genotype::get_mutation_magnitude2(){
    return mutation_magnitude2;
}
// --------------------------------------------------
            // Mutate 1
// randomly choose an element from the solution set and add random + or - number.
void Genotype::mutate1(){
    int gs1 = genotype_size1;
    int dex1 = rand() % gs1;
    double range = mutation_magnitude1;
    double r1 = ((double)rand() / RAND_MAX) * range;
    double r2 = ((double)rand() / RAND_MAX) * range;
    genotype_vec1.at(dex1) += r1 - r2;
}
// --------------------------------------------------
            // Mutate 2
// randomly choose an element from the solution set and add random + or - number.
void Genotype::mutate2(){
    int gs2 = genotype_size2;
    int dex2 = rand() % gs2;
    double range = mutation_magnitude2;
    double r1 = ((double)rand() / RAND_MAX) * range;
    double r2 = ((double)rand() / RAND_MAX) * range;
    genotype_vec2.at(dex2) += r1 - r2;
}
// --------------------------------------------------












