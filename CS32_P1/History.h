//
//  History.h
//  Project 1
//
//  Created by Vignesh Balasundaram on 7/6/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "globals.h"

#ifndef History_h
#define History_h

class Arena;

class History
{
public:
    History(int nRows, int nCols);
    
    bool record(int r, int c);
    void display() const;
    
private:
    int     m_rows;
    int     m_cols;
    char    grid[MAXROWS][MAXCOLS];

};

#endif /* History_h */
