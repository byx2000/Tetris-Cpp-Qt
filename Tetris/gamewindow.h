#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "game/GamePainter.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget, public GamePainter
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void updateFrame(int msg);

private:
    Ui::GameWindow *ui;
    int timerId;
    int cnt;
    int unit;
    bool isEscPressed;
    bool isWaittingForClose;
    vector<QColor> blockColor;
    void showEvent(QShowEvent* event);
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);
    void focusOutEvent(QFocusEvent* event);
    //void resizeEvent(QResizeEvent* event);
    void launchTimer();
    void storeGameRecord();
    void updateTitle();
};

#endif // GAMEWINDOW_H
