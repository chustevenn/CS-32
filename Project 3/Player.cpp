//
//  Player.cpp
//  cs32-p3
//
//  Created by Stephen Chu on 5/11/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <list>
#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"
using namespace std;

//Player constructor. Initialize player's inventory and current weapon to be a short sword.
Player::Player(Dungeon* dl, int r, int c) : m_dungeon(dl), m_row(r), m_col(c), m_hitpoints(20), m_maxHitpoints(20), m_armor(2), m_strength(2), m_dexterity(2), m_won(false), m_sleep(0)
{
    Weapon* wp = new Weapon(0, 0, "short sword");
    m_inventory.push_back(wp);
    m_currentWeapon = wp;
}

//Player destructor. Destroy player, and all of the items in its inventory
Player::~Player()
{
    for(list<GameObject*>::iterator p = m_inventory.begin(); p != m_inventory.end(); p++)
    {
        delete *p;
    }
}

//Player assignment operator
Player& Player::operator=(const Player& rhs)
{
    if(this != &rhs)
    {
        m_hitpoints = rhs.m_hitpoints;
        m_armor = rhs.m_hitpoints;
        m_strength = rhs.m_strength;
        m_dexterity = rhs.m_dexterity;
    }
    return *this;
}

//trivial getters and setters
int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::dexterity() const
{
    return m_dexterity;
}

int Player::armor() const
{
    return m_armor;
}

int Player::hitpoints() const
{
    return m_hitpoints;
}

int Player::max_hitpoints() const
{
    return m_maxHitpoints;
}

int Player::strength() const
{
    return m_strength;
}

void Player::setRow(int row)
{
    m_row = row;
}

void Player::setCol(int col)
{
    m_col = col;
}

void Player::takeDamage(int damage)
{
    m_hitpoints -= damage;
}

void Player::setSleep(int sleep)
{
    m_sleep += sleep;
}

//Player move function. Takes in the getCharacter() and utilizes a switch statement for proper response
string Player::move(char dir)
{
    //do nothing if asleep
    string msg = "";
    if(m_sleep > 0)
    {
        m_sleep--;
        return msg;
    }
    //1 in 10 chance of regenerating a hitpoint
    int regen = randInt(1,10);
    if(regen == 5)
    {
        if(m_hitpoints < m_maxHitpoints)
            m_hitpoints++;
    }
    //handle input cases
    switch(dir)
    {
        //move in direction requested if possible. If there is a monster in that direction, attack that monster instead of moving.
        case ARROW_UP:
            if(m_dungeon->hasMonster(m_row-1, m_col))
            {
                Monster* attackMonster = m_dungeon->getMonster(m_row-1, m_col);
                return attack(attackMonster);
            }
            if(m_dungeon->getCellStatus(m_row-1, m_col) != WALL)
                m_row--;
            break;
        case ARROW_DOWN:
            if(m_dungeon->hasMonster(m_row+1, m_col))
            {
                Monster* attackMonster = m_dungeon->getMonster(m_row+1, m_col);
                return attack(attackMonster);
            }
            if(m_dungeon->getCellStatus(m_row+1, m_col) != WALL)
                m_row++;
            break;
        case ARROW_RIGHT:
            if(m_dungeon->hasMonster(m_row, m_col+1))
            {
                Monster* attackMonster = m_dungeon->getMonster(m_row, m_col+1);
                return attack(attackMonster);
            }
            if(m_dungeon->getCellStatus(m_row, m_col+1) != WALL)
                m_col++;
            break;
        case ARROW_LEFT:
            if(m_dungeon->hasMonster(m_row, m_col-1))
            {
                Monster* attackMonster = m_dungeon->getMonster(m_row, m_col-1);
                return attack(attackMonster);
            }
            if(m_dungeon->getCellStatus(m_row, m_col-1) != WALL)
                m_col--;
            break;
            //cheat functionality as requested by spec
        case 'c':
            m_maxHitpoints = 50;
            m_hitpoints = 50;
            m_strength = 9;
            break;
            //pick up an item present in the cell
        case 'g':
            if(m_dungeon->getCellStatus(m_row, m_col) == GOLD)
            {
                msg += "You pick up the golden idol\nCongratulations, you won!";
                m_won = true;
            }
            if(m_dungeon->getCellStatus(m_row, m_col) == SCROLL)
            {
                if(m_inventory.size() >= 25)
                {
                    msg += "Your knapsack is full; you can't pick that up.";
                    return msg;
                }
                GameObject* pickScroll = m_dungeon->getObject(m_row, m_col);
                m_inventory.push_back(pickScroll);
                string message = "You pick up a " + pickScroll->name();
                msg += message;
            }
            if(m_dungeon->getCellStatus(m_row, m_col) == WEAPON)
            {
                if(m_inventory.size() >= 25)
                {
                    msg += "Your knapsack is full; you cant pick that up.";
                    return msg;
                }
                GameObject* pickWeapon = m_dungeon->getObject(m_row, m_col);
                m_inventory.push_back(pickWeapon);
                string message = "You pick up " + pickWeapon->name();
                msg += message;
            }
            break;
    }
    return msg;
}

