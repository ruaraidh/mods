#include "timesignal.h"

dictionary<timesignal> timesignal::dict;

timesignal::timesignal(string name, double value) : signal(name, "timesignal"){
  dict.add(name, this);
  set_value(value);
  //  m_status = false;
}
void timesignal::update(double time){
}
