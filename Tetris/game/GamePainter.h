#ifndef GAMEPAINTER_H
#define GAMEPAINTER_H

#include "GameMap.h"
#include "GameController.h"
#include <iostream>
#include <Windows.h>

using namespace std;

struct GameController;

struct GamePainter
{
	GameMap* gameMap;
	GameController* game;
	int spaceX, spaceY;

    //GamePainter();
	virtual void updateFrame(int msg) = 0;
};

#endif
