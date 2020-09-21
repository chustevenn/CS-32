#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet(){}

bool SSNSet::add(unsigned long ssn)
{
  bool success = numberSet.insert(ssn);
  return success;
}

int SSNSet::size() const
{
  return numberSet.size();
}

void SSNSet::print() const
{
  unsigned long temp;
  for(int i = 0; i < numberSet.size(); i++)
    {
      numberSet.get(i, temp);
      cout << temp << endl;
    }
}
