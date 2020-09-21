//
//  Monster.cpp
//  cs32-p3
//
//  Created by Stephen Chu on 5/16/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <random>
#include "Dungeon.h"
#include "Monster.h"
#include "Player.h"
#include "GameObject.h"
#include "utilities.h"
using namespace std;

//Monster constructor, takes in the dungeon, position, and name, and assigns attributes according to the name
Monster::Monster(Dungeon* dl, int row, int col, string name) : m_dungeon(dl), m_row(row), m_col(col), m_name(name), m_sleep(0)
{
    if(name == "the Goblin")
    {
        m_hitpoints = randInt(15,20);
        Weapon* wp = new Weapon(0, 0, "short sword");
        m_currentWeapon = wp;
        m_strength = 3;
        m_dexterity = 1;
        m_armor = 1;
    }
    if(name == "the Snakewoman")
    {
        m_hitpoints = randInt(3,6);
        Weapon* wp = new Weapon(0, 0, "magic fangs of sleep");
        m_currentWeapon = wp;
        m_strength = 2;
        m_dexterity = 3;
        m_armor = 3;
    }
    if(name == "the Bogeyman")
    {
        m_hitpoints = randInt(5,10);
        Weapon* wp = new Weapon(0, 0, "short sword");
        m_currentWeapon = wp;
        m_strength = randInt(2,3);
        m_dexterity = randInt(2,3);
        m_armor = 2;
    }
    if(name == "the Dragon")
    {
        m_hitpoints = randInt(20,25);
        Weapon* wp = new Weapon(0, 0, "long sword");
        m_currentWeapon = wp;
        m_strength = 4;
        m_dexterity = 4;
        m_armor = 4;
    }
}

//Monster destructor
Monster::~Monster()
{
    delete m_currentWeapon;
}

//trivial getters and setters
int Monster::row() const
{
    return m_row;
}

int Monster::col() const
{
    return m_col;
}

void Monster::setRow(int row)
{
    m_row = row;
}

void Monster::setCol(int col)
{
    m_col = col;
}

int Monster::hitpoints() const
{
    return m_hitpoints;
}

int Monster::strength() const
{
    return m_strength;
}

int Monster::armor() const
{
    return m_armor;
}

int Monster::dexterity() const
{
    return m_dexterity;
}

void Monster::takeDamage(int damage)
{
    m_hitpoints -= damage;
}

bool Monster::isDead() const
{
    return m_hitpoints <= 0;
}

Dungeon* Monster::dungeon() const
{
    return m_dungeon;
}

string Monster::name() const
{
    return m_name;
}

int Monster::sleep()
{
    return m_sleep;
}

void Monster::setSleep(int sleep)
{
    m_sleep += sleep;
}

//compute the absolute distance to players, disregarding walls and other monsters
int Monster::dumbDistanceToPlayer()
{
    int dr = m_row - m_dungeon->player()->row();
    int dc = m_col - m_dungeon->player()->col();
    if(dr < 0)
        dr = -1*dr;
    if(dc < 0)
        dc = -1*dc;
    return dr+dc;
}

