//
//  Dungeon.cpp
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
#include "GameObject.h"
#include "utilities.h"
#include "Dungeon.h"
#include "Player.h"
#include "Monster.h"
using namespace std;

//Dungeon constructor
Dungeon::Dungeon(int level, int goblinSmellDistance): m_rows(18), m_cols(70), m_level(level), m_player(nullptr)
{
        //Set everything to be a wall
    
        for(int i = 1; i <= m_rows; i++)
        {
            for(int j = 1 ; j <= m_cols; j++)
            {
                setCellStatus(i, j, WALL);
            }
        }
        //Create 6 random rectangular rooms
        list<int> rectangleCoordinates;
        for(int i = 0; i < 6; i++)
        {
            int r, c, dr, dc;
            do{
                r = randInt(2, 10);
                c = randInt(2, 57);
                dr = randInt(4, 6);
                dc = randInt(6, 12);
            } while(getCellStatus(r-1, c-1) != WALL || getCellStatus(r+dr+1, c-1) != WALL || getCellStatus(r-1, c+dc+1) != WALL || getCellStatus(r+dr+1, c+dc+1) != WALL);
            for(int j = r; j <= r+dr; j++)
                for(int k = c; k <= c+dc; k++)
                {
                    setCellStatus(j, k, EMPTY);
                }
            rectangleCoordinates.push_back(r);
            rectangleCoordinates.push_back(c);
            rectangleCoordinates.push_back(dr);
            rectangleCoordinates.push_back(dc);
        }
        //Generate corridors to connect the rectangles
        int row, col, rowL, colL;
        for(list<int>::iterator p = rectangleCoordinates.begin(); p != rectangleCoordinates.end();)
        {
            row = *p;
            p++;
            col = *p;
            p++;
            rowL = *p;
            p++;
            colL = *p;
            p++;
            generateCorridors(row, col, rowL, colL);
        }
    
        //if it's the final level, generate a golden idol instead of stairs
        if(m_level < 4)
        {
            int r, c;
            do {
                r = randInt(1, 18);
                c = randInt(1, 70);
            } while (getCellStatus(r, c) != EMPTY);
            setCellStatus(r, c, STAIRS);
            m_endRow = r;
            m_endCol = c;
        }
        //generate stairs
        if(m_level == 4)
        {
            int r, c;
            do {
                r = randInt(1, 18);
                c = randInt(1, 70);
            } while (getCellStatus(r, c) != EMPTY);
            setCellStatus(r, c, GOLD);
            m_endRow = r;
            m_endCol = c;
        }
    //generate random items to be present on the dungeon floor
    for(int i = 0; i < 3; i++)
    {
        int type = randInt(1, 2);
        if(type == 1)
        {
            int r,c;
            do
            {
                r = randInt(1, 18);
                c = randInt(1, 70);
            } while(getCellStatus(r,c) != EMPTY);
            string scrollType[] = {"scroll of enhance health", "scroll of improve armor", "scroll of enhance dexterity", "scroll of raise strength"};
            int chooseType = randInt(0, 3);
            Scroll* sc = new Scroll(r, c, scrollType[chooseType]);
            m_items.push_back(sc);
            setCellStatus(r, c, SCROLL);
        }
        if(type == 2)
        {
            int r,c;
            do
            {
                r = randInt(1, 18);
                c = randInt(1, 70);
            } while(getCellStatus(r, c) != EMPTY);
            string weaponType[] = {"mace", "short sword", "long sword"};
            int chooseType = randInt(0, 2);
            Weapon* wp = new Weapon(r, c, weaponType[chooseType]);
            m_items.push_back(wp);
            setCellStatus(r, c, WEAPON);
        }
    }
    //generate monsters randomly, in accordance with the current level
    int numMonsters = randInt(2, 5*(level+1)+1);
    for(int i = 0; i < numMonsters; i++)
    {
        int type = 0;
        if(level < 2)
        {
            type = randInt(1,2);
            if(type == 1)
            {
                int r, c;
                do{
                    r = randInt(2,17);
                    c = randInt(2,69);
                } while(getCellStatus(r, c) != EMPTY);
                Goblin* gb = new Goblin(this, r, c, "the Goblin", goblinSmellDistance);
                m_monsters.push_back(gb);
            }
            if(type == 2)
            {
                int r, c;
                do{
                    r = randInt(2,17);
                    c = randInt(2,69);
                } while(getCellStatus(r, c) != EMPTY);
                Snakewoman* gb = new Snakewoman(this, r, c, "the Snakewoman");
                m_monsters.push_back(gb);
            }
        }
        if(level == 2)
        {
            type = randInt(1,3);
            if(type == 1)
            {
                int r, c;
                do{
                    r = randInt(2,17);
                    c = randInt(2,69);
                } while(getCellStatus(r, c) != EMPTY);
                Goblin* gb = new Goblin(this, r, c, "the Goblin", goblinSmellDistance);
                m_monsters.push_back(gb);
            }
            if(type == 2)
            {
                int r, c;
                do{
                    r = randInt(2,17);
                    c = randInt(2,69);
                } while(getCellStatus(r, c) != EMPTY);
                Snakewoman* sw = new Snakewoman(this, r, c, "the Snakewoman");
                m_monsters.push_back(sw);
            }
            if(type == 3)
            {
                int r, c;
                do{
                    r = randInt(2,17);
                    c = randInt(2,69);
                } while(getCellStatus(r, c) != EMPTY);
                Bogeyman* bg = new Bogeyman(this, r, c, "the Bogeyman");
                m_monsters.push_back(bg);
            }
        }
        if(level > 2)
               {
                   type = randInt(1,4);
                   if(type == 1)
                   {
                       int r, c;
                       do{
                           r = randInt(2,17);
                           c = randInt(2,69);
                       } while(getCellStatus(r, c) != EMPTY);
                       Goblin* gb = new Goblin(this, r, c, "the Goblin", goblinSmellDistance);
                       m_monsters.push_back(gb);
                   }
                   if(type == 2)
                   {
                       int r, c;
                       do{
                           r = randInt(2,17);
                           c = randInt(2,69);
                       } while(getCellStatus(r, c) != EMPTY);
                       Snakewoman* sw = new Snakewoman(this, r, c, "the Snakewoman");
                       m_monsters.push_back(sw);
                   }
                   if(type == 3)
                   {
                       int r, c;
                       do{
                           r = randInt(2,17);
                           c = randInt(2,69);
                       } while(getCellStatus(r, c) != EMPTY);
                       Bogeyman* bg = new Bogeyman(this, r, c, "the Bogeyman");
                       m_monsters.push_back(bg);
                   }
                   if(type == 4)
                   {
                       int r, c;
                       do{
                           r = randInt(2,17);
                           c = randInt(2,69);
                       } while(getCellStatus(r, c) != EMPTY);
                       Dragon* dg = new Dragon(this, r, c, "the Dragon");
                       m_monsters.push_back(dg);
                   }
               }
    }
    //initialize this data member for use later in the pathExists function
    for(int i = 0; i < 18; i++)
        for(int j = 0; j < 70; j++)
            m_visitStatus[i][j] = 0;
}

