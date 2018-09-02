#include "mainwidget.h"
#include "global.h"
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //初始化随机数种子
    qsrand(QTime::currentTime().msec());

    //加载记录文件
    QFileInfo inf("record.dat");
    if (inf.exists()) //文件存在
    {
        //读取文件
        QFile gameRecord("record.dat");
        gameRecord.open(QIODevice::ReadWrite);
        QTextStream in(&gameRecord);
        if (!in.atEnd()) //读取成功
        {
            //存储消除行数记录
            QString line = in.readLine();
            Global::countOfLine = line.toInt();
        }
        else //读取失败
        {
            //消除行数为0
            gameRecord.write("0");
            Global::countOfLine = 0;
        }
        //关闭文件
        gameRecord.close();
    }
    else //文件不存在
    {
        //创建新文件
        QFile gameRecord("record.dat");
        gameRecord.open(QIODevice::ReadWrite);
        //写入初始数据（消除行数为0）
        gameRecord.write("0");
        Global::countOfLine = 0;
        //关闭文件
        gameRecord.close();
    }

    //加载所有窗口
    Global::mainWidget = new MainWidget;
    Global::gameWindow = new GameWindow;

    //加载游戏数据
    Global::game = new GameController(30, 20, Global::gameWindow);

    //显示主界面
    Global::mainWidget->show();

    return a.exec();
}
