//
//  Vampire.h
//  CS 32 Project 1
//
//  Created by Stephen Chu on 4/3/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#ifndef Vampire_h
#define Vampire_h
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

class Arena;

class Vampire
{
  public:
      // Constructor
    Vampire(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif /* Vampire_h */
