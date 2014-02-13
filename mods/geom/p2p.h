#ifndef p2p_h
#define p2p_h 
#include "dir.h"
#include <cmath>

class p2p : public dir{
 public:
  p2p(string name);
  void update(double time);
  void connect();
};

#endif
