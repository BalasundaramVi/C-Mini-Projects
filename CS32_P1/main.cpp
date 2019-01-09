//
//  main.cpp
//  Project 1
//
//  Created by Vignesh Balasundaram on 7/6/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Game.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(3, 3, 1);
    
    // Play the game
    g.play();
}
