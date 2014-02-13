#include "testmod_b.h"
#include "testmod_a.h"
#include <cassert>

testmod_b::testmod_b(string name) : model(name, "testmod_b"){
  createSig(name + "_sig1");
};

void testmod_b::connect(){
  if (!m_connect){
    connectpar("par");
    model *mod = connectmod("mod");
    if (dynamic_cast<testmod_a*>(mod) == NULL){
      cout << "ERROR: testmod_b must be connected to a testmod_a"<<endl;
      exit(1);
    } 
    initialiseVectors();
    m_connect = true;
  }
}

void testmod_b::update(double time){
  //
  // Update input models and parameters
  //
  update_inp(time);
  if (update_status()){
    // 
    // Perform local model calculations
    // 
    so[0]         = sin( si[1] * time + si[0] );
    dso_dsi[0][1] = cos( si[1] * time + si[0] ) * time;
    dso_dsi[0][0] = cos( si[1] * time + si[0] );
    //
    // Process partials
    //
    chain_partials();
  }
}
