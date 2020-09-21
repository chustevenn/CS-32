#include "Set.h"
using namespace std;

Set::Set(): isEmpty(true), numElements(0){}

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
  if(numElements < DEFAULT_MAX_ITEMS && !isPresentAlready)
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
  int temp;
  for(int i = 0; i < other.numElements; i++)
    {
      itemArray[i+numElements] = other.itemArray[i];
    }
  for(int i = 0; i < numElements; i++)
    {
      other.itemArray[i] = itemArray[i];
    }
  for(int i = 0; i < other.numElements; i++)
    {
      itemArray[i] = itemArray[numElements + i];
    }
  temp = numElements;
  numElements = other.numElements;
  other.numElements = temp;
}
