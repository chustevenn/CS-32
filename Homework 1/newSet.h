#ifndef newSet_h
#define newSet_h

#include<string>
using namespace std;

using ItemType = string;
const int DEFAULT_MAX_ITEMS = 240;

class Set
{
 public:
  Set(const int& num = DEFAULT_MAX_ITEMS);
  Set(const Set& copy);
  ~Set();

  Set& operator=(const Set& assign);
  
  bool empty() const;
  int size() const;

  bool insert(const ItemType& value);

  bool erase(const ItemType& value);

  bool contains(const ItemType& value) const;

  bool get(int i, ItemType& value) const;

  void swap(Set& other);

private:
  ItemType* itemArray;
  bool isEmpty;
  int maxElements;
  int numElements;
};

#endif
