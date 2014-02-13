#include <iostream>
using namespace std;
extern"C" {
  void PLAEPH_(double & DAY,int * LIST, int & IPV, double *PV, int & KRUT);
}
int main(int argc, char* argv[]){

  double day = 5020.123;
  int list[11] = {2,2,2,2,2,2,2,2,2,2,2};
  int ipv = 6;
  double pv[66]={66*0.0};;
  double planet[6][11];
  int krut = 0;
  for (int i=0 ; i<11 ; ++i)
    {
      cout << list[i] << endl;
    }
  cout <<  "!!!"<< endl;

  for (int i=0 ; i<66 ; ++i)
    {
      cout << pv[i] << endl;
    }
  PLAEPH_(day, list, ipv, pv, krut);

  for (int i=0 ; i<11 ; ++i)
    for (int j=0 ; j<6 ; ++j)
      {
	{
	  planet[j][i] =  pv[j+6*i];
	  cout <<j+6*i <<" " << pv[j+6*i] << endl;
	}
      }
  return 0;
}
