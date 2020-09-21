//
//  History.cpp
//  CS 32 Project 1
//
//  Created by Stephen Chu on 4/3/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include "globals.h"
#include "History.h"
using namespace std;

//constructor for the History object: creates a grid similar to that of the Arena object
History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for(int i = 0; i < m_rows; i++)
    {
        for(int j = 0; j < m_cols; j++)
        {
            m_grid[i][j] = 0;
        }
    }
}
//increments the grid datatype, which we are using to track the number of vials dropped at each
//grid location
bool History::record(int r, int c)
{
    if(r > m_rows || c > m_cols)
    {
        return false;
    }
    m_grid[r-1][c-1]++;
    return true;
}

void History::display() const
{
    //fill grid with dots and corresponding letters to number of vials dropped
    char vialStatus[MAXROWS][MAXCOLS];
    for(int i = 0; i < m_rows; i++)
    {
        for(int j = 0; j < m_cols; j++)
        {
            int numVials = m_grid[i][j];
            switch(numVials)
            {
                case 0:
                vialStatus[i][j] = '.';
                break;
                case 1:
                vialStatus[i][j] = 'A';
                break;
                case 2:
                vialStatus[i][j] = 'B';
                break;
                case 3:
                vialStatus[i][j] = 'C';
                break;
                case 4:
                vialStatus[i][j] = 'D';
                break;
                case 5:
                vialStatus[i][j] = 'E';
                break;
                case 6:
                vialStatus[i][j] = 'F';
                break;
                case 7:
                vialStatus[i][j] = 'G';
                break;
                case 8:
                vialStatus[i][j] = 'H';
                break;
                case 9:
                vialStatus[i][j] = 'I';
                break;
                case 10:
                vialStatus[i][j] = 'J';
                break;
                case 11:
                vialStatus[i][j] = 'K';
                break;
                case 12:
                vialStatus[i][j] = 'L';
                break;
                case 13:
                vialStatus[i][j] = 'M';
                break;
                case 14:
                vialStatus[i][j] = 'N';
                break;
                case 15:
                vialStatus[i][j] = 'O';
                break;
                case 16:
                vialStatus[i][j] = 'P';
                break;
                case 17:
                vialStatus[i][j] = 'Q';
                break;
                case 18:
                vialStatus[i][j] = 'R';
                break;
                case 19:
                vialStatus[i][j] = 'S';
                break;
                case 20:
                vialStatus[i][j] = 'T';
                break;
                case 21:
                vialStatus[i][j] = 'U';
                break;
                case 22:
                vialStatus[i][j] = 'V';
                break;
                case 23:
                vialStatus[i][j] = 'W';
                break;
                case 24:
                vialStatus[i][j] = 'X';
                break;
                case 25:
                vialStatus[i][j] = 'Y';
                break;
                default:
                vialStatus[i][j] = 'Z';
                break;
            }
        }
    }
    //print the grid
    clearScreen();
    for(int i = 0; i < m_rows; i++)
    {
        for(int j = 0; j < m_cols; j++)
        {
            cout << vialStatus[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
