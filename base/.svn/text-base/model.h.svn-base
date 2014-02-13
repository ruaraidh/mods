#ifndef model_h
#define model_h
#include<cstdlib>
#include <vector>
#include <iostream>
#include "base.h"
#include "signal.h"
#include "dictionary.h"

class model : public base{
 public:
  ///
  /// constructor - used in fact class
  ///
  model(string name, string class_name);
  ///
  /// static collection of models for access by name
  ///
  static dictionary<model> dict;
  ///
  /// vectors of doubles for performing calculations
  /// they are initialised according to connection status 
  /// and updated in the chain_partials method (TBD remove the update from this method)
  ///
  std::vector<double> so;
  std::vector<double> si;
  std::vector<std::vector<double> > dso_dsi;
  std::vector<std::vector<string> > si_name;
  ///
  /// virtual update method to be implemented by concrete class
  ///
  virtual void update(double time)=0;
  ///
  /// virtual connect method to be implemented by concrete class
  ///
  virtual void connect()=0;
 protected:
  ///
  /// default method for handling chain rule for partial derivatives
  ///
  void chain_partials();
  ///
  /// update all input signals
  ///
  void update_inp(double time);
  ///
  /// initialise so,si,dso_dsi,si_name with correct dimensions after connecting model
  ///
  void initialiseVectors();
  ///
  /// create an output signal 
  ///
  void createSig(const string &sig);
  ///
  /// connect to another model using the property field for this model
  /// returns pointer to the other model for checking and accessing additional information
  ///
  model* connectmod(const string &property);
  ///
  /// connect to a parameter or a double using the property field for this model
  ///
  void connectpar(const string &property);
  ///
  /// connection status of this model (true = connected)
  ///
  bool m_connect;
  ///
  /// return update status - true = already updated, no need to re-evaluate
  ///
  bool update_status();
  ///
  /// set update status
  ///
  void update_status(bool stat);
 private:
  ///
  /// vector of input signals
  ///
  std::vector<signal*> m_inp;
  ///
  /// vector of output signals
  ///
  std::vector<signal*> m_out;
  ///
  /// status flag
  /// should be set to false once the model has been updated - this is TBD awaiting finalisation of time usage
  ///
  bool m_status;
};

#endif
