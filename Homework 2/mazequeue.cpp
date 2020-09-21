#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
  Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
  int r() const
  {
    return m_row;
  }
  int c() const
  {
    return m_col;
  }
private:
  int m_row;
  int m_col;
};

bool pathExists(char maze[10][10], int sr, int sc, int er, int ec)
{
  queue<Coord> coordQueue;
  coordQueue.push(Coord(sr, sc));
  maze[sr][sc] = 'O';
  while(!coordQueue.empty())
    {
      Coord currentCell = coordQueue.front();
      coordQueue.pop();
      if(currentCell.r() == er && currentCell.c() == ec)
	{
	  return true;
	}
      if(maze[currentCell.r()+1][currentCell.c()] == '.')
	{
	  coordQueue.push(Coord(currentCell.r()+1, currentCell.c()));
	  maze[currentCell.r()+1][currentCell.c()] = 'O';
	}
      if(maze[currentCell.r()][currentCell.c()-1] == '.')
	{
	  coordQueue.push(Coord(currentCell.r(), currentCell.c()-1));
	  maze[currentCell.r()][currentCell.c()-1] = 'O';
	}
      if(maze[currentCell.r()-1][currentCell.c()] == '.')
	{
	  coordQueue.push(Coord(currentCell.r()-1, currentCell.c()));
	  maze[currentCell.r()-1][currentCell.c()] = 'O';
	}
      if(maze[currentCell.r()][currentCell.c()+1] == '.')
	{
	  coordQueue.push(Coord(currentCell.r(), currentCell.c()+1));
	  maze[currentCell.r()][currentCell.c()+1] = 'O';
	}
    }
  return false; 
}

int main()
{
            char maze[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','.','.','.','X','.','.','.','X' },
                { 'X','.','X','X','.','X','X','.','.','X' },
                { 'X','X','X','.','.','.','.','X','.','X' },
                { 'X','.','X','X','X','.','X','X','X','X' },
                { 'X','.','X','.','.','.','X','.','.','X' },
                { 'X','.','.','.','X','.','X','.','.','X' },
                { 'X','X','X','X','X','.','X','.','X','X' },
                { 'X','.','.','.','.','.','.','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
            };
        
            if (pathExists(maze, 3,5, 8,8))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
}
