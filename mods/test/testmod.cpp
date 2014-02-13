#include "testmod.h"
#include <cassert>


testmod::testmod(string name) : model(name, "testmod"){
  createSig(name + "_sig1");
  createSig(name + "_sig2");
};

void testmod::connect(){
  if (!m_connect){
    connectpar("par");
    model *mod = connectmod("mod1");
    initialiseVectors();
    m_connect = true;
  }
};

void testmod::update(double time){
  //
  // update input models and parameters
  //
  update_inp(time);
  if (update_status()){
    // 
    // Perform local model calculations
    // 
    so[0]         = si[1] * sin( si[0] * time );
    dso_dsi[0][1] = sin( si[0] * time );
    dso_dsi[0][0]  = si[1] * cos( si[0] * time) * time;

    chain_partials();

  }
};
