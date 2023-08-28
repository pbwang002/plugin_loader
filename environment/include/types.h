#ifndef TYPES_H
#define TYPES_H
#include <string>
using namespace std;

class BaseType {
public:
  virtual string GetSuffix() = 0; 
};
#endif