//
//  dynamics.h
//  R2D2ae
//
//  Created by Sierra Adibi on 11/23/15.
//  Copyright © 2015 Sierra Adibi. All rights reserved.
//

//#include "anglemath.h"
using namespace std;

#include "Craft.hpp"
#include "anglemath.h"

#ifndef dynamics_h
#define dynamics_h

void getalpha(double a, double &colift, double &codrag, vector<vector<double> > aero){
    double clLower, clUpper, cdLower, cdUpper, aLower, aUpper;
    for(int i=0;i<(aero.size()-1);i++){
        if(aero.at(i).at(0)==a){    //If we get an integer for the degrees, use that.
            colift = aero.at(i).at(1);
            codrag = aero.at(i).at(2);
            break;
        }else if(aero.at(i).at(0)<a && aero.at(i+1).at(0)>=a){   //Otherwise, linearly interpolate
            //get alpha, cl and cd for the values on either side
            clLower = aero.at(i).at(1);
            clUpper = aero.at(i+1).at(1);
            cdLower = aero.at(i).at(2);
            cdUpper = aero.at(i+1).at(2);
            aLower = aero.at(i).at(0);
            aUpper = aero.at(i+1).at(0);
            
            //calculate the values of cl and cd
            colift = clUpper - (aUpper-a)*(clUpper-clLower)/(aUpper-aLower);
            codrag = cdUpper - (aUpper-a)*(cdUpper-cdLower)/(aUpper-aLower);
            break;
        }
    }
    
}

// calc controls to forces in newtonian directions
// theta describes the angle of the velocity with respect to the x-axis, negative or positive
// phi describes the angle of the body with respect to the negative x-axis
vector<double> forcecalc(vector<double> controller, Craft& c, double rho, vector<vector<double> > ae) {
    vector<double> forcevec;                        // vector to be returned
    double phi = reset_angle(c.orientation.at(0).q);             //renaming pitch for ease of use
    c.orientation.at(0).q = phi;
    double lx, lz, dx, dz, tx, tz;      //newtonian force components
    double g = -9.81*c.mass;                               //gravitational component
    double velsqr = pow(c.frame.at(0).sdot,2)+pow(c.frame.at(1).sdot,2);    //square of total velocity
    double vel = sqrt(velsqr);                      //total velocity
    double theta = asin(abs(c.frame.at(1).sdot)/vel);       //orientation of velocity vector
    
    // initialize coefficients of lift and drag to 0
    double cl = 0;
    double cd = 0;
    
    // test which quadrant velocity vector is in
    vector<int> quad = checkquadrant(c);
    
    // calling functions to find coefficients
    vector<double> coefficients = coeffcalc(quad, phi, theta);
    
    c.alpha = reset_angle(coefficients.at(0));
    //c.alpha = reset_angle(c.alpha);
    //cout << "ALPHA IS: " << alpha << endl;
    
    
    // determine if coefficients of lift and drag are known, assign if possible {{DEGREES}}
    double alpha_degrees = c.alpha * 180 / (4*atan(1));
    
    getalpha(alpha_degrees, cl, cd, ae);
//    for(int i=0;i<ae.size();i++){
//        if(ae.at(i).at(0)==round(alpha_degrees)){
//            cl = ae.at(i).at(1);
//            cd = ae.at(i).at(2);
//            break;
//        }
//    }

    
    //cout << "cl = " << cl;
    //cout << "\tcd = " << cd << endl;
    
    //cout << "AoA is " << alpha_degrees << "\t Cl is " << cl << "\t Cd is " << cd << "\n";
    
    //Calculate forces of lift and drag, will be 0 if cl and cd not available from file.
    c.lift = cl*rho*velsqr*c.sref*0.5;
    c.drag = cd*rho*velsqr*c.sref*0.5;
    
    //cout << "LIFT IS: " << c.lift << " AND DRAG: " << c.drag << endl;
    //cout << "COEF:::: " << cl << "\t" << cd << endl;
    //cout << "ALPHA IS: " << alpha << endl;
    
    //calculate newtonian components of force, lift, drag, and thrust
    tx = controller.at(0)*coefficients.at(1);
    tz = controller.at(0)*coefficients.at(2);
    lx = c.lift*coefficients.at(3);
    lz = c.lift*coefficients.at(4);
    dx = c.drag*coefficients.at(5);
    dz = c.drag*coefficients.at(6);
    
    
    // calculate total forces in x and z, return along with moment.
    double forcesx = lx+dx+tx;
    forcevec.push_back(forcesx);
    double forcesz = lz+dz+tz+g;
    forcevec.push_back(forcesz);
    forcevec.push_back(controller.at(1));
    return forcevec;
}


// calculate new position, velocity, and acceleration for each direction.
double dynamicscalc(Craft & ref, vector<double> forcevec, double ts, int lincount, int rotcount){
    double prevphi = ref.orientation.at(0).q;
    
    //linear calculations using trapezoidal integration
    
    for(int i=0;i<lincount;i++){
        double accelprev = ref.frame.at(i).sdotdot;
        double velprev = ref.frame.at(i).sdot;
        
        ref.frame.at(i).sdotdot = forcevec.at(i)/ref.mass;
        
        ref.frame.at(i).sdot = ref.frame.at(i).sdot + 0.5*ts*(accelprev+ref.frame.at(i).sdotdot);
        ref.frame.at(i).s = ref.frame.at(i).s + 0.5*ts*(velprev+ref.frame.at(i).sdot);
    }
    
    //rotational calculations using trapezoidal integration
    
    for(int i=0;i<rotcount;i++){
        double accelprev = ref.orientation.at(i).qdotdot;
        double velprev = ref.orientation.at(i).qdot;
        
        ref.orientation.at(i).qdotdot = forcevec.at(i+lincount)/ref.inertia;
        
        ref.orientation.at(i).qdot = ref.orientation.at(i).qdot + 0.5*ts*(accelprev+ref.orientation.at(i).qdotdot);
        ref.orientation.at(i).q = ref.orientation.at(i).q + 0.5*ts*(velprev+ref.orientation.at(i).qdot);
    }
    
     // return how much the craft rotated
    return ref.orientation.at(0).q - prevphi;
}

#endif /* dynamics_h */
