//
//  StudentWorld.cpp
//  Project 4.1
//
//  Created by Vignesh Balasundaram on 8/8/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "StudentWorld.h"
#include <string>
#include "Actor.h"
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir)
{
    m_Iceman = NULL;
    for (int x=0; x < VIEW_WIDTH; x++)
    {
        for (int y=0; y < 60; y++)
        {
            m_Ice[x][y] = NULL;
        }
    }
    
    boulders = 0;
    nuggets = 0;
    barrels = 0;
    
    squirts = 5;
    sonar = 1;
    nuggets = 0;
}


StudentWorld::~StudentWorld()
{
    ICEMAN* temp = m_Iceman;
    m_Iceman = NULL;
    delete temp;
    
    for (int x=0; x < VIEW_WIDTH; x++)
    {
        for (int y=0; y < 60; y++)
        {
            ICE* temp = m_Ice[x][y];
            m_Ice[x][y] = NULL;
            delete temp;
        }
    }
}

int StudentWorld::init()
{
    curTicks = 0;
    
    m_Iceman = new ICEMAN(this);
    
    int level = getLevel();
    
    int boulders = min(level/2 + 2, 9);
    setBoulders(boulders);
    for (int i = 0; i < numBoulders();)
    {
        bool check = true;
        
        int randX = rand() % 61;
        int randY = rand() % 37 + 20;
        for (int j = 0; j < m_Actors.size(); j++)
        {
            int a = m_Actors[j]->getX();
            int b = m_Actors[j]->getY();
            double distance = sqrt((randX-a)*(randX-a)+(randY-b)*(randY-b));
            if (distance <= 6.00)
                check = false;
        }
        if (check==true)
        {
            BOULDER* B = new BOULDER(randX, randY, this);
            m_Actors.push_back(B);
            BCHECK* BC = new BCHECK(randX, randY);
            m_Iceman->BC.push_back(BC);
            i++;
        }
    }
    
    barrels = min(2 + level, 21);
    for (int i = 0; i < barrels;)
    {
        bool check = true;
        
        int randX = rand() % 61;
        int randY = rand() % 57;
        
        for (int j = 0; j < m_Actors.size(); j++)
        {
            int a = m_Actors[j]->getX();
            int b = m_Actors[j]->getY();
            double distance = sqrt((randX-a)*(randX-a)+(randY-b)*(randY-b));
            if (distance <= 6.00)
                check = false;
        }
        if (check==true)
        {
            BARREL* B = new BARREL(randX, randY, this);
            m_Actors.push_back(B);
            i++;
        }
    }
    
    nuggets = max(5 - level/2, 2);
    for (int i=0; i<nuggets;)
    {
        bool check = true;
        
        int randX = rand() % 61;
        int randY = rand() % 57;
        
        for (int j = 0; j < m_Actors.size(); j++)
        {
            int a = m_Actors[j]->getX();
            int b = m_Actors[j]->getY();
            double distance = sqrt((randX-a)*(randX-a)+(randY-b)*(randY-b));
            if (distance <= 6.00)
                check = false;
        }
        if (check==true)
        {
            NUGGET* N = new NUGGET(randX, randY, this, false);
            m_Actors.push_back(N);
            i++;
        }
    }


    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 60; y++)
        {
            if (x >= 30 && x < 34)
                m_Ice[x][y] = NULL;
            else
            {
                m_Ice[x][y] = new ICE(x, y, this);
            }
        }
    }
    
    for (int i = 0; i < m_Actors.size(); i++)
    {
        if (m_Actors[i]->getID() == IID_BOULDER)
        {
            int bX = m_Actors[i]->getX();
            int bY = m_Actors[i]->getY();
            
            for (int x = bX; x < (bX+4); x++)
            {
                for (int y = bY; y < (bY+4); y++)
                {
                    if (x >= 0 && x < VIEW_WIDTH && y >= 0 && y < 60)
                    {
                        ICE* temp = m_Ice[x][y];
                        m_Ice[x][y] = NULL;
                        delete temp;
                    }
                }
            }
        }
    }

    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    if (m_Iceman->alive() == false)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    curTicks++;
    
    setDisplayText();
    
    m_Iceman->doSomething();
    if (m_Iceman->getSquirt()!=0)
    {
        fireSquirt(m_Iceman->getSquirt());
    }
    
    
    if (m_Iceman->getEvent()!=0)
    {
        if (m_Iceman->getEvent()==1)
        {
            NUGGET* N = new NUGGET(m_Iceman->getX(), m_Iceman->getY(), this, true);
            setNuggets(numNuggets()-1);
            m_Actors.push_back(N);
        }
        else if (m_Iceman->getEvent()==2)
        {
            int IX = m_Iceman->getX()+2;
            int IY = m_Iceman->getY()+2;
            for (int i = 0; i < m_Actors.size(); i++)
            {
                if (m_Actors[i]->getID() == 5 || m_Actors[i]->getID() == 7)
                {
                    int aX = m_Actors[i]->getX()+2;
                    int aY = m_Actors[i]->getY()+2;
                    double radius = sqrt((IX-aX)*(IX-aX)+(IY-aY)*(IY-aY));
                    
                    if (radius < 12)
                        m_Actors[i]->setVisible(true);
                }
            }
            setSonar(numSonar()-1);
        }
    }
    
    for (int x = m_Iceman->getX(); x < m_Iceman->getX()+4; x++)
    {
        for (int y = m_Iceman->getY(); y < m_Iceman->getY()+4; y++)
        {
            if (m_Ice[x][y] != NULL && x < VIEW_WIDTH && x >= 0 && y < 60 && y >= 0)
            {
                ICE* temp = m_Ice[x][y];
                m_Ice[x][y] = NULL;
                delete temp;
                playSound(SOUND_DIG);
            }
        }
    }
    
    
    int G = getLevel()*25 + 300;
    int random = rand() % G;
    if (random == 0)
    {
        int r = rand() % 5;
        if (r==1)
        {
            SONAR* S = new SONAR(this);
            m_Actors.push_back(S);
        }
        else
        {
            bool check = true;
            int random = 0;
            int wX,wY;
            do
            {
                vector<int> X;
                vector<int> Y;
                for (int i = 0; i < VIEW_WIDTH; i++)
                {
                    for (int j = 0; j < VIEW_HEIGHT; j++)
                    {
                        if (m_Ice[i][j] == NULL)
                        {
                            if (m_Ice[i+3][j+3]==NULL)
                            {
                                X.push_back(i);
                                Y.push_back(j);
                            }
                        }
                    }
                }
                int s = X.size();
                random = rand()%s;
                wX = X[random];
                wY = Y[random];
                for (int i = wX; i < wX+4; i++)
                {
                    for (int j = wY; j < wY+4; j++)
                    {
                        if (m_Ice[i][j] != NULL)
                            check = false;
                    }
                }
            } while (check==false);
            if (check==true)
            {
                WATER* W = new WATER(wX, wY, this);
                m_Actors.push_back(W);
            }
        }
    }
    
    int x = rand()%100;
    if (x == 0)
    {
        PROTESTER* P = new PROTESTER(IID_PROTESTER, VIEW_WIDTH-5, VIEW_HEIGHT-1, this, 5);
        m_Actors.push_back(P);
    }
    
    int HX = rand()%150;
    if (HX == 0)
    {
        HPROTESTER* HP = new HPROTESTER(VIEW_WIDTH-5, VIEW_HEIGHT-1, this);
        m_Actors.push_back(HP);
    }
    
    for (int i = 0; i < m_Actors.size(); i++)
    {
        m_Actors[i]->doSomething();
        if (m_Actors[i]->alive() == false)
        {
            BASE* temp = m_Actors[i];
            if (i < numBoulders())
            {
                m_Iceman->BC.pop_back();
                setBoulders(numBoulders()-1);
            }
            m_Actors[i] = NULL;
            delete temp;
            m_Actors.erase(m_Actors.begin() + i);
        }
    }
    
    if(numBarrels()== 0)
    {
        return GWSTATUS_FINISHED_LEVEL;
    }
    else
        return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    ICEMAN* temp = m_Iceman;
    m_Iceman = NULL;
    delete temp;
    
    for (int i = 0; i < m_Actors.size(); i++)
    {
        BASE* temp = m_Actors[i];
        m_Actors[i] = NULL;
        delete temp;
    }
    m_Actors.clear();
    
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < 59; y++)
        {
            ICE* temp = m_Ice[x][y];
            m_Ice[x][y] = NULL;
            delete temp;
        }
    }
}

