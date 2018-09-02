#include "Block.h"
#include <iostream>
#include <QTime>

Block::Block(int type, GameMap* gameMap)
{
	assert(type >= SHAPE_L && type <= SHAPE_SQUARE);

	this->type = type;
	this->gameMap = gameMap;
	this->spaceX = gameMap->spaceX;
	this->spaceY = gameMap->spaceY;
	isReachBottom = false;

	points.resize(4);

	switch (type)
	{
	case SHAPE_L:
	{
		Point p[] = { { 2, 0 },{ 1, 0 },{ 1, 1 },{ 1, 2 } };
		points.assign(begin(p), end(p));
		break;
	}
	case SHAPE_RL:
	{
		Point p[] = { { 1, 0 },{ 2, 0 },{ 2, 1 },{ 2, 2 } };
		points.assign(begin(p), end(p));
		break;
	}
	case SHAPE_Z:
	{
		Point p[] = { { 2, 0 },{ 2, 1 },{ 1, 1 },{ 1, 2 } };
		points.assign(begin(p), end(p));
		break;
	}
	case SHAPE_RZ:
	{
		Point p[] = { { 1, 0 },{ 1, 1 },{ 2, 1 },{ 2, 2 } };
		points.assign(begin(p), end(p));
		break;
	}
	case SHAPE_T:
	{
		Point p[] = { { 0, 2 },{ 1, 2 },{ 2, 2 },{ 1, 1 } };
		points.assign(begin(p), end(p));
		break;
	}
	case SHAPE_LINE:
	{
		Point p[] = { { 1, 0 },{ 1, 1 },{ 1, 2 },{ 1, 3 } };
		points.assign(begin(p), end(p));
		break;
	}
	case SHAPE_SQUARE:
	{
		Point p[] = { { 1, 1 },{ 2, 1 },{ 1, 2 },{ 2, 2 } };
		points.assign(begin(p), end(p));
		break;
	}
	}

	//随机生成x坐标
    //qsrand(QTime::currentTime().msec());
	do
	{
        globalX = qrand() % (spaceX);
		globalY = 0;
    } while (isHorizontalOutOfRange());
	
}

void Block::rotate()
{
	if (type != SHAPE_SQUARE && !isReachBottom)
	{
		processRotate();

		//防止方块出墙
		vector<int> xs;
		for (size_t i = 0; i < points.size(); ++i)
		{
			xs.push_back(points[i].x + globalX);
		}
		int minX = *min_element(xs.begin(), xs.end());
		int maxX = *max_element(xs.begin(), xs.end());
		if (minX < 0)
		{
			globalX += (0 - minX);
		}
		else if (maxX > spaceX)
		{
			globalX -= (maxX - spaceX);
		}

		if (collision())
		{
			processRotate();
			processRotate();
			processRotate();
		}
	}
}

void Block::processRotate()
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		int t = points[i].x;
		points[i].x = 3 - points[i].y;
		points[i].y = t;
	}
}

/*bool Block::leftOut()
{
	vector<int> xs;
	for (size_t i = 0; i < points.size(); ++i)
	{
		xs.push_back(points[i].x + globalX);
	}
	return *min_element(xs.begin(), xs.end()) < 0;
}

bool Block::rightOut()
{
	vector<int> xs;
	for (size_t i = 0; i < points.size(); ++i)
	{
		xs.push_back(points[i].x + globalX);
	}
	return *max_element(xs.begin(), xs.end()) > spaceX;
}

bool Block::upOut()
{
	vector<int> ys;
	for (size_t i = 0; i < points.size(); ++i)
	{
		ys.push_back(points[i].y + globalY);
	}
	return *min_element(ys.begin(), ys.end()) < 0;
}*/

bool Block::collision()
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (gameMap->getProperty(points[i].x + globalX, points[i].y + globalY) == GameMap::OCCUPY)
			return true;
	}
	return false;
}

void Block::detectReachBottom()
{
	if (!isReachBottom)
	{
		for (size_t i = 0; i < points.size(); ++i)
		{
			if (gameMap->getProperty(points[i].x + globalX, points[i].y + globalY + 1) == GameMap::OCCUPY)
			{
				isReachBottom = true;
				updateGameMap();
                break;
			}
		}
	}
}

bool Block::reachWall()
{
	vector<int> xs, ys;

	for (size_t i = 0; i < points.size(); ++i)
	{
		xs.push_back(points[i].x + globalX);
		ys.push_back(points[i].y + globalY);
	}

	int minX = *min_element(xs.begin(), xs.end());
	int maxX = *max_element(xs.begin(), xs.end());
	int minY = *min_element(ys.begin(), ys.end());
	int maxY = *max_element(ys.begin(), ys.end());

	return !(minX >= 0 && maxX <= spaceX && minY >= 0 && maxY <= spaceY);
}

