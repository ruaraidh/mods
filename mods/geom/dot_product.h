#ifndef dot_product_h
#define dot_product_h 
#include "model.h"
#include <cmath>

class dot_product : public model{
public:
  dot_product(string name);
  void update(double time);
  void connect();
};
#endif