void StudentWorld::setDisplayText()
{
    int level = getLevel();
    int lives = getLives();
    int health = m_Iceman->getHealth();
    int squirts = numSquirts();
    int gold = numNuggets();
    int barrels = numBarrels();
    int sonar = numSonar();
    int score = getScore();
    
    string output = FormatText(level, lives, health, squirts, gold, barrels, sonar, score);
    setGameStatText(output);
}

string StudentWorld::FormatText(int level, int lives, int health, int squirts, int gold, int barrels, int sonar, int score)
{
    string display = "";
    
    display += "Lvl:";
    if (level < 10)
    {
        display += " ";
        display += (level + 48);
    }
    else
    {
        display += (level/10) + 48;
        level = level%10;
        display += level + 48;
    }
    
    display += "  Lives:";
    display += (lives+48);
    
    display += "  Health:";
    if (health < 10)
    {
        display += " ";
        display += health + 48;
        display += "0%";
    }
    else
    {
        display += "100%";
    }
    
    display += "  Wtr:";
    if (squirts < 10)
    {
        display += " ";
        display += (squirts + 48);
    }
    else
    {
        display += (squirts/10) + 48;
        squirts = squirts%10;
        display += squirts + 48;
    }
    
    display += "  Gld:";
    if (gold < 10)
    {
        display += " ";
        display += (gold + 48);
    }
    else
    {
        display += (gold/10) + 48;
        gold = gold%10;
        display += gold + 48;
    }
    
    display += "  Oil Left:";
    if (barrels < 10)
    {
        display += " ";
        display += (barrels + 48);
    }
    else
    {
        display += (barrels/10) + 48;
        barrels = barrels%10;
        display += barrels + 48;
    }
    
    display += "  Sonar:";
    if (sonar < 10)
    {
        display += " ";
        display += (sonar + 48);
    }
    else
    {
        display += (sonar/10) + 48;
        sonar = sonar%10;
        display += sonar + 48;
    }
    
    display += "  Scr:";
    int temp = score, count=0;
    while (temp > 0)
    {
        count++;
        temp = temp/10;
    }
    for (int i = 0; i < (6-count); i++)
        display+="0";
    for (int j = 0; j < count-1; j++)
    {
        display += to_string(score);
    }
    
    return display;
}

