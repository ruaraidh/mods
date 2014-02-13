#include "model.h"
#include <cmath>

class testmod_d : public model{
public:
  testmod_d(string name);
  void update(double time);
  void connect();
};

