//
//  Actor.cpp
//  Project 4.1
//
//  Created by Vignesh Balasundaram on 8/8/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

BASE::BASE(int id, int x, int y, StudentWorld* s_world, Direction dir, double size, int depth) : GraphObject(id, x, y, dir, size, depth)
{
    m_world = s_world;
    setVisible(true);
    ID = id;
    state = true;
}

BASE::~BASE()
{
    //MUST GET RID OF OBJECT
}

bool BASE::BoulderCheck(int a, int b, Direction dir)
{    
    int IX = a + 2;
    int IY = b + 2;
    for (int i = 0; i < world()->numBoulders(); i++)
    {
        int bX = world()->Actors()[i]->getX() + 2;
        int bY = world()->Actors()[i]->getY() + 2;
        
        double radius = sqrt((IX-bX)*(IX-bX)+(IY-bY)*(IY-bY));
        if (radius<=3)
            return false;
    }
    return true;
}

ACTOR::ACTOR(int ID, int x, int y, StudentWorld* m_world, Direction dir, double size, int depth, int hp) : BASE(ID, x, y, m_world, dir, size, depth)
{
    m_health = hp;
}

ACTOR::~ACTOR()
{
    //FILL THIS IN
}

void ACTOR::setHealth(int hp)
{
    m_health = hp;
    if (m_health <= 0)
    {
        setStatus(false);
    }
}


ICE::ICE(int x, int y, StudentWorld* m_world) : BASE(IID_ICE, x, y, m_world, right, 0.25, 3)
{
    setVisible(true);
}

ICE::~ICE() {};


void ICE::doSomething() {return;}


ICEMAN::ICEMAN(StudentWorld* s_world) : ACTOR(IID_PLAYER, 30, 60, s_world, right, 1.0, 0, 10)
{
    setVisible(true);
}

ICEMAN::~ICEMAN() {};

void ICEMAN::doSomething()
{
    if (!alive())
        return;
    
    setSquirt(0);
    setEVENT(0);
    setMove(0);
    
    world()->getKey(move);
    switch (move)
    {
        case 1002 :                            //UP
            if (getDirection() == up && getY()+3 < VIEW_HEIGHT-1)
            {
                if (BoulderCheck(getX(), getY()+1, up))
                    moveTo(getX(), getY()+1);
                else
                    moveTo(getX(), getY());
            }
            else
                setDirection(up);
            break;
        case 1003 :                        //DOWN
            if (getDirection() == down && getY() > 0)
            {
                if (BoulderCheck(getX(), getY()-1, down))
                    moveTo(getX(), getY()-1);
                else
                    moveTo(getX(), getY());
            }
            else
                setDirection(down);
            break;
        case 1000 :                        //LEFT
            if (getDirection() == left && getX() > 0)
            {
                if (BoulderCheck(getX()-1, getY(), left))
                    moveTo(getX()-1, getY());
                else
                    moveTo(getX(), getY());
            }
            else
                setDirection(left);
            break;
        case 1001 :                        //RIGHT
            if (getDirection() == right && getX() + 3 < VIEW_WIDTH-1)
            {
                if (BoulderCheck(getX()+1, getY(), right))
                    moveTo(getX()+1, getY());
                else
                    moveTo(getX(), getY());
            }
            else
                setDirection(right);
            break;
        case ' ' :                          //SPACE
            if (move== ' ')
            {
                int d = getDirection();
                if (d==up) {setSquirt(1);}
                else if (d==down) {setSquirt(2);}
                else if (d==left) {setSquirt(3);}
                else if (d==right) {setSquirt(4);}
            }
            break;
        case '\x1b':                        //ESCAPE
            setStatus(false);
            setHealth(0);
            return;
        case '\t' :                         //TAB
            if (world()->numNuggets()>0)
            {
                setEVENT(1);
            }
            break;
        case 'Z':                           //Z
        case 'z':
            if (world()->numSonar()>0)
            {
                setEVENT(2);
            }
            break;
        default :
            break;
    }
    return;
}

///////////////////////////////////////////////////////////
/////   (3) REGULAR PROTESTOR CLASS     ///////////////////
///////////////////////////////////////////////////////////

