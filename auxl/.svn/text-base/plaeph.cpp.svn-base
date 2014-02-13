#include "plaeph.h"

extern"C" {
  void PLAEPH_(double & t,int * l, int & ipv, double *pv, int & k);
}

namespace ephem{
  std::vector<double> plaeph(double & t , int & ID){
    std::vector<double> s;
    if (ID < 1 || ID > 11){
      std::cerr << "ERROR: plaeph ID must be from 1 to 11: ID = " << ID <<std::endl;
      exit(1);
    }
    int l[11] = {2,2,2,2,2,2,2,2,2,2,2};
    int ipv = 6;
    double pv[66]={66*0.0};
    int k = 0;
    PLAEPH_(t, l, ipv, pv, k);
    if (k != 0 ) { std::cerr << "ERROR: plaeph KRUT = " << k <<std::endl;; }
    s.clear();
    for (int j = 0 ; j < 6 ; ++j){
      s.push_back(pv[ j + 6 * ( ID - 1 )]);
    }
    return s;
  }
}
