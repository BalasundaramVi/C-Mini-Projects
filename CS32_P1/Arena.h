//
//  Arena.h
//  Project 1
//
//  Created by Vignesh Balasundaram on 7/6/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "globals.h"
#include "History.h"
#include <string>
using namespace std;

#ifndef Arena_h
#define Arena_h

class Player;
class Robot;

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(string msg) const;
    History& history();
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
    History m_History;
};

#endif /* Arena_h */
