//
//  Individual.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/26/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Individual.hpp"
// --------------------------------------------------
// Once ran through simulation, the Individual is given its phenotypes, phenotypes determine where the Individual will be placed in the Map, which Map_space its phenotypes lie in.
            // Phenotypes
void Individual::set_phenotypes(double p1, double p2){   // from simulation
        phenotype1=p1;
        phenotype2=p2;
        //phenotype3=p3;
        phenotype.push_back(phenotype1);
        phenotype.push_back(phenotype2);
        //phenotype.push_back(phenotype3);
}
double Individual::get_phenotype1(){
    return phenotype1;
}
void Individual::display_phenotype1(){
    cout << endl << "phenotype1 is: " << phenotype1 << endl;
}
double Individual::get_phenotype2(){
    return phenotype2;
}
void Individual::display_phenotype2(){
    cout << endl << "phenotype2 is: " << phenotype2 << endl;
}
double Individual::get_phenotype3(){
    return phenotype3;
}
void Individual::display_phenotype3(){
    cout << endl << "phenotype3 is: " << phenotype3 << endl;
}
// --------------------------------------------------
// Gives Individual a numerical rank based on fitness function from results of simulation.
            // Fit Rating
void Individual::set_fit_rating(double r){
    fit_rating=r;
}
double Individual::get_fit_rating(){
    return fit_rating;
}
void Individual::display_fit_rating(){
    cout << endl << "Fit Rating is: " << fit_rating << endl;
}
// --------------------------------------------------
            // Random Number between 0 and 1
double Individual::rand01(){
    double r = ((double)rand() / RAND_MAX);
    return r;
}
// --------------------------------------------------
// Size is determined by how many weights the neural network layers need
            // Individual Size1
void Individual::set_individual_size1(int s){    // sized for neural network
    individual_size1=s;
}
int Individual::get_individual_size1(){
    return individual_size1;
}
void Individual::display_individual_size1(){
cout << endl << "Individual Size 1 is: " << individual_size1 << endl;
}
            // Individual Size2
void Individual::set_individual_size2(int s){    // sized for neural network
    individual_size2=s;
}
int Individual::get_individual_size2(){
    return individual_size2;
}
void Individual::display_individual_size2(){
    cout << endl << "Individual Size 2 is: " << individual_size2 << endl;
}
// --------------------------------------------------
// Itialization function used outside of class.
            // Set Individual Parameters
void Individual::set_individual_params(int g1, int g2, double m1 , double m2, int p1, int p2){
    set_individual_size1(g1);
    set_individual_size2(g2);
    set_mutation_magnitude1(m1);
    set_mutation_magnitude2(m2);
    set_mutation_amount1(p1);
    set_mutation_amount2(p2);
}
            // Display Individual Parameters
void Individual::display_individual_params(){
display_individual_size1();
display_individual_size2();
}
// --------------------------------------------------
// Builds 2 vector of doubles for weights of the NN layers.
            // Build Individuals
void Individual::build_individuals(){
    for (int s = 0; s < individual_size1; s++)
    {
        genome1.push_back(rand01());	// random 0 - 1
    }
    for (int s = 0; s < individual_size2; s++)
    {
        genome2.push_back(rand01());	// random 0 - 1
    }
}
// --------------------------------------------------
// Get and display functions for the weights of the layers
            // Get Individual1
vector<double>& Individual::get_individual1() {
    return genome1;
}
            // Display Individual1
vector<double>& Individual::display_individual1() {
    //cout << endl << "Individual is: " << endl;
    std::copy(genome1.begin(), genome1.end(), std::ostream_iterator<double>(std::cout, " "));
    return genome1;
}
            // Get Individual2
vector<double>& Individual::get_individual2() {
    return genome2;
}
            // Display Individual2
vector<double>& Individual::display_individual2() {
    //cout << endl << "Individual is: " << endl;
    std::copy(genome2.begin(), genome2.end(), std::ostream_iterator<double>(std::cout, " "));
    return genome2;
}
// --------------------------------------------------
            // Mutation Magnitude
// mutates number by preset magnitude, ex. 0.1, 0.01, 0.001
void Individual::set_mutation_magnitude1(double m1){
    mutation_magnitude1= m1;
}
double Individual::get_mutation_magnitude1(){
    return mutation_magnitude1;
}
void Individual::display_mutation_magnitude1(){
    cout << endl << "Mutation magnitude 1 is: " << mutation_magnitude1 << endl;
}
void Individual::set_mutation_magnitude2(double m2){
    mutation_magnitude2= m2;
}
double Individual::get_mutation_magnitude2(){
    return mutation_magnitude2;
}
void Individual::display_mutation_magnitude2(){
    cout << endl << "Mutation magnitude 2 is: " << mutation_magnitude2 << endl;
}
// --------------------------------------------------
            // Mutation amount
// amount of possible elements in Individual that can be mutated
void Individual::set_mutation_amount1(int m1){     // 0-100%, input 15 for 15%
    mutation_amount1= m1;
}
double Individual::get_mutation_amount1(){
    return mutation_amount1;
}
void Individual::display_mutation_amount1(){
    cout << endl << "Mutation amount 1 is: " << mutation_amount1 << endl;
}
void Individual::set_mutation_amount2(int m2){     // 0-100%, input 15 for 15%
    mutation_amount2= m2;
}
double Individual::get_mutation_amount2(){
    return mutation_amount2;
}
void Individual::display_mutation_amount2(){
    cout << endl << "Mutation amount 2 is: " << mutation_amount2 << endl;
}
// --------------------------------------------------
            // Mutate 1
// randomly choose an element from the solution set and add random + or - number.
void Individual::mutate1(){
    int gs1 = individual_size1;
    double range = mutation_magnitude1;
    int p1 = mutation_amount1;
    for (int a=0; a<(gs1%p1); a++){
        int dex1 = rand() % gs1;
        double r1 = ((double)rand() / RAND_MAX) * range;
        double r2 = ((double)rand() / RAND_MAX) * range;
        genome1.at(dex1) += r1 - r2;
    }
}
// --------------------------------------------------
            // Mutate 2
// randomly choose an element from the solution set and add random + or - number.
void Individual::mutate2(){
    int gs2 = individual_size2;
    double range = mutation_magnitude2;
    int p2 = mutation_amount2;
    for (int b=0; b<(gs2%p2); b++){
        int dex2 = rand() % gs2;
        double r1 = ((double)rand() / RAND_MAX) * range;
        double r2 = ((double)rand() / RAND_MAX) * range;
        genome2.at(dex2) += r1 - r2;
    }
}
// --------------------------------------------------












