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

	//��Ϣ����
    enum {MAIN, START, RUN, PAUSE, CONTINUE, EXIT, LOSE, LINECLEAR, SPEEDCHANGE, WAITTOCLOSE};

	//���캯��
	GameController(int row, int column, GamePainter* gamePainter);
	//��������
	~GameController();
	//������Ϸ������
	void setGamePainter(GamePainter* gamePainter);

    bool isExit();
    bool isRunning();
    bool isPausing();


	//�������һ������
	void randomBlock();
	//�����������
	void clearRows();
	//�ж��Ƿ���
	bool isLose();
	//��ʼ��Ϸ
	void start();
	//��ͣ��Ϸ
	void pause();
	//������Ϸ
	void exit();
	//��ת
	void rotate();
	//���¼���
	void down();
	//����
	void left();
	//����
	void right();
	//ǰ����Ϸ
	void step();
};

#endif
