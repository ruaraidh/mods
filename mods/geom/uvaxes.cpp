#include "uvaxes.h"
#include "axes.h"
#include "dir.h"
#include "function.cpp"
#include "vector3.h"
#include <cassert>

uvaxes::uvaxes(string name) : axes(name, "uvaxes"){
};

void uvaxes::connect(){
  if (!m_connect){
    model *mod1 = connectmod("dir_1");
    if (dynamic_cast<dir*>(mod1) == NULL){
      cout << "ERROR: uvaxes must be connected to a dir"<<endl;
      exit(1);
    }
    model *mod2 = connectmod("dir_2");
    if (dynamic_cast<dir*>(mod2) == NULL){
      cout << "ERROR: uvaxes must be connected to a dir"<<endl;
      exit(1);
    }
    initialiseVectors();
    m_connect = true;
  }
}

void uvaxes::update(double time){
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
    vector3 u(si[0],si[1],si[2]);
    vector3 v(si[3],si[4],si[5]);
    vector3 e1;
    vector3 e2;
    vector3 e3;
    uv2axes(u,v, e1, e2, e3);
    
    for (int i = 0 ; i < 3 ; ++i){
      so[i]              = e1[i];
      so[i+3]            = e2[i];
      so[i+6]            = e3[i];
    }
    double d = 0.001;
    for (int i = 0 ; i < 6 ; ++i){
      vector3 e1p,e1m;
      vector3 e2p,e2m;
      vector3 e3p,e3m;
      si[i] = si[i] + d; 
      for (int k = 0 ; k < 3 ; ++k){u[k]=si[k];v[k]=si[k+3];}
      uv2axes(u, v, e1p, e2p, e3p);
      si[i] = si[i] - 2*d; 
      for (int k = 0 ; k < 3 ; ++k){u[k]=si[k];v[k]=si[k+3];}
      uv2axes(u, v, e1m, e2m, e3m);
      si[i] = si[i] + d; 

      for (int j = 0 ; j < 3 ; ++j){
	dso_dsi[j][i] = (e1p[j] - e1m[j])/(2.0*d);
	dso_dsi[j+3][i] = (e2p[j] - e2m[j])/(2.0*d);
	dso_dsi[j+6][i] = (e3p[j] - e3m[j])/(2.0*d);
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


void uvaxes::uv2axes( vector3 & u,  vector3 &v, vector3 &e1, vector3 &e2, vector3 &e3 ){
  e2 = u^v;
  double au = u.mod();
  double av = v.mod();
  double ae2 = e2.mod();
  if (myequal(au,0.0) || myequal(av,0.0)){
    cerr << "Error: zero vector not usable for uvaxes";
    exit(1);
  }
  if (myequal(ae2,0.0)){
    cerr << "Error: colinear vectors not usable for uvaxes";
    exit(1);
  }
  e1 = u/au;
  e2 = e2 / ae2;
  e3 = e1^e2;
  return;
}