//Dungeon destructor, destroy all remaining items and monsters inside the dungeon
Dungeon::~Dungeon()
{
    for(list<GameObject*>::iterator p = m_items.begin(); p != m_items.end(); p++)
    {
        delete *p;
    }
    for(list<Monster*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
    {
        delete *p;
    }
}

//trivial getters and setters
int Dungeon::rows() const
{
    return m_rows;
}

int Dungeon::cols() const
{
    return m_cols;
}

int Dungeon::level() const
{
    return m_level;
}

Player* Dungeon::player() const
{
    return m_player;
}

int Dungeon::endCol() const
{
    return m_endCol;
}

int Dungeon::endRow() const
{
    return m_endRow;
}

void Dungeon::setPlayer(Player* p)
{
    m_player = p;
}

//Display the layout of the dungeon according to spec
void Dungeon::display(string msg)
{
    char displayGrid[18][70];
    int r, c;
    
    //depict walls with '#', and items accordingly
    for(r = 1; r <= rows(); r++)
        for(c = 1; c <= cols(); c++)
        {
            displayGrid[r-1][c-1] = (getCellStatus(r, c) == WALL ? '#' : ' ');
            if(getCellStatus(r, c) == STAIRS)
                displayGrid[r-1][c-1] = '>';
            if(getCellStatus(r, c) == GOLD)
                displayGrid[r-1][c-1] = '&';
            if(getCellStatus(r, c) == SCROLL)
                displayGrid[r-1][c-1] = '?';
            if(getCellStatus(r, c) == WEAPON)
                displayGrid[r-1][c-1] = ')';
        }
    //depict monsters
    for(list<Monster*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
    {
        int r = (*p)->row();
        int c = (*p)->col();
        if((*p)->name() == "the Goblin")
            displayGrid[r-1][c-1] = 'G';
        if((*p)->name() == "the Snakewoman")
            displayGrid[r-1][c-1] = 'S';
        if((*p)->name() == "the Bogeyman")
            displayGrid[r-1][c-1] = 'B';
        if((*p)->name() == "the Dragon")
            displayGrid[r-1][c-1] = 'D';
    }
    
    //indicate player's position
    if(m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = '@';
    
    clearScreen();
    //print out the grid
    for(r = 1; r <= rows(); r++)
    {
        for(c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << "Dungeon Level: " << level() << ", Hit points: " << m_player->hitpoints() << ", Armor: " << m_player->armor() << ", Strength: " << m_player->strength() << ", Dexterity: " << m_player->dexterity() << endl;
    //cout << endl;
    if(msg != "")
        cout << msg << endl;
}

//returns the object that is present on the dungeon floor at a given location, if any
GameObject* Dungeon::getObject(int r, int c)
{
    for(list<GameObject*>::iterator p = m_items.begin(); p != m_items.end(); p++)
    {
        if((*p)->row() == r && (*p)->col() == c)
        {
            GameObject* selectedItem = *p;
            m_items.erase(p);
            setCellStatus(r, c, EMPTY);
            return selectedItem;
        }
    }
    return nullptr;
}

//return the monster present in the dungeon at a given location, if any
Monster* Dungeon::getMonster(int r, int c)
{
    for(list<Monster*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
    {
        if((*p)->row() == r && (*p)->col() == c)
        {
            return *p;
        }
    }
    return nullptr;
}

//is there a monster at this specific location?
bool Dungeon::hasMonster(int r, int c)
{
    for(list<Monster*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
    {
        if((*p)->row() == r && (*p)->col() == c)
        {
            return true;
        }
    }
    return false;
}

//have the monsters take their move, and also check if any of them died due to the Player's move
string Dungeon::moveMonsters()
{
    string msg = "";
    list<Monster*>::iterator p = m_monsters.begin();
    while(p != m_monsters.end())
    {
        if((*p)->isDead())
        {
            Monster* dead = *p;
            p = m_monsters.erase(p);
            int r = dead->row();
            int c = dead->col();
            if(dead->name() == "the Goblin")
            {
                int dropAxe = randInt(1,3);
                if(dropAxe == 3 && getCellStatus(r, c) == EMPTY)
                {
                    Weapon* drop = new Weapon(r, c, "magic axe");
                    m_items.push_back(drop);
                    setCellStatus(r, c, WEAPON);
                }
            }
            if(dead->name() == "the Snakewoman")
            {
                int dropFangs = randInt(1,3);
                if(dropFangs == 3 && getCellStatus(r, c) == EMPTY)
                {
                    Weapon* drop = new Weapon(r, c, "magic fangs of sleep");
                    m_items.push_back(drop);
                    setCellStatus(r, c, WEAPON);
                }
            }
            if(dead->name() == "the Bogeyman")
            {
                int dropAxe = randInt(1,10);
                if(dropAxe == 3 && getCellStatus(r, c) == EMPTY)
                {
                    Weapon* drop = new Weapon(r, c, "magic axe");
                    m_items.push_back(drop);
                    setCellStatus(r, c, WEAPON);
                }
            }
            if(dead->name() == "the Dragon")
            {
                if(getCellStatus(r, c) == EMPTY)
                {
                    Scroll* drop = new Scroll(r, c, "scroll of teleportation");
                    m_items.push_back(drop);
                    setCellStatus(r, c, SCROLL);
                }
            }
            delete dead;
        }
        else
        {
            string monsterMessage = (*p)->move();
            if(monsterMessage != "")
            {
                msg += "\n" + monsterMessage;
            }
            p++;
        }
    }
    return msg;
}

//check if the Player or a Monster can move to this cell
bool Dungeon::canMoveTo(int r, int c)
{
    bool isAvailableCell = getCellStatus(r, c) != WALL && !hasMonster(r, c);
    return isAvailableCell;
}

//return what is at the cell
int Dungeon::getCellStatus(int r, int c) const
{
    return m_grid[r-1][c-1];
}

//change what is at the cell
void Dungeon::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Dungeon::setCellStatus");
    m_grid[r-1][c-1] = status;
}

//add a player to the dungeon
bool Dungeon::addPlayer(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    m_player = new Player(this, r, c);
    return true;
}


bool Dungeon::isPosInBounds(int r, int c) const
{
    return (r >= 0  &&  r <= m_rows  &&  c >= 0  &&  c <= m_cols);
}

void Dungeon::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid level position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

//generates corridors to connect the rooms of the dungeon
void Dungeon::generateCorridors(int r, int c, int dr, int dc)
{
    //Check for rectangle to left
    int rowLeft = (r+(r+dr))/2;
    int colLeft = c-1;
    bool pathLeftExists = false;
    while(colLeft > 1)
    {
        if(getCellStatus(rowLeft, colLeft) == EMPTY)
        {
            pathLeftExists = true;
            break;
        }
        colLeft--;
    }
    //Create corridor to left
    if(pathLeftExists)
    {
        colLeft = c-1;
        while(getCellStatus(rowLeft, colLeft) != EMPTY)
        {
            setCellStatus(rowLeft, colLeft, EMPTY);
            colLeft--;
        }
    }
    //Check for rectangle to right
    int rowRight = (r+(r+dr))/2;
    int colRight = c+dc+1;
    bool pathRightExists = false;
    while(colRight < 70)
    {
        if(getCellStatus(rowRight, colRight) == EMPTY)
        {
            pathRightExists = true;
            break;
        }
        colRight++;
    }
    //Create corridor to right
    if(pathRightExists)
    {
        colRight = c+dc+1;
        while(getCellStatus(rowRight, colRight) != EMPTY)
        {
            setCellStatus(rowRight, colRight, EMPTY);
            colRight++;
        }
    }
    //check for rectangle above
    int rowAbove = r-1;
    int colAbove = (c+(c+dc))/2;
    bool pathAboveExists = false;
    while(rowAbove > 1)
    {
        if(getCellStatus(rowAbove, colAbove) == EMPTY)
        {
            pathAboveExists = true;
            break;
        }
        rowAbove--;
    }
    //Create corridor above
    if(pathAboveExists)
    {
        rowAbove = r-1;
        while(getCellStatus(rowAbove, colAbove) != EMPTY)
        {
            setCellStatus(rowAbove, colAbove, EMPTY);
            rowAbove--;
        }
    }
    //check for rectangle below
    int rowBelow = r+dr+1;
    int colBelow = (c+(c+dc))/2;
    bool pathBelowExists = false;
    while(rowBelow < 18)
    {
        if(getCellStatus(rowBelow, colBelow) == EMPTY)
        {
            pathBelowExists = true;
            break;
        }
        rowBelow++;
    }
    //Create corridor below
    if(pathBelowExists)
    {
        rowBelow = r+dr+1;
        while(getCellStatus(rowBelow, colBelow) != EMPTY)
        {
            setCellStatus(rowBelow, colBelow, EMPTY);
            rowBelow++;
        }
    }
}

//conducts a recursive depth first search to find out if the endpoint of the level (be it stairs or the golden idol) is
//reachable from the player's position
bool Dungeon::pathExists(int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
        return true;
    if(getCellStatus(sr, sc) == WALL)
        return false;
    m_visitStatus[sr-1][sc-1] = 1;
    if(getCellStatus(sr+1, sc) != WALL && m_visitStatus[sr][sc-1] != 1 && pathExists(sr+1, sc, er, ec))
        return true;
    if(getCellStatus(sr, sc+1) != WALL && m_visitStatus[sr-1][sc] != 1 && pathExists(sr, sc+1, er, ec))
        return true;
    if(getCellStatus(sr-1, sc) != WALL && m_visitStatus[sr-2][sc-1] != 1 && pathExists(sr-1, sc, er, ec))
        return true;
    if(getCellStatus(sr, sc-1) != WALL && m_visitStatus[sr-1][sc-2] != 1 && pathExists(sr, sc-1, er, ec))
        return true;
    return false;
}
