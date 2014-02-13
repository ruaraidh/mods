#include "point.h"

point::point(string name, string class_name) : model(name, class_name){
  createSig(name + "_x");
  createSig(name + "_y");
  createSig(name + "_z");
}
