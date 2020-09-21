//
//  Monster.h
//  cs32-p3
//
//  Created by Stephen Chu on 5/16/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#ifndef Monster_h
#define Monster_h
#include <list>
#include <queue>
#include <string>
#include "GameObject.h"
using namespace std;

class Dungeon;

class Monster
{
public:
    Monster(Dungeon* dl, int row, int col, string name);
    virtual ~Monster();
    virtual string move();
    bool isDead() const;
    int row() const;
    int col() const;
    void setRow(int row);
    void setCol(int col);
    int dexterity() const;
    int armor() const;
    int hitpoints() const;
    int strength() const;
    Dungeon* dungeon() const;
    int dumbDistanceToPlayer();
    void dumbMove();
    void smartPath(int path[18][70], int r, int c, queue<int> rows, queue<int> cols);
    void takeDamage(int damage);
    int sleep();
    void setSleep(int sleep);
    virtual string attack();
    string name() const;
private:
    Dungeon* m_dungeon;
    Weapon* m_currentWeapon;
    int m_row;
    int m_col;
    int m_hitpoints;
    int m_armor;
    int m_dexterity;
    int m_strength;
    int m_sleep;
    string m_name;
};

class Goblin : public Monster
{
public:
    Goblin(Dungeon* dl, int row, int col, string name, int smellDistance);
    //~Goblin();
    string move();
private:
    int m_smellDistance;
};

class Snakewoman : public Monster
{
public:
    Snakewoman(Dungeon* dl, int row, int col, string name);
    string move();
};

class Bogeyman : public Monster
{
public:
    Bogeyman(Dungeon* dl, int row, int col, string name);
    string move();
};

class Dragon : public Monster
{
public:
    Dragon(Dungeon* dl, int row, int col, string name);
    //string move();
};
#endif /* Monster_h */
