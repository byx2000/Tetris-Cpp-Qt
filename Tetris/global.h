#ifndef GLOBAL_H
#define GLOBAL_H

#include "mainwidget.h"
#include "gamewindow.h"
#include "game/GameController.h"
#include "aboutwindow.h"

struct Global
{
    static MainWidget* mainWidget;
    static GameWindow* gameWindow;
    static GameController* game;
    static int countOfLine;
};

#endif // GLOBAL_H
