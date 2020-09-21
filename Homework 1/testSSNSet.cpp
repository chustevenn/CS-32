#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
  SSNSet s;
  assert(s.add(123456) && s.size() == 1);
  s.add(987654);
  s.add(102938);
  assert(s.size() == 3);
  s.print();
  cout << "all tests passed" << endl;
}
