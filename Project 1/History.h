//
//  History.h
//  CS 32 Project 1
//
//  Created by Stephen Chu on 4/3/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int m_grid[MAXROWS][MAXCOLS];
};

#endif /* History_h */
