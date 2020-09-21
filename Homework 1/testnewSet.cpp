#include "newSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
  Set a(1000);
  Set b(5);
  Set s;
  assert(s.empty());
  ItemType x = "yes";
  ItemType y = "no";
  ItemType v[6] = {"we", "you", "nah", "yes", "no", "rand"};
  for(int i = 0; i < 5; i++)
    {
      assert(b.insert(v[i]));
    }
  assert(!b.insert(v[5]));
  a.swap(b);
  assert(!a.insert(v[5]) && b.insert(v[5]));
  assert(!s.get(42, x) && x == "yes");
  s.insert("david smallberg is my daddy");
  assert(s.size() == 1);
  assert(s.get(0,x) && x == "david smallberg is my daddy");
  s.insert("randomstring");
  assert(s.get(1,y) && y == "randomstring");
  assert(s.erase("david smallberg is my daddy") && s.erase("randomstring"));
  assert(s.empty());
  cout << "Passed all tests" << endl;
}
