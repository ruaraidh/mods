#ifndef partial_h
#define partial_h

#include "signal.h"

class partial{
public:
  ///
  /// constructor : define partial derivative of signal SA wrt SB equal to a value
  ///
  partial(signal* SA, signal* SB, double);
  /// 
  /// return dependent signal of partial derivative
  ///
  signal* getSA();
  /// 
  /// return independent signal of partial derivative
  ///
  signal* getSB();
  ///
  /// set value of partial derivative
  ///
  void setVal(double);
  ///
  /// return value of partial derivative
  ///
  double getVal();
 private:
  ///
  /// value
  ///
  double m_value;
  ///
  /// dependent signal
  ///
  signal* m_sigA;
  ///
  /// independent signal
  ///
  signal* m_sigB;
};

#endif