void Block::left()
{
    /*if (!isReachBottom)
	{
        globalX--;
		if (collision())
		{
			globalX++;
        }
		detectReachBottom();
    }*/
    /*if (!reachLeftBoundary() && !collision())
    {
        globalX--;
    }
    detectReachBottom();*/
    /*globalX--;
    if (collision())
    {
        globalX++;
    }
    detectReachBottom();*/
    if (!reachLeftBoundary())
        globalX--;
}

void Block::right()
{
    /*if (!isReachBottom)
	{
		globalX++;
		if (collision())
		{
			globalX--;
		}
		detectReachBottom();
    }*/
    /*globalX++;
    if (collision())
    {
        globalX--;
    }
    detectReachBottom();*/
    if (!reachRightBoundary())
        globalX++;
}

void Block::up()
{
    globalY--;
	while (collision())
	{
		globalY++;
	}
}

void Block::down()
{
    /*if (!isReachBottom)
	{
		globalY++;
        if (collision())
		{
			globalY--;
        }
		detectReachBottom();
    }*/
    detectReachBottom();
    if (!isReachBottom)
    {
        globalY++;
    }
    /*if (!reachBottom())
    {
        isReachBottom = false;
        globalY++;
    }
    else
        isReachBottom = true;*/
}

void Block::updateGameMap()
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		gameMap->setProperty(points[i].x + globalX, points[i].y + globalY, GameMap::OCCUPY);
	}
}

bool Block::isHorizontalOutOfRange()
{
    vector<int> xs;
    for (size_t i = 0; i < points.size(); ++i)
    {
        xs.push_back(points[i].x + globalX);
    }
    int minX = *min_element(xs.begin(), xs.end());
    int maxX = *max_element(xs.begin(), xs.end());
    return (minX < 0 || maxX > spaceX);
}

bool Block::isVerticalOutOfRange()
{
    vector<int> ys;
    for (size_t i = 0; i < points.size(); ++i)
    {
        ys.push_back(points[i].y + globalY);
    }
    int minY = *min_element(ys.begin(), ys.end());
    int maxY = *max_element(ys.begin(), ys.end());
    return (minY < 0 || maxY > spaceY);
}

bool Block::reachLeftBoundary()
{
    /*vector<int> xs;
    for (size_t i = 0; i < points.size(); ++i)
    {
        xs.push_back(points[i].x + globalX);
    }
    int minX = *min_element(xs.begin(), xs.end());
    return (minX == 0);*/
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (gameMap->getProperty(points[i].x + globalX - 1, points[i].y + globalY) == GameMap::OCCUPY)
            return true;
    }
    return false;
}

bool Block::reachRightBoundary()
{
    /*vector<int> xs;
    for (size_t i = 0; i < points.size(); ++i)
    {
        xs.push_back(points[i].x + globalX);
    }
    int maxX = *max_element(xs.begin(), xs.end());
    return (maxX == spaceX);*/
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (gameMap->getProperty(points[i].x + globalX + 1, points[i].y + globalY) == GameMap::OCCUPY)
            return true;
    }
    return false;
}

int Block::getMinX()
{
    vector<int> xs;
    for (size_t i = 0; i < points.size(); ++i)
    {
        xs.push_back(points[i].x + globalX);
    }
    return *min_element(xs.begin(), xs.end());
}

int Block::getMaxX()
{
    vector<int> xs;
    for (size_t i = 0; i < points.size(); ++i)
    {
        xs.push_back(points[i].x + globalX);
    }
    return *max_element(xs.begin(), xs.end());
}

int Block::getMinY()
{
    vector<int> ys;
    for (size_t i = 0; i < points.size(); ++i)
    {
        ys.push_back(points[i].y + globalY);
    }
    return *min_element(ys.begin(), ys.end());
}

int Block::getMaxY()
{
    vector<int> ys;
    for (size_t i = 0; i < points.size(); ++i)
    {
        ys.push_back(points[i].y + globalY);
    }
    return *max_element(ys.begin(), ys.end());
}

bool Block::reachBottom()
{
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (gameMap->getProperty(points[i].x + globalX, points[i].y + globalY + 1) == GameMap::OCCUPY)
            return true;
    }
    return false;
}

Point Block::getBottomLocation()
{
    int t = globalY;
    while (!reachBottom())
    {
        globalY++;
    }
    Point res = {globalX, globalY};
    globalY = t;
    return res;
}
