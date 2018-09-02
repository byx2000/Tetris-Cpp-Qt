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
	//��������
	enum {BLANK, OCCUPY};
	//���캯��
	GameMap(int spaceX, int spaceY);
	//���
	void clearMap();
	//��ȡָ�����귽������
	int getProperty(int x, int y);
	//����ָ�����귽������
	void setProperty(int x, int y, int pro);
};

#endif
