#ifndef SSNSet_h
#define SSNSEt_h

#include "Set.h"
emacs 
class SSNSet
{
 public:
  SSNSet();

  bool add(unsigned long ssn);

  int size() const;

  void print() const;

 private:
  Set numberSet;
};

#endif
