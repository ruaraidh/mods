#include "testmod_c.h"
#include <cassert>


testmod_c::testmod_c(string name) : model(name, "testmod_c"){
  createSig(name + "_sig1");
};

void testmod_c::connect(){
  if (!m_connect){
    connectpar("par");
    model *mod = connectmod("mod");
    initialiseVectors();
    m_connect = true;
  }
};

void testmod_c::update(double time){
  //
  // update input models and parameters
  //
  update_inp(time);
  if (update_status()){
    // 
    // Perform local model calculations
    // 
    so[0]         = tan( si[1] * si[0] );
    dso_dsi[0][1] = si[0]  / cos( si[1] * si[0] )  / cos( si[1] * si[0] );
    dso_dsi[0][0]  = si[1] / cos( si[1] * si[0] )  / cos( si[1] * si[0] );
    
    chain_partials();
  }
};
