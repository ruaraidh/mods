#include "movingpoint.h"
#include "dir.h"
#include "function.cpp"
#include <cassert>

movingpoint::movingpoint(string name) : point(name, "movingpoint"){
}

void movingpoint::connect(){
  if (!m_connect){

    model *mod1 = connectmod("point");
    if (dynamic_cast<point*>(mod1) == NULL){
      cout << "ERROR: movingpoint point must be connected to a point"<<endl;
      exit(1);
    }
    model *mod2 = connectmod("dir");
    if (dynamic_cast<dir*>(mod2) == NULL){
      cout << "ERROR: movingpoint dir must be connected to a dir"<<endl;
      exit(1);
    }


    initialiseVectors();
    m_connect = true;
  }
}

void movingpoint::update(double time){
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
    assert(si.size() == 6);
    assert(so.size() == 3);
    for (int i = 0 ; i < 3 ; ++i){
      so[i] = si[i] + si[i+3]*time;
      dso_dsi[i][i]    = 1.0;     
      dso_dsi[i][i+3]  = 1.0;     
      for (int j = 0 ; j < i ; ++j){
	dso_dsi[i][j]    = dso_dsi[j][i]    = 0.0;     
 	dso_dsi[i][j+3]  = dso_dsi[j][i+3]  = 0.0;     
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
