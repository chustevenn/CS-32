// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include <string>
using namespace std;
// You may add data members and other member functions to this class.
class Dungeon;

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
private:
    Dungeon* m_dungeon;
    string takePlayerTurn();
    int m_goblinSmellDistance;
};

#endif // GAME_INCLUDED
