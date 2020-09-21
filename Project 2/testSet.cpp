#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
  Set s; //tests default constructor
  s.insert("Yes"); //tests insert
  s.insert("no"); //tests insert
  s.insert("maybe"); //tests insert
  assert(!s.empty()); //tests empty
  string n;
  s.get(2, n); //tests get
  assert(n == "no"); //tests get
  s.get(1,n); //tests get
  assert(n == "maybe"); //tests get
  Set y; //tests default constructor
  y.insert("har"); //tests insert
  y.insert("oof"); //tests insert
  y.insert("ye"); //tests insert
  y.get(2,n); //tests get
  assert(n == "ye"); //tests get
  assert(s.contains("Yes")); //tests get
  y.swap(s); //tests swap
  assert(!s.contains("Yes")); //tests swap
  Set z; //tests default constructor
  unite(s,y,z); //tests unite
  assert(z.size() == 6); //tests unite
  assert(z.contains("Yes")); //tests unite
  assert(z.contains("oof")); //tests unite
  Set t; //tests default constructor
  t.insert("Yes"); //tests insert
  t.insert("oof"); //tests insert
  Set r; //tests default constructor
  subtract(z,t,r); //tests subtract
  assert(r.size() == 4); //tests subtract
  assert(!r.contains("oof")); //tests subtract
  assert(r.contains("maybe")); //tests subtract
  Set a = t; //tests assignment operator
  unite(t, z, a); //tests unite alias case
  assert(a.contains("Yes")); //tests unite alias case
  subtract(t, z, a); //tests subtract alias case
  assert(!a.contains("Yes")); //tests subtract alias case
  assert(!a.contains("ye")); //tests subtract alias case
    Set v;
    v.insert("ten");
    assert(!v.empty());
    v.erase("ten");
    assert(v.empty());
    assert(!a.get(-1, n));
    assert(!a.get(6,n));
  cout << "all tests passed" << endl;
  return 0;
}
