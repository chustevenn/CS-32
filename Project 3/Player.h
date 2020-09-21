//
//  Player.h
//  cs32-p3
//
//  Created by Stephen Chu on 5/11/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include <string>
#include <list>
#include "GameObject.h"
#include "Monster.h"
using namespace std;

class Dungeon;

class Player
{
public:
    Player(Dungeon* dl, int r, int c);
    ~Player();
    Player& operator=(const Player& rhs);
    
    int row() const;
    int col() const;
    bool isDead() const;
    int dexterity() const;
    int armor() const;
    int hitpoints() const;
    int max_hitpoints() const;
    int strength() const;
    void takeDamage(int damage);
    string setWieldedWeapon(Weapon* wp);
    void setRow(int row);
    void setCol(int col);
    void setSleep(int sleep);
    string viewInventory(char action);
    string move(char dir);
    string attack(Monster* m);
    void setDungeon(Dungeon* d);
    bool won();
    
private:
    Dungeon* m_dungeon;
    list<GameObject*> m_inventory;
    Weapon* m_currentWeapon;
    int m_row;
    int m_col;
    int m_dexterity;
    int m_armor;
    int m_hitpoints;
    int m_maxHitpoints;
    int m_strength;
    int m_sleep;
    bool m_won;
};

#endif /* Player_h */
