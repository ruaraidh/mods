#include "partial.h"

partial::partial(signal* SA, signal* SB, double val){
  m_sigA  = SA;
  m_sigB  = SB;
  m_value = val;
}
signal* partial::getSA(){
  return m_sigA;
}
signal* partial::getSB(){
  return m_sigB;
}
void partial::setVal(double val){
  m_value = val;
}
double partial::getVal(){
  return m_value;
}
