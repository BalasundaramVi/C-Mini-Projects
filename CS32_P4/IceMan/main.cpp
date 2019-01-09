//
//  main.cpp
//  Project 4.1
//
//  Created by Vignesh Balasundaram on 8/8/17.
//  Copyright © 2017 Vignesh Balasundaram. All rights reserved.
//

#include "GameController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

  // If your program is having trouble finding the Assets directory,
  // replace the string literal with a full path name to the directory,
  // e.g., "Z:/CS32/IceMan/Assets" or "/Users/fred/cs32/IceMan/Assets"

const string assetDirectory = "/Users/VigneshB/Documents/UCLA/COURSES/Summer 2017/CS32/Project 4/DerivedData/IceMan/Build/Products/Debug/Assets";

class GameWorld;

GameWorld* createStudentWorld(string assetDir = "");

int main(int argc, char* argv[])
{
	{
		string path = assetDirectory;
		if (!path.empty())
			path += '/';
		const string someAsset = "dig1.tga";
		ifstream ifs(path + someAsset);
		if (!ifs)
		{
			cout << "Cannot find " << someAsset << " in ";
			cout << (assetDirectory.empty() ? "current directory"
											: assetDirectory) << endl;
			return 1;
		}
	}

	srand(static_cast<unsigned int>(time(nullptr)));
    cout << "1" << endl;

	GameWorld* gw = createStudentWorld(assetDirectory);
	Game().run(argc, argv, gw, "IceMan");
    cout << "2" << endl;
}
