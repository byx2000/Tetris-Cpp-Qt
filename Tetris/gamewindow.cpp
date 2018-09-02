#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "game/GamePainter.h"
#include "global.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDesktopWidget>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    cnt = 0;
    isWaittingForClose = false;

    //初始化方块颜色
    QColor a[] = {QColor(239, 83, 80), QColor(239, 83, 80), QColor(239, 108, 0), QColor(239, 108, 0), QColor(77, 182, 172), QColor(118, 204, 222), QColor(253, 216, 53)};
    blockColor.assign(begin(a), end(a));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::showEvent(QShowEvent *event)
{
    //计算单位方格大小
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    unit = screenHeight*3 / 4 / spaceY;
    //根据显示屏尺寸调节游戏窗口大小
    this->setFixedSize((spaceX + 3) * unit, (spaceY + 3) * unit);
    //将窗口移动到屏幕中央
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    //设置标签大小
    ui->FloatWindow->setFixedSize(this->width(), this->height());
    //移动标签
    ui->FloatWindow->move(0, 0);
    //隐藏标签
    if (!isEscPressed)
    ui->FloatWindow->hide();
    //更新标题
    //setWindowTitle(tr("游戏进行中 消除行数:") + QString::number(game->countOfLine));
    updateTitle();
    setFocus();
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    //qDebug() << "paint event";
    QPainter painter(this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    //绘制边框和方块
    brush.setColor(QColor(161, 136, 127));
    painter.setBrush(brush);
    for (int i = 0; i <= spaceX + 2; ++i)
    {
        painter.drawRect((i) * unit, 0, unit, unit);
        painter.drawRect((i) * unit, (spaceY + 2) * unit, unit, unit);
    }
    for (int i = 1; i <= spaceY + 1; ++i)
    {
        painter.drawRect(0, i * unit, unit, unit);
        painter.drawRect((spaceX + 2) * unit, i * unit, unit, unit);
    }
    brush.setColor(QColor(120, 144, 156));
    painter.setBrush(brush);
    for (int i = 0; i <= spaceX; ++i)
    {
        for (int j = 0; j <= spaceY; ++j)
        {
            if (gameMap->getProperty(i, j) == GameMap::OCCUPY)
            {

                painter.drawRect((i + 1) * unit, (j + 1) * unit, unit, unit);
            }
        }
    }

    //绘制当前形状
    for (size_t i = 0; i < game->currentBlock->points.size(); ++i)
    {
        brush.setColor(blockColor[game->currentBlock->type]);
        painter.setBrush(brush);
        painter.drawRect((game->currentBlock->points[i].x + game->currentBlock->globalX + 1) * unit, (game->currentBlock->points[i].y + game->currentBlock->globalY + 1) * unit, unit, unit);
    }

    //计算并绘制方块预览图
    /*GameMap tm(gameMap->spaceX, gameMap->spaceY);
    tm.map = gameMap->map;
    Block temp(game->currentBlock->type, &tm);
    temp.points = game->currentBlock->points;
    temp.globalX = game->currentBlock->globalX;
    temp.globalY = game->currentBlock->globalY;
    while (!temp.isReachBottom)
    {
        temp.down();
    }
    QColor color(blockColor[temp.type].red(), blockColor[temp.type].green(), blockColor[temp.type].blue(), 50);
    brush.setColor(color);
    painter.setBrush(brush);
    for (size_t i = 0; i < temp.points.size(); ++i)
    {
        painter.drawRect((temp.points[i].x + temp.globalX + 1) * unit, (temp.points[i].y + temp.globalY + 1) * unit, unit, unit);
    }*/
    Point p = game->currentBlock->getBottomLocation();
    for (size_t i = 0; i < game->currentBlock->points.size(); ++i)
    {
        QColor color(blockColor[game->currentBlock->type].red(), blockColor[game->currentBlock->type].green(), blockColor[game->currentBlock->type].blue(), 50);
        brush.setColor(color);
        painter.setBrush(brush);
        painter.drawRect((game->currentBlock->points[i].x + p.x + 1) * unit, (game->currentBlock->points[i].y + p.y + 1) * unit, unit, unit);
    }
}

void GameWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        //qDebug() << "timer event: " << cnt++;
        //qDebug() << QString::number(game->speed);
        game->step();
        //update();
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        if (isEscPressed)
        {
            game->start();
        }
        else
        {
            game->pause();
        }
        isEscPressed = !isEscPressed;
        break;
    case Qt::Key_Up:
        if (!game->isPausing())
        {
            game->rotate();
        }
        break;
    case Qt::Key_Down:
    {
        //game->down();
        if (!game->isPausing())
        {
            Point p = game->currentBlock->getBottomLocation();
            game->currentBlock->globalY = p.y;
            game->currentBlock->updateGameMap();
        }
        break;
    }
    case Qt::Key_Left:
        if (!game->isPausing())
        game->left();
        break;
    case Qt::Key_Right:
        if (!game->isPausing())
        game->right();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void GameWindow::closeEvent(QCloseEvent *event)
{
    isWaittingForClose = true;
    //qDebug() << "close";
    if (game->isExit())
    {
        event->accept();
        return;
    }
    game->pause();

    /*if (game->isRunning())
    {
        //销毁计时器
        killTimer(timerId);
    }*/

    int select = QMessageBox::question(this, tr("退出游戏"), tr("您确定要退出游戏吗？"), QMessageBox::Yes | QMessageBox::No);
    if (select == QMessageBox::Yes)
    {
        //ui->FloatWindow->hide();
        //退出游戏 返回主界面
        if (game->countOfLine > Global::countOfLine) //破纪录
        {
            QMessageBox::information(this, tr("游戏结束"), tr("恭喜您创造了新纪录！\n") + tr("您本次消除行数:") + QString::number(game->countOfLine) + tr("\n旧记录:") + QString::number(Global::countOfLine), QMessageBox::Ok);
            //存储新纪录
            storeGameRecord();
            Global::countOfLine = game->countOfLine;
        }
        else //未破纪录
        {
            QMessageBox::information(this, tr("游戏结束"), tr("您本次消除行数:") + QString::number(game->countOfLine), QMessageBox::Ok);
        }
        launchTimer();
        game->exit();
        Global::mainWidget->show();
        isWaittingForClose = false;
        close();
    }
    else
    {
        isWaittingForClose = false;
        event->ignore();
        //if (game->currentState != game->pausingState)
            game->start();
        if (game->isRunning())
        {
            launchTimer();
        }
    }
}

void GameWindow::updateFrame(int msg)
{
    switch (msg)
    {
    case GameController::START:
        //启动计时器
        //qDebug() << "start timer";
        launchTimer();
        isEscPressed = false;
        break;
    case GameController::EXIT:
        //销毁计时器
        killTimer(timerId);
        //返回主界面
        Global::mainWidget->show();
        close();
        break;
    case GameController::RUN:
        //重绘窗口
        update();
        break;
    case GameController::LOSE:
        //弹出游戏结束提示框
        if (game->countOfLine > Global::countOfLine) //破纪录
        {
            QMessageBox::information(this, tr("游戏结束"), tr("您输了！\n") + tr("恭喜您创造了新纪录！\n") + tr("您本次消除行数:") + QString::number(game->countOfLine) + tr("\n旧记录:") + QString::number(Global::countOfLine), QMessageBox::Ok);
            //存储新纪录
            /*QFile gameRecord("record.dat");
            gameRecord.open(QIODevice::ReadWrite);
            gameRecord.write(to_string(game->countOfLine).c_str());
            gameRecord.close();*/
            storeGameRecord();
            Global::countOfLine = game->countOfLine;
        }
        else //未破纪录
        {
            QMessageBox::information(this, tr("游戏结束"), tr("您输了！\n") + tr("您本次消除行数:") + QString::number(game->countOfLine), QMessageBox::Ok);
        }
        break;
    case GameController::PAUSE:
        //qDebug() << "pause";
        //销毁计时器
        killTimer(timerId);
        //显示标签
        if (!isWaittingForClose)
            ui->FloatWindow->show();
        break;
    case GameController::CONTINUE:
        //启动计时器
        //timerId = startTimer(200);
        launchTimer();
        //隐藏标签
        ui->FloatWindow->hide();
        break;
    case GameController::LINECLEAR:
        //setWindowTitle(tr("游戏进行中 消除行数:") + QString::number(game->countOfLine) + tr("按ESC暂停//继续游戏"));
        updateTitle();
        break;
    case GameController::SPEEDCHANGE:
        //销毁计时器
        killTimer(timerId);
        //启动计时器
        launchTimer();
        break;
    default:
        break;
    }
}

void GameWindow::launchTimer()
{
    timerId = startTimer(game->speed);
}

void GameWindow::storeGameRecord()
{
    //存储新纪录
    QFile gameRecord("record.dat");
    gameRecord.open(QIODevice::ReadWrite);
    gameRecord.write(to_string(game->countOfLine).c_str());
    gameRecord.close();
}

void GameWindow::focusOutEvent(QFocusEvent *event)
{
    //qDebug() << "out";
    if (!isWaittingForClose)
    {
        ui->FloatWindow->show();
        //暂停游戏
        if (game->isRunning())
        {
            isEscPressed = true;
            game->pause();
            //显示标签
            ui->FloatWindow->show();
        }
    }

}

void GameWindow::updateTitle()
{
    setWindowTitle(tr("游戏进行中 消除行数:") + QString::number(game->countOfLine) + tr("       按ESC暂停/继续游戏"));
}
