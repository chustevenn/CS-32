// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Player.h"
#include "Dungeon.h"
#include <iostream>
#include <string>
using namespace std;

// Implement these and other Game member functions you may have added.

//Game constructor
Game::Game(int goblinSmellDistance)
{
    //conditional loop to ensure that there exists a path between the player and the end of the level, be it the idol or stairs
    bool pathExists = false;
    while (!pathExists)
    {
        int level = 0;
        m_goblinSmellDistance = goblinSmellDistance;
        int rPlayer;
        int cPlayer;
        m_dungeon = new Dungeon(level, goblinSmellDistance);
        rPlayer = randInt(2, 17);
        cPlayer = randInt(2, 69);
        if(m_dungeon->pathExists(rPlayer,cPlayer,m_dungeon->endRow(), m_dungeon->endCol()) && m_dungeon->getCellStatus(rPlayer, cPlayer) == EMPTY && !m_dungeon->hasMonster(rPlayer, cPlayer))
        {
            pathExists = true;
        }
        else
        {
            Dungeon* tempDungeon = m_dungeon;
            delete tempDungeon;
            continue;
        }
        m_dungeon->addPlayer(rPlayer, cPlayer);
    }
}

// Game destructor
Game::~Game()
{
    delete m_dungeon;
}

// player turn function
string Game::takePlayerTurn()
{
    Player* player = m_dungeon->player();
    for(;;)
    {
        //takes the player's keyboard input
        char ch = getCharacter();
        //generate a new level if the player goes down stairs, same conditions as initial level applied
        if(ch == '>' && m_dungeon->getCellStatus(player->row(), player->col()) == STAIRS)
        {
            int level = m_dungeon->level();
            Dungeon* tempDungeon = m_dungeon;
            bool pathExists = false;
            while (!pathExists)
            {
                int rPlayer;
                int cPlayer;
                m_dungeon = new Dungeon(level+1, m_goblinSmellDistance);
                rPlayer = randInt(2, 17);
                cPlayer = randInt(2, 69);
                if(m_dungeon->pathExists(rPlayer,cPlayer,m_dungeon->endRow(), m_dungeon->endCol()) && m_dungeon->getCellStatus(rPlayer, cPlayer) == EMPTY && !m_dungeon->hasMonster(rPlayer, cPlayer))
                {
                    pathExists = true;
                    player->setRow(rPlayer);
                    player->setCol(cPlayer);
                }
                else
                {
                    Dungeon* tempDungeon = m_dungeon;
                    delete tempDungeon;
                    continue;
                }
            }
            delete tempDungeon;
            //set the same player onto a new level
            player->setDungeon(m_dungeon);
            m_dungeon->setPlayer(player);
        }
        //display the inventory if the proper characters are entered
        if(ch == 'w' || ch == 'i' || ch == 'r')
            return player->viewInventory(ch);
        //all other characters enter the move function
        return player->move(ch);
    }
}

void Game::play()
{
    m_dungeon->display("");
    Player* player = m_dungeon->player();
    //keep running the game until the player is dead or has won
    while (!player->isDead() && !player->won())
    {
        string msg = takePlayerTurn();
        msg += m_dungeon->moveMonsters();
        m_dungeon->display(msg);
    }
    delete player;
    cout << "Press q to exit game." << endl;
    while(getCharacter() != 'q')
        ;
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
