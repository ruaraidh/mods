#include "fixedpoint.h"
#include "point.h"
#include "function.cpp"
#include <cassert>

fixedpoint::fixedpoint(string name) : point(name, "fixedpoint"){
}

void fixedpoint::connect(){
  if (!m_connect){
    connectpar("x");
    connectpar("y");
    connectpar("z");
    initialiseVectors();
    m_connect = true;
  }
}

void fixedpoint::update(double time){
  double last;
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
      so[i] = si[i];
      dso_dsi[i][i]  = 1.0;     
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