PROTESTER::PROTESTER(int ID, int x, int y, StudentWorld* m_world, int hp) : ACTOR(ID, x, y, m_world, left, 1, 0, hp)
{
    walk = rand()%53 + 8;
    setVisible(true);
}

void PROTESTER::doSomething()
{
    if (!alive())
    {
        return;
    }
    
    for (int i = 0; i < walk; i++)
    {
        moveTo(getX(), getY()-1);
    }
    setWalk(0);
    
    int W = rand()%4;
    switch (W)
    {
        case 0:
            if (world()->Ice(getX(), getY()+1) == NULL && BoulderCheck(getX(), getY()+1, up))
            {
                moveTo(getX(), getY()+1);
            }
            break;
        case 1:
            if (world()->Ice(getX(), getY()-1) == NULL && BoulderCheck(getX(), getY()-1, down))
            {
                moveTo(getX(), getY()-1);
            }
            break;
        case 2:
            if (world()->Ice(getX()-1, getY()) == NULL && BoulderCheck(getX()-1, getY(), left))
            {
                moveTo(getX()-1, getY());
            }
            break;
        case 3:
            if (world()->Ice(getX()+1, getY()) == NULL && BoulderCheck(getX()+1, getY(), right))
            {
                moveTo(getX()+1, getY());
            }
            break;
        default:
            break;
    }
}


///////////////////////////////////////////////////////////
/////   (3) HARDCORE PROTESTOR CLASS    ///////////////////
///////////////////////////////////////////////////////////

HPROTESTER::HPROTESTER(int x, int y, StudentWorld* m_world) : PROTESTER(2, x, y, m_world, 20)
{
    int random = rand()%53 + 8;
    setWalk(random);
    setVisible(true);
}

void HPROTESTER::doSomething()
{
    if (!alive())
    {
        return;
    }
    
    for (int i = 0; i < getWalk(); i++)
    {
        moveTo(getX(), getY()-1);
    }
    setWalk(0);
    
    int W = rand()%4;
    switch (W)
    {
        case 0:
            if (world()->Ice(getX(), getY()+1) == NULL && BoulderCheck(getX(), getY()+1, up))
            {
                moveTo(getX(), getY()+1);
            }
            break;
        case 1:
            if (world()->Ice(getX(), getY()-1) == NULL && BoulderCheck(getX(), getY()-1, down))
            {
                moveTo(getX(), getY()-1);
            }
            break;
        case 2:
            if (world()->Ice(getX()-1, getY()) == NULL && BoulderCheck(getX()-1, getY(), left))
            {
                moveTo(getX()-1, getY());
            }
            break;
        case 3:
            if (world()->Ice(getX()+1, getY()) == NULL && BoulderCheck(getX()+1, getY(), right))
            {
                moveTo(getX()+1, getY());
            }
            break;
        default:
            break;
    }
}

///////////////////////////////////////////////////////////
/////    (0) SQUIRTS OF WATER CLASS     ///////////////////
///////////////////////////////////////////////////////////

SQUIRTS::SQUIRTS(int x, int y, StudentWorld* m_world, Direction dir) : BASE(IID_WATER_SPURT, x, y, m_world, dir, 1, 1)
{
    distance = 4;
    setVisible(true);
}

void SQUIRTS::doSomething()
{
    if (!alive())
        return;
    
    while (distance > 0)
    {
        unsigned long count = world()->Actors().size();
        for (int i=0; i < count-1; i++)
        {
            BASE* temp = world()->Actor(i);
            if (temp->getID() == 1 || temp->getID() == 2)
            {
                setStatus(false);
            }
        }
        
        Direction dir = getDirection();
        int x = getX();
        int y = getY();
        switch (dir)
        {
            case up:
                if (BoulderCheck(x, y+1, up) && world()->Ice(x, y+1) == NULL)
                {
                    moveTo(x, y+1);
                    distance--;
                    return;
                }
                else
                {
                    setStatus(false);
                    return;
                }
                break;
            case down:
                if (BoulderCheck(x, y-1, down) && world()->Ice(x, y-1) == NULL)
                {
                    moveTo(x, y-1);
                    distance--;
                    return;
                }
                else
                {
                    setStatus(false);
                    return;
                }
                break;
            case left:
                if (BoulderCheck(x-1, y, left) && world()->Ice(x-1, y) == NULL)
                {
                    moveTo(x-1, y);
                    distance--;
                    return;
                }
                else
                {
                    setStatus(false);
                    return;
                }
                break;
            case right:
                if (BoulderCheck(x+1, y, right) && world()->Ice(x+1, y) == NULL)
                {
                    moveTo(x+1, y);
                    distance--;
                    return;
                }
                else
                {
                    setStatus(false);
                    return;
                }
                break;
            default:
                break;
        }
        
    }
    setStatus(false);
}

