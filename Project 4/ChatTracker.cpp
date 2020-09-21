// ChatTracker.cpp

// This is a correct but inefficient implementation of
// the ChatTracker functionality.

#include "ChatTracker.h"
#include <string>
#include <list>
#include <vector>
#include <functional>
using namespace std;

  // This class does the real work of the implementation.

class ChatTrackerImpl
{
  public:
    ChatTrackerImpl(int maxBuckets);
    void join(string user, string chat);
    int terminate(string chat);
    int contribute(string user);
    int leave(string user, string chat);
    int leave(string user);
  unsigned int getKeyU(string input);
  unsigned int getKeyC(string input);

  private:
    struct Info
    {
        Info(string u, string c) : user(u), chat(c), count(0) {}
        string user;
        string chat;
        int count;
    };

  struct HashTable
  {
    list<Info> *table;
    unsigned int numberBuckets;
 
    HashTable(int n)
    {
      numberBuckets = n;
      table = new list<Info>[numberBuckets];
    }
    
    ~HashTable()
    {
	delete [] table;
    }
  };

    vector<Info> m_info;
    vector<Info> m_usersWhoLeft;
  HashTable m_users;
  HashTable m_chats;
};   

ChatTrackerImpl::ChatTrackerImpl(int maxBuckets): m_users(maxBuckets), m_chats(maxBuckets)
{
    // Construct hash tables with sizes appropriate to assumptions provided
  // in spec.
}

unsigned int ChatTrackerImpl::getKeyU(string input)
{
    return hash<string>()(input) % 20000;
}

unsigned int ChatTrackerImpl::getKeyC(string input)
{
    return hash<string>()(input) % 20000;
}

void ChatTrackerImpl::join(string user, string chat)
{
  unsigned int chatKey = getKeyC(chat);
  unsigned int userKey = getKeyU(user);
  bool alreadyIn = false;
  list<Info>::iterator c;
  for(c = m_users.table[userKey].begin(); c != m_users.table[userKey].end(); c++)
    {
      if(c->user == user && c->chat == chat)
	{
      	  m_users.table[userKey].push_back(*c);
	  m_users.table[userKey].erase(c);
	  alreadyIn = true;
	  break;
	}
    }
   if(!alreadyIn)
     {
      m_users.table[userKey].push_back(Info(user, chat));
     }
   m_chats.table[chatKey].push_back(Info(user, chat));
}

int ChatTrackerImpl::terminate(string chat)
{
    int total = 0;
    unsigned int chatKey = getKeyC(chat);
    list<Info>::iterator p = m_chats.table[chatKey].begin();
    while (p != m_chats.table[chatKey].end())
    {
        if (p->chat == chat)
	{
	    leave(p->user, chat);
            total += p->count;
            p = m_chats.table[chatKey].erase(p);
	}
	else
	    p++;
    }
    return total;
}

int ChatTrackerImpl::contribute(string user)
{
  unsigned int userKey = getKeyU(user);
    list<Info>::iterator p = m_users.table[userKey].end();
    while (p != m_users.table[userKey].begin())
    {
        p--;
        if (p->user == user)
        {
            p->count++;
	    return p->count;
        }
    }
    return 0;
}

int ChatTrackerImpl::leave(string user, string chat)
{
  unsigned int userKey = getKeyU(user);
  unsigned int chatKey = getKeyC(chat);;
  bool userFound = false;
  int count = 0;
    list<Info>::iterator q = m_users.table[userKey].end();
    while (q != m_users.table[userKey].begin())
      {
	q--;
	if(q->user == user && q->chat == chat)
	  {
	    count = q->count;
	    q = m_users.table[userKey].erase(q);
	    userFound = true;
	    break;
	  }
      }
    if(userFound)
      {
	list<Info>::iterator p = m_chats.table[chatKey].end();
	while(p != m_chats.table[chatKey].begin())
	  {
	    p--;
	    if(p->user == user && p->chat == chat)
	      {
		p->count += count;
		return count;
	      }
	  }
      }
    return -1;
}

int ChatTrackerImpl::leave(string user)
{
  unsigned int userKey = getKeyU(user);
  unsigned int chatKey;
  bool userFound = false;
  int count = 0;
    list<Info>::iterator q = m_users.table[userKey].end();
    while (q != m_users.table[userKey].begin())
      {
	q--;
	if(q->user == user)
	  {
	    count = q->count;
	    chatKey = getKeyC(q->chat);
	    q = m_users.table[userKey].erase(q);
	    userFound = true;
	    break;
	  }
      }
    if(userFound)
      {
	list<Info>::iterator p = m_chats.table[chatKey].end();
	while(p != m_chats.table[chatKey].begin())
	  {
	    p--;
	    if(p->user == user)
	      {
		p->count += count;
		return count;
	      }
	  }
      }
    return -1;
}

//*********** ChatTracker functions **************

// These functions simply delegate to ChatTrackerImpl's functions.
// You probably don't want to change any of this code.

ChatTracker::ChatTracker(int maxBuckets)
{
    m_impl = new ChatTrackerImpl(maxBuckets);
}

ChatTracker::~ChatTracker()
{
    delete m_impl;
}

void ChatTracker::join(string user, string chat)
{
    m_impl->join(user, chat);
}

int ChatTracker::terminate(string chat)
{
    return m_impl->terminate(chat);
}

int ChatTracker::contribute(string user)
{
    return m_impl->contribute(user);
}

int ChatTracker::leave(string user, string chat)
{
    return m_impl->leave(user, chat);
}

int ChatTracker::leave(string user)
{
    return m_impl->leave(user);
}
