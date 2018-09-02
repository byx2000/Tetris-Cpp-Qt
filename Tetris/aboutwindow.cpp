#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    //固定窗口大小
    setFixedSize(width(), height());
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
