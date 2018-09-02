#include "floatwindow.h"
#include "ui_floatwindow.h"

FloatWindow::FloatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatWindow)
{
    ui->setupUi(this);
}

FloatWindow::~FloatWindow()
{
    delete ui;
}