///////////////////////////////////////////////////////////
/////       (2) OBJECTS CLASS           ///////////////////
///////////////////////////////////////////////////////////

OBJECT::OBJECT(int ID, int x, int y, StudentWorld* m_world, Direction dir, int depth) : BASE(ID, x, y, m_world, dir, 1.0, depth) {}
                                                                                                          
///////////////////////////////////////////////////////////
////     (3) BARRELS OF OIL CLASS       ///////////////////
///////////////////////////////////////////////////////////

BARREL::BARREL(int x, int y, StudentWorld* m_world) : OBJECT(IID_BARREL, x, y, m_world, right, 2){setVisible(false);}

void BARREL::doSomething()
{
    if (!alive())
        return;
    
    int IceX = world()->Iceman()->getX();
    int IceY = world()->Iceman()->getY();
    int x = getX();
    int y = getY();
    double distance = sqrt((IceX-x)*(IceX-x) + (IceY-y)*(IceY-y));
    
    if (distance <= 4.00 && !isVisible())
    {
        setVisible(true);
        return;
    }
    
    if (distance <= 3.00)
    {
        setStatus(false);
        world()->playSound(SOUND_FOUND_OIL);
        world()->increaseScore(1000);
        world()->setBarrels(world()->numBarrels()-1);
    }
}

///////////////////////////////////////////////////////////
/////     (3) BOULDERS CLASS            ///////////////////
///////////////////////////////////////////////////////////

BOULDER::BOULDER(int x, int y, StudentWorld* m_world) : OBJECT(IID_BOULDER, x, y, m_world, down, 1)
{
    state = 0;
    timeStamp = 0;
    setVisible(true);
}

void BOULDER::doSomething()
{
    if (!alive())
        return;
    
    if (state==0)
    {
        bool fall = true;
        
        int x = getX();
        int y = getY();
        
        for (int i = x; i < (x+4); i++)
        {
            if (world()->Ice(i, y-1) != NULL)
                fall = false;
        }
        
        if (fall)
        {
            state = 1;
            timeStamp = world()->CurrentTicks();
            return;
        }
    }
    
    else if (state == 1)
    {
        if (world()->CurrentTicks() == (timeStamp+30))
        {
            state = 2;
            world()->playSound(SOUND_FALLING_ROCK);
        }
        else return;
    }
    
    else if (state == 2)
    {
        int y = getY()-1;
        moveTo(getX(), y);
        
        if (y==-1)
        {
            setStatus(false);
            return;
        }
        
        for (int i = 0; i < world()->Actors().size(); i++)
        {
            BASE* test = world()->Actor(i);
            if (test == this)
                continue;
            if (test->getID() == IID_BOULDER)
            {
                if (test->getX() >= getX() && test->getX() < (getX()+4) &&
                    getY() < (test->getY()+4))
                    {
                        setStatus(false);
                        return;
                    }
            }
            else if (test->getID() >= 1 && test->getID() <= 2)
            {
                double distance = sqrt((getX()-test->getX())*(getX()-test->getX()) +
                                   (getY()-test->getY())*(getY()-test->getY()));
                if (distance <= 3)
                {
                    test->setHealth(getHealth()-100);
                }
            }
        }
        
        BASE* test = world()->Iceman();
        double distance = sqrt((getX()-test->getX())*(getX()-test->getX()) +
                               (getY()-test->getY())*(getY()-test->getY()));
        if (distance <= 3)
        {
            test->setHealth(getHealth()-10);
            setStatus(false);
            return;
        }
        
    
        for (int x = getX(); x < (getX()+4); x++)
        {
            ICE* temp = world()->Ice(x,y);
            if (temp != NULL)
            {
                setStatus(false);
                return;
            }
        }
    }
}

