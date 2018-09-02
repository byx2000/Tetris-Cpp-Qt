#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameMap.h"
#include "Block.h"
#include "GamePainter.h"
#include <ctime>

struct GamePainter;
struct GameController;

struct GameState
{
	GameController* game;

	virtual void start() = 0;
	virtual void pause() = 0;
	virtual void exit() = 0;
	virtual void rotate() = 0;
	virtual void down() = 0;
	virtual void left() = 0;
	virtual void right() = 0;
	virtual void step() = 0;
};

struct ExitState : public GameState
{
	ExitState(GameController* game);
	void start();
	void pause();
	void exit();
	void rotate();
	void down();
	void left();
	void right();
	void step();
};

struct RunningState : public GameState
{
	RunningState(GameController* game);
	void start();
	void pause();
	void exit();
	void rotate();
	void down();
	void left();
	void right();
	void step();
};

struct PausingState : public GameState
{
	PausingState(GameController* game);
	void start();
	void pause();
	void exit();
	void rotate();
	void down();
	void left();
	void right();
	void step();
};

struct GameController
{
	GameMap* gameMap;
	int spaceX, spaceY;
	Block* currentBlock;
	GamePainter* gamePainter;
	GameState* currentState;
	ExitState* exitState;
	RunningState* runningState;
	PausingState* pausingState;
    int countOfLine;
    int speed;

	//消息类型
    enum {MAIN, START, RUN, PAUSE, CONTINUE, EXIT, LOSE, LINECLEAR, SPEEDCHANGE, WAITTOCLOSE};

	//构造函数
	GameController(int row, int column, GamePainter* gamePainter);
	//析构函数
	~GameController();
	//设置游戏绘制器
	void setGamePainter(GamePainter* gamePainter);

    bool isExit();
    bool isRunning();
    bool isPausing();


	//随机生成一个方块
	void randomBlock();
	//清除填满的行
	void clearRows();
	//判断是否输
	bool isLose();
	//开始游戏
	void start();
	//暂停游戏
	void pause();
	//结束游戏
	void exit();
	//旋转
	void rotate();
	//向下加速
	void down();
	//左移
	void left();
	//右移
	void right();
	//前进游戏
	void step();
};

#endif
