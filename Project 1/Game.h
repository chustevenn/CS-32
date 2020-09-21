//
//  Game.h
//  CS 32 Project 1
//
//  Created by Stephen Chu on 4/3/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <stdio.h>
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};

#endif /* Game_h */
