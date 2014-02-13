#include "config.h"
#include "fact.h"
#include "value.h"
#include <iostream>

using namespace std;

std::map<std::pair<string,string>,std::map<string,value*> > config::g_config;

void config::factory(){
  fact fact;
  std::map<std::pair<string,string>,std::map<string,value*> >::iterator it;
  for (it = g_config.begin() ; it != g_config.end() ; ++it){
    string keyword = it->first.first;
    string name = it->first.second;
    if (keyword == "parameter") {
      value* val = get_property("parameter",name,"value");
      double_value* dval;
      if (dval = dynamic_cast<double_value*>(val), dval){
	  fact.createParameter(name,dval->get_value());
	}
      else
	{
	  cerr << "Error: parameter " << name  << " should have a double value" <<endl;
	  exit(1);
	}
    }
    else
      {
	fact.createModel(keyword,name);
      }
  }
}

value* config::get_property(string keyword, string name , string property){
  std::pair<string,string> instance(keyword, name);
  if (g_config.find(instance) == g_config.end()){
    cerr << "Error " << instance << " is not available"<<endl;
    exit(1); 
  }
  if (g_config[instance].find(property) == g_config[instance].end()){
    cerr << "Error " << property << " is not available for "<< instance <<endl;
    exit(1); 
  }
  return g_config[instance][property];
}


value* config::get_value(const string &keyword,const string &name, const string &property){
  std::map<string,value*> lmap = get_map(keyword,name);
  for (std::map<string,value*>::iterator it = lmap.begin() ; it != lmap.end() ; ++it){
    string str = it->first;
    value* val = it->second;
    if (str == property){
      return val;
    }
  }

  cerr << "FATAL: Unable to get value for keyword=" << keyword << ", name=" << name << ", property=" << property << endl;
  exit (1);
}

std::map<string,value*> config::get_map(const string &keyword,const string &name){
  std::map<std::pair<string,string>,std::map<string,value*> >::iterator it;
  for (it = g_config.begin() ; it != g_config.end() ; ++it){
    string str1 = it->first.first;
    string str2 = it->first.second;
    if (str1 == keyword && str2 == name){
      return it->second;
    }
  }
  cerr << "FATAL: Unable to get map for keyword=" << keyword << ", name=" << name;
  exit (1);
}

int config::readinput( istream& inputstr){
  string line;
  
  while(getline(inputstr,line)){
    if (line.length() == 0 || line[0] == '#'){
      continue;
    }
    
    istringstream input(line);
    
    string keyword;
    
    input >> keyword;

    if (!input){
      cerr << "Error: missing input keyword"<<endl;
      exit(1);
    }  
    string name;
    input >> name;
    if (!input){
      cerr << "Error: missing input name"<<endl;
      exit(1);
    }

    pair<string,string> instance(keyword, name);

    string separator;
    input >> separator;
    if (!input || separator != ":")
      {
	cerr << "Error:" << instance << " " 
	     << " has no properties!" << endl;
	exit(1);
      }
    while(true)
      {
	string property;
	input >> property;
	if(!input){
	  cerr << "Error:" << instance << " " 
	       << " has missing property" << endl;
	  exit(1);
	}
	input >> separator;
	if (!input || separator != "=")
	  {
	    cerr << "Error:" << instance << " " 
		 << property 
		 << " has no value!" << endl;
	    exit(1);
	  }
	string valstr;
	input >> valstr;
	if(!input){
	  cerr << "Error:" << instance << " " 
	       << property 
	       << " without a value!" << endl;
	  exit(1);
	}
	if (g_config[instance].find(property) != g_config[instance].end()){
	  cout << "Warning: overwriting " 
	       << instance << " "
	       << property 
	       << " entry"<<endl;
	}
	////////////////
	// Decide here what type of value we have
	value* val = create_value(valstr);
	////////////////
	g_config[instance][property]=val;
	input >> separator;
	if (!input) 
	  {
	    // successful read to end of line
	    break;
	  }
	if (separator != ",")
	  {
	    cerr << "Error:" << instance
		 << " has illegal property separator: " << separator  
		 << endl;
	    exit(1);
	  }	
      }
  }
  return 0;
};

