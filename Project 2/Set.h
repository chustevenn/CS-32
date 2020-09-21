#ifndef Set_h
#define Set_h
#include <string>
using namespace std;

using ItemType = string;

class Set
{
 public:
  Set();
  Set(const Set& copy);
  ~Set();
  Set& operator=(const Set& assign);
  bool empty() const;
  int size() const;
  bool insert(const ItemType& value);
  bool erase(const ItemType& value);
  bool contains(const ItemType& value) const;
  bool get(int pos, ItemType& value) const;
  void swap(Set& other);
 private:
  struct Node
  {
    Node* next;
    Node* prev;
    ItemType value;
  };
  Node* head;
  int numElements;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);
#endif
