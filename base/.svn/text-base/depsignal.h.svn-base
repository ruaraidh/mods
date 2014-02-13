#ifndef depsignal_h
#define depsignal_h

class model;

#include "signal.h"
#include "partial.h"
#include "parameter.h"
#include <vector>
#include <iostream>
using namespace std;

class depsignal:public signal{
 public:
  ///
  /// Constructor - dependent signal. 
  /// A dependent signal belongs to a model. The constructor is called from a model constructor 
  ///
  depsignal(string name, model* mod);
  ///
  /// Model to which the dependent signal belongs
  ///
  std::string source_mod();
  ///
  /// Update value of the signal by updating its model
  ///
  void update(double);
  ///
  /// Add a partial derivative of this signal WRT other signal to the vector of partials
  ///
  void add_partial(signal* other, double value);
  ///
  ///  Apply chain rule for this signal (sA) to get partials only of input signals of input signals
  ///  application of this method ensures only parameters are retained in the partials array.
  ///  dsA/dsC = sum_over_all_Bs( dsA/dSB * dsB/dsC) + dsA/dsC
  ///
  void chain_partials();
  ///
  /// Remove all partials from vector
  ///
  void clear_partials();
  ///
  /// is NOT independent  since it belongs to a model
  ///
  bool isindependent(){return false;};
  ///
  /// get partial values
  ///
  vector<double> get_partial_values();
  ///
  /// get name of other signal in each partial
  ///
  vector<string> get_partial_SB();
 protected:
 private:
  /// vector of partials
  vector<partial*> m_partials;
  /// pointer to model to which this signal belongs
  model *mod;
};

#endif

