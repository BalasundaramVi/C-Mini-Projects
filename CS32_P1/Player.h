//
//  Player.h
//  Project 1
//
//  Created by Vignesh Balasundaram on 7/6/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <string>
using namespace std;

#ifndef Player_h
#define Player_h

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
    
    int    computeDanger(int r, int c) const;
};


#endif /* Player_h */
