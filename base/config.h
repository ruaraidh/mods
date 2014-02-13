#ifndef config_h
#define config_h 

#include<iosfwd>
#include<iostream>
#include<cstdlib>
#include<map>
#include<sstream>
#include<string>
using std::string;
using std::cerr;
using std::endl;

class value;

class config{
 public:
  ///  
  /// Read input from file and populate g_config
  ///  
  int readinput(std::istream&);
  ///
  /// Use fact create.model and create.parameter methods to instantiate all models and parameters
  /// Object pointers are then stored in static dictionaries, using name_value as key.
  ///
  void factory();
  ///
  /// Methods for getting a value of known type
  ///
  double get_double (const string &keyword,const string &name, const string &property);
  int    get_integer(const string &keyword,const string &name, const string &property);
  string get_string (const string &keyword,const string &name, const string &property);
  string get_name   (const string &keyword,const string &name, const string &property);
  bool   get_bool   (const string &keyword,const string &name, const string &property);
  ///
  /// Get pointer to a generic value. Useful in case of multiple possibilities for type (e.g. double or parameter) 
  ///
  value* get_value  (const string &keyword,const string &name, const string &property);
 private:
  ///
  /// static configuration map g_config. Input file containing entries of form:
  /// <<class_name instance_name : property = value , other_property = other_value , ...>>
  /// is converted to this map.
  /// Value type can be bool, int, double, "string" or name (string) where name refers to another instance_name
  ///
  static std::map<std::pair<string,string>,std::map<string,value*> > g_config;
  ///
  /// Get the map for a particular class and instance
  ///
  std::map<string,value*> get_map(const string &keyword,const string &name);
  /// 
  /// Create a value by trying each allowed type
  ///
  value* create_value(const string &str);
  ///
  /// Get the value of a property
  ///
  value* get_property(string keyword, string name, string property);
protected:
};
inline std::ostream& operator<<(std::ostream& os,std::pair<string,string> inst){
  os << inst.first << ":" << inst.second;
  return os;
} 
#endif
