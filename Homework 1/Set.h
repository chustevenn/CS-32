#ifndef Set_h
#define Set_h

#include<string>
using namespace std;

using ItemType = string;
const int DEFAULT_MAX_ITEMS = 240;

class Set
{
 public:
  Set();
  bool empty() const;
  int size() const;

  bool insert(const ItemType& value);

  bool erase(const ItemType& value);

  bool contains(const ItemType& value) const;

  bool get(int i, ItemType& value) const;

  void swap(Set& other);

private:
  ItemType itemArray[DEFAULT_MAX_ITEMS];
  bool isEmpty;
  int numElements;
};

#endif
