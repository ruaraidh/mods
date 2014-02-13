#include "model.h"
#include <cmath>

class testmod_c : public model{
public:
  testmod_c(string name);
  void update(double time);
  void connect();
};

