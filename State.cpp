//
//  State.cpp
//  Mapping_Elites v1
//
//  Created by Jeremy Fries on 12/2/15.
//  Copyright © 2015 Jeremy Fries. All rights reserved.
//

#include "State.hpp"


void State::get_state(craft l, double t, double ts){
    time = t;
    timestep = ts;
    xpos = l.frame.at(0).s;
    xvel = l.frame.at(0).sdot;
    zpos = l.frame.at(1).s;
    zvel = l.frame.at(1).sdot;
    phi = l.orientation.at(0).q;
    phivel = l.orientation.at(0).qdot;
    
    KEx = 0.5*pow(xvel,2)*l.mass;
    KEz = 0.5*pow(zvel,2)*l.mass;
    KEp = 0.5*pow(phivel,2)*l.inertia;
}
// --------------------------------------------------
//print header for keeping track of positions
void State::printheader(){
    cout << "Time \t TStep \t\t X-Pos \t X-Velocity \t Z-Pos \t Z-Velocity \t Pitch \t Omega \t Kinetic Energy" << endl;
}
// --------------------------------------------------
//print values for each round
//file is the output file to be read by MatLab
void State::printround(ofstream & file){
    
    cout << time << "\t\t\t" << timestep << "\t\t\t" << xpos << "\t\t\t" << xvel << "\t\t\t" << zpos << "\t\t\t";
    cout << zvel << "\t\t\t" << phi << "\t\t\t" << phivel << "\t\t\t" << KEx << "\t\t\t" << KEz << "\t\t\t" << KEp << endl;
    file << time << "\t\t\t" << timestep << "\t\t\t" << xpos << "\t\t\t" << xvel << "\t\t\t" << zpos << "\t\t\t";
    file << zvel << "\t\t\t" << phi << "\t\t\t" << phivel << "\t\t\t" << KEx << "\t\t\t" << KEz << "\t\t\t" << KEp << endl;
}
// --------------------------------------------------