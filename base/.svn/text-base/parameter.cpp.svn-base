#include "parameter.h"

dictionary<parameter> parameter::dict;

parameter::parameter(string name, double value) : signal(name, "parameter"){
  dict.add(name, this);
  set_value(value);
  //  m_status = false;
}
void parameter::update(double time){
}