//compute the direction to move strictly closer to the player, disregarding walls and other monsters
void Monster::dumbMove()
{
    //check if player is on same row
    if(m_row == m_dungeon->player()->row())
    {
        if(m_col < m_dungeon->player()->col() && m_dungeon->getCellStatus(m_row,m_col+1) != WALL && !m_dungeon->hasMonster(m_row, m_col+1))
        {
            m_col++;
            return;
        }
        if(m_col > m_dungeon->player()->col() && m_dungeon->getCellStatus(m_row,m_col-1) != WALL && !m_dungeon->hasMonster(m_row, m_col-1))
        {
            m_col--;
            return;
        }
    }
    //check if player is on same column
    else if(m_col == m_dungeon->player()->col())
    {
        if(m_row < m_dungeon->player()->row() && m_dungeon->getCellStatus(m_row+1,m_col) != WALL && !m_dungeon->hasMonster(m_row+1, m_col))
        {
            m_row++;
            return;
        }
           
        if(m_row > m_dungeon->player()->row() && m_dungeon->getCellStatus(m_row-1,m_col) != WALL && !m_dungeon->hasMonster(m_row-1, m_col))
        {
            m_row--;
            return;
        }
    }
    //if neither same row nor column choose best direction to move based on if either direction is blocked
    //if neither is blocked, pick randomly
    else
    {
        int dirX = m_row > m_dungeon->player()->row() ? -1 : 1;
        int dirY = m_col > m_dungeon->player()->col() ? -1 : 1;
        if((m_dungeon->getCellStatus(m_row,m_col+dirY) != WALL && !m_dungeon->hasMonster(m_row, m_col+dirY)) && (m_dungeon->getCellStatus(m_row+dirX,m_col) == WALL || m_dungeon->hasMonster(m_row+dirX, m_col)))
        {
            m_col += dirY;
            return;
        }
        if((m_dungeon->getCellStatus(m_row,m_col+dirY) == WALL || m_dungeon->hasMonster(m_row, m_col+dirY)) && (m_dungeon->getCellStatus(m_row+dirX,m_col) != WALL && !m_dungeon->hasMonster(m_row+dirX, m_col)))
        {
            m_row += dirX;
            return;
        }
        if((m_dungeon->getCellStatus(m_row,m_col+dirY) != WALL && !m_dungeon->hasMonster(m_row, m_col+dirY)) && (m_dungeon->getCellStatus(m_row+dirX,m_col) != WALL && !m_dungeon->hasMonster(m_row+dirX, m_col)))
        {
            int choice = randInt(1,2);
            if(choice == 1)
                m_row += dirX;
            else
                m_col += dirY;
        }
    }
}

//base class monster's move. Only used by Dragon.
string Monster::move()
{
    string msg = "";
    if(m_sleep > 0)
    {
        m_sleep--;
        return msg;
    }
    //if the monster is one step away from the player, attack the player
    int r = m_dungeon->player()->row();
    int c = m_dungeon->player()->col();
    if((m_row+1 == r && m_col == c) || (m_row-1 == r && m_col == c) || (m_row == r && m_col+1 == c) || (m_row == r && m_col-1 == c))
        return attack();
    return msg;
}

//takes in the current weapon and target attributes and computes the effect according to the guidelines
string Monster::attack()
{
    string msg = "";
    int hit = 0;
    int attackerPoints = m_dexterity + m_currentWeapon->dexterityBonus();
    int defenderPoints = m_dungeon->player()->dexterity() + m_dungeon->player()->armor();
    if(randInt(1, attackerPoints) >= randInt(1, defenderPoints))
        hit = 1;
    if(hit == 0)
    {
        msg = m_name + " " + m_currentWeapon->attackAction() + " Player and misses.";
        return msg;
    }
    if(hit == 1)
    {
        int sleep = 0;
        int damagePoints = randInt(0, m_strength + m_currentWeapon->damageAmount() - 1);
        m_dungeon->player()->takeDamage(damagePoints);
        if(m_currentWeapon->name() == "magic fangs of sleep")
            sleep = randInt(1, 5);
        if(m_dungeon->player()->hitpoints() > 0 && sleep == 3)
        {
            m_dungeon->player()->setSleep(randInt(2,6));
            msg = m_name + " " + m_currentWeapon->attackAction() + " Player and hits, putting the Player to sleep.";
            return msg;
        }
        if(m_dungeon->player()->hitpoints() > 0)
        {
            msg = m_name + " " + m_currentWeapon->attackAction() + " Player and hits.";
            return msg;
        }
        if(m_dungeon->player()->hitpoints() <= 0)
            msg = m_name + " " + m_currentWeapon->attackAction() + " Player dealing a final blow.";
        return msg;
    }
    return msg;
}

//Goblin constructor
Goblin::Goblin(Dungeon* dl, int row, int col, string name, int smellDistance) : Monster(dl, row, col, name)
{
    m_smellDistance = smellDistance;
}

