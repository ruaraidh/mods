#include <cstring>
#include "config.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "cross_product.h"
#include "dot_product.h"
#include "movingpoint.h"
#include "base.h"

int main(int argc, char* argv[]) {
  int result = 0;

  config conf;
  if (argc == 2){
    ifstream file(argv[1]); 
    result = conf.readinput(file);
  }else{
    result = conf.readinput(cin);
  }
  conf.factory();

  //cross_product* fun = cross_product::dict.get("mycp");
  //dot_product* fun = dot_product::dict.get("mydp");
  //movingpoint* fun = movingpoint::dict.get("mymp");
  //movingpoint* fun = dynamic_cast<movingpoint*>(model::dict.get("mymp"));
  model* fun = model::dict.get("mydir1");
  fun->connect();
  for(double t=3420.0;t<3421.0;t+=0.05)
    {
      fun->update(t);
      cout << t;
      for (vector<int>::size_type i = 0; i < (fun->dso_dsi).size();++i )
	{
	  cout << " " << fun->so[i];
	}
      for (vector<int>::size_type i = 0; i < (fun->dso_dsi).size();++i )
	{
	  for (vector<int>::size_type j = 0; j < (fun->dso_dsi[i]).size();++j )
	    {
	      cout << "     " <<fun->si_name[i][j] << ":" << fun->dso_dsi[i][j];
	    }
	}
      cout << endl;
    }  
  return result;
}

