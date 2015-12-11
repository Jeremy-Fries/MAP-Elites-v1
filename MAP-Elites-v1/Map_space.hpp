//
//  Map_space.hpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

class Map_space;

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

// --------------------------------------------------
// Display parameters of Map_space
void Map_space::display_space(){
    display_LB1();
    display_UB1();
    display_LB2();
    display_UB2();
    display_LB3();
    display_UB3();
}
// Lower Bound 1
void Map_space::set_LB1(int L1){
    LB1 = L1;
}
int Map_space::get_LB1(){
    return LB1;
}
void Map_space::display_LB1(){
    cout << endl << "LB1 is: " << LB1 << endl;
}
// Lower Bound 2
void Map_space::set_LB2(int L2){
    LB2 = L2;
}
int Map_space::get_LB2(){
    return LB2;
}
void Map_space::display_LB2(){
    cout << endl << "LB2 is: " << LB2 << endl;
}
// Lower Bound 3
void Map_space::set_LB3(int L3){
    LB3 = L3;
}
int Map_space::get_LB3(){
    return LB3;
}
void Map_space::display_LB3(){
    cout << endl << "LB3 is: " << LB3 << endl;
}
// Upper Bound 1
void Map_space::set_UB1(int U1){
    UB1 = U1;
}
int Map_space::get_UB1(){
    return UB1;
}
void Map_space::display_UB1(){
    cout << endl << "UB1 is: " << UB1 << endl;
}
// Upper Bound 2
void Map_space::set_UB2(int U2){
    UB2 = U2;
}
int Map_space::get_UB2(){
    return UB2;
}
void Map_space::display_UB2(){
    cout << endl << "UB2 is: " << UB2 << endl;
}
// Upper Bound 3
void Map_space::set_UB3(int U3){
    UB3 = U3;
}
int Map_space::get_UB3(){
    return UB3;
}
void Map_space::display_UB3(){
    cout << endl << "UB3 is: " << UB3 << endl;
}
// --------------------------------------------------
// Builds lower bound and uppper bound vector of Map_space, used to deterine where Map_space lies in Map.
void Map_space::build_map_space(){
    LB_vec.push_back(LB1);
    LB_vec.push_back(LB2);
    //LB_vec.push_back(LB3);
    
    UB_vec.push_back(UB1);
    UB_vec.push_back(UB2);
    //UB_vec.push_back(UB3);
}
// --------------------------------------------------
// If later a Map_space can hold many Individuals, best fitness rating map_space will be first element. Currently Map_space can hold only one Individual, so that will also lie in the first element. This function may not be used in the case of only one Individual.
void Map_space::set_best_fit(){
    best_fit_rating=current_individual.at(0).get_fit_rating();
}
// --------------------------------------------------
// If an Individual is placed into an already occupied Map_space, currently worse fitness rated Individual is deleted. Can be used to sort Individuals if more than one is allowed.
// Compare Individuals in bin
void Map_space::compare_new_individual(){
    if(current_individual.size()>1){
        counter++;
        // compare individual fit_ratings and delete worst
        double f1,f2;
        f1=current_individual.at(0).get_fit_rating();
        f2=current_individual.at(1).get_fit_rating();
        if (f1>f2){
            current_individual.erase(current_individual.end());
        }
        else {
            current_individual.erase(current_individual.begin());
        }
    }
    else if(current_individual.empty()){
        cout << endl << "NO individual in space: " << endl;
        display_space();
    }
    else {
        cout << endl << "individual in space, all GOOD! " << endl;  // only used for debugging.
    }
}


// LATER - can have multiple individuals in vector and sorts based on best fit_rating, possible diversity in Map_space?

// --------------------------------------------------
// Counts how many times a Map_space has been accessed to place an Individual.
// TODO - 2 seperate counters, one that counts how many times the one being placed is better, possible tuning of mutation.
// Counter
int Map_space::get_counter(){
    return counter;
}
void Map_space::display_counter(){
    cout << endl << "NUmber of times bin has been accessed: " << counter << endl;
}
// --------------------------------------------------


#endif /* Map_space_hpp */
