//
//  History.cpp
//  Project 1
//
//  Created by Vignesh Balasundaram on 7/6/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "History.h"
#include <iostream>
#include "Arena.h"
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    int r, c;
    // Fill the grid with dots
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
            grid[r][c] = '.';
}

bool History::record(int r, int c)
{
    if (r > m_rows || r <= 0)
        return false;
    if (c > m_cols || r <= 0)
        return false;
    
    if (grid[r-1][c-1] == '.')
        grid[r-1][c-1] = 'A';
    else if (grid[r-1][c-1] >= 'A' && grid[r-1][c-1] < 'Z')
        grid[r-1][c-1] = grid[r-1][c-1] + 1;
    else
        return true;
    
    return true;
}

void History::display() const
{
    clearScreen();
    
    for (int i=0; i<m_rows; i++)
    {
        for (int j=0; j< m_cols; j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
