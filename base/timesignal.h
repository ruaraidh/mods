#ifndef timesignal_h
#define timesignal_h

#include "dictionary.h"
#include "signal.h"

class timesignal:public signal{
 public:
  static dictionary<timesignal> dict;
  timesignal(string name, double value);
  void update(double);
  bool isindependent(){return true;};
 protected:
 private:
};

#endif

