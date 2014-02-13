#include "fact.h"
#include "geom_fact.h"
#include "test_fact.h"
#include "parameter.h"
#include <iostream>
#include <cstdlib>


using namespace std;
void fact::createModel(const std::string &keyword, const std::string &name){
  bool created = false;
  if (!created) created = geom_fact::createModel(keyword,name);
  if (!created) created = test_fact::createModel(keyword,name);
  if (!created)
    {
      cerr << "Error: Unknown model " << keyword << endl;
      exit(1);
    }
}
void fact::createParameter(const std::string &name,const double &value){
  new parameter(name,value);
  cout << "new " << "parameter"<<"("<<name<<","<<value<<");"<<endl;
}
