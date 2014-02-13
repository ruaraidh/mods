#include "geom_fact.h"
//#include <iostream>
#include "p2p.h"
#include "fixedpoint.h"
#include "plapoint.h"
#include "fixeddir.h"
#include "movingpoint.h"
#include "dot_product.h"
#include "cross_product.h"
#include "uvaxes.h"

using namespace std;
namespace geom_fact{
  bool createModel(const std::string &keyword, const std::string &name){
    bool created  = true;
    if (keyword == "p2p")
      {
	new p2p(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "fixedpoint") 
      {
	new fixedpoint(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "fixeddir") 
      {
	new fixeddir(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "movingpoint") 
      {
	new movingpoint(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "plapoint") 
      {
	new plapoint(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "dot_product") 
      {
	new dot_product(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "cross_product") 
      {
	new cross_product(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else if (keyword == "uvaxes") 
      {
	new uvaxes(name);
	cout << "new " << keyword<<"("<<name<<");"<<endl;
      }
    else
      {
      created = false;
    }
    return created;
  }
} // namespace geom_fact