///////////////////////////////////////////////////////////
///       (2) COLLECTABLES CLASS        ///////////////////
///////////////////////////////////////////////////////////
COLLECTABLE::COLLECTABLE(int ID, int x, int y, StudentWorld* m_world) : BASE(ID, x, y, m_world, right, 1.0, 2) {}

///////////////////////////////////////////////////////////
/////     (3) GOLD NUGGETS CLASS        ///////////////////
///////////////////////////////////////////////////////////

NUGGET::NUGGET(int x, int y, StudentWorld* m_world, bool IcemanDrop) : COLLECTABLE(IID_GOLD, x, y, m_world)
{
    if (IcemanDrop == true)
    {
        
        permanent = false;
        setVisible(true);
        setState(true);
    }
    else
    {
        permanent = true;
        setVisible(false);
    }
}

void NUGGET::doSomething()
{
    if (!alive())
        return;
    
    int IX = world()->Iceman()->getX() + 2;
    int IY = world()->Iceman()->getY() + 2;
    int nX = getX() + 2;
    int nY = getY() + 2;
    double Iradius = sqrt((IX-nX)*(IX-nX)+(IY-nY)*(IY-nY));
    
    if (Iradius <= 3.00 && permanent==true)
    {
        setStatus(false);
        world()->playSound(SOUND_GOT_GOODIE);
        world()->increaseScore(10);
        world()->setNuggets(world()->numNuggets()+1);
        
    }
    else if (Iradius <= 4.00 && permanent==true)
    {
        setVisible(true);
        return;
    }
    
    if (getState()==true)
    {
        setTicks(world()->CurrentTicks());
        dropped();
        setState(false);
        permanent = false;
    }
    
    if (permanent == false && world()->CurrentTicks() > (getTicks()+100))
    {
        setStatus(false);
        return;
    }
}

///////////////////////////////////////////////////////////
/////     (3) SONAR KITS CLASS          ///////////////////
///////////////////////////////////////////////////////////

SONAR::SONAR(StudentWorld* m_World) : COLLECTABLE(IID_SONAR, 0, 60, m_World)
{
    setVisible(true);
    setTicks(world()->CurrentTicks());
}

void SONAR::doSomething()
{
    if (!alive())
        return;
    
    int IX = world()->Iceman()->getX() + 2;
    int IY = world()->Iceman()->getY() + 2;
    int sX = getX() + 2;
    int sY = getY() + 2;
    double Iradius = sqrt((IX-sX)*(IX-sX)+(IY-sY)*(IY-sY));
    
    if (Iradius <= 3.00)
    {
        setStatus(false);
        world()->playSound(SOUND_GOT_GOODIE);
        world()->setSonar(world()->numSonar()+1);
        world()->increaseScore(75);
    }
    
    int CLN = world()->getLevel();
    int T = max(100, 300-10*CLN);
    if (world()->CurrentTicks() > getTicks()+T)
    {
        setStatus(false);
        return;
    }
}


///////////////////////////////////////////////////////////
/////     (3) WATER REFILLS CLASS       ///////////////////
///////////////////////////////////////////////////////////


WATER::WATER(int x, int y, StudentWorld* m_world) : COLLECTABLE(IID_WATER_POOL, x, y, m_world)
{
    setVisible(true);
    setTicks(world()->CurrentTicks());
}

void WATER::doSomething()
{
    if (!alive())
        return;
    
    int CLN = world()->getLevel();
    int T = max(100, 300-(10*CLN));
    if (world()->CurrentTicks() > getTicks() + T)
    {
        setStatus(false);
        return;
    }
    
    int IX = world()->Iceman()->getX() + 2;
    int IY = world()->Iceman()->getY() + 2;
    int sX = getX() + 2;
    int sY = getY() + 2;
    double radius = sqrt((IX-sX)*(IX-sX)+(IY-sY)*(IY-sY));
    if (radius <= 3.00)
    {
        setStatus(false);
        world()->playSound(SOUND_GOT_GOODIE);
        world()->setSquirts(world()->numSquirts() + 5);
        world()->increaseScore(100);
    }
}


///////////////////////////////////////////////////////////
/////             ACCESSORY             ///////////////////
///////////////////////////////////////////////////////////

