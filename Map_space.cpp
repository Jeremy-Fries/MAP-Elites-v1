//
//  Map_space.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Map_space.hpp"

// --------------------------------------------------
            // Phenotypes
void Map_space::set_phenotypes(double p1, double p2){
    if (phenotype.size()==0){
        phenotype1=p1;
        phenotype2=p2;
        //phenotype3=p3;
        phenotype.push_back(phenotype1);
        phenotype.push_back(phenotype2);
        //phenotype.push_back(phenotype3);
    }
    else {
        possible_phenotype1=p1;
        possible_phenotype2=p2;
        //possible_phenotype3=p3;
        possible_phenotype.push_back(possible_phenotype1);
        possible_phenotype.push_back(possible_phenotype2);
    }
}
double Map_space::get_phenotype1(){
    return phenotype1;
}
void Map_space::display_phenotype1(){
    cout << endl << "phenotype1 is: " << phenotype1 << endl;
}
double Map_space::get_phenotype2(){
    return phenotype2;
}
void Map_space::display_phenotype2(){
    cout << endl << "phenotype2 is: " << phenotype2 << endl;
}
double Map_space::get_phenotype3(){
    return phenotype3;
}
void Map_space::display_phenotype3(){
    cout << endl << "phenotype3 is: " << phenotype3 << endl;
}
// --------------------------------------------------
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
void Map_space::build_map_space(){
    LB_vec.push_back(LB1);
    LB_vec.push_back(LB2);
    //LB_vec.push_back(LB3);
    
    UB_vec.push_back(UB1);
    UB_vec.push_back(UB2);
    //UB_vec.push_back(UB3);
}
// --------------------------------------------------






// --------------------------------------------------



















