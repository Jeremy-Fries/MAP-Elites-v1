//
//  Map_Elites.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Map_Elites.hpp"

// --------------------------------------------------
// Dimensions of Map
            // Min of dim1
void Map_Elites::set_min_dim1(double min1){
    dim1_min = min1;
}
double Map_Elites::get_min_dim1(){
    return dim1_min;
}
void Map_Elites::display_min_dim1(){
cout << endl << "Min of dim1 is: " << dim1_min << endl;
}
            // Min of dim2
void Map_Elites::set_min_dim2(double min2){
    dim2_min = min2;
}
double Map_Elites::get_min_dim2(){
    return dim2_min;
}
void Map_Elites::display_min_dim2(){
    cout << endl << "Min of dim2 is: " << dim2_min << endl;
}
            // Min of dim3
void Map_Elites::set_min_dim3(double min3){
    dim3_min = min3;
}
double Map_Elites::get_min_dim3(){
    return dim3_min;
}
void Map_Elites::display_min_dim3(){
    cout << endl << "Min of dim3 is: " << dim3_min << endl;
}
            // Max of dim1
void Map_Elites::set_max_dim1(double max1){
    dim1_max = max1;
}
double Map_Elites::get_max_dim1(){
    return dim1_max;
}
void Map_Elites::display_max_dim1(){
    cout << endl << "Max of dim1 is: " << dim1_max << endl;
}
            // Max of dim2
void Map_Elites::set_max_dim2(double max2){
    dim2_max = max2;
}
double Map_Elites::get_max_dim2(){
    return dim2_max;
}
void Map_Elites::display_max_dim2(){
    cout << endl << "Max of dim2 is: " << dim2_max << endl;
}
            // Max of dim3
void Map_Elites::set_max_dim3(double max3){
    dim3_max = max3;
}
double Map_Elites::get_max_dim3(){
    return dim3_max;
}
void Map_Elites::display_max_dim3(){
    cout << endl << "Max of dim3 is: " << dim3_max << endl;
}
// --------------------------------------------------
// Sets resolution of Map, will determine size of Map_space and how many.
            // Resolution
void Map_Elites::set_resolution(int r1, int r2) {
    resolution1=r1;
    resolution2=r2;
    num_spacing1=r1;
    num_spacing2=r2;
    //num_spacing3=r3;
    spacing1=(dim1_max-dim1_min)/resolution1;
    spacing2=(dim2_max-dim2_min)/resolution2;
    // spacing3=(dim3_max-dim3_min)/resolution3;
}
int Map_Elites::get_resolution1(){
    return resolution1;
}
void Map_Elites::display_resolution1(){
    cout << endl << "Resolution 1 is: " << resolution1 << endl;
}
int Map_Elites::get_resolution2(){
    return resolution2;
}
void Map_Elites::display_resolution2(){
    cout << endl << "Resolution 2 is: " << resolution2 << endl;
}
// --------------------------------------------------
// Fill Generation, fills Map with individuals for desired amount.
void Map_Elites::set_fill_generation(int f){
    fill_generation=f;
}
int Map_Elites::get_fill_generation(){
    return fill_generation;
}
void Map_Elites::display_fill_generation(){
    cout << endl << "Fill generation is: " << fill_generation << endl;
}
// --------------------------------------------------
// Mutate Generation, muatates individuals in Map for desired amount.
void Map_Elites::set_mutate_generation(int m){
    mutate_generation=m;
}
int Map_Elites::get_mutate_generation(){
    return mutate_generation;
}
void Map_Elites::display_mutate_generation(){
    cout << endl << "Mutate generation is: " << mutate_generation << endl;
}
// --------------------------------------------------
// Itialization function used outside of class.
            // Set Map Parameters
void Map_Elites::set_map_params(double d1_min, double d1_max, double d2_min, double d2_max, int res1, int res2, int fill_gen, int mutate_gen){
    set_min_dim1(d1_min);
    set_max_dim1(d1_max);
    set_min_dim2(d2_min);
    set_max_dim2(d2_max);
    set_resolution(res1, res2);
    set_fill_generation(fill_gen);
    set_mutate_generation(mutate_gen);
    initialize_map();
    //set_out_scope_magnitude();
}
// --------------------------------------------------
            // Display Map Parameters
void Map_Elites::display_Map_params(){
    display_min_dim1();
    display_max_dim1();
    display_min_dim2();
    display_max_dim2();
    display_resolution1();
    display_resolution2();
    display_fill_generation();
    display_mutate_generation();
}
// --------------------------------------------------
// TODO - Make dynamic
            // Check out of scope magnitude
