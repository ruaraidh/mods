#ifndef uvaxes_h
#define uvaxes_h 
#include "axes.h"
#include "vector3.h"
#include <cmath>

class uvaxes : public axes{
public:
  uvaxes(string name);
  void update(double time);
  void connect();
 private:
  void uv2axes( vector3 & u,  vector3 &v, vector3 &e1, vector3 &e2, vector3 &e3 );
};

#endif
