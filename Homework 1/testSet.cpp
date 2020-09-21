#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
  Set s;
  assert(s.empty());
  ItemType x = "yes";
  ItemType y = "no";
  assert(!s.get(42, x) && x == "yes");
  s.insert("david smallberg is my daddy");
  assert(s.size() == 1);
  assert(s.get(0,x) && x == "david smallberg is my daddy");
  s.insert("randomstring");
  assert(s.get(1,y) && y == "randomstring");
  assert(s.erase("david smallberg is my daddy") && s.erase("randomstring")
	 && s.empty());
  cout << "Passed all tests" << endl;
}
