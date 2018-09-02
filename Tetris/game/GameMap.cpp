#include "GameMap.h"

GameMap::GameMap(int spaceX, int spaceY)
{
	assert(spaceX > 4 && spaceY > 4);

	this->spaceX = spaceX;
	this->spaceY = spaceY;

	//����spaceY+1��spaceX+1�еĶ�ά����
	map.resize(spaceY + 1);
	for (int i = 0; i <= spaceY; ++i)
	{
		map[i].resize(spaceX + 1);
	}

	//�����з�������ΪBLANK
	clearMap();
}

void GameMap::clearMap()
{
	for (int i = 0; i <= spaceY; ++i)
	{
		for (int j = 0; j <= spaceX; ++j)
		{
			map[i][j] = BLANK;
		}
	}
}

int GameMap::getProperty(int x, int y)
{
	if (x < 0 || y < 0 || x > spaceX || y > spaceY)
		return OCCUPY;
	return map[y][x];
}

void GameMap::setProperty(int x, int y, int pro)
{
	//assert(x >= 0 && y >= 0 && x <= spaceX && y <= spaceY && pro >= BLANK && pro <= OCCUPY);
	assert(x >= 0);
	assert(y >= 0);
	assert(x <= spaceX);
	assert(y <= spaceY);
	assert(pro >= BLANK);
	assert(pro <= OCCUPY);
	map[y][x] = pro;
}
