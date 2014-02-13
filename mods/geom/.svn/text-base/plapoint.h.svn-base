#ifndef plapoint_h
#define plapoint_h 
#include "point.h"
#include <cmath>
#include "plaeph.h"
using namespace ephem;

class plapoint : public point{
public:
  plapoint(string name);
  void update(double time);
  void connect();
 private:
  int planet_;
};

#endif