//view inventory function
string Player::viewInventory(char action)
{
    clearScreen();
    string msg = "";
    cout << "Inventory: " << endl;
    char index = 'a';
    for(list<GameObject*>::iterator p = m_inventory.begin(); p != m_inventory.end(); p++)
    {
        cout << " " << index++ << ". " << (*p)->name() << endl;
    }
    char select = getCharacter();
    //if the player wants to read a scroll
    if(select >= 'a' && select < index && !m_inventory.empty() && action == 'r')
    {
        //get the item indicated by the player's input
        list<GameObject*>::iterator p = m_inventory.begin();
        char track = 'a';
        while(track != select)
        {
            track++;
            p++;
        }
        GameObject* selectedItem = *p;
        //cast item to scroll type and apply its corresponding effect
        Scroll* useScroll = dynamic_cast<Scroll*>(selectedItem);
        if(useScroll != nullptr)
        {
            string effect = useScroll->read();
            if(effect == "heal")
            {
                int increase = randInt(3, 8);
                m_maxHitpoints += increase;
                msg += "You feel your heart beating stronger.";
            }
            if(effect == "armor")
            {
                int increase = randInt(1, 3);
                m_armor += increase;
                msg += "Your armor glows blue.";
            }
            if(effect == "dexterity")
            {
                m_dexterity++;
                msg += "You feel like less of a klutz.";
            }
            if(effect == "strength")
            {
                int increase = randInt(1, 3);
                m_strength += increase;
                msg += "Your muscles bulge.";
            }
            if(effect == "teleportation")
            {
                int r,c;
                do{
                    r = randInt(2,17);
                    c = randInt(2,69);
                } while(m_dungeon->getCellStatus(r, c) != EMPTY);
                m_row = r;
                m_col = c;
                msg += "You feel your body wrenched in space and time";
            }
        }
        m_inventory.erase(p);
        delete selectedItem;
    }
    //if the player wants to wield a different weapon
    if(select >= 'a' && select < index && !m_inventory.empty() && action == 'w')
    {
        //get item indicated by player input
        list<GameObject*>::iterator p = m_inventory.begin();
        char track = 'a';
        while(track != select)
        {
            track++;
            p++;
        }
        GameObject* selectedItem = *p;
        //cast the item to weapon type and set to Player's current weapon.
        Weapon* wieldWeapon = dynamic_cast<Weapon*>(selectedItem);
        if(wieldWeapon != nullptr)
        {
            string changeWeapon = setWieldedWeapon(wieldWeapon);
            msg += changeWeapon;
        }
    }
    return msg;
}

//Attacks the monster present in the direction specified by player input. Computes effect on target based on guidelines and the
//current weapon equipped
string Player::attack(Monster* m)
{
    string msg = "";
    int hit = 0;
    int attackerPoints = m_dexterity + m_currentWeapon->dexterityBonus();
    int defenderPoints = m->dexterity() + m->armor();
    if(randInt(1, attackerPoints) >= randInt(1, defenderPoints))
        hit = 1;
    if(hit == 0)
    {
        msg = "Player " + m_currentWeapon->attackAction() + " " + m->name() + " and misses.";
        return msg;
    }
    if(hit == 1)
    {
        int sleep = 0;
        int damagePoints = randInt(0, m_strength + m_currentWeapon->damageAmount() - 1);
        m->takeDamage(damagePoints);
        if(m_currentWeapon->name() == "magic fangs of sleep")
            sleep = randInt(1, 5);
        if(m->hitpoints() > 0 && sleep == 5)
        {
            m->setSleep(randInt(2,6));
            msg = "Player " + m_currentWeapon->attackAction() + " " + m->name() + " and hits, putting " + m->name() + " to sleep.";
            return msg;
        }
        if(m->hitpoints() > 0)
        {
            msg = "Player " + m_currentWeapon->attackAction() + " " + m->name() + " and hits.";
            return msg;
        }
        if(m->hitpoints() <= 0)
            msg = "Player " + m_currentWeapon->attackAction() + " " + m->name() + " dealing a final blow.";
        return msg;
    }
    return msg;
}

//set the Player's wielded weapon to a different weapon
string Player::setWieldedWeapon(Weapon* wp)
{
    m_currentWeapon = wp;
    string msg = "You are wielding " + wp->name();
    return msg;
}

//trivial getters and setters
bool Player::isDead() const
{
    return m_hitpoints <= 0;
}

void Player::setDungeon(Dungeon* d)
{
    m_dungeon = d;
}

bool Player::won()
{
    return m_won;
}
