#include<algorithm>
#include<limits>
#include<cmath>
#include<cstdlib>
using namespace std;
inline bool myequal(double a, double b, double error_factor = 1.0){
return a==b ||
  std::abs(a-b) < std::abs(std::min(a,b))*std::numeric_limits<double>::epsilon()*error_factor;
}
