#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "gamewindow.h"
#include "global.h"
#include "aboutwindow.h"
#include "helpwindow.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //固定窗口大小
    this->setFixedSize( this->width (),this->height ());
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_StartButton_clicked()
{
    //弹出游戏进行窗口 开始游戏
    Global::game->start();
    Global::gameWindow->show();

    close();
}

void MainWidget::on_HelpButton_clicked()
{
    //弹出游戏帮助窗口
    HelpWindow* helpWindow = new HelpWindow(this);
    helpWindow->setWindowFlags(Qt::Dialog);
    helpWindow->setWindowModality(Qt::ApplicationModal);
    helpWindow->show();
}

void MainWidget::on_AboutButton_clicked()
{
    //弹出关于游戏窗口
    AboutWindow* aboutWindow = new AboutWindow(this);
    aboutWindow->setWindowFlags(Qt::Dialog);
    aboutWindow->setWindowModality(Qt::ApplicationModal);
    aboutWindow->show();
}

void MainWidget::on_RecordButton_clicked()
{
    //弹出游戏记录
    QMessageBox::information(this, tr("游戏记录"), tr("最多消除的行数:") + QString::number(Global::countOfLine), QMessageBox::Ok);
}
