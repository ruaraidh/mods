#ifndef vector3_H
#define vector3_H

class vector3{
  double x,y,z;
public:
  vector3(){ x = 0.0; y = 0.0; z = 0.0;}
  vector3( double u, double v, double w){ x = u; y = v; z = w;}
  double getx(){ return x; }
  double gety(){ return y; }
  double getz(){ return z; }
  void print();
  vector3 operator+( vector3 v);
  vector3 operator*( double d);
  double operator*( vector3 v);
  vector3 operator/( double d);
  vector3 operator^( vector3 v);
  double  & operator[](int i);
  const double & operator[](int i) const;
  double mod();
};
#endif // vector3_H
