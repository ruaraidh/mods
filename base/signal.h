#ifndef signal_h
#define signal_h

#include "base.h"
#include <vector>

class signal : public base{
public:
  signal(std::string name, std::string class_name);
  void set_value(double);
  double get_value();
  virtual void update(double) = 0;
  virtual void add_partial(signal*, double){};
  virtual void clear_partials(){};
  virtual void chain_partials(){};
  virtual bool isindependent(){return true;};
  virtual std::vector<double> get_partial_values(){ std::vector<double> t; return t;};
  virtual std::vector<std::string> get_partial_SB(){ std::vector<std::string> t; return t;};
  bool update_status(){return m_status;};
  void update_status(bool stat){m_status = stat;};
 private:
  bool m_status;
  double m_value;
};

#endif

