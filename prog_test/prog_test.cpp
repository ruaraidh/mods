#include <cstring>
#include "config.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "testmod_d.h"
#include "base.h"

double testfun(const double &t,const double &p1, const double &p2, const double &p3,const double &p4){
    double fa = p4*t-25.0; 
    double fb = sin(fa*t+p3);
    double fc = tan(fb*p2);
    double fd = sin(fb*p1)*fc;
    return fd;
}


int main(int argc, char* argv[]) {
  int result = 0;

  config conf;
  if (argc == 2){
    ifstream file(argv[1]); 
    result = conf.readinput(file);
  }else{
    result = conf.readinput(cin);
  }
  conf.factory();

  testmod_d* modd = dynamic_cast<testmod_d*>(model::dict.get("modd"));
  modd->connect();
  for(double t=0.0;t<10.0;t+=0.1){
    modd->update(t);
    cout << t <<" "<< modd->so[0] <<" " <<   testfun(t,1.0,2.0,3.0,4.0)    <<endl;
 
    for (vector<int>::size_type i = 0; i < (modd->dso_dsi[0]).size();++i ){
      cout << modd->si_name[0][i] << ":" << modd->dso_dsi[0][i]<<endl;
    }
    cout << 1<<" "<< (testfun(t,1.00001,2.0,3.0,4.0)-testfun(t,0.99999,2.0,3.0,4.0))/0.00002<<endl;
    cout << 2<<" "<< (testfun(t,1.0,2.00001,3.0,4.0)-testfun(t,1.0,1.99999,3.0,4.0))/0.00002<<endl;
    cout << 3<<" "<< (testfun(t,1.0,2.0,3.00001,4.0)-testfun(t,1.0,2.0,2.99999,4.0))/0.00002<<endl;
    cout << 4<<" "<< (testfun(t,1.0,2.0,3.0,4.0000001)-testfun(t,1.0,2.0,3.0,3.9999999))/0.0000002<<endl;
 }  
  return result;
}

