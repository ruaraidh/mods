#include "test_fact.h"
#include <iostream>
#include "testmod.h"
#include "testmod_a.h"
#include "testmod_b.h"
#include "testmod_c.h"
#include "testmod_d.h"
using namespace std;

namespace test_fact{
  bool createModel(const std::string &keyword, const std::string &name){
    bool created = true;
    if (keyword == "testmod")
      {
	new testmod(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "testmod_a") 
      {
	new testmod_a(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "testmod_b") {
      new testmod_b(name);
      cout << "new " << keyword<<"("<<name<<");"<<endl;
    }
    else if (keyword == "testmod_c") {
      new testmod_c(name);
      cout << "new " << keyword<<"("<<name<<");"<<endl;
    }
    else if (keyword == "testmod_d") {
      new testmod_d(name);
      cout << "new " << keyword<<"("<<name<<");"<<endl;
    }
    else
      {
	created = false;
      }
    return created;
  }
} // namespace test_fact
