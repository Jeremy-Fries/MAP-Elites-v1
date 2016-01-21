//
//  Individual.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/26/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class Individual;

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
    friend class Map_Elites;
    friend class Wrapper;
    // --------------------------------------------------
protected:
    vector<double> genome1, genome2;
    vector <int> parents_id;
    vector <double> parents_fitness;
    int mutate_counter_individual=0;
    // --------------------------------------------------
public:
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
    // Individual
    void build_individual();
    // Return individual1
    vector <double>& get_individual1();
    // Display individual1
    vector <double>& display_individual1();
    // Return individual2
    vector <double>& get_individual2();
    // Display individual2
    vector <double>& display_individual2();
    
    // build individual from another
    void build_individual_1_from_another(vector <double>);
    void build_individual_2_from_another(vector <double>);
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
    void mutate1();
    void mutate2();
    // --------------------------------------------------
    // Make Parents id vector
    void set_parent_id_vector(vector <int> temp_parents_id);             // Make vector <double> temp_parents_id in Map_Elites
    vector <int>& get_parent_id_vector();
    void grow_parent_id_vector(int);
    // Make Parents fitness vector
    void set_parent_fitness_vector(vector <double> temp_parents_fitness);   // Make vector <double> temp_parents_fitness in Map_Elites
    vector <double>& get_parent_fitness_vector();
    void grow_parent_fitness_vector(double);
    // --------------------------------------------------
private:
    double fit_rating;
    double phenotype1, phenotype2, phenotype3;
    int individual_size1, individual_size2;
    double mutation_magnitude1, mutation_magnitude2;
    int mutation_amount1, mutation_amount2;
    vector<double> phenotype;
    int home_id;
    
    // vector <double> movement;        // ?????
};
// ------------------------------------------------------------------------------------------------ ^^ Declarations
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ------------------------------------------------------------------------------------------------ vv Definitions

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
// Fit Rating
// Gives Individual a numerical rank based on fitness function from results of simulation.
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
// Individual Size1
// Size is determined by how many weights the neural network layers need
void Individual::set_individual_size1(int s){    // size of neural network "Input to Hidden" Layer
    individual_size1=s;
}
int Individual::get_individual_size1(){
    return individual_size1;
}
void Individual::display_individual_size1(){
    cout << endl << "Individual Size 1 is: " << individual_size1 << endl;
}
// Individual Size2
void Individual::set_individual_size2(int s){    // size of neural network "Hidden to Output" Layer
    individual_size2=s;
}
int Individual::get_individual_size2(){
    return individual_size2;
}
void Individual::display_individual_size2(){
    cout << endl << "Individual Size 2 is: " << individual_size2 << endl;
}
// --------------------------------------------------
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
    cout << endl << "------------------------------- Individual Parameters" << endl;
    display_individual_size1();
    display_individual_size2();
    display_mutation_magnitude1();
    display_mutation_magnitude2();
    display_mutation_amount1();
    display_mutation_amount2();
    cout << endl << "-------------------------------" << endl;
}
// --------------------------------------------------
// Build Individuals
// Builds 2 vector of doubles for weights of the NN layers.
void Individual::build_individual(){
    for (int s = 0; s < individual_size1; s++)
    {
        genome1.push_back(rand01());	// random 0 - 1
    }
    for (int s = 0; s < individual_size2; s++)
    {
        genome2.push_back(rand01());	// random 0 - 1
    }
    home_id = -1;
}
// --------------------------------------------------
// Build individuals from another
void Individual::build_individual_1_from_another(vector <double> temp_individual1){
    genome1=temp_individual1;
}
void Individual::build_individual_2_from_another(vector <double> temp_individual2){
    genome2=temp_individual2;
}
// --------------------------------------------------
// Get Individual1
// Get and display functions for the weights of the layers
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
void Individual::set_mutation_amount1(int m1){
    mutation_amount1= m1;
}
double Individual::get_mutation_amount1(){
    return mutation_amount1;
}
void Individual::display_mutation_amount1(){
    cout << endl << "Mutation amount 1 is: " << mutation_amount1 << endl;
}
void Individual::set_mutation_amount2(int m2){
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
    unsigned int gs1 = genome1.size();
    double range = mutation_magnitude1;
    int p1 = mutation_amount1;
    for (int a=0; a<p1; a++){
        int dex1 = rand() % gs1;
        double r1 = ((double)rand() / RAND_MAX) * range;
        double r2 = ((double)rand() / RAND_MAX) * range;
        genome1.at(dex1) += r1;
        genome1.at(dex1) -= r2;
    }
}
// --------------------------------------------------
// Mutate 2
// randomly choose an element from the solution set and add random + or - number.
void Individual::mutate2(){
    unsigned int gs2 = genome2.size();
    double range = mutation_magnitude2;
    int p2 = mutation_amount2;
    for (int b=0; b<p2; b++){
        int dex2 = rand() % gs2;
        double r1 = ((double)rand() / RAND_MAX) * range;
        double r2 = ((double)rand() / RAND_MAX) * range;
        genome1.at(dex2) += r1;
        genome1.at(dex2) -= r2;
    }
}
// --------------------------------------------------
// Parents id vector
void Individual::set_parent_id_vector(vector <int> temp_parents_id){
    parents_id=temp_parents_id;
}
vector <int>& Individual::get_parent_id_vector(){
    return parents_id;
}
void Individual::grow_parent_id_vector(int i){
    parents_id.push_back(i);
}
// Parents fitness vector
void Individual::set_parent_fitness_vector(vector <double> temp_parents_fitness){
    parents_fitness=temp_parents_fitness;
}
vector <double>& Individual::get_parent_fitness_vector(){
    return parents_fitness;
}
void Individual::grow_parent_fitness_vector(double f){
    parents_fitness.push_back(f);
}
// --------------------------------------------------



#endif /* Individual_hpp */
