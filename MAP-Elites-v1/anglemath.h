//
//  anglemath.h
//  R2D2ae
//
//  Created by Sierra Adibi on 11/23/15.
//  Copyright © 2015 Sierra Adibi. All rights reserved.
//

using namespace std;

#ifndef anglemath_h
#define anglemath_h

//make sure the angle is between pi and negative pi
double reset_angle(double angle){
    double pi = 4*atan(1);
    
    if(angle>pi){
        while(angle>pi){
            angle = angle-2*pi;
        }
    }else if(angle< (pi*-1)){
        while(angle<(pi*-1)){
            angle = angle + 2*pi;
        }
    }else if((-1*pi)<=angle && angle <=pi){
        angle = angle;
    }
    return angle;
}

// check which quadrant the velocity vector and aircraft x vector are in
vector<int> checkquadrant(craft land){
    int direction;
    vector<int> quadrants;
    double phi;
    
    // check quadrant for velocity vector
    if (land.frame.at(0).sdot >= 0){
        if(land.frame.at(1).sdot >= 0){
            direction = 1; //first quadrant
        }else{
            direction = 4; //fourth quadrant
        }
    }else{
        if(land.frame.at(1).sdot >= 0){
            direction = 2; //second quadrant
        }else{
            direction = 3; //third quadrant
        }
    }
    quadrants.push_back(direction);
    
    // check quadrant for aircraft body
    
    phi = reset_angle(land.orientation.at(0).q);
    double pi = 4*atan(1);
    
    if(0<=phi && phi<=(pi/2)){
        direction = 2;
    }else if((pi/2)<phi&& phi <=pi){
        direction = 1;
    }else if(phi<0 && phi>=(-pi/2)){
        direction = 3;
    }else if((-pi/2)>phi&& phi>=(-pi)){
        direction = 4;
    }else{
        cout << "\n ERROR, HOMIE \n";
    }
    quadrants.push_back(direction);
    
    return quadrants;
}

// determine how we are making vectors components
// 0 value is angle of attack
// 1,2 are multipliers for lift in nx and nz, respectively
// 3,4 are multipliers for drag in nx and nz
// 5,6 are multipliers for thrust in nx and nz
vector<double> coeffcalc(vector<int> directions, double q, double t){
    double aoa;
    double pi = 4*atan(1);
    double lxm, lzm, dxm, dzm, txm, tzm;
    vector<double> coefficients;
    
    if(directions.at(0)==1){
        if(directions.at(1)==1){
            aoa = pi-q-t;
            txm = cos(pi-q);
            tzm = sin(pi-q);
            lxm = -sin(t);
            lzm = cos(t);
            dxm = -cos(t);
            dzm = -sin(t);
        }else if(directions.at(1)==2){
            aoa = pi-q-t;
            txm = -cos(q);
            tzm = sin(q);
            lxm = sin(t);
            lzm = -cos(t);
            dxm = -cos(t);
            dzm = -sin(t);
        }else if(directions.at(1)==3){
            aoa = pi/2;
            txm = -cos(q);
            tzm = -sin(q);
            lxm = 0;
            lzm = 0;
            dxm = 0;
            dzm = 0;
        }else if(directions.at(1)==4){
            aoa = -(pi-q+t);
            txm = cos(pi-q);
            tzm = -sin(pi-q);
            lxm = -sin(t);
            lzm = cos(t);
            dxm = -cos(t);
            dzm = -sin(t);
        }else{
            cout << "\n ERROR, HOMIE \n";
        }
    }else if(directions.at(0)==2){
        if(directions.at(1)==1){
            aoa = q-t;
            txm = cos(pi-q);
            tzm = sin(pi-q);
            lxm = -cos(t);
            lzm = -sin(t);
            dxm = cos(t);
            dzm = -sin(t);
        }else if(directions.at(1)==2){
            aoa = q-t;
            txm = -cos(q);
            tzm = sin(q);
            lxm = cos(t);
            lzm = sin(t);
            dxm = cos(t);
            dzm = -sin(t);
        }else if(directions.at(1)==3){
            aoa = -(q+t);
            txm = -cos(q);
            tzm = -sin(q);
            lxm = -cos(t);
            lzm = sin(t);
            dxm = cos(t);
            dzm = -sin(t);
        }else if(directions.at(1)==4){
            aoa = pi/2;
            txm = cos(pi-q);
            tzm = -sin(pi-q);
            lxm = 0;
            lzm = 0;
            dxm = 0;
            dzm = 0;
        }else{
            cout << "\n ERROR, HOMIE \n";
        }
    }else if(directions.at(0)==3){
        if(directions.at(1)==1){
            aoa = pi/2;
            txm = cos(pi-q);
            tzm = sin(pi-q);
            lxm = 0;
            lzm = 0;
            dxm = 0;
            dzm = 0;
        }else if(directions.at(1)==2){
            aoa = q+t;
            txm = -cos(q);
            tzm = sin(q);
            lxm = -sin(t);
            lzm = cos(t);
            dxm = cos(t);
            dzm = sin(t);
        }else if(directions.at(1)==3){
            aoa = t-q;
            txm = cos(q);
            tzm = -sin(q);
            lxm = -sin(t);
            lzm = cos(t);
            dxm = cos(t);
            dzm = sin(t);
        }else if(directions.at(1)==4){
            aoa = t-q;
            txm = cos(pi-q);
            tzm = -sin(pi-q);
            lxm = sin(t);
            lzm = -cos(t);
            dxm = cos(t);
            dzm = sin(t);
        }else{
            cout << "\n ERROR, HOMIE \n";
        }
    }else if(directions.at(0)==4){
        if(directions.at(1)==1){
            aoa = pi-q+t;
            txm = cos(pi-q);
            tzm = sin(pi-q);
            lxm = sin(t);
            lzm = cos(t);
            dxm = -cos(t);
            dzm = sin(t);
        }else if(directions.at(1)==2){
            aoa = pi/2;
            txm = -cos(q);
            tzm = sin(q);
            lxm = 0;
            lzm = 0;
            dxm = 0;
            dzm = 0;
        }else if(directions.at(1)==3){
            aoa = pi-q-t;
            txm = -cos(q);
            tzm = -sin(q);
            lxm = sin(t);
            lzm = cos(t);
            dxm = -cos(t);
            dzm = sin(t);
        }else if(directions.at(1)==4){
            aoa = pi-q-t;
            txm = cos(pi-q);
            tzm = -sin(pi-q);
            lxm = sin(t);
            lzm = cos(t);
            dxm = -cos(t);
            dzm = sin(t);
        }else{
            cout << "\n ERROR, HOMIE \n";
        }
    }else{
        cout << "\n ERROR, HOMIE \n";
    }
    
    // pushback values into a vector
    coefficients.push_back(aoa);
    coefficients.push_back(txm);
    coefficients.push_back(tzm);
    coefficients.push_back(lxm);
    coefficients.push_back(lzm);
    coefficients.push_back(dxm);
    coefficients.push_back(dzm);
    
    return coefficients;
}



#endif /* anglemath_h */
