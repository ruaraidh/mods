#include "dir.h"
#include "cross_product.h"
#include "function.cpp"
#include <cassert>

cross_product::cross_product(string name) : dir(name, "cross_product"){
};

void cross_product::connect(){
  if (!m_connect){
    model *mod1 = connectmod("dir_1");
    if (dynamic_cast<dir*>(mod1) == NULL){
      cout << "ERROR: cross_product must be connected to a dir"<<endl;
      exit(1);
    }
    model *mod2 = connectmod("dir_2");
    if (dynamic_cast<dir*>(mod2) == NULL){
      cout << "ERROR: cross_product must be connected to a dir"<<endl;
      exit(1);
    }
    initialiseVectors();
    m_connect = true;
  }
}

void cross_product::update(double time){
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
    so[0] = si[1]*si[5] - si[2]*si[4];
    so[1] = si[2]*si[3] - si[0]*si[5];
    so[2] = si[0]*si[4] - si[3]*si[1];
    for (int i = 0; i<3 ; ++i)
      {
	for (int j = 0; j<6 ; ++j)
	  {
	    dso_dsi[i][j] = 0.0;
	  }	
      }
    dso_dsi[0][1] =  si[5];
    dso_dsi[0][2] = -si[4];
    dso_dsi[0][4] = -si[2];
    dso_dsi[0][5] =  si[1];
    dso_dsi[1][2] =  si[3];
    dso_dsi[1][3] =  si[2];
    dso_dsi[1][0] = -si[5];
    dso_dsi[1][5] = -si[0];
    dso_dsi[2][0] =  si[4];
    dso_dsi[2][4] =  si[0];
    dso_dsi[2][3] = -si[1];
    dso_dsi[2][1] = -si[3];
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
