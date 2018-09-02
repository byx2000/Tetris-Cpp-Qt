#ifndef FLOATWINDOW_H
#define FLOATWINDOW_H

#include <QWidget>

namespace Ui {
class FloatWindow;
}

class FloatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FloatWindow(QWidget *parent = 0);
    ~FloatWindow();

private:
    Ui::FloatWindow *ui;
};

#endif // FLOATWINDOW_H