void Map_Elites::set_out_scope_magnitude(){
    // auto set scope magnitude relative to dims min and max
}
// --------------------------------------------------
// Builds Map based on parameters, ALSO creates and sets Map_space LB and UB
void Map_Elites::initialize_map(){
    // PEIC - if min/max dims are on the same magnitude as out_scope_num, increase out_scope_num
    int out_scope_num=100000;       // TODO - Make dynamic
    double pre_LB1=dim1_min;
    double pre_LB2=dim2_min;
    //int row_in_Map=1;
    for(int d1=0; d1<num_spacing1; d1++){
        //int num_in_row=1;
        for(int d2=0; d2<num_spacing2; d2++){
            Map_space M;
            if (d1==0){
             M.set_LB1(-out_scope_num);
            }
            else{
                M.set_LB1(pre_LB1);
            }
            if (d2==0){
                M.set_LB2(-out_scope_num);
            }
            else{
                M.set_LB2(pre_LB2);
            }
            if(d1==num_spacing1){
                double calc_UB1= out_scope_num;
                M.set_UB1(calc_UB1);
            }
            else {
                double calc_UB1= pre_LB1+spacing1;
                M.set_UB1(calc_UB1);
            }
            if (d2==num_spacing2){
                double calc_UB2= out_scope_num;
                M.set_UB2(calc_UB2);
            }
            else {
                double calc_UB2= pre_LB2+spacing2;
                M.set_UB2(calc_UB2);
            }
            M.build_map_space();
            Row.push_back(M);
            pre_LB2+=spacing2;
            //cout << endl << "number in row is: "<< num_in_row << endl;
            //num_in_row++;
        }
        Map.push_back(Row);
        pre_LB1+=spacing1;
        //cout << endl << "rows in Map is: "<< row_in_Map << endl;
        //row_in_Map++;
    }
    cout << endl << "Map is made" << endl;
}
// --------------------------------------------------
// Places individual into corresponding map_space in Map
void Map_Elites::place_individual_in_map(Individual Passed_I){
    double p1=Passed_I.get_phenotype1();
    double p2=Passed_I.get_phenotype2();
    double pLB1=dim1_min;
    double pLB2=dim2_min;
    int row_value=0;
    int element_value=0;
    // to find which row phenotype belongs in
    for(int d1=0; d1<num_spacing1; d1++){
        // TODO - dex 0 and dex end special case handling in bin not this one
        double pUB1= pLB1+spacing1;
        // between range of LB1 and UB1
        if (pLB1<p1 && p1<pUB1){
            row_value=d1;
        }
        else {
            pLB1+=spacing1;
        }
    }
    // to find which element in row phenotype beolongs in
    for(int d2=0; d2<num_spacing2; d2++){
        double pUB2= pLB2+spacing2;
        // between range of LB2 and UB2
        if (pLB2<p2 && p2<pUB2){
            element_value=d2;
        }
        else {
            pLB2+=spacing2;
        }
    }
    Map.at(row_value).at(element_value).current_individual.push_back(Passed_I);
    // compare new individual in map space and erase worse
    Map.at(row_value).at(element_value).compare_new_individual();
}
// --------------------------------------------------
// Get individual from a map_space in Map
void Map_Elites::individual_from_map(double p1, double p2){
    temp_individual1.clear();
    temp_individual2.clear();
    double pLB1=dim1_min;
    double pLB2=dim2_min;
    int row_value=0;
    int element_value=0;
    // to find which row phenotype belongs in
    for(int d1=0; d1<num_spacing1; d1++){
        double pUB1= pLB1+spacing1;
        // between range of LB1 and UB1
        if (pLB1<p1 && p1<pUB1){
            row_value=d1;
        }
        else {
            pLB1+=spacing1;
        }
    }
    // to find which element in row phenotype beolongs in
    for(int d2=0; d2<num_spacing2; d2++){
        double pUB2= pLB2+spacing2;
        // between range of LB2 and UB2
        if (pLB2<p2 && p2<pUB2){
            element_value=d2;
        }
        else {
            pLB2+=spacing2;
        }
    }
    if (Map.at(row_value).at(element_value).current_individual.size()>0){
        temp_individual1 = Map.at(row_value).at(element_value).current_individual.at(0).get_individual1();
        
        temp_individual2 = Map.at(row_value).at(element_value).current_individual.at(0).get_individual2();
        cout << endl << "individuals passed to temp" << endl;
        get_temp_individual1();     // TODO - check to see if works !!!!!!!!!!
        get_temp_individual2();
    }
    else {
        cout << endl << "No individual in: " << p1 << p2 << endl;
        // closest filled map_space function?
    }
}
            // Get temp_individuals
vector<double>& Map_Elites::get_temp_individual1(){
    return temp_individual1;
}
vector<double>& Map_Elites::get_temp_individual2(){
    return temp_individual2;
}
// --------------------------------------------------
/*void Map_Elites::fill_Map(){           // take in fit and pheno from simulation
    for(int f=0; f<fill_generation; f++){
        I.build_individuals();
        // pass individual vectors to controller          // TODO
        // take fitness rating and set phenotypes       // TODO
        place_individual_in_map(I);
    }
        cout << endl << "Fill Generation Complete" << endl;
}
// --------------------------------------------------

*/








