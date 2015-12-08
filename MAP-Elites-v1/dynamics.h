//
//  dynamics.h
//  R2D2ae
//
//  Created by Sierra Adibi on 11/23/15.
//  Copyright © 2015 Sierra Adibi. All rights reserved.
//

#include "anglemath.h"
using namespace std;

#ifndef dynamics_h
#define dynamics_h

// calc controls to forces in newtonian directions
// theta describes the angle of the velocity with respect to the x-axis
// phi describes the angle of the body with respect to the x-axis
vector<double> forcecalc(vector<double> controller, craft c, double rho, vector<vector<double> > ae) {
    vector<double> forcevec;
    double phi = c.orientation.at(0).q;
    double lift, drag, lx, lz, dx, dz, tx, tz;
    double g = -9.81;
    double velsqr = pow(c.frame.at(0).sdot,2)+pow(c.frame.at(1).sdot,2);
    double vel = sqrt(velsqr);
    double theta = asin(abs(c.frame.at(1).sdot)/vel);
    double cl = 0;
    double cd = 0;
    
    // test which quadrant velocity vector is in
    vector<int> quad = checkquadrant(c);
    
    vector<double> angles = coeffcalc(quad, phi, theta);
    
    double alpha = angles.at(0);
    
    
    // find coefficients of lift and drag
    for(int i=0;i<ae.size();i++){
        if(ae.at(i).at(0)==alpha){
            cl = ae.at(i).at(1);
            cd = ae.at(i).at(2);
            break;
        }
    }
    
    //cout << "AoA is " << alpha << "\t Cl is " << cl << "\t Cd is " << cd << "\n";
    
    lift = cl*rho*velsqr*c.sref*0.5;
    drag = cd*rho*velsqr*c.sref*0.5;
    
    lx = lift*sin(theta);
    lz = lift*cos(theta);
    dx = drag*cos(theta);
    dz = -drag*sin(theta);
    tx = controller.at(0)*cos(phi);
    tz = controller.at(0)*sin(phi);
    
    
    double forcesx = lx+dx+tx;
    forcevec.push_back(forcesx);
    double forcesz = lz+dz+tz+g;
    forcevec.push_back(forcesz);
    forcevec.push_back(controller.at(1));
    return forcevec;
}


// calculate new position, velocity, and acceleration for each direction.
// check trig things
double dynamicscalc(craft & ref, vector<double> forcevec, double ts, int lincount, int rotcount){
    double prevphi = ref.orientation.at(0).q;
    
    //linear calculations
    
    for(int i=0;i<lincount;i++){
        double accelprev = ref.frame.at(i).sdotdot;
        double velprev = ref.frame.at(i).sdot;
        
        ref.frame.at(i).sdotdot = forcevec.at(i)/ref.mass;
        
        ref.frame.at(i).sdot = ref.frame.at(i).sdot + 0.5*ts*(accelprev+ref.frame.at(i).sdotdot);
        ref.frame.at(i).s = ref.frame.at(i).s + 0.5*ts*(velprev+ref.frame.at(i).sdot);
    }
    
    //rotational calculations
    
    for(int i=0;i<rotcount;i++){
        double accelprev = ref.orientation.at(i).qdotdot;
        double velprev = ref.orientation.at(i).qdot;
        
        ref.orientation.at(i).qdotdot = forcevec.at(i+lincount)/ref.inertia;
        
        ref.orientation.at(i).qdot = ref.orientation.at(i).qdot + 0.5*ts*(accelprev+ref.orientation.at(i).qdotdot);
        ref.orientation.at(i).q = ref.orientation.at(i).q + 0.5*ts*(velprev+ref.orientation.at(i).qdot);
    }
    
    return ref.orientation.at(0).q - prevphi;
}

#endif /* dynamics_h */
