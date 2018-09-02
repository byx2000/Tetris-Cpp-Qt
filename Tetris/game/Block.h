#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <cassert>
#include <algorithm>
#include "GameMap.h"

using namespace std;

struct Point
{
	int x;
	int y;
};

struct Block
{
	//方块类型
	int type;
	//全局坐标
	int globalX, globalY;
	//游戏空间尺寸
	int spaceX, spaceY;
	//标记是否触底
	bool isReachBottom;
	//四个方块的相对坐标
	vector<Point> points;
	//游戏地图
	GameMap* gameMap;
	//方块类型（七种）
    enum {SHAPE_L = 0, SHAPE_RL, SHAPE_Z, SHAPE_RZ, SHAPE_T, SHAPE_LINE, SHAPE_SQUARE};
	//构造函数 根据方块类型初始化方块坐标 设置全局坐标为(0, 0)
	Block(int type, GameMap* gameMap);
	//顺时针旋转方块90°
	void rotate();
	void processRotate();
	/*bool leftOut();
	bool rightOut();
	bool upOut();*/
	//判断是否碰撞
	bool collision();
    bool isHorizontalOutOfRange();
    bool isVerticalOutOfRange();
    bool reachLeftBoundary();
    bool reachRightBoundary();
    bool reachBottom();
    int getMinX();
    int getMaxX();
    int getMinY();
    int getMaxY();
    Point getBottomLocation();
	//判断是否触底
    void detectReachBottom();
	//判断是否超出地图范围
	bool reachWall();
	//向左移动 包含范围检测 下面同理
	void left();
	//向右移动
	void right();
	//向上移动
	void up();
	//向下移动
	void down();
	//更新游戏地图
	void updateGameMap();
};

#endif
