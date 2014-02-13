#ifndef dictionary_h
#define dictionary_h

#include <string>
#include <iostream>
#include <map>

using namespace std;


template <typename T>
class dictionary{
  
public:

  void add(string instance_name,T* inst){

    if (mymap.find(instance_name) != mymap.end()){
      cerr << "Warn: " << instance_name << " is being overwritten in this dictionary" <<endl;
    }
    mymap[instance_name] = inst;
  }

  T* get(string instance_name){
    T* inst = NULL;
    if (mymap.find(instance_name) != mymap.end()){
      inst = mymap[instance_name];
    }
    else{
      //cerr << "Error: " << instance_name << " is not in this dictionary" <<endl;
    }
    return inst;
  }

  void listall(){
    typename map<string,T*>::iterator it;
    for(it=mymap.begin();it!=mymap.end();it++){
      cout << it->first <<" "<<it->second<<endl;  
    }
  }

private:
  map<string,T*> mymap;
};

#endif
