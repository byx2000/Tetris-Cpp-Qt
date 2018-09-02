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
	//��������
	int type;
	//ȫ������
	int globalX, globalY;
	//��Ϸ�ռ�ߴ�
	int spaceX, spaceY;
	//����Ƿ񴥵�
	bool isReachBottom;
	//�ĸ�������������
	vector<Point> points;
	//��Ϸ��ͼ
	GameMap* gameMap;
	//�������ͣ����֣�
    enum {SHAPE_L = 0, SHAPE_RL, SHAPE_Z, SHAPE_RZ, SHAPE_T, SHAPE_LINE, SHAPE_SQUARE};
	//���캯�� ���ݷ������ͳ�ʼ���������� ����ȫ������Ϊ(0, 0)
	Block(int type, GameMap* gameMap);
	//˳ʱ����ת����90��
	void rotate();
	void processRotate();
	/*bool leftOut();
	bool rightOut();
	bool upOut();*/
	//�ж��Ƿ���ײ
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
	//�ж��Ƿ񴥵�
    void detectReachBottom();
	//�ж��Ƿ񳬳���ͼ��Χ
	bool reachWall();
	//�����ƶ� ������Χ��� ����ͬ��
	void left();
	//�����ƶ�
	void right();
	//�����ƶ�
	void up();
	//�����ƶ�
	void down();
	//������Ϸ��ͼ
	void updateGameMap();
};

#endif
