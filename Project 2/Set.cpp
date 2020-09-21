#include "Set.h"
#include <iostream>
#include <string>
using namespace std;

//default constructor for a doubly circular linked list
Set::Set(): numElements(0)
{
  head = new Node;
  head->next = head;
  head->prev = head;
}

//copy constructor
Set::Set(const Set& copy)
{
  //copy over the number of elements value to the copy and create a new empty list
  numElements = copy.numElements;
  head = new Node;
  head->next = head;
  head->prev = head;
  //if the copied Set is not empty, append a new node
  if(numElements != 0)
    {
      Node* pNext = new Node;
      head->next = pNext;
    }
  //define placeholder pointers to make pointer manipulation easier
  Node* curNode = head->next;
  Node* tempPrev = head;
  Node* tempNext;
  //for each node present in the copied set, create a new Node, and update the
  //values and pointers of the current node accordingly
  for(Node* p = copy.head->next; p != copy.head; p = p->next)
    {
      Node* newNext = new Node;
      tempNext = newNext;
      curNode->prev = tempPrev;
      curNode->next = newNext;
      curNode->value = p->value;
      tempPrev = curNode;
      curNode = tempNext;
    }
  //because the loop allocates a new node preemptively, we need to delete the
  //created node when the next node in the copied set turns out to loop back
  //around to the head
  delete curNode;
  tempPrev->next = head;
  head->prev = tempPrev;
}
//trival checking operation
bool Set::empty() const
{
  if(numElements == 0)
    {
      return true;
    }
  else
    return false;
}
//trivial getter
int Set::size() const
{
  return numElements;
}
//assignment operator
Set& Set::operator=(const Set& assign)
{
  //copy over the number of elements datatype
  numElements = assign.numElements;
  //check if the operator is acting on an alias
  if(head != assign.head)
    {
      Node* p = head->next;
      Node* tempPointer;
      //empty out whatever was in the original set
      while(p != head)
	{
	  tempPointer = p->next;
	  delete p;
	  p = tempPointer;
	}
      //check if copied set was empty
      if(numElements == 0)
	{
	  head->next = head;
	  head->prev = head;
	  return *this;
	}
      //if not empty, reuse logic of the copy constructor to copy the elements
      //of the set over
      Node* pNext = new Node;
      head->next = pNext;
      Node* curNode = head->next;
      Node* tempPrev = head;
      Node* tempNext;
      for(Node* p = assign.head->next; p != assign.head; p = p->next)
	{
	  Node* newNext = new Node;
	  tempNext = newNext;
	  curNode->prev = tempPrev;
	  curNode->next = newNext;
	  curNode->value = p->value;
	  tempPrev = curNode;
	  curNode = tempNext;
	}
      delete curNode;
      tempPrev->next = head;
      head->prev = tempPrev;
    }
  return *this;
}
//destructor
Set::~Set()
{
  Node* p = head->next;
  Node* tempPointer;
  //iterate through the list, and delete each node
  while(p != head)
    {
      tempPointer = p->next;
      delete p;
      p = tempPointer;
    }
  //delete the beginning dummy node
  delete head;
}

bool Set::insert(const ItemType& value)
{
  //checks if the element is already present in the set
  for(Node* p = head->next; p != head; p = p->next)
    {
      if(p->value == value)
	return false;
    }
  //if not present, allocate a new node, assign the node the value to be inserted,
  //and insert the node
  Node* newNode = new Node;
  newNode->value = value;
  newNode->prev = head->prev;
  head->prev->next = newNode;
  newNode->next = head;
  head->prev = newNode;
  numElements++;
  return true;
} 

bool Set::get(int pos, ItemType& value) const
{
  //checks proper bounds on the given position value
  if(pos >= numElements || pos < 0)
    return false;
  //loops through the list
  ItemType tempValue;
  for(Node* p = head->next; p != head; p = p->next)
    {
      tempValue = p->value;
      int count = 0;
      //check number greater than for each element
      for(Node* j = head->next; j != head; j = j->next)
	{
	  if(tempValue > j->value)
	    {
	      count++;
	    }
	}
      //if number matches, assign value at node to value
      if(count == pos)
	{
	  value = tempValue;
	}
    }
  return true;
}

bool Set::contains(const ItemType& value) const
{
  //loops through list and checks each element
  for(Node* p = head->next; p != head; p = p->next)
    {
      //return true if matching value is found
      if(p->value == value)
	return true;
    }
  return false;
}

bool Set::erase(const ItemType& value)
{
  //check if the set contains the value you're trying to remove
  if(!this->contains(value))
    {
      return false;
    }
  //if the value is present, loop through the list to find it
  for(Node* p = head->next; p != head; p = p->next)
    {
      //delete the node when its found, reassign the pointers accordingly
      if(p->value == value)
	{
	  Node* tempPointer = p->next;
	  tempPointer->prev = p->prev;
	  p->prev->next = tempPointer;
	  delete p;
	  numElements--;
	  break;
	}
    }
  return true;
}

//swaps number of elements datatype and head pointers
void Set::swap(Set& other)
{
  int holder = numElements;
  numElements = other.numElements;
  other.numElements = holder;
  Node* tempPointer = head;
  head = other.head;
  other.head = tempPointer;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
  //checks if result is an alias for s1
  if(&s1 == &result)
    {
      //insert elements of s2 that are not in s1 to result
      for(int i = 0; i < s2.size(); i++)
	{
	  ItemType holder;
	  s2.get(i, holder);
	  result.insert(holder);
	}
      return;
    }
  //checks if result is an alias for s2
  if(&s2 == &result)
    {
      //insert elements of s1 that are not in s2 to result
      for(int i = 0; i < s1.size(); i++)
	{
	  ItemType holder;
	  s1.get(i, holder);
	  result.insert(holder);
	}
      return;
    }
  //assign s1 to result
  result = s1;
  for(int i = 0; i < s2.size(); i++)
    {
      //insert elements of s2 that are not in s1 to result
      ItemType holder;
      s2.get(i, holder);
      result.insert(holder);
    }
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
  //checks if result is an alias to s1
  if(&result == &s1)
    {
      //removes all elements from s2 that appear in s1
      for(int i = 0; i < s2.size(); i++)
	{
	  ItemType holder;
	  s2.get(i, holder);
	  result.erase(holder);
	}
      return;
    }
  //creates a new set, inserts values present exclusively in s1
  Set s;
  for(int i = 0; i < s1.size(); i++)
    {
      ItemType holder;
      s1.get(i, holder);
      if(!s2.contains(holder))
	s.insert(holder);
    }
  //assign s to result
  result = s;
}
