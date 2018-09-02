#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <cassert>
#include <ctime>

using namespace std;

struct GameMap
{
	int spaceX, spaceY;
	vector<vector<int>> map;
	//方块属性
	enum {BLANK, OCCUPY};
	//构造函数
	GameMap(int spaceX, int spaceY);
	//清空
	void clearMap();
	//获取指定坐标方块属性
	int getProperty(int x, int y);
	//设置指定坐标方块属性
	void setProperty(int x, int y, int pro);
};

#endif
