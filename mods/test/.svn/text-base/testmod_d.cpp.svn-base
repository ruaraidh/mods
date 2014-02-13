#include "testmod_d.h"
#include <cassert>

testmod_d::testmod_d(string name) : model(name, "testmod_d"){
  createSig(name + "_sig1");

};

void testmod_d::connect(){
  if (!m_connect){
    connectpar("par");
    model *mod1 = connectmod("mod1");
    model *mod2 = connectmod("mod2");
    initialiseVectors();
    m_connect = true;
  }
};

//#define SIZEOF( x ) (sizeof(x)/sizeof(x[0]))

void testmod_d::update(double time){
  //
  // update input models and parameters
  //
  update_inp(time);
  if (update_status()){
    // 
    // Perform local model calculations
    // 
    so[0]         = si[2]          * sin( si[1] * si[0] );
    dso_dsi[0][1] = si[2] * si[0]  * cos( si[1] * si[0] );
    dso_dsi[0][2] =                  sin( si[1] * si[0] );
    dso_dsi[0][0] = si[2] * si[1]  * cos( si[1] * si[0] );
    chain_partials();
  }
};

