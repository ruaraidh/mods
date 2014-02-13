#include "point.h"
#include "dir.h"
#include "p2p.h"
#include "function.cpp"
#include <cassert>

p2p::p2p(string name) : dir(name, "p2p"){
}

void p2p::connect(){
  if (!m_connect){
    model *mod1 = connectmod("point_1");
    if (dynamic_cast<point*>(mod1) == NULL){
      cout << "ERROR: p2p must be connected to a point"<<endl;
      exit(1);
    }
    model *mod2 = connectmod("point_2");
    if (dynamic_cast<point*>(mod2) == NULL){
      cout << "ERROR: p2p must be connected to a point"<<endl;
      exit(1);
    }
    initialiseVectors();
    m_connect = true;
  }
}

void p2p::update(double time){
  static double last;
  //if (!myequal(time,last))
    {
    //
    // Update input models and parameters
    //
    update_inp(time);
    // 
    // Perform local model calculations
    // 
    for (int i = 0 ; i < 3 ; ++i){
      so[i]              = si[i+3] - si[i];
      dso_dsi[i][i]      = -1.0;
      dso_dsi[i][i+3]    =  1.0;
    for (int j = 0 ; j < i ; ++j){
	dso_dsi[i][j]  = dso_dsi[j][i]  = 0.0;     
      }
    }
    //
    // Process partials
    //
    chain_partials();
    //
    // Update last
    //
    last = time;
 }
}
