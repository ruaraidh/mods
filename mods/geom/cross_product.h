#ifndef cross_product_h
#define cross_product_h 
#include "dir.h"
#include <cmath>

class cross_product : public dir{
 public:
  cross_product(string name);
  void update(double time);
  void connect();
};
#endif

