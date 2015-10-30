//
//  Table_space.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 10/20/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "Table_space.hpp"

// --------------------------------------------------
            // Min of dim1
void Table_space::set_min_dim1(double min1){
    dim1_min = min1;
}
double Table_space::get_min_dim1(){
    return dim1_min;
}
void Table_space::display_min_dim1(){
cout << endl << "Min of dim1 is: " << dim1_min << endl;
}
            // Min of dim2
void Table_space::set_min_dim2(double min2){
    dim2_min = min2;
}
double Table_space::get_min_dim2(){
    return dim2_min;
}
void Table_space::display_min_dim2(){
    cout << endl << "Min of dim2 is: " << dim2_min << endl;
}
            // Min of dim3
void Table_space::set_min_dim3(double min3){
    dim3_min = min3;
}
double Table_space::get_min_dim3(){
    return dim3_min;
}
void Table_space::display_min_dim3(){
    cout << endl << "Min of dim3 is: " << dim3_min << endl;
}
            // Max of dim1
void Table_space::set_max_dim1(double max1){
    dim1_max = max1;
}
double Table_space::get_max_dim1(){
    return dim1_max;
}
void Table_space::display_max_dim1(){
    cout << endl << "Max of dim1 is: " << dim1_max << endl;
}
            // Max of dim2
void Table_space::set_max_dim2(double max2){
    dim2_max = max2;
}
double Table_space::get_max_dim2(){
    return dim2_max;
}
void Table_space::display_max_dim2(){
    cout << endl << "Max of dim2 is: " << dim2_max << endl;
}
            // Max of dim3
void Table_space::set_max_dim3(double max3){
    dim3_max = max3;
}
double Table_space::get_max_dim3(){
    return dim3_max;
}
void Table_space::display_max_dim3(){
    cout << endl << "Max of dim3 is: " << dim3_max << endl;
}
// --------------------------------------------------
            // Resolution
void Table_space::set_resolution(int r1, int r2) {
    resolution1=r1;
    resolution2=r2;
    num_spacing1=r1;
    num_spacing2=r2;
    //num_spacing3=r3;
    spacing1=(dim1_max-dim1_min)/resolution1;
    spacing2=(dim2_max-dim2_min)/resolution2;
    // spacing3=(dim3_max-dim3_min)/resolution3;
}
int Table_space::get_resolution1(){
    return resolution1;
}
void Table_space::display_resolution1(){
    cout << endl << "Resolution 1 is: " << resolution1 << endl;
}
int Table_space::get_resolution2(){
    return resolution2;
}
void Table_space::display_resolution2(){
    cout << endl << "Resolution 2 is: " << resolution2 << endl;
}
// --------------------------------------------------
void Table_space::build_table(){
    double pre_LB1=dim1_min;
    double pre_LB2=dim2_min;
    //int row_in_table=1;
    for(int d1=0; d1<num_spacing1; d1++){
        //int num_in_row=1;
        for(int d2=0; d2<num_spacing2; d2++){
            Map_space M;
            M.set_LB1(pre_LB1);
            M.set_LB2(pre_LB2);
            double calc_UB1= pre_LB1+spacing1;
            double calc_UB2= pre_LB2+spacing2;
            M.set_UB1(calc_UB1);
            M.set_UB2(calc_UB2);
            M.build_map_space();
            Row.push_back(M);
            pre_LB2+=spacing2;
            //cout << endl << "number in row is: "<< num_in_row << endl;
            //num_in_row++;
        }
        Table.push_back(Row);
        pre_LB1+=spacing1;
        //cout << endl << "rows in table is: "<< row_in_table << endl;
        //row_in_table++;
    }
    cout << endl << "Table is made" << endl;
}
// --------------------------------------------------
void Table_space::place_genome(){


}
















// --------------------------------------------------