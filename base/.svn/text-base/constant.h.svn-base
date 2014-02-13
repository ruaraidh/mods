#ifndef constant_h
#define constant_h

#include "signal.h"

class constant:public signal{
 public:
  ///
  /// Constructor - constant double value. Its value is obtained from the config map
  /// The class constant contains no dictionary so a value can only be used locally in a single model
  ///
  constant(double value);
  ///
  /// Implement pure virtual update method from signal
  ///
  void update(double);
  ///
  /// is independent - does not emanate from a model
  ///
  bool isindependent(){return true;};
 protected:
 private:
};

#endif

