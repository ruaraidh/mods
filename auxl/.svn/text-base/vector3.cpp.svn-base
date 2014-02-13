#include <stdlib.h>
#include <iostream>
using namespace std;
#include <cmath>
#include "vector3.h"

vector3 vector3::operator+( vector3 v){ 
  return vector3(x + v.getx(),y + v.gety(),z + v.getz());
}
vector3 vector3::operator*( double d){
  return vector3(x*d,y*d,z*d);
}
// why does this nor work?
//vector3 operator*(double d,vector3 v){
//  return vector3(v.getx()*d,v.gety()*d,v.getz()*d);
//}
vector3 vector3::operator/( double d){
  return vector3(x/d,y/d,z/d);
}
double vector3::operator*( vector3 v){
  return x*v.getx()+y*v.gety()+z*v.getz();
}
vector3 vector3::operator^( vector3 v){
  return vector3(y*v.getz()-z*v.gety(),z*v.getx()-x*v.getz(),x*v.gety()-y*v.getx());
}
double vector3::mod(){
  return sqrt(x*x+y*y+z*z);
}
void vector3::print(){  cout  << "["<< x << "," << y << "," << z <<  "]"<< endl;}

double & vector3::operator[](int i){
  if ( i == 0 )
    {
      return x;
    }
  else if (i == 1)
    {
      return y;
    }
  else if (i == 2)
    {
      return z;
    }
  else
    {
      cerr << "ERROR: attempt to access vector3 out of bounds";
      exit(1);
    }
}
const double & vector3::operator[](int i) const {
  if ( i == 0 )
    {
      return x;
    }
  else if (i == 1)
    {
      return y;
    }
  else if (i == 2)
    {
      return z;
    }
  else
    {
      cerr << "ERROR: attempt to access vector3 out of bounds";
      exit(1);
    }
}



