//
//  Dungeon.h
//  cs32-p3
//
//  Created by Stephen Chu on 5/11/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#ifndef Dungeon_h
#define Dungeon_h
#include <string>
#include <list>
#include "GameObject.h"
#include "Monster.h"
using namespace std;

class Player;
class Monster;

class Dungeon
{
public:
    Dungeon(int level, int goblinSmellDistance);
    ~Dungeon();
    
    int rows() const;
    int cols() const;
    Player* player() const;
    void display(string msg);
    int getCellStatus(int r, int c) const;
    int level() const;
    int endRow() const;
    int endCol() const;
    bool hasMonster(int r, int c);
    bool canMoveTo(int r, int c);
    void setPlayer(Player* p);
    bool addPlayer(int r, int c);
    void setCellStatus(int r, int c, int status);
    GameObject* getObject(int r, int c);
    Monster* getMonster(int r, int c);
    string moveMonsters();
    void generateCorridors(int r, int c, int dr, int dc);
    bool pathExists(int sr, int sc, int er, int ec);
    
private:
    int m_grid[18][70];
    int m_visitStatus[18][70];
    list<GameObject*> m_items;
    list<Monster*> m_monsters;
    int m_rows;
    int m_cols;
    int m_level;
    int m_endRow;
    int m_endCol;
    Player* m_player;
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

#endif /* Dungeon_h */
