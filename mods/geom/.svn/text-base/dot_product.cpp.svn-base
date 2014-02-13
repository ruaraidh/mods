#include "dir.h"
#include "dot_product.h"
#include "function.cpp"
#include <cassert>

dot_product::dot_product(string name) : model(name, "dot_product"){
  createSig(name + "_sig");
};

void dot_product::connect(){
  if (!m_connect){
    model *mod1 = connectmod("dir_1");
    if (dynamic_cast<dir*>(mod1) == NULL){
      cout << "ERROR: dot_product must be connected to a dir"<<endl;
      exit(1);
    }
    model *mod2 = connectmod("dir_2");
    if (dynamic_cast<dir*>(mod2) == NULL){
      cout << "ERROR: dot_product must be connected to a dir"<<endl;
      exit(1);
    }
    initialiseVectors();
    m_connect = true;
  }
}

void dot_product::update(double time){
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
    so[0]              = si[0]*si[3] + si[1]*si[4] + si[2]*si[5];
    for (int i = 0 ; i < 3 ; ++i){
      dso_dsi[0][i]      = si[i+3];
      dso_dsi[0][i+3]    = si[i];
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
