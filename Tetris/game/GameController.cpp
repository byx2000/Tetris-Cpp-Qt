#include "GameController.h"
#include <QDebug>
#include <QTime>

GameController::GameController(int row, int column, GamePainter* gamePainter)
{
	//初始化游戏地图
	gameMap = new GameMap(column - 1, row - 1);
	spaceX = gameMap->spaceX;
	spaceY = gameMap->spaceY;
	//初始化所有状态
	exitState = new ExitState(this);
	runningState = new RunningState(this);
	pausingState = new PausingState(this);
	//设置当前状态
	currentState = exitState;
	currentBlock = NULL;
    countOfLine = 0;
    speed = 500;
	//设置游戏绘制器
	setGamePainter(gamePainter);
	//发送绘制消息
	gamePainter->updateFrame(MAIN);
}

GameController::~GameController()
{
	if (gameMap != NULL)
	{
		delete gameMap;
		gameMap = NULL;
	}

	if (currentBlock != NULL)
	{
		delete currentBlock;
		currentBlock = NULL;
	}

	if (currentState != NULL)
	{
		delete currentState;
		currentState = NULL;
	}

	/*if (gamePainter != NULL)
	{
		delete gamePainter;
		gamePainter = NULL;
	}*/
}

void GameController::setGamePainter(GamePainter * gamePainter)
{
	this->gamePainter = gamePainter;
	/*this->game = game;
	gameMap = game->gameMap;
	spaceX = game->spaceX;
	spaceY = game->spaceY;*/
	//初始化GamePainter
	gamePainter->game = this;
	gamePainter->gameMap = gameMap;
	gamePainter->spaceX = spaceX;
	gamePainter->spaceY = spaceY;
}

void GameController::randomBlock()
{
	if (currentBlock != NULL)
		delete currentBlock;
	//随机生成方块类型
    //qsrand(QTime::currentTime().msec());
    currentBlock = new Block(qrand() % 7, gameMap);
    //srand((unsigned int)time(NULL));
    //currentBlock = new Block(rand() % 7, gameMap);
	//随机旋转方块
    //qsrand(QTime::currentTime().msec());
    int cnt = qrand() % 4;
	for (int i = 0; i < cnt; ++i)
	{
		currentBlock->rotate();
	}
	//currentBlock = new Block(Block::SHAPE_SQUARE, gameMap);

}

void GameController::clearRows()
{
    //qDebug() << "clean";
    bool needToAccelerate = false;
    for (int i = spaceY; i >= 1; --i)
	{
        bool flag = true;
		for (int j = 0; j <= spaceX; ++j)
		{
			if (gameMap->map[i][j] == GameMap::BLANK)
            {
                flag = false;
                break;
            }
		}
		if (flag)
		{
            needToAccelerate = true;
            countOfLine++;
			gameMap->map.erase(gameMap->map.begin() + i);
			vector<int> newRow(spaceX + 1, GameMap::BLANK);
			gameMap->map.insert(gameMap->map.begin(), newRow);
			i++;
		}
	}
    gamePainter->updateFrame(GameController::LINECLEAR);
    if (needToAccelerate)
    {
        speed  = max(speed - 10, 150);
        gamePainter->updateFrame(GameController::SPEEDCHANGE);
    }
}

bool GameController::isLose()
{
	for (int i = 0; i <= spaceX; ++i)
	{
		if (gameMap->map[0][i] == GameMap::OCCUPY)
			return true;
	}
	return false;
}

void GameController::start()
{
	currentState->start();
}

void GameController::pause()
{
	currentState->pause();
}

void GameController::exit()
{
	currentState->exit();
}

void GameController::rotate()
{
	currentState->rotate();
}

void GameController::down()
{
	currentState->down();
}

void GameController::left()
{
	currentState->left();
}

void GameController::right()
{
	currentState->right();
}

void GameController::step()
{
	currentState->step();
}

bool GameController::isPausing()
{
    return currentState == pausingState;
}

bool GameController::isExit()
{
    return currentState == exitState;
}

bool GameController::isRunning()
{
    return currentState == runningState;
}

/*ExitState*/
ExitState::ExitState(GameController * game)
{
	this->game = game;
}
void ExitState::start()
{
    game->countOfLine = 0;
    game->speed = 500;
    game->gamePainter->updateFrame(GameController::START);
	//清空地图
	game->gameMap->clearMap();
	//随机生成方块
	game->randomBlock();
	game->currentState = game->runningState;
    game->gamePainter->updateFrame(GameController::RUN);
    //qDebug() << "game init completed";
}
void ExitState::pause(){}
void ExitState::exit(){}
void ExitState::rotate(){}
void ExitState::down(){}
void ExitState::left(){}
void ExitState::right(){}
void ExitState::step(){}

/*RunningState*/
RunningState::RunningState(GameController * game)
{
	this->game = game;
}
void RunningState::start(){}
void RunningState::pause()
{
	game->currentState = game->pausingState;
	game->gamePainter->updateFrame(GameController::PAUSE);
}
void RunningState::exit()
{
	game->currentState = game->exitState;
	game->gamePainter->updateFrame(GameController::EXIT);
	game->gamePainter->updateFrame(GameController::MAIN);
}
void RunningState::rotate()
{
	game->currentBlock->rotate();
	game->gamePainter->updateFrame(GameController::RUN);
}
void RunningState::down()
{
	game->currentBlock->down();
	if (game->currentBlock->isReachBottom)
	{
		if (game->isLose())
		{
            game->currentState = game->exitState;
			game->gamePainter->updateFrame(GameController::LOSE);
            game->gamePainter->updateFrame(GameController::EXIT);
			return;
		}
		game->randomBlock();
		game->clearRows();
	}
	game->gamePainter->updateFrame(GameController::RUN);
}
void RunningState::left()
{
	game->currentBlock->left();
    /*if (game->currentBlock->isReachBottom)
	{
        if (game->isLose())
		{
			game->gamePainter->updateFrame(GameController::LOSE);
			game->currentState = game->exitState;
            game->gamePainter->updateFrame(GameController::EXIT);
			return;
        }
		game->randomBlock();
		game->clearRows();
    }*/
	game->gamePainter->updateFrame(GameController::RUN);
}
void RunningState::right()
{
	game->currentBlock->right();
    /*if (game->currentBlock->isReachBottom)
	{
        if (game->isLose())
		{
			game->gamePainter->updateFrame(GameController::LOSE);
			game->currentState = game->exitState;
            game->gamePainter->updateFrame(GameController::EXIT);
			return;
        }
		game->randomBlock();
		game->clearRows();
    }*/
	game->gamePainter->updateFrame(GameController::RUN);
}
void RunningState::step()
{
	down();
}

/*PausingState*/
PausingState::PausingState(GameController * game)
{
	this->game = game;
}
void PausingState::start()
{
	game->currentState = game->runningState;
	game->gamePainter->updateFrame(GameController::CONTINUE);
	game->gamePainter->updateFrame(GameController::RUN);
}
void PausingState::pause(){}
void PausingState::exit()
{
	game->currentState = game->exitState;
	game->gamePainter->updateFrame(GameController::EXIT);
	game->gamePainter->updateFrame(GameController::MAIN);
}
void PausingState::rotate(){}
void PausingState::down(){}
void PausingState::left(){}
void PausingState::right(){}
void PausingState::step(){}
