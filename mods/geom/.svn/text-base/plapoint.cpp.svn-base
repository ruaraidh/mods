#include "plapoint.h"
#include "dir.h"
#include "config.h"
#include <cassert>

plapoint::plapoint(string name) : point(name, "plapoint"){
}

void plapoint::connect(){
  if (!m_connect){
    config conf;
    planet_ = conf.get_integer("plapoint",m_name,"planet");
    if (planet_ < 1 || planet_ > 11){
      cerr << "ERROR: plapoint planet must be from 1 to 11"<<endl;
      exit(1);
    }
    initialiseVectors();
    m_connect = true;
  }
};

void plapoint::update(double time){
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
    assert(si.size() == 0);
    assert(so.size() == 3);
    std::vector<double> s = ephem::plaeph(time,planet_);
    for (int i = 0 ; i < 3 ; ++i){
      so[i] = s[i];
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