value* config::create_value(const string & str){
  {
    istringstream input(str);
    int i;
    input >> i;
    if (input)
      {
	string s;
	input >> s;
	if (!input){
	  return new int_value(i);
	}
      }  
  }
  {
    istringstream input(str);
    double dbl;
    input >> dbl;
    if (input)
      {
	string s;
	input >> s;
	if (!input){
	  return new double_value(dbl);
	}
      }
  }
  {
    istringstream input(str);
    bool b;
    input >> b;
    if (input)
      {
	string s;
	input >> s;
	if (!input){
	  return new bool_value(b);
	}
      }
  }   
  {
    if ((str.substr(0,1) == "\"") && (str.substr(str.size()-1,1) == "\"") && str.size() > 1 )
      {
	return new string_value(str.substr(1,str.size()-1));
      }
  }

  {
    return new name_value(str);
  }
} 

double config::get_double(const string &keyword, const string &name ,const string &property){
  value* val = get_value(keyword,name,property);
  double ret;
  if (double_value* dv = dynamic_cast< double_value*>(val)){
    ret = dv->get_value();
  }
  else
  {
    cerr << "Error: unexpected type found in " << keyword << ":" << name <<  " when trying to get double " << property <<endl;
    std::exit(1);
  }
  return ret;
}

int config::get_integer(const string &keyword, const string &name ,const string &property){
  value* val = get_value(keyword,name,property);
  int ret;
  if (int_value* dv = dynamic_cast< int_value*>(val)){
    ret = dv->get_value();
  }
  else
  {
    cerr << "Error: unexpected type found in " << keyword << ":" << name <<  " when trying to get integer " << property <<endl;
    std::exit(1);
  }
  return ret;
}

string config::get_string(const string &keyword, const string &name ,const string &property){
  value* val = get_value(keyword,name,property);
  string ret;
  if (string_value* dv = dynamic_cast< string_value*>(val)){
    ret = dv->get_value();
  }
  else
  {
    cerr << "Error: unexpected type found in " << keyword << ":" << name << " when trying to get string " << property <<endl;
    std::exit(1);
  }
  return ret;
}

string config::get_name(const string &keyword, const string &name ,const string &property){
  value* val = get_value(keyword,name,property);
  string ret;
  if (name_value* dv = dynamic_cast< name_value*>(val)){
    ret = dv->get_value();
  }
  else
  {
    cerr << "Error: unexpected type found in "  << keyword << ":" << name << " when trying to get name " << property <<endl;
    std::exit(1);
  }
  return ret;
}
bool config::get_bool( const string &keyword, const string &name ,const string &property){
  value* val = get_value(keyword,name,property);
  bool ret;
  if (bool_value* dv = dynamic_cast< bool_value*>(val)){
    ret = dv->get_value();
  }
  else
  {
    cerr << "Error: unexpected type found in "  << keyword << ":" << name << " when trying to get bool " << property <<endl;
    std::exit(1);
  }
  return ret;
}


// string config::getkeyword(string name){
//   string result = ""; 
//   std::map<std::pair<string,string>,std::map<string,value*> >::iterator it;
//   for (it = g_config.begin() ; it != g_config.end() ; ++it){
//     string keyword = it->first.first;
//     string str = it->first.second;
//     if (str == name) result =  keyword;
//   }
//   return result;
// }

// bool config::nameispresent(string name){
//   bool result = 0;
//   std::map<std::pair<string,string>,std::map<string,value*> >::iterator it;
//   for (it = g_config.begin() ; it != g_config.end() ; ++it){
//     string str = it->first.second;
//     if (str == name) result = 1;
//   }
//   return result;
// }
// bool config::keywordispresent(string keyword){
//   bool result = 0;
//   std::map<std::pair<string,string>,std::map<string,value*> >::iterator it;
//   for (it = g_config.begin() ; it != g_config.end() ; ++it){
//     string str = it->first.first;
//     if (str == keyword) result = 1;
//   }
//   return result;
// }