//Goblin move function, takes in recursive helper function smartMove()
string Goblin::move()
{
    Dungeon* m_dungeon = dungeon();
    string msg = "";
    if(sleep() > 0)
    {
        setSleep(-1);
        return msg;
    }
    //attack player if one step away
    if(dumbDistanceToPlayer() == 1)
        return attack();
    int path[18][70] = {};
    for(int i = 0; i < 18; i++)
        for(int j = 0; j < 70; j++)
            path[i][j] = 0;
    int arrayRow = row()-1;
    int arrayCol = col()-1;
    queue<int> rowVals;
    queue<int> colVals;
    //initialize path[][] to the number of steps needed to get to the player for each cell
    smartPath(path,m_dungeon->player()->row(), m_dungeon->player()->col(), rowVals, colVals);
    //if the number of steps to get to the player is less than smell distance, move such that the number of steps to get to the
    //Player decreases
    if(path[arrayRow][arrayCol] <= m_smellDistance)
    {
        if(path[arrayRow-1][arrayCol] <= path[arrayRow][arrayCol] && m_dungeon->canMoveTo(row()-1, col()))
        {
            setRow(row()-1);
            return msg;
        }
        if(path[arrayRow+1][arrayCol] <= path[arrayRow][arrayCol] && m_dungeon->canMoveTo(row()+1, col()))
        {
            setRow(row()+1);
            return msg;
        }
        if(path[arrayRow][arrayCol-1] <= path[arrayRow][arrayCol] && m_dungeon->canMoveTo(row(), col()-1))
        {
            setCol(col()-1);
            return msg;
        }
        if(path[arrayRow][arrayCol+1] <= path[arrayRow][arrayCol] && m_dungeon->canMoveTo(row(), col()+1))
        {
            setCol(col()+1);
            return msg;
        }
    }
    return msg;
}

//This is a recursive breadth first search function. Conduct a breadth first search starting from the Player's position to each
//accessaible cell on the map. Set the values of path[][] to be the number of steps needed to get to that cell from the Player for
//each cell.
void Monster::smartPath(int path[18][70], int r, int c, queue<int> rows, queue<int> cols)
{
    if(m_dungeon->getCellStatus(r+1, c) != WALL && path[r][c-1] == 0)
    {
        rows.push(r+1);
        cols.push(c);
        path[r][c-1] = path[r-1][c-1]+1;
    }
    if(m_dungeon->getCellStatus(r, c+1) != WALL && path[r-1][c] == 0)
    {
        rows.push(r);
        cols.push(c+1);
        path[r-1][c] = path[r-1][c-1]+1;
    }
    if(m_dungeon->getCellStatus(r-1, c) != WALL && path[r-2][c-1] == 0)
    {
        rows.push(r-1);
        cols.push(c);
        path[r-2][c-1] = path[r-1][c-1]+1;
    }
    if(m_dungeon->getCellStatus(r, c-1) != WALL && path[r-1][c-2] == 0)
    {
        rows.push(r);
        cols.push(c-1);
        path[r-1][c-2] = path[r-1][c-1]+1;
    }
    if(!rows.empty() && !cols.empty())
    {
        r = rows.front();
        c = cols.front();
        rows.pop();
        cols.pop();
        smartPath(path, r, c, rows, cols);
    }
}

//Snakewoman constructor
Snakewoman::Snakewoman(Dungeon* dl, int row, int col, string name) : Monster(dl, row, col, name)
{}

//Snakewoman move function, utilizing the dumbDistance and dumbMove functions
string Snakewoman::move()
{
    string msg = "";
    if(sleep() > 0)
    {
        setSleep(-1);
        return msg;
    }
    if(dumbDistanceToPlayer() == 1)
        return attack();
    if(dumbDistanceToPlayer() > 1  && dumbDistanceToPlayer() <= 3)
    {
        dumbMove();
    }
    return msg;
}

//Bogeyman constructor
Bogeyman::Bogeyman(Dungeon* dl, int row, int col, string name) : Monster(dl, row, col, name)
{}

//Bogeyman move function, utilizing the dumbDistance and dumbMove functions
string Bogeyman::move()
{
    string msg = "";
    if(sleep() > 0)
    {
        setSleep(-1);
        return msg;
    }
    if(dumbDistanceToPlayer() == 1)
        return attack();
    if(dumbDistanceToPlayer() > 1  && dumbDistanceToPlayer() <= 5)
    {
        dumbMove();
    }
    return msg;
}

//Dragon constructor. No dragon move function, it uses Monster's move function because it doesn't move
Dragon::Dragon(Dungeon* dl, int row, int col, string name) : Monster(dl, row, col, name)
{}

