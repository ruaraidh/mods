#ifndef value_h
#define value_h
#include<string>

class value{
 protected:
  virtual ~value(){};
};

class int_value:public value{
 public:
  int_value(const int i) {i_ = i;}
  int get_value() const {return i_;}
 private:
  int i_;
};

class double_value:public value{
 public:
  double_value(const double d) {d_ = d;}
  double get_value() const {return d_;}
 private:
  double d_;
};


class name_value:public value{
 public:
  name_value(const std::string n) {n_ = n;}
  std::string get_value() const {return n_;}
 private:
  std::string n_;
};


class string_value:public value{
 public:
  string_value(const std::string s) {s_ = s;}
  std::string get_value() const {return s_;}
 private:
  std::string s_;
};

class bool_value:public value{
 public:
  bool_value(const bool b) {b_ = b;}
  bool get_value() const {return b_;}
 private:
  bool b_;
};


#endif
