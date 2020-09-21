#include "newSet.h"
#include <iostream>
using namespace std;

Set::Set(const int& num): numElements(0)
{
  if(num < 0)
    {
      cout << "Negative number of elements not allowed" << endl;
      exit(1);
    }
  maxElements = num;
  itemArray = new ItemType[num];
}

Set::Set(const Set& copy)
{
  numElements = copy.numElements;
  itemArray = new ItemType[numElements];
  for(int i = 0; i < numElements; i++)
    {
      itemArray[i] = copy.itemArray[i];
    }
}

Set& Set::operator=(const Set& assign)
{
  if(this != &assign)
    {
      Set temp(assign);
      this->swap(temp);
    }
  return *this;
}

Set::~Set()
{
  delete [] itemArray;
}

bool Set::empty() const
{
  if(numElements == 0)
    return true;
  else
    return false;
}

int Set::size() const
{
  return numElements;
}

bool Set::insert(const ItemType& value)
{
  bool isPresentAlready = false;
  for(int i = 0; i < numElements; i++)
    {
      if(itemArray[i] == value)
	{
	  isPresentAlready = true;
	}
    }
  isEmpty = false;
  if(numElements < maxElements && !isPresentAlready)
    {
      itemArray[numElements] = value;
      numElements++;
      return true;
    }
  else
    {
      return false;
    }
}

bool Set::erase(const ItemType& value)
{
  int valueIndex;
  bool isPresent = false;
  for(int i = 0; i < numElements; i++)
    {
      if(itemArray[i] == value)
	{
	  isPresent = true;
	  valueIndex = i;
	  break;
	}
    }
  if(isPresent)
    {
      for(int i = valueIndex; i < numElements-1; i++)
	{
	  itemArray[i] = itemArray[i+1];
	}
      numElements--;
      return true;
    }
  else
    {
      return false;
    }
}

bool Set::contains(const ItemType& value) const
{
  bool isPresent = false;
  for(int i = 0; i < numElements; i++)
    {
      if(itemArray[i] == value)
	{
	  isPresent = true;
	}
    }
  return isPresent;
}

bool Set::get(int i, ItemType& value) const
{
  if(i >= numElements || i < 0)
    {
      return false;
    }
  ItemType temp;
  int count = 0;
  for(int j = 0; j < numElements; j++)
    {
      temp = itemArray[j];
      for(int k = 0; k < numElements; k++)
	{
	  if(temp > itemArray[k])
	    {
	      count++;
	    }
	}
      if(count == i)
	break;
    }
  value = temp;
  return true;
}

void Set::swap(Set& other)
{
  int t,m;
  ItemType* temp;
  temp = itemArray;
  itemArray = other.itemArray;
  other.itemArray = temp;
  t = numElements;
  m = maxElements;
  maxElements = other.maxElements;
  numElements = other.numElements;
  other.numElements = t;
  other.maxElements = m;
}
