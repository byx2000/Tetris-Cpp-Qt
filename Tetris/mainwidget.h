#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_StartButton_clicked();

    void on_HelpButton_clicked();

    void on_AboutButton_clicked();

    void on_RecordButton_clicked();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
