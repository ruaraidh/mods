#ifndef parameter_h
#define parameter_h

#include "dictionary.h"
#include "signal.h"

class parameter:public signal{
 public:
  static dictionary<parameter> dict;
  parameter(string name, double value);
  void update(double);
  bool isindependent(){return true;};
 protected:
 private:
};

#endif