void StudentWorld::fireSquirt(int direction)
{
    if (direction == 0) {return;}
    int S = numSquirts();
    if (S > 0)
    {
        int D = direction;
        int x = m_Iceman->getX();
        int y = m_Iceman->getY();
        switch (D)
        {
            case 1:                 //UP
                if (m_Ice[x][y+4] == NULL && m_Iceman->BoulderCheck(x, y+4, ACTOR::up))
                {
                    SQUIRTS* temp = new SQUIRTS(x, y+4, this, ACTOR::up);
                    m_Actors.push_back(temp);
                }
                break;
            case 2:                 //DOWN
                if (m_Ice[x][y-4] == NULL && m_Iceman->BoulderCheck(x, y-4, ACTOR::down))
                {
                    SQUIRTS* temp = new SQUIRTS(x, y-4, this, ACTOR::down);
                    m_Actors.push_back(temp);
                }
                break;
            case 3:                 //LEFT
                if (m_Ice[x-4][y] == NULL && m_Iceman->BoulderCheck(x-4, y, ACTOR::left))
                {
                    SQUIRTS* temp = new SQUIRTS(x-4, y, this, ACTOR::left);
                    m_Actors.push_back(temp);
                }
                break;
            case 4:                 //RIGHT
                if (m_Ice[x+4][y] == NULL && m_Iceman->BoulderCheck(x+4, y, ACTOR::right))
                {
                    SQUIRTS* temp = new SQUIRTS(x+4, y, this, ACTOR::right);
                    m_Actors.push_back(temp);
                }
                break;
            default:
                break;
        }
        playSound(SOUND_PLAYER_SQUIRT);
        setSquirts(S-1);
    }
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
