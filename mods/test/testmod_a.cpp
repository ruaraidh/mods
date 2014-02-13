#include "testmod_a.h"
#include <iostream>
using namespace std;

testmod_a::testmod_a(string name) : model(name, "testmod_a"){
  createSig(name + "_sig1");
};

void testmod_a::connect(){
  if (!m_connect){
    connectpar("par");
    initialiseVectors();
    m_connect=true;
  }
}

void testmod_a::update(double time){
  //
  // update input models and parameters
  //
  update_inp(time);
  if (update_status()){
    // 
    // Perform local model calculations
    // 
    so[0]         = si[0] * time -25.0;
    dso_dsi[0][0] = time;
    
    chain_partials();
  }
};

