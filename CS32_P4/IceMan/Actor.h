//
//  Actor.h
//  Project 4.1
//
//  Created by Vignesh Balasundaram on 8/8/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <vector>

class StudentWorld;
class GameWorld;
struct BCHECK;

///////////////////////////////////////////////////////////
/////      (1) BASE CLASS               ///////////////////
///////////////////////////////////////////////////////////
class BASE : public GraphObject
{
public:
    //Constructor + Destructor
    BASE(int ID, int x, int y, StudentWorld* s_world, Direction dir, double size, int depth);
    virtual ~BASE();
    
    virtual void doSomething() = 0;
    
    //ACCESSORS
    StudentWorld* world() {return m_world;}
    int getID() {return ID;}
    virtual int getHealth() {return 0;}
    bool alive() {return state;}
    
    //MUTATORS
    virtual void setHealth(int hp) {return;}
    void setStatus(bool check) {state = check;}
    
    //BOULDER CHECKS
    bool BoulderCheck(int x, int y, Direction dir);
    std::vector<BCHECK*> BC;
    
private:
    StudentWorld* m_world;
    int ID;
    bool state;
    
};

///////////////////////////////////////////////////////////
/////      (2) ICE CLASS                ///////////////////
///////////////////////////////////////////////////////////
class ICE : public BASE
{
public:
    ICE(int x, int y, StudentWorld* m_world);
    virtual ~ICE();
    
    void doSomething();
};

///////////////////////////////////////////////////////////
/////       (2) ACTOR CLASS             ///////////////////
///////////////////////////////////////////////////////////

class ACTOR : public BASE
{
public:
    ACTOR(int ID, int x, int y, StudentWorld* m_world, Direction dir, double size, int depth, int hp);
    virtual ~ACTOR();
    
    virtual void doSomething() = 0;
    virtual void setHealth(int hp);
    
    virtual int getHealth() {return m_health;}
    
private:
    int m_health;
};

///////////////////////////////////////////////////////////
/////        (3) ICEMAN CLASS           ///////////////////
///////////////////////////////////////////////////////////
class ICEMAN : public ACTOR
{
public:
    ICEMAN(StudentWorld* s_world);
    virtual ~ICEMAN();
    
    void doSomething();
    int getMove() {return move;}
    int getSquirt() {return dsquirt;}
    int getEvent() {return EVENT;}
    
    //MUTATORS
    void setMove(int M) {move = M;}
    void setSquirt(int S) {dsquirt = S;}
    void setEVENT(int E) {EVENT = E;}
    
private:
    int move;
    int dsquirt;
    int EVENT;
    
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

///////////////////////////////////////////////////////////
/////   (3) REGULAR PROTESTOR CLASS     ///////////////////
///////////////////////////////////////////////////////////

class PROTESTER : public ACTOR
{
public:
    PROTESTER(int ID, int x, int y, StudentWorld* m_world, int hp);
    virtual ~PROTESTER() {};
    
    void setWalk(int W) {walk =W;}
    int getWalk() {return walk;}
    
    virtual void doSomething();
private:
    int walk;
};

///////////////////////////////////////////////////////////
/////   (3) HARDCORE PROTESTOR CLASS    ///////////////////
///////////////////////////////////////////////////////////

class HPROTESTER : public PROTESTER
{
public:
    HPROTESTER(int x, int y, StudentWorld* m_world);
    virtual ~HPROTESTER() {};
    
    virtual void doSomething();
};

///////////////////////////////////////////////////////////
/////   (2) SQUIRTS OF WATER CLASS      ///////////////////
///////////////////////////////////////////////////////////
class SQUIRTS : public BASE
{
public:
    SQUIRTS(int x, int y, StudentWorld* m_world, Direction dir);
    virtual ~SQUIRTS() {};
    
    virtual void doSomething();
    
    //ACCESSORS
    int getDistance() {return distance;}
    
    //MUTATORS
    void setDistance(int D) {distance = D;}
    
private:
    int distance;
    
};

///////////////////////////////////////////////////////////
/////       (2) OBJECTS CLASS           ///////////////////
///////////////////////////////////////////////////////////
class OBJECT : public BASE
{
public:
    OBJECT(int ID, int x,  int y, StudentWorld* m_world, Direction dir, int depth);
    virtual ~OBJECT() {}
    
    virtual void doSomething() = 0;
    
};
///////////////////////////////////////////////////////////
////     (3) BARRELS OF OIL CLASS       ///////////////////
///////////////////////////////////////////////////////////
class BARREL : public OBJECT
{
public:
    BARREL(int x,  int y, StudentWorld* m_world);
    virtual ~BARREL() {}
    
    virtual void doSomething();
    
};

///////////////////////////////////////////////////////////
/////     (3) BOULDERS CLASS            ///////////////////
///////////////////////////////////////////////////////////
class BOULDER : public OBJECT
{
public:
    BOULDER(int x,  int y, StudentWorld* m_world);
    virtual ~BOULDER() {}
    
    virtual void doSomething();
    
private:
    int state;
    //state = 0 = stable
    //state = 1 = waiting
    //state = 2 = falling
    double timeStamp;
    
};


///////////////////////////////////////////////////////////
///       (2) COLLECTABLES CLASS        ///////////////////
///////////////////////////////////////////////////////////

class COLLECTABLE : public BASE
{
public:
    COLLECTABLE(int ID, int x, int y, StudentWorld* m_world);
    virtual ~COLLECTABLE() {};
    
    virtual void doSomething() = 0;
    
    void setTicks(double CT) {CurrentTicks = CT;}
    double getTicks() {return CurrentTicks;}
    
private:
    double CurrentTicks;
};

///////////////////////////////////////////////////////////
/////     (3) GOLD NUGGETS CLASS        ///////////////////
///////////////////////////////////////////////////////////

class NUGGET : public COLLECTABLE
{
public:
    NUGGET(int x, int y, StudentWorld* m_world, bool IcemanDrop);
    virtual ~NUGGET() {};
    
    virtual void doSomething();
    
    void setState(bool S) {state = S;}
    bool getState() {return state;}
    void dropped() {state=false;}
    
private:
    bool permanent;
    bool state;

    
};

///////////////////////////////////////////////////////////
/////     (3) SONAR KITS CLASS          ///////////////////
///////////////////////////////////////////////////////////

class SONAR : public COLLECTABLE
{
public:
    SONAR(StudentWorld* m_World);
    virtual ~SONAR() {};
    
    virtual void doSomething();
};

///////////////////////////////////////////////////////////
/////     (3) WATER REFILLS CLASS       ///////////////////
///////////////////////////////////////////////////////////

class WATER : public COLLECTABLE
{
public:
    WATER(int x, int y, StudentWorld* m_world);
    virtual ~WATER() {};
    
    virtual void doSomething();
};

///////////////////////////////////////////////////////////
/////             ACCESSORY             ///////////////////
///////////////////////////////////////////////////////////

struct BCHECK
{
public:
    BCHECK(int a, int b) {x=a; y=b;}
    ~BCHECK();
    int x;
    int y;
};

#endif // ACTOR_H_
