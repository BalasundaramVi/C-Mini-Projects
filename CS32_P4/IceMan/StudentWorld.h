//
//  StudentWorld.h
//  Project 4.1
//
//  Created by Vignesh Balasundaram on 8/8/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    
    //GIVEN
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    //ACCESSORS
    double CurrentTicks() {return curTicks;}
    ICEMAN* Iceman() {return m_Iceman;}
    ICE* Ice(int x, int y) {return m_Ice[x][y];}
    int numBoulders() {return boulders;}
    int numNuggets() {return nuggets;}
    int numBarrels() {return barrels;}
    int numSquirts() {return squirts;}
    int numSonar() {return sonar;}
    BASE* Actor(int n) {return m_Actors[n];}
    std::vector<BASE*> Actors() {return m_Actors;}
    
    //MUTATORS
    void setBoulders(int B) {boulders = B;}
    void setNuggets(int G) {nuggets = G;}
    void setBarrels(int O) {barrels = O;}
    void setSquirts(int Q) {squirts = Q;}
    void setSonar(int S) {sonar = S;}
    void setDisplayText();
    void fireSquirt(int direction);
    
    //HELPERS
    std::string FormatText(int level, int lives, int health, int squirts, int gold, int barrels, int sonar, int score);
    

private:
    double curTicks;
    
    std::vector<BASE*> m_Actors;
    ICEMAN* m_Iceman;
    ICE* m_Ice[64][60];
    
    int boulders;
    int barrels;
    int squirts;
    int nuggets;
    int sonar;
    
};

#endif // STUDENTWORLD_H_
